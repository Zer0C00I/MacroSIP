#include "models/Settings.h"
#include <QStandardPaths>
#include <QDir>

namespace macrosip {

AppSettings &AppSettings::instance()
{
    static AppSettings s;
    return s;
}

QString AppSettings::configDir() const
{
    return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
           + QStringLiteral("/MacroSIP");
}

QString AppSettings::contactsFile() const
{
    return configDir() + QStringLiteral("/contacts.csv");
}

QString AppSettings::callsFile() const
{
    return configDir() + QStringLiteral("/calls.csv");
}

void AppSettings::loadAccount(QSettings &s, const QString &group, Account &acc)
{
    s.beginGroup(group);
    acc.label          = s.value(QStringLiteral("label")).toString();
    acc.server         = s.value(QStringLiteral("server")).toString();
    acc.proxy          = s.value(QStringLiteral("proxy")).toString();
    acc.username       = s.value(QStringLiteral("username")).toString();
    acc.domain         = s.value(QStringLiteral("domain")).toString();
    acc.authID         = s.value(QStringLiteral("authID")).toString();
    acc.password       = s.value(QStringLiteral("password")).toString();
    acc.displayName    = s.value(QStringLiteral("displayName")).toString();
    acc.publicAddr     = s.value(QStringLiteral("publicAddr")).toString();
    acc.dialingPrefix  = s.value(QStringLiteral("dialingPrefix")).toString();
    acc.dialPlan       = s.value(QStringLiteral("dialPlan")).toString();
    acc.srtp           = s.value(QStringLiteral("srtp"), QStringLiteral("disabled")).toString();
    acc.transport      = s.value(QStringLiteral("transport"), QStringLiteral("udp")).toString();
    acc.port           = s.value(QStringLiteral("port"), 5060).toInt();
    acc.registerRefresh = s.value(QStringLiteral("registerRefresh"), 300).toInt();
    acc.keepAlive      = s.value(QStringLiteral("keepAlive"), 15).toInt();
    acc.publish        = s.value(QStringLiteral("publish"), false).toBool();
    acc.ice            = s.value(QStringLiteral("ice"), false).toBool();
    acc.allowRewrite   = s.value(QStringLiteral("allowRewrite"), false).toBool();
    acc.hideCID        = s.value(QStringLiteral("hideCID"), false).toBool();
    s.endGroup();
}

void AppSettings::saveAccount(QSettings &s, const QString &group, const Account &acc)
{
    s.beginGroup(group);
    s.setValue(QStringLiteral("label"),           acc.label);
    s.setValue(QStringLiteral("server"),          acc.server);
    s.setValue(QStringLiteral("proxy"),           acc.proxy);
    s.setValue(QStringLiteral("username"),        acc.username);
    s.setValue(QStringLiteral("domain"),          acc.domain);
    s.setValue(QStringLiteral("authID"),          acc.authID);
    s.setValue(QStringLiteral("password"),        acc.password);
    s.setValue(QStringLiteral("displayName"),     acc.displayName);
    s.setValue(QStringLiteral("publicAddr"),      acc.publicAddr);
    s.setValue(QStringLiteral("dialingPrefix"),   acc.dialingPrefix);
    s.setValue(QStringLiteral("dialPlan"),        acc.dialPlan);
    s.setValue(QStringLiteral("srtp"),            acc.srtp);
    s.setValue(QStringLiteral("transport"),       acc.transport);
    s.setValue(QStringLiteral("port"),            acc.port);
    s.setValue(QStringLiteral("registerRefresh"), acc.registerRefresh);
    s.setValue(QStringLiteral("keepAlive"),       acc.keepAlive);
    s.setValue(QStringLiteral("publish"),         acc.publish);
    s.setValue(QStringLiteral("ice"),             acc.ice);
    s.setValue(QStringLiteral("allowRewrite"),    acc.allowRewrite);
    s.setValue(QStringLiteral("hideCID"),         acc.hideCID);
    s.endGroup();
}

void AppSettings::load()
{
    QDir().mkpath(configDir());
    QSettings s(configDir() + QStringLiteral("/settings.ini"), QSettings::IniFormat);

    loadAccount(s, QStringLiteral("Account"), account);
    loadAccount(s, QStringLiteral("AccountLocal"), accountLocal);

    s.beginGroup(QStringLiteral("General"));
    singleMode = s.value(QStringLiteral("singleMode"), true).toBool();
    s.endGroup();

    // Audio
    s.beginGroup(QStringLiteral("Audio"));
    audioCodecs        = s.value(QStringLiteral("codecs"), QStringLiteral("PCMA/8000/1 PCMU/8000/1")).toString();
    vad                = s.value(QStringLiteral("vad"), false).toBool();
    ec                 = s.value(QStringLiteral("ec"), true).toBool();
    forceCodec         = s.value(QStringLiteral("forceCodec"), false).toBool();
    audioInputDevice   = s.value(QStringLiteral("inputDevice")).toString();
    audioOutputDevice  = s.value(QStringLiteral("outputDevice")).toString();
    audioRingDevice    = s.value(QStringLiteral("ringDevice")).toString();
    ringtone           = s.value(QStringLiteral("ringtone")).toString();
    opusStereo         = s.value(QStringLiteral("opusStereo"), false).toBool();
    micAmplification   = s.value(QStringLiteral("micAmplification"), false).toBool();
    swLevelAdjustment  = s.value(QStringLiteral("swLevelAdjustment"), false).toBool();
    localDTMF          = s.value(QStringLiteral("localDTMF"), true).toBool();
    s.endGroup();

    // Network
    s.beginGroup(QStringLiteral("Network"));
    stun        = s.value(QStringLiteral("stun")).toString();
    dnsSrvNs    = s.value(QStringLiteral("dnsSrvNs")).toString();
    enableSTUN  = s.value(QStringLiteral("enableSTUN"), false).toBool();
    dnsSrv      = s.value(QStringLiteral("dnsSrv"), false).toBool();
    rport       = s.value(QStringLiteral("rport"), true).toBool();
    sourcePort  = s.value(QStringLiteral("sourcePort"), 5060).toInt();
    rtpPortMin  = s.value(QStringLiteral("rtpPortMin"), 5000).toInt();
    rtpPortMax  = s.value(QStringLiteral("rtpPortMax"), 5100).toInt();
    s.endGroup();

    // Call Features
    s.beginGroup(QStringLiteral("CallFeatures"));
    autoAnswer       = s.value(QStringLiteral("autoAnswer"), false).toBool();
    autoAnswerDelay  = s.value(QStringLiteral("autoAnswerDelay"), 0).toInt();
    dnd              = s.value(QStringLiteral("dnd"), false).toBool();
    callWaiting      = s.value(QStringLiteral("callWaiting"), true).toBool();
    forwardingNumber = s.value(QStringLiteral("forwardingNumber")).toString();
    forwardingDelay  = s.value(QStringLiteral("forwardingDelay"), 0).toInt();
    denyIncoming     = s.value(QStringLiteral("denyIncoming")).toString();
    s.endGroup();

    // Feature Codes
    s.beginGroup(QStringLiteral("FeatureCodes"));
    featureCodeCP       = s.value(QStringLiteral("featureCodeCP")).toString();
    featureCodeBT       = s.value(QStringLiteral("featureCodeBT")).toString();
    featureCodeAT       = s.value(QStringLiteral("featureCodeAT")).toString();
    enableFeatureCodeCP = s.value(QStringLiteral("enableFeatureCodeCP"), false).toBool();
    enableFeatureCodeBT = s.value(QStringLiteral("enableFeatureCodeBT"), false).toBool();
    enableFeatureCodeAT = s.value(QStringLiteral("enableFeatureCodeAT"), false).toBool();
    s.endGroup();

    // Recording
    s.beginGroup(QStringLiteral("Recording"));
    recordingPath = s.value(QStringLiteral("recordingPath")).toString();
    autoRecording = s.value(QStringLiteral("autoRecording"), false).toBool();
    s.endGroup();

    // UI
    s.beginGroup(QStringLiteral("UI"));
    mainX                  = s.value(QStringLiteral("mainX"), 0).toInt();
    mainY                  = s.value(QStringLiteral("mainY"), 0).toInt();
    mainW                  = s.value(QStringLiteral("mainW"), 0).toInt();
    mainH                  = s.value(QStringLiteral("mainH"), 0).toInt();
    activeTab              = s.value(QStringLiteral("activeTab"), 0).toInt();
    alwaysOnTop            = s.value(QStringLiteral("alwaysOnTop"), false).toBool();
    bringToFrontOnIncoming = s.value(QStringLiteral("bringToFrontOnIncoming"), true).toBool();
    langPack               = s.value(QStringLiteral("langPack")).toString();
    s.endGroup();

    // Diagnostics
    s.beginGroup(QStringLiteral("Diagnostics"));
    enableLog   = s.value(QStringLiteral("enableLog"), false).toBool();
    crashReport = s.value(QStringLiteral("crashReport"), false).toBool();
    s.endGroup();

    // Shortcuts
    shortcuts.clear();
    int scCount = s.beginReadArray(QStringLiteral("Shortcuts"));
    for (int i = 0; i < scCount; ++i) {
        s.setArrayIndex(i);
        Shortcut sc;
        sc.label  = s.value(QStringLiteral("label")).toString();
        sc.number = s.value(QStringLiteral("number")).toString();
        sc.type   = s.value(QStringLiteral("type"), 0).toInt();
        shortcuts.append(sc);
    }
    s.endArray();

    // Headset
    s.beginGroup(QStringLiteral("Headset"));
    headsetSupport = s.value(QStringLiteral("headsetSupport"), false).toBool();
    s.endGroup();
}

void AppSettings::save()
{
    QDir().mkpath(configDir());
    QSettings s(configDir() + QStringLiteral("/settings.ini"), QSettings::IniFormat);

    saveAccount(s, QStringLiteral("Account"), account);
    saveAccount(s, QStringLiteral("AccountLocal"), accountLocal);

    s.beginGroup(QStringLiteral("General"));
    s.setValue(QStringLiteral("singleMode"), singleMode);
    s.endGroup();

    // Audio
    s.beginGroup(QStringLiteral("Audio"));
    s.setValue(QStringLiteral("codecs"),            audioCodecs);
    s.setValue(QStringLiteral("vad"),               vad);
    s.setValue(QStringLiteral("ec"),                ec);
    s.setValue(QStringLiteral("forceCodec"),        forceCodec);
    s.setValue(QStringLiteral("inputDevice"),       audioInputDevice);
    s.setValue(QStringLiteral("outputDevice"),      audioOutputDevice);
    s.setValue(QStringLiteral("ringDevice"),        audioRingDevice);
    s.setValue(QStringLiteral("ringtone"),          ringtone);
    s.setValue(QStringLiteral("opusStereo"),        opusStereo);
    s.setValue(QStringLiteral("micAmplification"),  micAmplification);
    s.setValue(QStringLiteral("swLevelAdjustment"), swLevelAdjustment);
    s.setValue(QStringLiteral("localDTMF"),         localDTMF);
    s.endGroup();

    // Network
    s.beginGroup(QStringLiteral("Network"));
    s.setValue(QStringLiteral("stun"),       stun);
    s.setValue(QStringLiteral("dnsSrvNs"),   dnsSrvNs);
    s.setValue(QStringLiteral("enableSTUN"), enableSTUN);
    s.setValue(QStringLiteral("dnsSrv"),     dnsSrv);
    s.setValue(QStringLiteral("rport"),      rport);
    s.setValue(QStringLiteral("sourcePort"), sourcePort);
    s.setValue(QStringLiteral("rtpPortMin"), rtpPortMin);
    s.setValue(QStringLiteral("rtpPortMax"), rtpPortMax);
    s.endGroup();

    // Call Features
    s.beginGroup(QStringLiteral("CallFeatures"));
    s.setValue(QStringLiteral("autoAnswer"),       autoAnswer);
    s.setValue(QStringLiteral("autoAnswerDelay"),  autoAnswerDelay);
    s.setValue(QStringLiteral("dnd"),              dnd);
    s.setValue(QStringLiteral("callWaiting"),      callWaiting);
    s.setValue(QStringLiteral("forwardingNumber"), forwardingNumber);
    s.setValue(QStringLiteral("forwardingDelay"),  forwardingDelay);
    s.setValue(QStringLiteral("denyIncoming"),     denyIncoming);
    s.endGroup();

    // Feature Codes
    s.beginGroup(QStringLiteral("FeatureCodes"));
    s.setValue(QStringLiteral("featureCodeCP"),       featureCodeCP);
    s.setValue(QStringLiteral("featureCodeBT"),       featureCodeBT);
    s.setValue(QStringLiteral("featureCodeAT"),       featureCodeAT);
    s.setValue(QStringLiteral("enableFeatureCodeCP"), enableFeatureCodeCP);
    s.setValue(QStringLiteral("enableFeatureCodeBT"), enableFeatureCodeBT);
    s.setValue(QStringLiteral("enableFeatureCodeAT"), enableFeatureCodeAT);
    s.endGroup();

    // Recording
    s.beginGroup(QStringLiteral("Recording"));
    s.setValue(QStringLiteral("recordingPath"), recordingPath);
    s.setValue(QStringLiteral("autoRecording"), autoRecording);
    s.endGroup();

    // UI
    s.beginGroup(QStringLiteral("UI"));
    s.setValue(QStringLiteral("mainX"),                  mainX);
    s.setValue(QStringLiteral("mainY"),                  mainY);
    s.setValue(QStringLiteral("mainW"),                  mainW);
    s.setValue(QStringLiteral("mainH"),                  mainH);
    s.setValue(QStringLiteral("activeTab"),              activeTab);
    s.setValue(QStringLiteral("alwaysOnTop"),            alwaysOnTop);
    s.setValue(QStringLiteral("bringToFrontOnIncoming"), bringToFrontOnIncoming);
    s.setValue(QStringLiteral("langPack"),               langPack);
    s.endGroup();

    // Diagnostics
    s.beginGroup(QStringLiteral("Diagnostics"));
    s.setValue(QStringLiteral("enableLog"),   enableLog);
    s.setValue(QStringLiteral("crashReport"), crashReport);
    s.endGroup();

    // Shortcuts
    s.beginWriteArray(QStringLiteral("Shortcuts"), static_cast<int>(shortcuts.size()));
    for (qsizetype i = 0; i < shortcuts.size(); ++i) {
        s.setArrayIndex(static_cast<int>(i));
        s.setValue(QStringLiteral("label"),  shortcuts.at(i).label);
        s.setValue(QStringLiteral("number"), shortcuts.at(i).number);
        s.setValue(QStringLiteral("type"),   shortcuts.at(i).type);
    }
    s.endArray();

    // Headset
    s.beginGroup(QStringLiteral("Headset"));
    s.setValue(QStringLiteral("headsetSupport"), headsetSupport);
    s.endGroup();

    s.sync();
}

} // namespace macrosip
