#include <QtTest>
#include <QSignalSpy>
#include "dialogs/RingingDialog.h"

using namespace macrosip;

class TestRingingDialog : public QObject {
    Q_OBJECT
private slots:
    void testConstruction();
    void testSetCallInfo();
    void testAnswerSignal();
    void testDeclineSignal();
    void testSetAutoCloseTimeout();
};

void TestRingingDialog::testConstruction()
{
    RingingDialog dlg;
    // Should create without crashing
    QVERIFY(true);
}

void TestRingingDialog::testSetCallInfo()
{
    RingingDialog dlg;
    dlg.setCallInfo(42, QStringLiteral("Alice"), QStringLiteral("100"));
    // Should display call info without crashing
    QVERIFY(true);
}

void TestRingingDialog::testAnswerSignal()
{
    RingingDialog dlg;
    QSignalSpy spy(&dlg, &RingingDialog::answered);
    QVERIFY(spy.isValid());

    dlg.setCallInfo(42, QStringLiteral("Alice"), QStringLiteral("100"));
}

void TestRingingDialog::testDeclineSignal()
{
    RingingDialog dlg;
    QSignalSpy spy(&dlg, &RingingDialog::declined);
    QVERIFY(spy.isValid());
}

void TestRingingDialog::testSetAutoCloseTimeout()
{
    RingingDialog dlg;
    dlg.setCallInfo(1, QStringLiteral("Bob"), QStringLiteral("200"));
    dlg.setAutoCloseTimeout(30);
    // Should not crash
    QVERIFY(true);
}

QTEST_MAIN(TestRingingDialog)
#include "test_ringingdialog.moc"
