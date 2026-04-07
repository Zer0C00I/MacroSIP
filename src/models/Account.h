#pragma once
#include <QString>

namespace macrosip {

struct Account {
    QString label;
    QString server;
    QString proxy;
    QString username;
    QString domain;
    QString authID;
    QString password;
    QString displayName;
    QString publicAddr;
    QString dialingPrefix;
    QString dialPlan;
    QString srtp;        // "disabled", "optional", "mandatory"
    QString transport;   // "udp", "tcp", "tls"
    int port = 5060;
    int registerRefresh = 300;
    int keepAlive = 15;
    bool publish = false;
    bool ice = false;
    bool allowRewrite = false;
    bool hideCID = false;

    bool isValid() const;
    QString sipUri() const;
    void clear();
};

} // namespace macrosip
