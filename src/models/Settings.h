#pragma once
#include <QString>
#include <QList>
#include <QSettings>
#include "models/Account.h"

namespace macrosip {

struct Shortcut {
    QString label;
    QString number;
    int type = 0;
};

class AppSettings {
public:
    static AppSettings &instance();

    void load();
    void save();

    // SIP Accounts
    Account account;
    Account accountLocal;
    bool singleMode = true;

    // Audio
    QString audioCodecs = QStringLiteral("PCMA/8000/1 PCMU/8000/1");
    bool vad = false;
    bool ec = true;
    bool forceCodec = false;
    QString audioInputDevice;
    QString audioOutputDevice;
    QString audioRingDevice;
    QString ringtone;
    bool opusStereo = false;
    bool micAmplification = false;
    bool swLevelAdjustment = false;
    bool localDTMF = true;

    // Network
    QString stun;
    QString dnsSrvNs;
    bool enableSTUN = false;
    bool dnsSrv = false;
    bool rport = true;
    int sourcePort = 5060;
    int rtpPortMin = 5000;
    int rtpPortMax = 5100;

    // Call Features
    bool autoAnswer = false;
    int autoAnswerDelay = 0;
    bool dnd = false;
    bool callWaiting = true;
    QString forwardingNumber;
    int forwardingDelay = 0;
    QString denyIncoming;

    // Feature Codes
    QString featureCodeCP;
    QString featureCodeBT;
    QString featureCodeAT;
    bool enableFeatureCodeCP = false;
    bool enableFeatureCodeBT = false;
    bool enableFeatureCodeAT = false;

    // Recording
    QString recordingPath;
    bool autoRecording = false;

    // UI
    int mainX = 0;
    int mainY = 0;
    int mainW = 0;
    int mainH = 0;
    int activeTab = 0;
    bool alwaysOnTop = false;
    bool bringToFrontOnIncoming = true;
    QString langPack;

    // Diagnostics
    bool enableLog = false;
    bool crashReport = false;

    // Shortcuts
    QList<Shortcut> shortcuts;

    // Headset
    bool headsetSupport = false;

    // Data paths
    QString configDir() const;
    QString contactsFile() const;
    QString callsFile() const;

private:
    AppSettings() = default;
    AppSettings(const AppSettings &) = delete;
    AppSettings &operator=(const AppSettings &) = delete;

    void loadAccount(QSettings &s, const QString &group, Account &acc);
    void saveAccount(QSettings &s, const QString &group, const Account &acc);
};

} // namespace macrosip
