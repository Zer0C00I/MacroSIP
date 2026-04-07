#include "headset/HeadsetManager.h"

#ifdef HEADSET_ENABLED
#include <hidapi/hidapi.h>
#endif

#include <QDebug>
#include <cstring>

namespace macrosip {

#ifdef HEADSET_ENABLED

// Poll interval in milliseconds (matches original Windows TimerProc cadence)
static constexpr int kPollIntervalMs = 200;

// Maximum HID report size we expect from telephony headsets
static constexpr int kMaxReportSize = 64;

HeadsetManager::HeadsetManager(QObject *parent)
    : QObject(parent)
{
    connect(&m_pollTimer, &QTimer::timeout, this, &HeadsetManager::pollDevice);
}

HeadsetManager::~HeadsetManager()
{
    closeDevice();
}

// ---------------------------------------------------------------------------
// Device open / close
// ---------------------------------------------------------------------------

bool HeadsetManager::openDevice()
{
    if (m_device != nullptr) {
        qDebug() << "HeadsetManager: device already open";
        return true;
    }

    // Enumerate all HID devices looking for Telephony usage page (0x0B).
    // Prefer usage 0x05 (Headset) or 0x04 (Handset); fall back to any 0x0B.
    struct hid_device_info *devs = hid_enumerate(0x0, 0x0);
    struct hid_device_info *cur = devs;
    struct hid_device_info *selected = nullptr;

    while (cur != nullptr) {
        if (cur->usage_page == kUsagePageTelephony) {
            if (selected == nullptr) {
                selected = cur;  // first telephony device
            }
            if (cur->usage == 0x05 || cur->usage == 0x04) {
                selected = cur;  // prefer headset/handset
            }
        }
        cur = cur->next;
    }

    if (selected == nullptr) {
        qDebug() << "HeadsetManager: no telephony HID device found";
        hid_free_enumeration(devs);
        return false;
    }

    qDebug() << "HeadsetManager: opening device"
             << QString::fromWCharArray(selected->manufacturer_string)
             << QString::fromWCharArray(selected->product_string)
             << QStringLiteral("%1:%2").arg(selected->vendor_id, 4, 16, QLatin1Char('0'))
                                        .arg(selected->product_id, 4, 16, QLatin1Char('0'));

    m_device = hid_open_path(selected->path);
    hid_free_enumeration(devs);

    if (m_device == nullptr) {
        qWarning() << "HeadsetManager: hid_open_path failed";
        return false;
    }

    // Non-blocking reads so pollDevice() never stalls the Qt event loop.
    hid_set_nonblocking(m_device, 1);

    m_offhookBtn = m_ledOffhook;
    updateLeds();

    m_pollTimer.start(kPollIntervalMs);
    qDebug() << "HeadsetManager: device opened, polling started";
    return true;
}

void HeadsetManager::closeDevice()
{
    m_pollTimer.stop();

    if (m_device != nullptr) {
        // Turn off all LEDs before closing
        m_ledOffhook = false;
        m_ledRing    = false;
        m_ledMute    = false;
        updateLeds();

        hid_close(m_device);
        m_device = nullptr;
        qDebug() << "HeadsetManager: device closed";
    }
}

bool HeadsetManager::isDeviceOpen() const
{
    return m_device != nullptr;
}

// ---------------------------------------------------------------------------
// LED control (output reports)
// ---------------------------------------------------------------------------

void HeadsetManager::setOffhook(bool state)
{
    if (m_ledOffhook != state) {
        m_ledOffhook = state;
        updateLeds();
    }
}

void HeadsetManager::setRing(bool state)
{
    if (m_ledRing != state) {
        m_ledRing = state;
        updateLeds();
    }
}

void HeadsetManager::setMute(bool state)
{
    if (m_ledMute != state) {
        m_ledMute = state;
        updateLeds();
    }
}

void HeadsetManager::updateLeds()
{
    if (m_device == nullptr) {
        return;
    }

    // Build an output report with the LED states.
    // Byte 0 = report ID (0 for single-report devices), remaining bytes =
    // bit-packed LED flags.  This works for the majority of USB telephony
    // headsets (Jabra, Plantronics/Poly, etc.).
    unsigned char report[3];
    std::memset(report, 0, sizeof(report));
    report[0] = 0x00;  // Report ID

    unsigned char flags = 0;
    if (m_ledOffhook) {
        flags |= 0x01u;
    }
    if (m_ledRing) {
        flags |= 0x02u;
    }
    if (m_ledMute) {
        flags |= 0x04u;
    }
    report[1] = flags;

    int written = hid_write(m_device, report, sizeof(report));
    if (written < 0) {
        qDebug() << "HeadsetManager: hid_write failed";
    }
}

// ---------------------------------------------------------------------------
// Polling (replaces Windows TimerProc)
// ---------------------------------------------------------------------------

void HeadsetManager::pollDevice()
{
    if (m_device == nullptr) {
        return;
    }

    unsigned char buf[kMaxReportSize];
    int bytesRead = hid_read(m_device, buf, sizeof(buf));

    if (bytesRead < 0) {
        // Read error → device disconnected
        qWarning() << "HeadsetManager: hid_read error, device lost";
        closeDevice();
        emit deviceLost();
        return;
    }

    if (bytesRead == 0) {
        return;  // no data available (non-blocking)
    }

    // Parse the input report.
    // For most telephony headsets:
    //   byte 0 = report ID (may be implicit if single-report)
    //   byte 1 = button bits: bit 0 = hook switch, bit 1 = mute, bit 2 = redial
    unsigned char buttons = (bytesRead > 1) ? buf[1] : buf[0];

    bool hookSwitch = (buttons & 0x01u) != 0;
    bool mute       = (buttons & 0x02u) != 0;
    bool redial     = (buttons & 0x04u) != 0;

    // Hook switch — detect transitions
    if (hookSwitch && !m_offhookBtn) {
        m_offhookBtn = true;
        emit hookSwitchOn();
    } else if (!hookSwitch && m_offhookBtn) {
        m_offhookBtn = false;
        emit hookSwitchOff();
    }

    // Mute — report changes
    if (mute != m_ledMute) {
        m_ledMute = mute;
        emit muteToggled(mute);
    }

    // Redial — edge-triggered (fire once on press, not on release)
    static bool lastRedial = false;
    if (redial && !lastRedial) {
        emit redialPressed();
    }
    lastRedial = redial;
}

#else // !HEADSET_ENABLED  — stub implementation

HeadsetManager::HeadsetManager(QObject *parent) : QObject(parent) {}
HeadsetManager::~HeadsetManager() = default;
bool HeadsetManager::openDevice()  { return false; }
void HeadsetManager::closeDevice() {}
bool HeadsetManager::isDeviceOpen() const { return false; }
void HeadsetManager::setOffhook(bool) {}
void HeadsetManager::setRing(bool) {}
void HeadsetManager::setMute(bool) {}
void HeadsetManager::pollDevice() {}

#endif // HEADSET_ENABLED

} // namespace macrosip
