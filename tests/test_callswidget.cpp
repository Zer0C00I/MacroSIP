#include <QtTest>
#include <QSignalSpy>
#include <QTreeWidget>
#include "widgets/CallsWidget.h"

using namespace macrosip;

class TestCallsWidget : public QObject {
    Q_OBJECT
private:
    static CallRecord makeRecord(const QString &id, const QString &name,
                                 const QString &number, CallType type,
                                 int duration = 0)
    {
        CallRecord r;
        r.id = id;
        r.name = name;
        r.number = number;
        r.type = type;
        r.duration = duration;
        r.time = QDateTime::currentDateTime();
        return r;
    }

private slots:
    void testDefaultEmpty();
    void testLoadCalls();
    void testLoadCallsReplacesOld();
    void testAddCallPrepends();
    void testClearHistory();
    void testRedialOnDoubleClick();
    void testFilterAll();
    void testFilterByType();
};

void TestCallsWidget::testDefaultEmpty()
{
    CallsWidget w;
    QCOMPARE(w.callCount(), 0);
    QCOMPARE(w.visibleCallCount(), 0);
}

void TestCallsWidget::testLoadCalls()
{
    CallsWidget w;
    QList<CallRecord> calls;
    calls.append(makeRecord(QStringLiteral("1"), QStringLiteral("Alice"),
                            QStringLiteral("100"), CallType::Outgoing, 60));
    calls.append(makeRecord(QStringLiteral("2"), QStringLiteral("Bob"),
                            QStringLiteral("200"), CallType::Missed));

    w.loadCalls(calls);

    QCOMPARE(w.callCount(), 2);
    QCOMPARE(w.visibleCallCount(), 2);
}

void TestCallsWidget::testLoadCallsReplacesOld()
{
    CallsWidget w;

    QList<CallRecord> first;
    first.append(makeRecord(QStringLiteral("1"), QStringLiteral("Alice"),
                            QStringLiteral("100"), CallType::Outgoing));
    w.loadCalls(first);
    QCOMPARE(w.callCount(), 1);

    QList<CallRecord> second;
    second.append(makeRecord(QStringLiteral("2"), QStringLiteral("Bob"),
                             QStringLiteral("200"), CallType::Incoming));
    second.append(makeRecord(QStringLiteral("3"), QStringLiteral("Charlie"),
                             QStringLiteral("300"), CallType::Missed));
    w.loadCalls(second);

    QCOMPARE(w.callCount(), 2);
    QCOMPARE(w.visibleCallCount(), 2);
}

void TestCallsWidget::testAddCallPrepends()
{
    CallsWidget w;
    w.addCall(makeRecord(QStringLiteral("1"), QStringLiteral("Alice"),
                         QStringLiteral("100"), CallType::Outgoing, 60));
    QCOMPARE(w.callCount(), 1);
    QCOMPARE(w.visibleCallCount(), 1);

    w.addCall(makeRecord(QStringLiteral("2"), QStringLiteral("Bob"),
                         QStringLiteral("200"), CallType::Incoming, 120));
    QCOMPARE(w.callCount(), 2);
    QCOMPARE(w.visibleCallCount(), 2);

    // Verify the tree widget shows the newer call first (prepended)
    auto *tree = w.findChild<QTreeWidget *>();
    QVERIFY(tree != nullptr);
    QCOMPARE(tree->topLevelItemCount(), 2);
    // Bob (id 2) was added last → prepended → should be row 0
    QCOMPARE(tree->topLevelItem(0)->data(0, Qt::UserRole).toString(),
             QStringLiteral("200"));
}

void TestCallsWidget::testClearHistory()
{
    CallsWidget w;
    w.addCall(makeRecord(QStringLiteral("1"), QStringLiteral("Alice"),
                         QStringLiteral("100"), CallType::Outgoing));
    w.addCall(makeRecord(QStringLiteral("2"), QStringLiteral("Bob"),
                         QStringLiteral("200"), CallType::Missed));
    QCOMPARE(w.callCount(), 2);

    w.clearHistory();

    QCOMPARE(w.callCount(), 0);
    QCOMPARE(w.visibleCallCount(), 0);
}

void TestCallsWidget::testRedialOnDoubleClick()
{
    CallsWidget w;
    w.addCall(makeRecord(QStringLiteral("1"), QStringLiteral("Alice"),
                         QStringLiteral("100"), CallType::Outgoing));

    QSignalSpy spy(&w, &CallsWidget::redial);

    auto *tree = w.findChild<QTreeWidget *>();
    QVERIFY(tree != nullptr);
    QVERIFY(tree->topLevelItemCount() == 1);

    // Simulate double-click on the first item
    QTreeWidgetItem *item = tree->topLevelItem(0);
    Q_EMIT tree->itemDoubleClicked(item, 0);

    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toString(), QStringLiteral("100"));
}

void TestCallsWidget::testFilterAll()
{
    CallsWidget w;
    w.addCall(makeRecord(QStringLiteral("1"), QStringLiteral("Alice"),
                         QStringLiteral("100"), CallType::Outgoing));
    w.addCall(makeRecord(QStringLiteral("2"), QStringLiteral("Bob"),
                         QStringLiteral("200"), CallType::Missed));
    w.addCall(makeRecord(QStringLiteral("3"), QStringLiteral("Charlie"),
                         QStringLiteral("300"), CallType::Incoming));

    // Default filter "All" → all 3 visible
    QCOMPARE(w.callCount(), 3);
    QCOMPARE(w.visibleCallCount(), 3);
}

void TestCallsWidget::testFilterByType()
{
    CallsWidget w;
    w.addCall(makeRecord(QStringLiteral("1"), QStringLiteral("Alice"),
                         QStringLiteral("100"), CallType::Outgoing));
    w.addCall(makeRecord(QStringLiteral("2"), QStringLiteral("Bob"),
                         QStringLiteral("200"), CallType::Missed));
    w.addCall(makeRecord(QStringLiteral("3"), QStringLiteral("Charlie"),
                         QStringLiteral("300"), CallType::Incoming));

    QCOMPARE(w.callCount(), 3);

    // Switch filter to "Missed" (index 3 in the combo: All=0, Incoming=1, Outgoing=2, Missed=3)
    auto *combo = w.findChild<QComboBox *>();
    QVERIFY(combo != nullptr);
    combo->setCurrentIndex(3);  // Missed

    // Total records unchanged, but visible should be just the 1 missed call
    QCOMPARE(w.callCount(), 3);
    QCOMPARE(w.visibleCallCount(), 1);

    // Switch to Outgoing (index 2)
    combo->setCurrentIndex(2);
    QCOMPARE(w.visibleCallCount(), 1);

    // Switch back to All (index 0)
    combo->setCurrentIndex(0);
    QCOMPARE(w.visibleCallCount(), 3);
}

QTEST_MAIN(TestCallsWidget)
#include "test_callswidget.moc"
