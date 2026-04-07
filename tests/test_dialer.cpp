#include <QtTest>
#include <QSignalSpy>
#include "widgets/DialerWidget.h"

using namespace macrosip;

class TestDialerWidget : public QObject {
    Q_OBJECT
private slots:
    void testDefaultState();
    void testSetNumber();
    void testCurrentNumber();
    void testClear();
    void testSetStatusText();
    void testCallSignal();
    void testHangupSignal();
};

void TestDialerWidget::testDefaultState()
{
    DialerWidget w;
    QVERIFY(w.currentNumber().isEmpty());
}

void TestDialerWidget::testSetNumber()
{
    DialerWidget w;
    w.setNumber(QStringLiteral("12345"));
    QCOMPARE(w.currentNumber(), QStringLiteral("12345"));
}

void TestDialerWidget::testCurrentNumber()
{
    DialerWidget w;
    w.setNumber(QStringLiteral("100"));
    QCOMPARE(w.currentNumber(), QStringLiteral("100"));

    w.setNumber(QStringLiteral("200"));
    QCOMPARE(w.currentNumber(), QStringLiteral("200"));
}

void TestDialerWidget::testClear()
{
    DialerWidget w;
    w.setNumber(QStringLiteral("100"));
    w.clear();
    QVERIFY(w.currentNumber().isEmpty());
}

void TestDialerWidget::testSetStatusText()
{
    DialerWidget w;
    // Should not crash
    w.setStatusText(QStringLiteral("Active call"));
    w.setStatusText(QString());
}

void TestDialerWidget::testCallSignal()
{
    DialerWidget w;
    QSignalSpy spy(&w, &DialerWidget::callRequested);
    QVERIFY(spy.isValid());

    w.setNumber(QStringLiteral("100"));
    // Simulate call button click via the exposed slot mechanism
    // The call button emits callRequested when clicked
    // We test that the signal exists and is connectable
    QCOMPARE(spy.count(), 0);
}

void TestDialerWidget::testHangupSignal()
{
    DialerWidget w;
    QSignalSpy spy(&w, &DialerWidget::hangupRequested);
    QVERIFY(spy.isValid());
    QCOMPARE(spy.count(), 0);
}

QTEST_MAIN(TestDialerWidget)
#include "test_dialer.moc"
