#pragma once
#include <QObject>
#include <QMap>
#include <QMutex>
#include "sip/SipTypes.h"
#include "sip/SipCall.h"
#include "sip/SipAccount.h"

namespace macrosip {

class SipManager : public QObject {
    Q_OBJECT
public:
    explicit SipManager(QObject *parent = nullptr);
    ~SipManager() override;

    bool initialize();
    void shutdown();
    bool isRunning() const;

    // Account management
    SipAccount *addAccount(const Account &config);
    void removeAccount(int accountId);
    SipAccount *findAccount(int accountId) const;

    // Call management
    SipCall *makeCall(const QString &number, int accountId = -1);
    SipCall *findCall(int callId) const;
    void answerCall(int callId, int code = 200);
    void hangupCall(int callId, int code = 0);
    void holdCall(int callId);
    void unholdCall(int callId);
    void transferCall(int callId, const QString &target);
    void sendDtmf(int callId, const QString &digits);
    void mergeConference(int callId1, int callId2);

    // Media
    void setInputVolume(int level);
    void setOutputVolume(int level);
    void setMuteInput(bool mute);
    void setMuteOutput(bool mute);
    QStringList audioInputDevices() const;
    QStringList audioOutputDevices() const;
    bool setAudioInputDevice(const QString &device);
    bool setAudioOutputDevice(const QString &device);

    // Presence
    void subscribePresence(const QString &uri);
    void unsubscribePresence(const QString &uri);
    void publishPresence(PresenceStatus status);

    // Codec configuration
    void setCodecPriority(const QString &codecId, int priority);
    QStringList availableCodecs() const;

signals:
    void initialized();
    void shutdownComplete();
    void incomingCall(int callId, const QString &from, const QString &name);
    void callStateChanged(int callId, CallState state);
    void callMediaStateChanged(int callId, MediaStatus status);
    void registrationStateChanged(int accountId, RegistrationState state,
                                  int code, const QString &reason);
    void buddyStateChanged(const QString &uri, PresenceStatus status);
    void messageReceived(const QString &from, const QString &to,
                         const QString &body);
    void messageStatus(const QString &to, int status);
    void mwiNotification(int accountId, int newMessages, int oldMessages);
    void audioDevicesChanged();

private:
    bool m_running = false;
    mutable QMutex m_mutex;
    QMap<int, SipAccount *> m_accounts;
    QMap<int, SipCall *> m_calls;

    void initPjsip();
    void cleanupPjsip();
    void setupCallbacks();
};

} // namespace macrosip
