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
    bool soundEvents = true;
    int volumeRing = 100;

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
    QString autoAnswerMode;          // "" / "button" / "header" / "all"
    bool dnd = false;
    bool callWaiting = true;
    QString forwardingNumber;
    int forwardingDelay = 0;
    QString denyIncoming;
    QString directoryOfUsers;
    QString defaultListAction;       // "" / "call" / "video" / "message"

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
    QString recordingFormat = QStringLiteral("mp3");  // "mp3" / "wav"

    // DTMF
    QString dtmfMethod;              // "" (auto) / "inband" / "rfc2833" / "sipinfo"

    // UI
    int mainX = 0;
    int mainY = 0;
    int mainW = 0;
    int mainH = 0;
    int activeTab = 0;
    bool alwaysOnTop = false;
    bool bringToFrontOnIncoming = true;
    QString langPack;
    bool randomPopupPosition = false;
    bool multiMonitor = false;
    bool disableNameLookup = false;

    // Diagnostics / Advanced
    bool enableLog = false;
    bool crashReport = false;
    bool enableLocalAccount = false;
    bool disableMessaging = false;
    bool handleIpChanges = false;
    bool handleMediaButtons = false;
    bool runAtStartup = false;
    QString updatesInterval;         // "" (weekly) / "daily" / "monthly" / "quarterly" / "never"

    // Video (stub — real PJSIP video is not implemented)
    bool videoEnabled = true;
    QString videoCodec;
    int videoBitrate = 0;
    bool videoH264 = false;
    bool videoH263 = false;
    bool videoVP8 = false;
    bool videoVP9 = false;
    QString cameraDevice;

    // Shortcuts
    QList<Shortcut> shortcuts;

    // Headset
    bool headsetSupport = false;

    // Data paths
    QString configDir() const;
    QString contactsFile() const;
    QString callsFile() const;

    // Desktop integration (Linux)
    static void setRunAtStartup(bool enable);

private:
    AppSettings() = default;
    AppSettings(const AppSettings &) = delete;
    AppSettings &operator=(const AppSettings &) = delete;

    void loadAccount(QSettings &s, const QString &group, Account &acc);
    void saveAccount(QSettings &s, const QString &group, const Account &acc);
};

} // namespace macrosip
