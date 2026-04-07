#include "FeatureCodesDialog.h"

#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace macrosip {

FeatureCodesDialog::FeatureCodesDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Feature Codes"));
    setupUi();
}

void FeatureCodesDialog::setCallParkCode(const QString &code)
{
    m_callParkEdit->setText(code);
}

QString FeatureCodesDialog::callParkCode() const
{
    return m_callParkEdit->text();
}

void FeatureCodesDialog::setCallParkEnabled(bool enabled)
{
    m_callParkCheck->setChecked(enabled);
}

bool FeatureCodesDialog::callParkEnabled() const
{
    return m_callParkCheck->isChecked();
}

void FeatureCodesDialog::setBlindTransferCode(const QString &code)
{
    m_blindTransferEdit->setText(code);
}

QString FeatureCodesDialog::blindTransferCode() const
{
    return m_blindTransferEdit->text();
}

void FeatureCodesDialog::setBlindTransferEnabled(bool enabled)
{
    m_blindTransferCheck->setChecked(enabled);
}

bool FeatureCodesDialog::blindTransferEnabled() const
{
    return m_blindTransferCheck->isChecked();
}

void FeatureCodesDialog::setAttendedTransferCode(const QString &code)
{
    m_attendedTransferEdit->setText(code);
}

QString FeatureCodesDialog::attendedTransferCode() const
{
    return m_attendedTransferEdit->text();
}

void FeatureCodesDialog::setAttendedTransferEnabled(bool enabled)
{
    m_attendedTransferCheck->setChecked(enabled);
}

bool FeatureCodesDialog::attendedTransferEnabled() const
{
    return m_attendedTransferCheck->isChecked();
}

void FeatureCodesDialog::onAccepted()
{
    accept();
}

void FeatureCodesDialog::setupUi()
{
    auto *mainLayout = new QVBoxLayout(this);
    auto *form = new QFormLayout;

    // Call Parking
    auto *cpLayout = new QHBoxLayout;
    m_callParkEdit = new QLineEdit(this);
    m_callParkEdit->setPlaceholderText(tr("e.g. *70"));
    cpLayout->addWidget(m_callParkEdit);
    m_callParkCheck = new QCheckBox(tr("Enable"), this);
    cpLayout->addWidget(m_callParkCheck);
    form->addRow(tr("Call Park:"), cpLayout);

    // Blind Transfer
    auto *btLayout = new QHBoxLayout;
    m_blindTransferEdit = new QLineEdit(this);
    m_blindTransferEdit->setPlaceholderText(tr("e.g. *71"));
    btLayout->addWidget(m_blindTransferEdit);
    m_blindTransferCheck = new QCheckBox(tr("Enable"), this);
    btLayout->addWidget(m_blindTransferCheck);
    form->addRow(tr("Blind Transfer:"), btLayout);

    // Attended Transfer
    auto *atLayout = new QHBoxLayout;
    m_attendedTransferEdit = new QLineEdit(this);
    m_attendedTransferEdit->setPlaceholderText(tr("e.g. *72"));
    atLayout->addWidget(m_attendedTransferEdit);
    m_attendedTransferCheck = new QCheckBox(tr("Enable"), this);
    atLayout->addWidget(m_attendedTransferCheck);
    form->addRow(tr("Attended Transfer:"), atLayout);

    mainLayout->addLayout(form);

    m_buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(m_buttonBox, &QDialogButtonBox::accepted,
            this, &FeatureCodesDialog::onAccepted);
    connect(m_buttonBox, &QDialogButtonBox::rejected,
            this, &QDialog::reject);
    mainLayout->addWidget(m_buttonBox);

    resize(400, 200);
}

} // namespace macrosip
