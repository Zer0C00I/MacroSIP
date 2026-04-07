#include <QtTest>
#include "headset/HeadsetManager.h"

using namespace macrosip;

class TestHeadsetManager : public QObject {
    Q_OBJECT
private slots:
    void testConstruction();
    void testOpenDeviceReturnsFalse();
    void testIsDeviceOpen();
    void testCloseDevice();
    void testSetOffhookNoDevice();
    void testSetRingNoDevice();
    void testSetMuteNoDevice();
    void testSignalHookSwitch();
    void testSignalMuteToggled();
    void testSignalRedialPressed();
    void testSignalDeviceLost();
};

void TestHeadsetManager::testConstruction()
{
    HeadsetManager mgr;
    QVERIFY(!mgr.isDeviceOpen());
}

void TestHeadsetManager::testOpenDeviceReturnsFalse()
{
    HeadsetManager mgr;
    // Without a real telephony HID device, openDevice should return false
    // (or false in stub mode when HEADSET_ENABLED is off)
    bool result = mgr.openDevice();
    QVERIFY(!result);
}

void TestHeadsetManager::testIsDeviceOpen()
{
    HeadsetManager mgr;
    QVERIFY(!mgr.isDeviceOpen());
}

void TestHeadsetManager::testCloseDevice()
{
    HeadsetManager mgr;
    // Should not crash when no device is open
    mgr.closeDevice();
    QVERIFY(!mgr.isDeviceOpen());
}

void TestHeadsetManager::testSetOffhookNoDevice()
{
    HeadsetManager mgr;
    // Should not crash
    mgr.setOffhook(true);
    mgr.setOffhook(false);
}

void TestHeadsetManager::testSetRingNoDevice()
{
    HeadsetManager mgr;
    mgr.setRing(true);
    mgr.setRing(false);
}

void TestHeadsetManager::testSetMuteNoDevice()
{
    HeadsetManager mgr;
    mgr.setMute(true);
    mgr.setMute(false);
}

void TestHeadsetManager::testSignalHookSwitch()
{
    HeadsetManager mgr;
    QSignalSpy spyOn(&mgr, &HeadsetManager::hookSwitchOn);
    QSignalSpy spyOff(&mgr, &HeadsetManager::hookSwitchOff);
    QVERIFY(spyOn.isValid());
    QVERIFY(spyOff.isValid());
}

void TestHeadsetManager::testSignalMuteToggled()
{
    HeadsetManager mgr;
    QSignalSpy spy(&mgr, &HeadsetManager::muteToggled);
    QVERIFY(spy.isValid());
}

void TestHeadsetManager::testSignalRedialPressed()
{
    HeadsetManager mgr;
    QSignalSpy spy(&mgr, &HeadsetManager::redialPressed);
    QVERIFY(spy.isValid());
}

void TestHeadsetManager::testSignalDeviceLost()
{
    HeadsetManager mgr;
    QSignalSpy spy(&mgr, &HeadsetManager::deviceLost);
    QVERIFY(spy.isValid());
}

QTEST_GUILESS_MAIN(TestHeadsetManager)
#include "test_headsetmanager.moc"
