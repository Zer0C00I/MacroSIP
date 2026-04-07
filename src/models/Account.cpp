#include "models/Account.h"

namespace macrosip {

bool Account::isValid() const
{
    return !server.isEmpty() && !username.isEmpty();
}

QString Account::sipUri() const
{
    const QString &d = domain.isEmpty() ? server : domain;
    return QStringLiteral("sip:") + username + QStringLiteral("@") + d;
}

void Account::clear()
{
    label.clear();
    server.clear();
    proxy.clear();
    username.clear();
    domain.clear();
    authID.clear();
    password.clear();
    displayName.clear();
    publicAddr.clear();
    dialingPrefix.clear();
    dialPlan.clear();
    srtp.clear();
    transport.clear();
    port = 5060;
    registerRefresh = 300;
    keepAlive = 15;
    publish = false;
    ice = false;
    allowRewrite = false;
    hideCID = false;
}

} // namespace macrosip
