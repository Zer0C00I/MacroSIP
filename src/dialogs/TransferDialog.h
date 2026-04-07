#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QDialogButtonBox>

namespace macrosip {

class TransferDialog : public QDialog {
    Q_OBJECT

public:
    explicit TransferDialog(QWidget *parent = nullptr);
    ~TransferDialog() override = default;

Q_SIGNALS:
    void transferRequested(const QString &target, bool attended);

private Q_SLOTS:
    void onTransfer();

private:
    void setupUi();

    QLineEdit *m_targetEdit = nullptr;
    QRadioButton *m_blindRadio = nullptr;
    QRadioButton *m_attendedRadio = nullptr;
    QDialogButtonBox *m_buttonBox = nullptr;
};

} // namespace macrosip
