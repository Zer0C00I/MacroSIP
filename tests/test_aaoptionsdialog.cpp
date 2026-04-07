#include <QtTest>
#include "dialogs/AAOptionsDialog.h"

using namespace macrosip;

class TestAAOptionsDialog : public QObject {
    Q_OBJECT
private slots:
    void testConstruction();
    void testAutoAnswerEnabled();
    void testAutoAnswerDelay();
    void testNumberFilter();
    void testRoundTrip();
};

void TestAAOptionsDialog::testConstruction()
{
    AAOptionsDialog dlg;
    // Defaults
    QVERIFY(!dlg.autoAnswerEnabled());
    QCOMPARE(dlg.autoAnswerDelay(), 0);
    QVERIFY(dlg.numberFilter().isEmpty());
}

void TestAAOptionsDialog::testAutoAnswerEnabled()
{
    AAOptionsDialog dlg;
    dlg.setAutoAnswerEnabled(true);
    QVERIFY(dlg.autoAnswerEnabled());

    dlg.setAutoAnswerEnabled(false);
    QVERIFY(!dlg.autoAnswerEnabled());
}

void TestAAOptionsDialog::testAutoAnswerDelay()
{
    AAOptionsDialog dlg;
    dlg.setAutoAnswerDelay(5);
    QCOMPARE(dlg.autoAnswerDelay(), 5);

    dlg.setAutoAnswerDelay(0);
    QCOMPARE(dlg.autoAnswerDelay(), 0);
}

void TestAAOptionsDialog::testNumberFilter()
{
    AAOptionsDialog dlg;
    dlg.setNumberFilter(QStringLiteral("100,200,300"));
    QCOMPARE(dlg.numberFilter(), QStringLiteral("100,200,300"));
}

void TestAAOptionsDialog::testRoundTrip()
{
    AAOptionsDialog dlg;
    dlg.setAutoAnswerEnabled(true);
    dlg.setAutoAnswerDelay(10);
    dlg.setNumberFilter(QStringLiteral("ext*"));

    QVERIFY(dlg.autoAnswerEnabled());
    QCOMPARE(dlg.autoAnswerDelay(), 10);
    QCOMPARE(dlg.numberFilter(), QStringLiteral("ext*"));
}

QTEST_MAIN(TestAAOptionsDialog)
#include "test_aaoptionsdialog.moc"
