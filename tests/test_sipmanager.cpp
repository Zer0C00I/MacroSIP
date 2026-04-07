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
    void testMergeConference();
    void testPresence();
    void testSetCodecPriority();
    void testSignalInitialized();
    void testSignalCallStateChanged();
    void testSignalRegistrationStateChanged();
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

    // In stub mode these return one entry each
    QStringList inputs = mgr.audioInputDevices();
    QStringList outputs = mgr.audioOutputDevices();
    QVERIFY(!inputs.isEmpty());
    QCOMPARE(inputs.first(), QStringLiteral("Default Input (stub)"));
    QVERIFY(!outputs.isEmpty());
    QCOMPARE(outputs.first(), QStringLiteral("Default Output (stub)"));

    mgr.shutdown();
}

void TestSipManager::testCodecs()
{
    SipManager mgr;
    mgr.initialize();

    QStringList codecs = mgr.availableCodecs();
    // In stub mode returns 4 codecs
    QCOMPARE(codecs.size(), 4);
    QVERIFY(codecs.contains(QStringLiteral("PCMA/8000/1")));
    QVERIFY(codecs.contains(QStringLiteral("PCMU/8000/1")));
    QVERIFY(codecs.contains(QStringLiteral("opus/48000/2")));

    mgr.setCodecPriority(QStringLiteral("PCMA/8000/1"), 200);

    mgr.shutdown();
}

void TestSipManager::testMergeConference()
{
    SipManager mgr;
    mgr.initialize();

    SipCall *call1 = mgr.makeCall(QStringLiteral("100"));
    SipCall *call2 = mgr.makeCall(QStringLiteral("200"));
    QVERIFY(call1 != nullptr);
    QVERIFY(call2 != nullptr);

    // Should not crash
    mgr.mergeConference(call1->callId(), call2->callId());
    // Invalid IDs should not crash
    mgr.mergeConference(9999, 8888);

    mgr.shutdown();
}

void TestSipManager::testPresence()
{
    SipManager mgr;
    mgr.initialize();

    // All presence operations should not crash in stub mode
    mgr.subscribePresence(QStringLiteral("sip:user@example.com"));
    mgr.unsubscribePresence(QStringLiteral("sip:user@example.com"));
    mgr.publishPresence(PresenceStatus::Online);
    mgr.publishPresence(PresenceStatus::Away);
    mgr.publishPresence(PresenceStatus::Busy);

    mgr.shutdown();
}

void TestSipManager::testSetCodecPriority()
{
    SipManager mgr;
    mgr.initialize();

    QStringList codecs = mgr.availableCodecs();
    // Set priority should not crash
    mgr.setCodecPriority(QStringLiteral("PCMA/8000/1"), 255);
    mgr.setCodecPriority(QStringLiteral("PCMU/8000/1"), 0);
    mgr.setCodecPriority(QStringLiteral("nonexistent"), 100);

    mgr.shutdown();
}

void TestSipManager::testSignalInitialized()
{
    SipManager mgr;
    QSignalSpy spy(&mgr, &SipManager::initialized);
    QVERIFY(spy.isValid());

    mgr.initialize();
    // In stub mode, initialized signal should fire
    QVERIFY(spy.count() >= 1);

    mgr.shutdown();
}

void TestSipManager::testSignalCallStateChanged()
{
    SipManager mgr;
    mgr.initialize();

    QSignalSpy spy(&mgr, &SipManager::callStateChanged);

    SipCall *call = mgr.makeCall(QStringLiteral("100"));
    QVERIFY(call != nullptr);

    // Trigger a state change on the call object, should propagate to SipManager
    call->handleStateChange(CallState::Confirmed);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(1).value<CallState>(), CallState::Confirmed);

    mgr.shutdown();
}

void TestSipManager::testSignalRegistrationStateChanged()
{
    SipManager mgr;
    mgr.initialize();

    QSignalSpy spy(&mgr, &SipManager::registrationStateChanged);
    QVERIFY(spy.isValid());

    Account cfg;
    cfg.server = QStringLiteral("sip.example.com");
    cfg.username = QStringLiteral("user1");
    SipAccount *acc = mgr.addAccount(cfg);
    QVERIFY(acc != nullptr);

    // The stub auto-registers synchronously before signal connection,
    // so trigger a manual state change to verify signal propagation
    acc->handleRegistrationState(RegistrationState::Error, 408,
                                 QStringLiteral("Timeout"));
    QVERIFY(spy.count() >= 1);

    mgr.shutdown();
}

QTEST_GUILESS_MAIN(TestSipManager)
#include "test_sipmanager.moc"
