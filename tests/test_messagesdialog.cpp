#include <QtTest>
#include <QSignalSpy>
#include <QTabWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include "dialogs/MessagesDialog.h"
#include "sip/SipTypes.h"

using namespace macrosip;

class TestMessagesDialog : public QObject {
    Q_OBJECT
private slots:
    void testDefaultEmpty();
    void testOpenTab();
    void testOpenTabDuplicate();
    void testAppendMessage();
    void testAppendMessageNonExistentTab();
    void testCloseTab();
    void testCloseTabInvalidIndex();
    void testSetCallStateUpdatesTitle();
    void testMessageSentSignal();
};

void TestMessagesDialog::testDefaultEmpty()
{
    MessagesDialog dlg;
    auto *tabs = dlg.findChild<QTabWidget *>();
    QVERIFY(tabs != nullptr);
    QCOMPARE(tabs->count(), 0);
}

void TestMessagesDialog::testOpenTab()
{
    MessagesDialog dlg;
    dlg.openTab(QStringLiteral("100"), QStringLiteral("Alice"));
    dlg.openTab(QStringLiteral("200"), QStringLiteral("Bob"));

    auto *tabs = dlg.findChild<QTabWidget *>();
    QVERIFY(tabs != nullptr);
    QCOMPARE(tabs->count(), 2);
    QCOMPARE(tabs->tabText(0), QStringLiteral("Alice"));
    QCOMPARE(tabs->tabText(1), QStringLiteral("Bob"));
}

void TestMessagesDialog::testOpenTabDuplicate()
{
    MessagesDialog dlg;
    dlg.openTab(QStringLiteral("100"), QStringLiteral("Alice"));
    dlg.openTab(QStringLiteral("100"), QStringLiteral("Alice"));  // duplicate

    auto *tabs = dlg.findChild<QTabWidget *>();
    QVERIFY(tabs != nullptr);
    QCOMPARE(tabs->count(), 1);  // should not create a second tab
}

void TestMessagesDialog::testAppendMessage()
{
    MessagesDialog dlg;
    dlg.openTab(QStringLiteral("100"), QStringLiteral("Alice"));

    dlg.appendMessage(QStringLiteral("100"), QStringLiteral("Hello!"), true);
    dlg.appendMessage(QStringLiteral("100"), QStringLiteral("Hi!"), false);

    // Verify the history text edit contains the messages
    auto histories = dlg.findChildren<QTextEdit *>();
    QVERIFY(!histories.isEmpty());

    bool foundHello = false;
    bool foundHi = false;
    for (auto *te : histories) {
        if (te->isReadOnly()) {
            const QString html = te->toPlainText();
            if (html.contains(QStringLiteral("Hello!")))
                foundHello = true;
            if (html.contains(QStringLiteral("Hi!")))
                foundHi = true;
        }
    }
    QVERIFY(foundHello);
    QVERIFY(foundHi);
}

void TestMessagesDialog::testAppendMessageNonExistentTab()
{
    MessagesDialog dlg;
    dlg.openTab(QStringLiteral("100"), QStringLiteral("Alice"));

    // Appending to a non-existent tab should silently do nothing
    dlg.appendMessage(QStringLiteral("999"), QStringLiteral("test"), true);

    auto *tabs = dlg.findChild<QTabWidget *>();
    QCOMPARE(tabs->count(), 1);  // still just one tab
}

void TestMessagesDialog::testCloseTab()
{
    MessagesDialog dlg;
    dlg.openTab(QStringLiteral("100"), QStringLiteral("Alice"));
    dlg.openTab(QStringLiteral("200"), QStringLiteral("Bob"));

    auto *tabs = dlg.findChild<QTabWidget *>();
    QCOMPARE(tabs->count(), 2);

    dlg.closeTab(0);
    QCOMPARE(tabs->count(), 1);
}

void TestMessagesDialog::testCloseTabInvalidIndex()
{
    MessagesDialog dlg;
    dlg.openTab(QStringLiteral("100"), QStringLiteral("Alice"));

    auto *tabs = dlg.findChild<QTabWidget *>();
    QCOMPARE(tabs->count(), 1);

    // Closing invalid index should not crash and not change count
    dlg.closeTab(99);
    QCOMPARE(tabs->count(), 1);
}

void TestMessagesDialog::testSetCallStateUpdatesTitle()
{
    MessagesDialog dlg;
    dlg.openTab(QStringLiteral("100"), QStringLiteral("Alice"));

    auto *tabs = dlg.findChild<QTabWidget *>();
    QVERIFY(tabs != nullptr);

    dlg.setCallState(QStringLiteral("100"), CallState::Confirmed);
    QVERIFY(tabs->tabText(0).contains(QStringLiteral("[Active]")));

    dlg.setCallState(QStringLiteral("100"), CallState::Disconnected);
    QVERIFY(tabs->tabText(0).contains(QStringLiteral("[Ended]")));
}

void TestMessagesDialog::testMessageSentSignal()
{
    MessagesDialog dlg;
    dlg.openTab(QStringLiteral("100"), QStringLiteral("Alice"));

    QSignalSpy spy(&dlg, &MessagesDialog::messageSent);

    // Find the Send button and the input field in Alice's tab
    auto *tabs = dlg.findChild<QTabWidget *>();
    QVERIFY(tabs != nullptr);
    QCOMPARE(tabs->count(), 1);
    QWidget *tabWidget = tabs->widget(0);

    auto *input = tabWidget->findChild<QLineEdit *>();
    QVERIFY(input != nullptr);

    // Type text and press Enter (triggers onSendMessage via returnPressed)
    input->setText(QStringLiteral("Hello World"));
    Q_EMIT input->returnPressed();

    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toString(), QStringLiteral("100"));
    QCOMPARE(spy.at(0).at(1).toString(), QStringLiteral("Hello World"));
}

QTEST_MAIN(TestMessagesDialog)
#include "test_messagesdialog.moc"
