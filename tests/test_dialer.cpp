#include <QtTest>
#include <QSignalSpy>
#include <QPushButton>
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
    void testCallButtonClick();
    void testCallButtonEmptyNoSignal();
    void testHangupButtonClick();
    void testDtmfDigitClick();
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
    w.setStatusText(QStringLiteral("Active call"));
    // Find the status label and verify its text
    auto labels = w.findChildren<QLabel *>();
    bool found = false;
    for (auto *label : labels) {
        if (label->text() == QStringLiteral("Active call")) {
            found = true;
            break;
        }
    }
    QVERIFY(found);
}

void TestDialerWidget::testCallButtonClick()
{
    DialerWidget w;
    QSignalSpy spy(&w, &DialerWidget::callRequested);

    // Find the Call button
    QPushButton *callBtn = nullptr;
    const auto buttons = w.findChildren<QPushButton *>();
    for (QPushButton *btn : buttons) {
        if (btn->text() == QObject::tr("Call")) {
            callBtn = btn;
            break;
        }
    }
    QVERIFY(callBtn != nullptr);

    w.setNumber(QStringLiteral("12345"));
    QTest::mouseClick(callBtn, Qt::LeftButton);

    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toString(), QStringLiteral("12345"));
}

void TestDialerWidget::testCallButtonEmptyNoSignal()
{
    DialerWidget w;
    QSignalSpy spy(&w, &DialerWidget::callRequested);

    QPushButton *callBtn = nullptr;
    const auto buttons = w.findChildren<QPushButton *>();
    for (QPushButton *btn : buttons) {
        if (btn->text() == QObject::tr("Call")) {
            callBtn = btn;
            break;
        }
    }
    QVERIFY(callBtn != nullptr);

    // No number → no signal
    QTest::mouseClick(callBtn, Qt::LeftButton);
    QCOMPARE(spy.count(), 0);
}

void TestDialerWidget::testHangupButtonClick()
{
    DialerWidget w;
    QSignalSpy spy(&w, &DialerWidget::hangupRequested);

    QPushButton *hangupBtn = nullptr;
    const auto buttons = w.findChildren<QPushButton *>();
    for (QPushButton *btn : buttons) {
        if (btn->text() == QObject::tr("Hangup")) {
            hangupBtn = btn;
            break;
        }
    }
    QVERIFY(hangupBtn != nullptr);

    QTest::mouseClick(hangupBtn, Qt::LeftButton);
    QCOMPARE(spy.count(), 1);
}

void TestDialerWidget::testDtmfDigitClick()
{
    DialerWidget w;
    QSignalSpy spy(&w, &DialerWidget::dtmfPressed);

    // Find a digit button — look for one with the "digit" property set to "5"
    QPushButton *digitBtn = nullptr;
    const auto buttons = w.findChildren<QPushButton *>();
    for (QPushButton *btn : buttons) {
        if (btn->property("digit").toString() == QStringLiteral("5")) {
            digitBtn = btn;
            break;
        }
    }
    QVERIFY(digitBtn != nullptr);

    w.clear();
    QTest::mouseClick(digitBtn, Qt::LeftButton);

    // Should have emitted dtmfPressed("5")
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toString(), QStringLiteral("5"));

    // Should have appended "5" to the number input
    QCOMPARE(w.currentNumber(), QStringLiteral("5"));
}

QTEST_MAIN(TestDialerWidget)
#include "test_dialer.moc"
