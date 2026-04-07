#include "AddContactDialog.h"
#include "models/Contact.h"

#include <QFormLayout>
#include <QVBoxLayout>

namespace macrosip {

AddContactDialog::AddContactDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Add Contact"));
    setupUi();
}

void AddContactDialog::setContact(const Contact &c)
{
    setWindowTitle(tr("Edit Contact"));
    m_nameEdit->setText(c.name);
    m_numberEdit->setText(c.number);
    m_firstnameEdit->setText(c.firstname);
    m_lastnameEdit->setText(c.lastname);
    m_phoneEdit->setText(c.phone);
    m_mobileEdit->setText(c.mobile);
    m_emailEdit->setText(c.email);
    m_addressEdit->setText(c.address);
    m_cityEdit->setText(c.city);
    m_stateEdit->setText(c.state);
    m_zipEdit->setText(c.zip);
    m_commentEdit->setText(c.comment);
    m_presenceCheck->setChecked(c.presence);
    m_starredCheck->setChecked(c.starred);
}

Contact AddContactDialog::contact() const
{
    Contact c;
    c.name      = m_nameEdit->text();
    c.number    = m_numberEdit->text();
    c.firstname = m_firstnameEdit->text();
    c.lastname  = m_lastnameEdit->text();
    c.phone     = m_phoneEdit->text();
    c.mobile    = m_mobileEdit->text();
    c.email     = m_emailEdit->text();
    c.address   = m_addressEdit->text();
    c.city      = m_cityEdit->text();
    c.state     = m_stateEdit->text();
    c.zip       = m_zipEdit->text();
    c.comment   = m_commentEdit->text();
    c.presence  = m_presenceCheck->isChecked();
    c.starred   = m_starredCheck->isChecked();
    return c;
}

void AddContactDialog::onAccepted()
{
    accept();
}

void AddContactDialog::setupUi()
{
    auto *mainLayout = new QVBoxLayout(this);
    auto *form = new QFormLayout;

    m_nameEdit = new QLineEdit(this);
    form->addRow(tr("Name:"), m_nameEdit);

    m_numberEdit = new QLineEdit(this);
    form->addRow(tr("Number:"), m_numberEdit);

    m_firstnameEdit = new QLineEdit(this);
    form->addRow(tr("First Name:"), m_firstnameEdit);

    m_lastnameEdit = new QLineEdit(this);
    form->addRow(tr("Last Name:"), m_lastnameEdit);

    m_phoneEdit = new QLineEdit(this);
    form->addRow(tr("Phone:"), m_phoneEdit);

    m_mobileEdit = new QLineEdit(this);
    form->addRow(tr("Mobile:"), m_mobileEdit);

    m_emailEdit = new QLineEdit(this);
    form->addRow(tr("Email:"), m_emailEdit);

    m_addressEdit = new QLineEdit(this);
    form->addRow(tr("Address:"), m_addressEdit);

    m_cityEdit = new QLineEdit(this);
    form->addRow(tr("City:"), m_cityEdit);

    m_stateEdit = new QLineEdit(this);
    form->addRow(tr("State:"), m_stateEdit);

    m_zipEdit = new QLineEdit(this);
    form->addRow(tr("ZIP:"), m_zipEdit);

    m_commentEdit = new QLineEdit(this);
    form->addRow(tr("Comment:"), m_commentEdit);

    mainLayout->addLayout(form);

    m_presenceCheck = new QCheckBox(tr("Subscribe to Presence"), this);
    mainLayout->addWidget(m_presenceCheck);

    m_starredCheck = new QCheckBox(tr("Starred"), this);
    mainLayout->addWidget(m_starredCheck);

    m_buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(m_buttonBox, &QDialogButtonBox::accepted,
            this, &AddContactDialog::onAccepted);
    connect(m_buttonBox, &QDialogButtonBox::rejected,
            this, &QDialog::reject);
    mainLayout->addWidget(m_buttonBox);

    resize(400, 520);
}

} // namespace macrosip
