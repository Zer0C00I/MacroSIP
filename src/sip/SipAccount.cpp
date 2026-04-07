#include "sip/SipAccount.h"
#include <QDebug>

#ifdef PJSIP_ENABLED
#include <pjsua-lib/pjsua.h>
#endif

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
    pjsua_acc_config cfg;
    pjsua_acc_config_default(&cfg);

    // Build SIP ID: "Display Name" <sip:user@domain>
    QString sipId;
    if (!m_config.displayName.isEmpty()) {
        sipId = QStringLiteral("\"%1\" ").arg(m_config.displayName);
    }
    sipId += QStringLiteral("<sip:%1@%2>")
                 .arg(m_config.username,
                      m_config.domain.isEmpty() ? m_config.server
                                                : m_config.domain);
    QByteArray sipIdBytes = sipId.toUtf8();
    cfg.id = pj_str(sipIdBytes.data());

    // Registrar URI
    QString regUri;
    if (!m_config.server.isEmpty()) {
        regUri = QStringLiteral("sip:%1").arg(m_config.server);
        // Append transport suffix
        if (m_config.transport == QLatin1String("tcp")) {
            regUri += QStringLiteral(";transport=tcp");
        } else if (m_config.transport == QLatin1String("tls")) {
            regUri = QStringLiteral("sips:%1").arg(m_config.server);
        }
    }
    QByteArray regUriBytes = regUri.toUtf8();
    if (!regUri.isEmpty()) {
        cfg.reg_uri = pj_str(regUriBytes.data());
    }

    // Credentials
    cfg.cred_count = 1;
    QByteArray realmBytes = (m_config.domain.isEmpty() ? QStringLiteral("*")
                                                       : m_config.domain)
                                .toUtf8();
    cfg.cred_info[0].realm = pj_str(realmBytes.data());
    static char digestScheme[] = "digest";
    cfg.cred_info[0].scheme = pj_str(digestScheme);

    QByteArray authUser = (m_config.authID.isEmpty() ? m_config.username
                                                     : m_config.authID)
                              .toUtf8();
    cfg.cred_info[0].username = pj_str(authUser.data());
    cfg.cred_info[0].data_type = PJSIP_CRED_DATA_PLAIN_PASSWD;
    QByteArray passBytes = m_config.password.toUtf8();
    cfg.cred_info[0].data = pj_str(passBytes.data());

    // Proxy
    QByteArray proxyBytes;
    if (!m_config.proxy.isEmpty()) {
        QString proxyUri = QStringLiteral("sip:%1;lr").arg(m_config.proxy);
        proxyBytes = proxyUri.toUtf8();
        cfg.proxy[0] = pj_str(proxyBytes.data());
        cfg.proxy_cnt = 1;
    }

    // Registration refresh
    if (m_config.registerRefresh > 0) {
        cfg.reg_timeout = static_cast<unsigned>(m_config.registerRefresh);
    }

    // Keep-alive
    if (m_config.keepAlive > 0) {
        cfg.ka_interval = static_cast<unsigned>(m_config.keepAlive);
    }

    // Publish presence
    cfg.publish_enabled = m_config.publish ? PJ_TRUE : PJ_FALSE;

    // ICE
    // (ICE is set at media-config level, not per-account, handled in SipManager)

    // SRTP
    if (m_config.srtp == QLatin1String("mandatory")) {
        cfg.use_srtp = PJMEDIA_SRTP_MANDATORY;
    } else if (m_config.srtp == QLatin1String("optional")) {
        cfg.use_srtp = PJMEDIA_SRTP_OPTIONAL;
    } else {
        cfg.use_srtp = PJMEDIA_SRTP_DISABLED;
    }
    cfg.srtp_secure_signaling = 0;

    // Allow contact rewrite
    cfg.allow_contact_rewrite = m_config.allowRewrite ? PJ_TRUE : PJ_FALSE;

    // Register the account
    pjsua_acc_id accId = PJSUA_INVALID_ID;
    pj_status_t status = pjsua_acc_add(&cfg, PJ_TRUE, &accId);
    if (status != PJ_SUCCESS) {
        qWarning() << "SipAccount::registerAccount: pjsua_acc_add failed:"
                    << status;
        return false;
    }

    m_accountId = static_cast<int>(accId);
    m_regState = RegistrationState::Registering;
    emit registrationStateChanged(m_regState, 0,
                                  QStringLiteral("Registering..."));
    return true;
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
    pjsua_acc_del(static_cast<pjsua_acc_id>(m_accountId));
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

void SipAccount::handleRegistrationState(RegistrationState state, int code,
                                          const QString &reason)
{
    m_regState = state;
    emit registrationStateChanged(state, code, reason);
}

} // namespace macrosip
