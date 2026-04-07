#include <QtTest>
#include <QSignalSpy>
#include <QLabel>
#include <QPushButton>
#include "dialogs/RingingDialog.h"

using namespace macrosip;

class TestRingingDialog : public QObject {
    Q_OBJECT
private slots:
    void testDefaultState();
    void testSetCallInfo();
    void testAnswerSignalViaButtonClick();
    void testDeclineSignalViaButtonClick();
    void testSetAutoCloseTimeout();
};

void TestRingingDialog::testDefaultState()
{
    RingingDialog dlg;
    // Dialog should have the expected child widgets
    auto *answerBtn = dlg.findChild<QPushButton *>(QString(), Qt::FindChildrenRecursively);
    QVERIFY(answerBtn != nullptr);
}

void TestRingingDialog::testSetCallInfo()
{
    RingingDialog dlg;
    dlg.setCallInfo(42, QStringLiteral("Alice"), QStringLiteral("100"));

    // Verify labels are populated
    auto labels = dlg.findChildren<QLabel *>();
    bool foundName = false;
    bool foundNumber = false;
    for (auto *label : labels) {
        if (label->text() == QStringLiteral("Alice"))
            foundName = true;
        if (label->text() == QStringLiteral("100"))
            foundNumber = true;
    }
    QVERIFY(foundName);
    QVERIFY(foundNumber);
}

void TestRingingDialog::testAnswerSignalViaButtonClick()
{
    RingingDialog dlg;
    dlg.setCallInfo(42, QStringLiteral("Alice"), QStringLiteral("100"));

    QSignalSpy spy(&dlg, &RingingDialog::answered);

    // Find the Answer button
    QPushButton *answerBtn = nullptr;
    const auto buttons = dlg.findChildren<QPushButton *>();
    for (QPushButton *btn : buttons) {
        if (btn->text() == QObject::tr("Answer")) {
            answerBtn = btn;
            break;
        }
    }
    QVERIFY(answerBtn != nullptr);

    QTest::mouseClick(answerBtn, Qt::LeftButton);

    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toInt(), 42);
}

void TestRingingDialog::testDeclineSignalViaButtonClick()
{
    RingingDialog dlg;
    dlg.setCallInfo(7, QStringLiteral("Bob"), QStringLiteral("200"));

    QSignalSpy spy(&dlg, &RingingDialog::declined);

    QPushButton *declineBtn = nullptr;
    const auto buttons = dlg.findChildren<QPushButton *>();
    for (QPushButton *btn : buttons) {
        if (btn->text() == QObject::tr("Decline")) {
            declineBtn = btn;
            break;
        }
    }
    QVERIFY(declineBtn != nullptr);

    QTest::mouseClick(declineBtn, Qt::LeftButton);

    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toInt(), 7);
}

void TestRingingDialog::testSetAutoCloseTimeout()
{
    RingingDialog dlg;
    dlg.setCallInfo(1, QStringLiteral("Bob"), QStringLiteral("200"));

    // Setting zero/negative should stop timer, not crash
    dlg.setAutoCloseTimeout(0);
    dlg.setAutoCloseTimeout(-1);

    // Setting positive starts the timer
    dlg.setAutoCloseTimeout(30);

    // Verify the timer is active
    auto *timer = dlg.findChild<QTimer *>();
    QVERIFY(timer != nullptr);
    QVERIFY(timer->isActive());

    // Setting zero again should stop it
    dlg.setAutoCloseTimeout(0);
    QVERIFY(!timer->isActive());
}

QTEST_MAIN(TestRingingDialog)
#include "test_ringingdialog.moc"
