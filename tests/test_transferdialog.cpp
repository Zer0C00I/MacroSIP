#include <QtTest>
#include <QSignalSpy>
#include "dialogs/TransferDialog.h"

using namespace macrosip;

class TestTransferDialog : public QObject {
    Q_OBJECT
private slots:
    void testConstruction();
    void testTransferSignal();
};

void TestTransferDialog::testConstruction()
{
    TransferDialog dlg;
    QVERIFY(true);
}

void TestTransferDialog::testTransferSignal()
{
    TransferDialog dlg;
    QSignalSpy spy(&dlg, &TransferDialog::transferRequested);
    QVERIFY(spy.isValid());
}

QTEST_MAIN(TestTransferDialog)
#include "test_transferdialog.moc"
