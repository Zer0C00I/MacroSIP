#include "AAOptionsDialog.h"

#include <QFormLayout>
#include <QVBoxLayout>

namespace macrosip {

AAOptionsDialog::AAOptionsDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Auto-Answer Options"));
    setupUi();
}

void AAOptionsDialog::setAutoAnswerEnabled(bool enabled)
{
    m_enableCheck->setChecked(enabled);
}

bool AAOptionsDialog::autoAnswerEnabled() const
{
    return m_enableCheck->isChecked();
}

void AAOptionsDialog::setAutoAnswerDelay(int seconds)
{
    m_delaySpin->setValue(seconds);
}

int AAOptionsDialog::autoAnswerDelay() const
{
    return m_delaySpin->value();
}

void AAOptionsDialog::setNumberFilter(const QString &filter)
{
    m_filterEdit->setText(filter);
}

QString AAOptionsDialog::numberFilter() const
{
    return m_filterEdit->text();
}

void AAOptionsDialog::onAccepted()
{
    accept();
}

void AAOptionsDialog::setupUi()
{
    auto *mainLayout = new QVBoxLayout(this);
    auto *form = new QFormLayout;

    m_enableCheck = new QCheckBox(tr("Enable Auto-Answer"), this);
    form->addRow(m_enableCheck);

    m_delaySpin = new QSpinBox(this);
    m_delaySpin->setRange(0, 60);
    m_delaySpin->setSuffix(tr(" s"));
    form->addRow(tr("Delay:"), m_delaySpin);

    m_filterEdit = new QLineEdit(this);
    m_filterEdit->setPlaceholderText(tr("Number filter pattern"));
    form->addRow(tr("Number Filter:"), m_filterEdit);

    mainLayout->addLayout(form);

    m_buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(m_buttonBox, &QDialogButtonBox::accepted,
            this, &AAOptionsDialog::onAccepted);
    connect(m_buttonBox, &QDialogButtonBox::rejected,
            this, &QDialog::reject);
    mainLayout->addWidget(m_buttonBox);

    resize(340, 180);
}

} // namespace macrosip
