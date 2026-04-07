#include "AccountDialog.h"
#include "models/Account.h"

#include <QFormLayout>
#include <QVBoxLayout>

namespace macrosip {

AccountDialog::AccountDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Account Settings"));
    setupUi();
}

void AccountDialog::setAccount(const Account &acct)
{
    m_labelEdit->setText(acct.label);
    m_serverEdit->setText(acct.server);
    m_proxyEdit->setText(acct.proxy);
    m_usernameEdit->setText(acct.username);
    m_domainEdit->setText(acct.domain);
    m_authIdEdit->setText(acct.authID);
    m_passwordEdit->setText(acct.password);
    m_displayNameEdit->setText(acct.displayName);
    m_dialingPrefixEdit->setText(acct.dialingPrefix);
    m_dialPlanEdit->setText(acct.dialPlan);
    m_publicAddrEdit->setText(acct.publicAddr);
    m_portSpin->setValue(acct.port);
    m_refreshSpin->setValue(acct.registerRefresh);
    m_keepAliveSpin->setValue(acct.keepAlive);

    // Transport combo
    const QString transport = acct.transport.toLower();
    if (transport == QLatin1String("tcp"))
        m_transportCombo->setCurrentIndex(1);
    else if (transport == QLatin1String("tls"))
        m_transportCombo->setCurrentIndex(2);
    else
        m_transportCombo->setCurrentIndex(0);

    // SRTP combo
    const QString srtp = acct.srtp.toLower();
    if (srtp == QLatin1String("optional"))
        m_srtpCombo->setCurrentIndex(1);
    else if (srtp == QLatin1String("mandatory"))
        m_srtpCombo->setCurrentIndex(2);
    else
        m_srtpCombo->setCurrentIndex(0);

    m_publishCheck->setChecked(acct.publish);
    m_iceCheck->setChecked(acct.ice);
    m_allowRewriteCheck->setChecked(acct.allowRewrite);
    m_hideCidCheck->setChecked(acct.hideCID);
}

Account AccountDialog::account() const
{
    Account acct;
    acct.label          = m_labelEdit->text();
    acct.server         = m_serverEdit->text();
    acct.proxy          = m_proxyEdit->text();
    acct.username       = m_usernameEdit->text();
    acct.domain         = m_domainEdit->text();
    acct.authID         = m_authIdEdit->text();
    acct.password       = m_passwordEdit->text();
    acct.displayName    = m_displayNameEdit->text();
    acct.dialingPrefix  = m_dialingPrefixEdit->text();
    acct.dialPlan       = m_dialPlanEdit->text();
    acct.publicAddr     = m_publicAddrEdit->text();
    acct.port           = m_portSpin->value();
    acct.registerRefresh = m_refreshSpin->value();
    acct.keepAlive      = m_keepAliveSpin->value();
    acct.transport      = m_transportCombo->currentData().toString();
    acct.srtp           = m_srtpCombo->currentData().toString();
    acct.publish        = m_publishCheck->isChecked();
    acct.ice            = m_iceCheck->isChecked();
    acct.allowRewrite   = m_allowRewriteCheck->isChecked();
    acct.hideCID        = m_hideCidCheck->isChecked();
    return acct;
}

void AccountDialog::onAccepted()
{
    accept();
}

void AccountDialog::setupUi()
{
    auto *mainLayout = new QVBoxLayout(this);
    auto *form = new QFormLayout;

    m_labelEdit = new QLineEdit(this);
    form->addRow(tr("Label:"), m_labelEdit);

    m_serverEdit = new QLineEdit(this);
    form->addRow(tr("SIP Server:"), m_serverEdit);

    m_proxyEdit = new QLineEdit(this);
    form->addRow(tr("Proxy:"), m_proxyEdit);

    m_usernameEdit = new QLineEdit(this);
    form->addRow(tr("Username:"), m_usernameEdit);

    m_domainEdit = new QLineEdit(this);
    form->addRow(tr("Domain:"), m_domainEdit);

    m_authIdEdit = new QLineEdit(this);
    form->addRow(tr("Auth ID:"), m_authIdEdit);

    m_passwordEdit = new QLineEdit(this);
    m_passwordEdit->setEchoMode(QLineEdit::Password);
    form->addRow(tr("Password:"), m_passwordEdit);

    m_displayNameEdit = new QLineEdit(this);
    form->addRow(tr("Display Name:"), m_displayNameEdit);

    m_dialingPrefixEdit = new QLineEdit(this);
    form->addRow(tr("Dialing Prefix:"), m_dialingPrefixEdit);

    m_dialPlanEdit = new QLineEdit(this);
    form->addRow(tr("Dial Plan:"), m_dialPlanEdit);

    m_publicAddrEdit = new QLineEdit(this);
    form->addRow(tr("Public Address:"), m_publicAddrEdit);

    m_portSpin = new QSpinBox(this);
    m_portSpin->setRange(1, 65535);
    m_portSpin->setValue(5060);
    form->addRow(tr("Port:"), m_portSpin);

    m_refreshSpin = new QSpinBox(this);
    m_refreshSpin->setRange(0, 86400);
    m_refreshSpin->setValue(300);
    m_refreshSpin->setSuffix(tr(" s"));
    form->addRow(tr("Register Refresh:"), m_refreshSpin);

    m_keepAliveSpin = new QSpinBox(this);
    m_keepAliveSpin->setRange(0, 3600);
    m_keepAliveSpin->setValue(15);
    m_keepAliveSpin->setSuffix(tr(" s"));
    form->addRow(tr("Keep Alive:"), m_keepAliveSpin);

    m_transportCombo = new QComboBox(this);
    m_transportCombo->addItem(tr("UDP"), QStringLiteral("udp"));
    m_transportCombo->addItem(tr("TCP"), QStringLiteral("tcp"));
    m_transportCombo->addItem(tr("TLS"), QStringLiteral("tls"));
    form->addRow(tr("Transport:"), m_transportCombo);

    m_srtpCombo = new QComboBox(this);
    m_srtpCombo->addItem(tr("Disabled"), QStringLiteral("disabled"));
    m_srtpCombo->addItem(tr("Optional"), QStringLiteral("optional"));
    m_srtpCombo->addItem(tr("Mandatory"), QStringLiteral("mandatory"));
    form->addRow(tr("SRTP:"), m_srtpCombo);

    m_publishCheck = new QCheckBox(tr("Publish Presence"), this);
    form->addRow(m_publishCheck);

    m_iceCheck = new QCheckBox(tr("Enable ICE"), this);
    form->addRow(m_iceCheck);

    m_allowRewriteCheck = new QCheckBox(tr("Allow Rewrite"), this);
    form->addRow(m_allowRewriteCheck);

    m_hideCidCheck = new QCheckBox(tr("Hide Caller ID"), this);
    form->addRow(m_hideCidCheck);

    mainLayout->addLayout(form);

    m_buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(m_buttonBox, &QDialogButtonBox::accepted,
            this, &AccountDialog::onAccepted);
    connect(m_buttonBox, &QDialogButtonBox::rejected,
            this, &QDialog::reject);
    mainLayout->addWidget(m_buttonBox);

    resize(420, 600);
}

} // namespace macrosip
