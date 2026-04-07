#include "TransferDialog.h"

#include <QFormLayout>
#include <QGroupBox>
#include <QVBoxLayout>

namespace macrosip {

TransferDialog::TransferDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Transfer Call"));
    setupUi();
}

void TransferDialog::onTransfer()
{
    const QString target = m_targetEdit->text().trimmed();
    if (!target.isEmpty()) {
        const bool attended = m_attendedRadio->isChecked();
        Q_EMIT transferRequested(target, attended);
        accept();
    }
}

void TransferDialog::setupUi()
{
    auto *mainLayout = new QVBoxLayout(this);

    auto *form = new QFormLayout;
    m_targetEdit = new QLineEdit(this);
    m_targetEdit->setPlaceholderText(tr("Transfer target number"));
    form->addRow(tr("Transfer To:"), m_targetEdit);
    mainLayout->addLayout(form);

    auto *typeGroup = new QGroupBox(tr("Transfer Type"), this);
    auto *typeLayout = new QVBoxLayout(typeGroup);
    m_blindRadio = new QRadioButton(tr("Blind Transfer"), typeGroup);
    m_blindRadio->setChecked(true);
    typeLayout->addWidget(m_blindRadio);
    m_attendedRadio = new QRadioButton(tr("Attended Transfer"), typeGroup);
    typeLayout->addWidget(m_attendedRadio);
    mainLayout->addWidget(typeGroup);

    m_buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Cancel, this);
    auto *transferBtn = m_buttonBox->addButton(tr("Transfer"),
                                                QDialogButtonBox::AcceptRole);
    connect(transferBtn, &QPushButton::clicked,
            this, &TransferDialog::onTransfer);
    connect(m_buttonBox, &QDialogButtonBox::rejected,
            this, &QDialog::reject);
    mainLayout->addWidget(m_buttonBox);

    resize(340, 200);
}

} // namespace macrosip
