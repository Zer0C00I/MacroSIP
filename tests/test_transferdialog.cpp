#include <QtTest>
#include <QSignalSpy>
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QDialogButtonBox>
#include "dialogs/TransferDialog.h"

using namespace macrosip;

class TestTransferDialog : public QObject {
    Q_OBJECT
private slots:
    void testDefaultState();
    void testTransferSignalBlind();
    void testTransferSignalAttended();
    void testEmptyTargetNoSignal();
};

void TestTransferDialog::testDefaultState()
{
    TransferDialog dlg;
    auto *targetEdit = dlg.findChild<QLineEdit *>();
    QVERIFY(targetEdit != nullptr);
    QVERIFY(targetEdit->text().isEmpty());

    // Blind radio should be checked by default
    auto *blindRadio = dlg.findChild<QRadioButton *>();
    QVERIFY(blindRadio != nullptr);
    QVERIFY(blindRadio->isChecked());
}

void TestTransferDialog::testTransferSignalBlind()
{
    TransferDialog dlg;
    QSignalSpy spy(&dlg, &TransferDialog::transferRequested);

    auto *targetEdit = dlg.findChild<QLineEdit *>();
    QVERIFY(targetEdit != nullptr);
    targetEdit->setText(QStringLiteral("300"));

    // Find the Transfer button
    QPushButton *transferBtn = nullptr;
    const auto buttons = dlg.findChildren<QPushButton *>();
    for (QPushButton *btn : buttons) {
        if (btn->text() == QObject::tr("Transfer")) {
            transferBtn = btn;
            break;
        }
    }
    QVERIFY(transferBtn != nullptr);
    QTest::mouseClick(transferBtn, Qt::LeftButton);

    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toString(), QStringLiteral("300"));
    QCOMPARE(spy.at(0).at(1).toBool(), false);  // blind (default)
}

void TestTransferDialog::testTransferSignalAttended()
{
    TransferDialog dlg;
    QSignalSpy spy(&dlg, &TransferDialog::transferRequested);

    auto *targetEdit = dlg.findChild<QLineEdit *>();
    QVERIFY(targetEdit != nullptr);
    targetEdit->setText(QStringLiteral("400"));

    // Switch to attended transfer
    auto radios = dlg.findChildren<QRadioButton *>();
    QRadioButton *attendedRadio = nullptr;
    for (auto *r : radios) {
        if (r->text() == QObject::tr("Attended Transfer")) {
            attendedRadio = r;
            break;
        }
    }
    QVERIFY(attendedRadio != nullptr);
    attendedRadio->setChecked(true);

    QPushButton *transferBtn = nullptr;
    const auto buttons = dlg.findChildren<QPushButton *>();
    for (QPushButton *btn : buttons) {
        if (btn->text() == QObject::tr("Transfer")) {
            transferBtn = btn;
            break;
        }
    }
    QVERIFY(transferBtn != nullptr);
    QTest::mouseClick(transferBtn, Qt::LeftButton);

    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toString(), QStringLiteral("400"));
    QCOMPARE(spy.at(0).at(1).toBool(), true);  // attended
}

void TestTransferDialog::testEmptyTargetNoSignal()
{
    TransferDialog dlg;
    QSignalSpy spy(&dlg, &TransferDialog::transferRequested);

    // Leave target empty, click Transfer → should not emit
    QPushButton *transferBtn = nullptr;
    const auto buttons = dlg.findChildren<QPushButton *>();
    for (QPushButton *btn : buttons) {
        if (btn->text() == QObject::tr("Transfer")) {
            transferBtn = btn;
            break;
        }
    }
    QVERIFY(transferBtn != nullptr);
    QTest::mouseClick(transferBtn, Qt::LeftButton);

    QCOMPARE(spy.count(), 0);
}

QTEST_MAIN(TestTransferDialog)
#include "test_transferdialog.moc"
