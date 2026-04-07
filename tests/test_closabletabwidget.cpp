#include <QtTest>
#include <QSignalSpy>
#include "widgets/ClosableTabWidget.h"

using namespace macrosip;

class TestClosableTabWidget : public QObject {
    Q_OBJECT
private slots:
    void testConstruction();
    void testAddClosableTab();
    void testSetTabIcon();
    void testTabCloseSignal();
};

void TestClosableTabWidget::testConstruction()
{
    ClosableTabWidget tw;
    QCOMPARE(tw.count(), 0);
}

void TestClosableTabWidget::testAddClosableTab()
{
    ClosableTabWidget tw;
    auto *w1 = new QWidget();
    auto *w2 = new QWidget();

    int idx1 = tw.addClosableTab(w1, QStringLiteral("Tab 1"));
    int idx2 = tw.addClosableTab(w2, QStringLiteral("Tab 2"));

    QCOMPARE(tw.count(), 2);
    QVERIFY(idx1 >= 0);
    QVERIFY(idx2 >= 0);
    QVERIFY(idx1 != idx2);
    QCOMPARE(tw.tabText(idx1), QStringLiteral("Tab 1"));
    QCOMPARE(tw.tabText(idx2), QStringLiteral("Tab 2"));
}

void TestClosableTabWidget::testSetTabIcon()
{
    ClosableTabWidget tw;
    auto *w = new QWidget();
    int idx = tw.addClosableTab(w, QStringLiteral("Tab"));

    // Should not crash with null icon
    tw.setTabIcon(idx, QIcon());
}

void TestClosableTabWidget::testTabCloseSignal()
{
    ClosableTabWidget tw;
    QSignalSpy spy(&tw, &ClosableTabWidget::tabCloseClicked);
    QVERIFY(spy.isValid());
}

QTEST_MAIN(TestClosableTabWidget)
#include "test_closabletabwidget.moc"
