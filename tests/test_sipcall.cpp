#include <QtTest>
#include <QSignalSpy>
#include "sip/SipCall.h"

using namespace macrosip;

class TestSipCall : public QObject {
    Q_OBJECT
private slots:
    void testDefaultState();
    void testSetCallId();
    void testSetUserData();
    void testConfirmedTime();
    void testHandleStateChange();
    void testHandleStateChangeConfirmedSetsTime();
    void testHandleMediaStatusChange();
    void testAnswerStub();
    void testHangupStub();
    void testHoldUnholdStub();
    void testTransferStub();
    void testSendDtmfStub();
    void testStartStopRecordingStub();
    void testAnswerInvalid();
    void testHangupInvalid();
    void testStateChangedSignal();
};

void TestSipCall::testDefaultState()
{
    SipCall call;
    QCOMPARE(call.callId(), -1);
    QCOMPARE(call.state(), CallState::Idle);
    QCOMPARE(call.mediaStatus(), MediaStatus::None);
    QVERIFY(!call.confirmedTime().isValid());
}

void TestSipCall::testSetCallId()
{
    SipCall call;
    call.setCallId(42);
    QCOMPARE(call.callId(), 42);
}

void TestSipCall::testSetUserData()
{
    SipCall call;
    CallUserData ud;
    ud.callId = 5;
    ud.name = QStringLiteral("Alice");
    ud.number = QStringLiteral("100");
    ud.direction = CallDirection::Incoming;
    call.setUserData(ud);

    const CallUserData &stored = call.userData();
    QCOMPARE(stored.callId, 5);
    QCOMPARE(stored.name, QStringLiteral("Alice"));
    QCOMPARE(stored.number, QStringLiteral("100"));
    QCOMPARE(stored.direction, CallDirection::Incoming);
}

void TestSipCall::testConfirmedTime()
{
    SipCall call;
    QVERIFY(!call.confirmedTime().isValid());
}

void TestSipCall::testHandleStateChange()
{
    SipCall call;
    QSignalSpy spy(&call, &SipCall::stateChanged);
    QVERIFY(spy.isValid());

    call.handleStateChange(CallState::Calling);
    QCOMPARE(call.state(), CallState::Calling);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).value<CallState>(), CallState::Calling);

    call.handleStateChange(CallState::Disconnected);
    QCOMPARE(call.state(), CallState::Disconnected);
    QCOMPARE(spy.count(), 2);
}

void TestSipCall::testHandleStateChangeConfirmedSetsTime()
{
    SipCall call;
    QVERIFY(!call.confirmedTime().isValid());

    QDateTime before = QDateTime::currentDateTime();
    call.handleStateChange(CallState::Confirmed);
    QDateTime after = QDateTime::currentDateTime();

    QVERIFY(call.confirmedTime().isValid());
    QVERIFY(call.confirmedTime() >= before);
    QVERIFY(call.confirmedTime() <= after);

    // Second Confirmed should not overwrite
    QDateTime first = call.confirmedTime();
    call.handleStateChange(CallState::Confirmed);
    QCOMPARE(call.confirmedTime(), first);
}

void TestSipCall::testHandleMediaStatusChange()
{
    SipCall call;
    QSignalSpy spy(&call, &SipCall::mediaStatusChanged);
    QVERIFY(spy.isValid());

    call.handleMediaStatusChange(MediaStatus::Active);
    QCOMPARE(call.mediaStatus(), MediaStatus::Active);
    QCOMPARE(spy.count(), 1);
}

void TestSipCall::testAnswerStub()
{
    SipCall call;
    call.setCallId(1);

    QSignalSpy stateSpy(&call, &SipCall::stateChanged);
    QSignalSpy mediaSpy(&call, &SipCall::mediaStatusChanged);

    bool ok = call.answer();
    QVERIFY(ok);
    QCOMPARE(call.state(), CallState::Confirmed);
    QCOMPARE(call.mediaStatus(), MediaStatus::Active);
    QVERIFY(call.confirmedTime().isValid());
    QCOMPARE(stateSpy.count(), 1);
    QCOMPARE(mediaSpy.count(), 1);
}

void TestSipCall::testHangupStub()
{
    SipCall call;
    call.setCallId(1);
    call.answer();

    QSignalSpy stateSpy(&call, &SipCall::stateChanged);
    bool ok = call.hangup();
    QVERIFY(ok);
    QCOMPARE(call.state(), CallState::Disconnected);
    QCOMPARE(call.mediaStatus(), MediaStatus::None);
    QCOMPARE(stateSpy.count(), 1);
}

void TestSipCall::testHoldUnholdStub()
{
    SipCall call;
    call.setCallId(1);
    call.answer();

    QSignalSpy mediaSpy(&call, &SipCall::mediaStatusChanged);

    bool ok = call.hold();
    QVERIFY(ok);
    QCOMPARE(call.mediaStatus(), MediaStatus::LocalHold);
    QCOMPARE(mediaSpy.count(), 1);

    ok = call.unhold();
    QVERIFY(ok);
    QCOMPARE(call.mediaStatus(), MediaStatus::Active);
    QCOMPARE(mediaSpy.count(), 2);
}

void TestSipCall::testTransferStub()
{
    SipCall call;
    call.setCallId(1);

    QSignalSpy spy(&call, &SipCall::transferStatusChanged);
    bool ok = call.transfer(QStringLiteral("200"));
    QVERIFY(ok);
    QCOMPARE(spy.count(), 1);
}

void TestSipCall::testSendDtmfStub()
{
    SipCall call;
    call.setCallId(1);

    QSignalSpy spy(&call, &SipCall::dtmfReceived);
    bool ok = call.sendDtmf(QStringLiteral("123"));
    QVERIFY(ok);
    QCOMPARE(spy.count(), 3);
    QCOMPARE(spy.at(0).at(0).toString(), QStringLiteral("1"));
    QCOMPARE(spy.at(1).at(0).toString(), QStringLiteral("2"));
    QCOMPARE(spy.at(2).at(0).toString(), QStringLiteral("3"));
}

void TestSipCall::testStartStopRecordingStub()
{
    SipCall call;
    call.setCallId(1);

    bool ok = call.startRecording(QStringLiteral("/tmp/test.wav"));
    QVERIFY(ok);

    call.stopRecording();
    // Can start again after stop
    bool ok3 = call.startRecording(QStringLiteral("/tmp/test3.wav"));
    QVERIFY(ok3);
}

void TestSipCall::testAnswerInvalid()
{
    SipCall call;  // callId = -1
    QVERIFY(!call.answer());
}

void TestSipCall::testHangupInvalid()
{
    SipCall call;
    QVERIFY(!call.hangup());
}

void TestSipCall::testStateChangedSignal()
{
    SipCall call;
    QSignalSpy spy(&call, &SipCall::stateChanged);

    call.handleStateChange(CallState::Incoming);
    call.handleStateChange(CallState::Confirmed);
    call.handleStateChange(CallState::Disconnected);

    QCOMPARE(spy.count(), 3);
    QCOMPARE(spy.at(0).at(0).value<CallState>(), CallState::Incoming);
    QCOMPARE(spy.at(1).at(0).value<CallState>(), CallState::Confirmed);
    QCOMPARE(spy.at(2).at(0).value<CallState>(), CallState::Disconnected);
}

QTEST_GUILESS_MAIN(TestSipCall)
#include "test_sipcall.moc"
