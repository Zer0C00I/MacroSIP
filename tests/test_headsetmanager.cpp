#include <QtTest>
#include <QSignalSpy>
#include "headset/HeadsetManager.h"

using namespace macrosip;

class TestHeadsetManager : public QObject {
    Q_OBJECT
private slots:
    void testDefaultNotOpen();
    void testOpenDeviceReturnsFalse();
    void testCloseDeviceNoOp();
    void testSetOffhookNoDevice();
    void testSetRingNoDevice();
    void testSetMuteNoDevice();
    void testOpenThenCloseDoesNotCrash();
    void testMultipleCloseCallsSafe();
    void testDeviceClosedAfterOpen();
};

void TestHeadsetManager::testDefaultNotOpen()
{
    HeadsetManager mgr;
    QVERIFY(!mgr.isDeviceOpen());
}

void TestHeadsetManager::testOpenDeviceReturnsFalse()
{
    HeadsetManager mgr;
    // Without a real HID device (or in stub mode), openDevice returns false
    bool result = mgr.openDevice();
    QVERIFY(!result);
    QVERIFY(!mgr.isDeviceOpen());
}

void TestHeadsetManager::testCloseDeviceNoOp()
{
    HeadsetManager mgr;
    QVERIFY(!mgr.isDeviceOpen());

    // Close when nothing is open should be safe and leave state unchanged
    mgr.closeDevice();
    QVERIFY(!mgr.isDeviceOpen());
}

void TestHeadsetManager::testSetOffhookNoDevice()
{
    HeadsetManager mgr;
    // Without a device open, LED setters should be no-ops (no crash)
    mgr.setOffhook(true);
    mgr.setOffhook(false);
    QVERIFY(!mgr.isDeviceOpen());
}

void TestHeadsetManager::testSetRingNoDevice()
{
    HeadsetManager mgr;
    mgr.setRing(true);
    mgr.setRing(false);
    QVERIFY(!mgr.isDeviceOpen());
}

void TestHeadsetManager::testSetMuteNoDevice()
{
    HeadsetManager mgr;
    mgr.setMute(true);
    mgr.setMute(false);
    QVERIFY(!mgr.isDeviceOpen());
}

void TestHeadsetManager::testOpenThenCloseDoesNotCrash()
{
    HeadsetManager mgr;
    bool opened = mgr.openDevice();
    // Regardless of open result, close should be safe
    mgr.closeDevice();
    QVERIFY(!mgr.isDeviceOpen());
    Q_UNUSED(opened)
}

void TestHeadsetManager::testMultipleCloseCallsSafe()
{
    HeadsetManager mgr;
    mgr.closeDevice();
    mgr.closeDevice();
    mgr.closeDevice();
    QVERIFY(!mgr.isDeviceOpen());
}

void TestHeadsetManager::testDeviceClosedAfterOpen()
{
    HeadsetManager mgr;
    mgr.openDevice();
    // openDevice failed (no device), so still closed
    QVERIFY(!mgr.isDeviceOpen());
    mgr.closeDevice();
    QVERIFY(!mgr.isDeviceOpen());
}

QTEST_GUILESS_MAIN(TestHeadsetManager)
#include "test_headsetmanager.moc"
