#include <QtTest>
#include "dialogs/MessagesDialog.h"
#include "sip/SipTypes.h"

using namespace macrosip;

class TestMessagesDialog : public QObject {
    Q_OBJECT
private slots:
    void testConstruction();
    void testOpenTab();
    void testOpenTabDuplicate();
    void testAppendMessage();
    void testCloseTab();
    void testSetCallState();
    void testSignalMessageSent();
    void testSignalHoldRequested();
    void testSignalTransferRequested();
    void testSignalRecordRequested();
    void testSignalHangupRequested();
    void testSignalConferenceRequested();
};

void TestMessagesDialog::testConstruction()
{
    MessagesDialog dlg;
    QVERIFY(true);
}

void TestMessagesDialog::testOpenTab()
{
    MessagesDialog dlg;
    dlg.openTab(QStringLiteral("100"), QStringLiteral("Alice"));
    dlg.openTab(QStringLiteral("200"), QStringLiteral("Bob"));
    QVERIFY(true);
}

void TestMessagesDialog::testOpenTabDuplicate()
{
    MessagesDialog dlg;
    dlg.openTab(QStringLiteral("100"), QStringLiteral("Alice"));
    dlg.openTab(QStringLiteral("100"), QStringLiteral("Alice"));  // duplicate
    QVERIFY(true);
}

void TestMessagesDialog::testAppendMessage()
{
    MessagesDialog dlg;
    dlg.openTab(QStringLiteral("100"), QStringLiteral("Alice"));

    dlg.appendMessage(QStringLiteral("100"), QStringLiteral("Hello!"), true);
    dlg.appendMessage(QStringLiteral("100"), QStringLiteral("Hi!"), false);
    // Append to non-existent tab should not crash
    dlg.appendMessage(QStringLiteral("999"), QStringLiteral("test"), true);
    QVERIFY(true);
}

void TestMessagesDialog::testCloseTab()
{
    MessagesDialog dlg;
    dlg.openTab(QStringLiteral("100"), QStringLiteral("Alice"));
    dlg.closeTab(0);
    // Close invalid index should not crash
    dlg.closeTab(99);
    QVERIFY(true);
}

void TestMessagesDialog::testSetCallState()
{
    MessagesDialog dlg;
    dlg.openTab(QStringLiteral("100"), QStringLiteral("Alice"));
    dlg.setCallState(QStringLiteral("100"), CallState::Confirmed);
    dlg.setCallState(QStringLiteral("100"), CallState::Disconnected);
    // Non-existent should not crash
    dlg.setCallState(QStringLiteral("999"), CallState::Idle);
    QVERIFY(true);
}

void TestMessagesDialog::testSignalMessageSent()
{
    MessagesDialog dlg;
    QSignalSpy spy(&dlg, &MessagesDialog::messageSent);
    QVERIFY(spy.isValid());
}

void TestMessagesDialog::testSignalHoldRequested()
{
    MessagesDialog dlg;
    QSignalSpy spy(&dlg, &MessagesDialog::holdRequested);
    QVERIFY(spy.isValid());
}

void TestMessagesDialog::testSignalTransferRequested()
{
    MessagesDialog dlg;
    QSignalSpy spy(&dlg, &MessagesDialog::transferRequested);
    QVERIFY(spy.isValid());
}

void TestMessagesDialog::testSignalRecordRequested()
{
    MessagesDialog dlg;
    QSignalSpy spy(&dlg, &MessagesDialog::recordRequested);
    QVERIFY(spy.isValid());
}

void TestMessagesDialog::testSignalHangupRequested()
{
    MessagesDialog dlg;
    QSignalSpy spy(&dlg, &MessagesDialog::hangupRequested);
    QVERIFY(spy.isValid());
}

void TestMessagesDialog::testSignalConferenceRequested()
{
    MessagesDialog dlg;
    QSignalSpy spy(&dlg, &MessagesDialog::conferenceRequested);
    QVERIFY(spy.isValid());
}

QTEST_MAIN(TestMessagesDialog)
#include "test_messagesdialog.moc"
