#include <QtTest>
#include "dialogs/FeatureCodesDialog.h"

using namespace macrosip;

class TestFeatureCodesDialog : public QObject {
    Q_OBJECT
private slots:
    void testConstruction();
    void testCallPark();
    void testBlindTransfer();
    void testAttendedTransfer();
    void testRoundTrip();
};

void TestFeatureCodesDialog::testConstruction()
{
    FeatureCodesDialog dlg;
    QVERIFY(dlg.callParkCode().isEmpty());
    QVERIFY(!dlg.callParkEnabled());
    QVERIFY(dlg.blindTransferCode().isEmpty());
    QVERIFY(!dlg.blindTransferEnabled());
    QVERIFY(dlg.attendedTransferCode().isEmpty());
    QVERIFY(!dlg.attendedTransferEnabled());
}

void TestFeatureCodesDialog::testCallPark()
{
    FeatureCodesDialog dlg;
    dlg.setCallParkCode(QStringLiteral("*70"));
    dlg.setCallParkEnabled(true);

    QCOMPARE(dlg.callParkCode(), QStringLiteral("*70"));
    QVERIFY(dlg.callParkEnabled());
}

void TestFeatureCodesDialog::testBlindTransfer()
{
    FeatureCodesDialog dlg;
    dlg.setBlindTransferCode(QStringLiteral("*71"));
    dlg.setBlindTransferEnabled(true);

    QCOMPARE(dlg.blindTransferCode(), QStringLiteral("*71"));
    QVERIFY(dlg.blindTransferEnabled());
}

void TestFeatureCodesDialog::testAttendedTransfer()
{
    FeatureCodesDialog dlg;
    dlg.setAttendedTransferCode(QStringLiteral("*72"));
    dlg.setAttendedTransferEnabled(true);

    QCOMPARE(dlg.attendedTransferCode(), QStringLiteral("*72"));
    QVERIFY(dlg.attendedTransferEnabled());
}

void TestFeatureCodesDialog::testRoundTrip()
{
    FeatureCodesDialog dlg;
    dlg.setCallParkCode(QStringLiteral("*70"));
    dlg.setCallParkEnabled(true);
    dlg.setBlindTransferCode(QStringLiteral("*71"));
    dlg.setBlindTransferEnabled(false);
    dlg.setAttendedTransferCode(QStringLiteral("*72"));
    dlg.setAttendedTransferEnabled(true);

    QCOMPARE(dlg.callParkCode(), QStringLiteral("*70"));
    QVERIFY(dlg.callParkEnabled());
    QCOMPARE(dlg.blindTransferCode(), QStringLiteral("*71"));
    QVERIFY(!dlg.blindTransferEnabled());
    QCOMPARE(dlg.attendedTransferCode(), QStringLiteral("*72"));
    QVERIFY(dlg.attendedTransferEnabled());
}

QTEST_MAIN(TestFeatureCodesDialog)
#include "test_featurecodesdialog.moc"
