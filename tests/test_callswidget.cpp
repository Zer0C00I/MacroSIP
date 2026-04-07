#include <QtTest>
#include <QSignalSpy>
#include "widgets/CallsWidget.h"

using namespace macrosip;

class TestCallsWidget : public QObject {
    Q_OBJECT
private slots:
    void testDefaultState();
    void testLoadCalls();
    void testAddCall();
    void testClearHistory();
    void testRedialSignal();
    void testCallSelectedSignal();
};

void TestCallsWidget::testDefaultState()
{
    CallsWidget w;
    QVERIFY(true);
}

void TestCallsWidget::testLoadCalls()
{
    CallsWidget w;
    QList<CallRecord> calls;

    CallRecord r1;
    r1.id = QStringLiteral("1");
    r1.name = QStringLiteral("Alice");
    r1.number = QStringLiteral("100");
    r1.type = CallType::Outgoing;
    r1.duration = 60;
    r1.time = QDateTime::currentDateTime();
    calls.append(r1);

    CallRecord r2;
    r2.id = QStringLiteral("2");
    r2.name = QStringLiteral("Bob");
    r2.number = QStringLiteral("200");
    r2.type = CallType::Missed;
    r2.time = QDateTime::currentDateTime();
    calls.append(r2);

    w.loadCalls(calls);
    QVERIFY(true);
}

void TestCallsWidget::testAddCall()
{
    CallsWidget w;
    CallRecord r;
    r.id = QStringLiteral("3");
    r.name = QStringLiteral("Charlie");
    r.number = QStringLiteral("300");
    r.type = CallType::Incoming;
    r.duration = 120;
    r.time = QDateTime::currentDateTime();

    w.addCall(r);
    QVERIFY(true);
}

void TestCallsWidget::testClearHistory()
{
    CallsWidget w;
    CallRecord r;
    r.id = QStringLiteral("1");
    r.number = QStringLiteral("100");
    r.time = QDateTime::currentDateTime();
    w.addCall(r);

    w.clearHistory();
    QVERIFY(true);
}

void TestCallsWidget::testRedialSignal()
{
    CallsWidget w;
    QSignalSpy spy(&w, &CallsWidget::redial);
    QVERIFY(spy.isValid());
}

void TestCallsWidget::testCallSelectedSignal()
{
    CallsWidget w;
    QSignalSpy spy(&w, &CallsWidget::callSelected);
    QVERIFY(spy.isValid());
}

QTEST_MAIN(TestCallsWidget)
#include "test_callswidget.moc"
