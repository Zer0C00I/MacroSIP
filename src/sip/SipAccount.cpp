#include "sip/SipAccount.h"
#include <QDebug>

namespace macrosip {

SipAccount::SipAccount(QObject *parent)
    : QObject(parent)
{
}

SipAccount::~SipAccount()
{
    unregisterAccount();
}

bool SipAccount::configure(const Account &acct)
{
    if (!acct.isValid()) {
        qWarning() << "SipAccount::configure: invalid account config";
        return false;
    }
    m_config = acct;
    return true;
}

bool SipAccount::registerAccount()
{
    if (!m_config.isValid()) {
        qWarning() << "SipAccount::registerAccount: no valid config";
        return false;
    }

#ifdef PJSIP_ENABLED
    // Real PJSIP registration would go here:
    // pjsua_acc_config cfg;
    // pjsua_acc_config_default(&cfg);
    // ... configure from m_config ...
    // pj_status_t status = pjsua_acc_add(&cfg, PJ_TRUE, &m_accountId);
    // return status == PJ_SUCCESS;
    return false;
#else
    // Stub: simulate successful registration
    m_accountId = 1;
    m_regState = RegistrationState::Registered;
    emit registrationStateChanged(m_regState, 200,
                                  QStringLiteral("OK (stub)"));
    return true;
#endif
}

void SipAccount::unregisterAccount()
{
    if (m_accountId < 0) {
        return;
    }

#ifdef PJSIP_ENABLED
    // pjsua_acc_del(m_accountId);
#endif

    m_regState = RegistrationState::Unregistered;
    int prevId = m_accountId;
    m_accountId = -1;
    Q_UNUSED(prevId)
    emit registrationStateChanged(m_regState, 0,
                                  QStringLiteral("Unregistered"));
}

RegistrationState SipAccount::registrationState() const
{
    return m_regState;
}

int SipAccount::accountId() const
{
    return m_accountId;
}

bool SipAccount::isRegistered() const
{
    return m_regState == RegistrationState::Registered;
}

} // namespace macrosip
