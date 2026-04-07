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
    void testTabCloseRequested();
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

void TestClosableTabWidget::testTabCloseRequested()
{
    ClosableTabWidget tw;
    auto *w1 = new QWidget();
    auto *w2 = new QWidget();
    tw.addClosableTab(w1, QStringLiteral("Tab 1"));
    tw.addClosableTab(w2, QStringLiteral("Tab 2"));

    QSignalSpy spy(&tw, &ClosableTabWidget::tabCloseClicked);

    // Simulate tab close request via the tabCloseRequested signal from QTabWidget
    emit tw.tabCloseRequested(0);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toInt(), 0);
}

QTEST_MAIN(TestClosableTabWidget)
#include "test_closabletabwidget.moc"
