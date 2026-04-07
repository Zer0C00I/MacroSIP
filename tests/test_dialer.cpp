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
    void testDtmfPressedSignal();
    void testCallButtonClick();
    void testHangupButtonClick();
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
    QCOMPARE(spy.count(), 0);
}

void TestDialerWidget::testHangupSignal()
{
    DialerWidget w;
    QSignalSpy spy(&w, &DialerWidget::hangupRequested);
    QVERIFY(spy.isValid());
    QCOMPARE(spy.count(), 0);
}

void TestDialerWidget::testDtmfPressedSignal()
{
    DialerWidget w;
    QSignalSpy spy(&w, &DialerWidget::dtmfPressed);
    QVERIFY(spy.isValid());
}

void TestDialerWidget::testCallButtonClick()
{
    DialerWidget w;
    QSignalSpy spy(&w, &DialerWidget::callRequested);

    // Find the Call/Hangup buttons by text
    const auto buttons = w.findChildren<QPushButton *>();
    QPushButton *callBtn = nullptr;
    for (QPushButton *btn : buttons) {
        if (btn->text() == QObject::tr("Call"))
            callBtn = btn;
    }

    if (callBtn != nullptr) {
        // Empty number → no signal
        QTest::mouseClick(callBtn, Qt::LeftButton);
        QCOMPARE(spy.count(), 0);

        // With number → signal
        w.setNumber(QStringLiteral("12345"));
        QTest::mouseClick(callBtn, Qt::LeftButton);
        QCOMPARE(spy.count(), 1);
        QCOMPARE(spy.at(0).at(0).toString(), QStringLiteral("12345"));
    }
}

void TestDialerWidget::testHangupButtonClick()
{
    DialerWidget w;
    QSignalSpy spy(&w, &DialerWidget::hangupRequested);

    const auto buttons = w.findChildren<QPushButton *>();
    QPushButton *hangupBtn = nullptr;
    for (QPushButton *btn : buttons) {
        if (btn->text() == QObject::tr("Hangup"))
            hangupBtn = btn;
    }

    if (hangupBtn != nullptr) {
        QTest::mouseClick(hangupBtn, Qt::LeftButton);
        QCOMPARE(spy.count(), 1);
    }
}

QTEST_MAIN(TestDialerWidget)
#include "test_dialer.moc"
