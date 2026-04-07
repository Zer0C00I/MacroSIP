#pragma once
#include <QObject>
#include <QTimer>

#ifdef HEADSET_ENABLED
// Forward-declare the opaque hidapi handle
struct hid_device_;
typedef struct hid_device_ hid_device;
#endif

namespace macrosip {

/**
 * Cross-platform USB HID telephony headset support.
 *
 * Ported from the Windows-only MicroSIP lib/Hid.cpp using the system
 * libhidapi (hidraw or libusb backend).  Communicates with headsets that
 * expose USB HID Telephony usage page (0x0B) — hook-switch, mute, redial,
 * and LED indicators (off-hook, ring, mute).
 *
 * The class is driven by a QTimer that polls the HID device every 200 ms
 * (same cadence as the original Windows TimerProc).
 *
 * When built without HEADSET_ENABLED all methods are no-ops.
 */
class HeadsetManager : public QObject {
    Q_OBJECT
public:
    explicit HeadsetManager(QObject *parent = nullptr);
    ~HeadsetManager() override;

    /** Try to find and open a telephony HID device.  Returns true on success. */
    bool openDevice();

    /** Close the currently open device (if any). */
    void closeDevice();

    /** Whether a HID device is currently open. */
    bool isDeviceOpen() const;

    // ---- LED state pushed from the application ----
    void setOffhook(bool state);
    void setRing(bool state);
    void setMute(bool state);

signals:
    /** Hook-switch pressed while idle → answer / initiate call. */
    void hookSwitchOn();
    /** Hook-switch released while off-hook → end call. */
    void hookSwitchOff();
    /** Mute button toggled. */
    void muteToggled(bool muted);
    /** Redial button pressed. */
    void redialPressed();
    /** Device was disconnected (read error). */
    void deviceLost();

private slots:
    void pollDevice();

private:
#ifdef HEADSET_ENABLED
    // HID Telephony usage IDs (input)
    static constexpr unsigned short kUsagePageTelephony = 0x0B;
    static constexpr unsigned short kUsageHookSwitch    = 0x20;
    static constexpr unsigned short kUsageFlash         = 0x21;
    static constexpr unsigned short kUsageRedial        = 0x24;
    static constexpr unsigned short kUsageMute          = 0x2F;

    // HID LED usage IDs (output)
    static constexpr unsigned short kUsagePageLed = 0x08;
    static constexpr unsigned short kLedOffHook   = 0x17;
    static constexpr unsigned short kLedRing      = 0x18;
    static constexpr unsigned short kLedMute      = 0x09;

    void updateLeds();

    hid_device *m_device = nullptr;
    QTimer m_pollTimer;

    // Tracked button state (absolute)
    bool m_offhookBtn = false;
    bool m_muteBtn    = false;
    bool m_lastRedial = false;

    // LED state the application wants
    bool m_ledOffhook = false;
    bool m_ledRing    = false;
    bool m_ledMute    = false;
#endif
};

} // namespace macrosip
