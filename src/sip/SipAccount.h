#pragma once
#include <QObject>
#include "sip/SipTypes.h"
#include "models/Account.h"

namespace macrosip {

class SipAccount : public QObject {
    Q_OBJECT
public:
    explicit SipAccount(QObject *parent = nullptr);
    ~SipAccount() override;

    bool configure(const Account &acct);
    bool registerAccount();
    void unregisterAccount();

    RegistrationState registrationState() const;
    int accountId() const;
    bool isRegistered() const;

signals:
    void registrationStateChanged(RegistrationState state, int code, const QString &reason);

private:
    int m_accountId = -1;
    RegistrationState m_regState = RegistrationState::Unregistered;
    Account m_config;
};

} // namespace macrosip
