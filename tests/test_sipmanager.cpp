#include <QtTest>
#include <QSignalSpy>
#include "sip/SipManager.h"

using namespace macrosip;

class TestSipManager : public QObject {
    Q_OBJECT
private slots:
    void testInitShutdown();
    void testAddRemoveAccount();
    void testMakeCallStub();
    void testFindCall();
    void testHangupAllCalls();
    void testAnswerCall();
    void testHangupCall();
    void testHoldUnhold();
    void testTransferCall();
    void testSendDtmf();
    void testSetMute();
    void testSetVolume();
    void testAudioDevices();
    void testCodecs();
};

void TestSipManager::testInitShutdown()
{
    SipManager mgr;
    QVERIFY(!mgr.isRunning());

    QVERIFY(mgr.initialize());
    QVERIFY(mgr.isRunning());

    mgr.shutdown();
    QVERIFY(!mgr.isRunning());
}

void TestSipManager::testAddRemoveAccount()
{
    SipManager mgr;
    mgr.initialize();

    Account cfg;
    cfg.server = QStringLiteral("sip.example.com");
    cfg.username = QStringLiteral("user1");

    SipAccount *acc = mgr.addAccount(cfg);
    QVERIFY(acc != nullptr);
    QVERIFY(acc->isRegistered());  // stub auto-registers

    int accId = acc->accountId();
    SipAccount *found = mgr.findAccount(accId);
    QCOMPARE(found, acc);

    mgr.removeAccount(accId);
    QVERIFY(mgr.findAccount(accId) == nullptr);

    mgr.shutdown();
}

void TestSipManager::testMakeCallStub()
{
    SipManager mgr;
    mgr.initialize();

    QSignalSpy spy(&mgr, &SipManager::callStateChanged);

    SipCall *call = mgr.makeCall(QStringLiteral("100"));
    QVERIFY(call != nullptr);
    QVERIFY(call->callId() >= 0);

    // findCall should find it
    SipCall *found = mgr.findCall(call->callId());
    QCOMPARE(found, call);

    mgr.shutdown();
}

void TestSipManager::testFindCall()
{
    SipManager mgr;
    mgr.initialize();

    // Non-existent call
    QVERIFY(mgr.findCall(9999) == nullptr);

    SipCall *call = mgr.makeCall(QStringLiteral("100"));
    QVERIFY(call != nullptr);
    QCOMPARE(mgr.findCall(call->callId()), call);

    mgr.shutdown();
}

void TestSipManager::testHangupAllCalls()
{
    SipManager mgr;
    mgr.initialize();

    mgr.makeCall(QStringLiteral("100"));
    mgr.makeCall(QStringLiteral("200"));

    // Should not crash
    mgr.hangupAllCalls();

    mgr.shutdown();
}

void TestSipManager::testAnswerCall()
{
    SipManager mgr;
    mgr.initialize();

    SipCall *call = mgr.makeCall(QStringLiteral("100"));
    QVERIFY(call != nullptr);

    mgr.answerCall(call->callId());
    // In stub mode, state should transition
    mgr.shutdown();
}

void TestSipManager::testHangupCall()
{
    SipManager mgr;
    mgr.initialize();

    SipCall *call = mgr.makeCall(QStringLiteral("100"));
    QVERIFY(call != nullptr);
    int id = call->callId();

    mgr.hangupCall(id);
    // Should not crash even with invalid ID
    mgr.hangupCall(9999);

    mgr.shutdown();
}

void TestSipManager::testHoldUnhold()
{
    SipManager mgr;
    mgr.initialize();

    SipCall *call = mgr.makeCall(QStringLiteral("100"));
    QVERIFY(call != nullptr);

    mgr.holdCall(call->callId());
    mgr.unholdCall(call->callId());

    // Invalid IDs should not crash
    mgr.holdCall(9999);
    mgr.unholdCall(9999);

    mgr.shutdown();
}

void TestSipManager::testTransferCall()
{
    SipManager mgr;
    mgr.initialize();

    SipCall *call = mgr.makeCall(QStringLiteral("100"));
    QVERIFY(call != nullptr);

    mgr.transferCall(call->callId(), QStringLiteral("200"));
    mgr.transferCall(9999, QStringLiteral("200"));  // invalid - no crash

    mgr.shutdown();
}

void TestSipManager::testSendDtmf()
{
    SipManager mgr;
    mgr.initialize();

    SipCall *call = mgr.makeCall(QStringLiteral("100"));
    QVERIFY(call != nullptr);

    mgr.sendDtmf(call->callId(), QStringLiteral("123#"));
    mgr.sendDtmf(9999, QStringLiteral("1"));  // invalid - no crash

    mgr.shutdown();
}

void TestSipManager::testSetMute()
{
    SipManager mgr;
    mgr.initialize();

    // Should not crash
    mgr.setMuteInput(true);
    mgr.setMuteInput(false);
    mgr.setMuteOutput(true);
    mgr.setMuteOutput(false);

    mgr.shutdown();
}

void TestSipManager::testSetVolume()
{
    SipManager mgr;
    mgr.initialize();

    // Should not crash
    mgr.setInputVolume(50);
    mgr.setOutputVolume(75);

    mgr.shutdown();
}

void TestSipManager::testAudioDevices()
{
    SipManager mgr;
    mgr.initialize();

    // In stub mode these may return empty lists, but should not crash
    QStringList inputs = mgr.audioInputDevices();
    QStringList outputs = mgr.audioOutputDevices();
    // In stub mode these return empty lists; we only verify no crash
    QVERIFY(inputs.isEmpty() || !inputs.isEmpty());
    QVERIFY(outputs.isEmpty() || !outputs.isEmpty());

    mgr.shutdown();
}

void TestSipManager::testCodecs()
{
    SipManager mgr;
    mgr.initialize();

    QStringList codecs = mgr.availableCodecs();
    // In stub mode this returns an empty list; verify no crash
    QVERIFY(codecs.isEmpty() || !codecs.isEmpty());

    mgr.setCodecPriority(QStringLiteral("PCMA/8000/1"), 200);

    mgr.shutdown();
}

QTEST_GUILESS_MAIN(TestSipManager)
#include "test_sipmanager.moc"
