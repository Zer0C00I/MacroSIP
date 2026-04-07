#pragma once
#include <QObject>
#include <QMap>
#include <QMutex>
#include "sip/SipTypes.h"
#include "sip/SipCall.h"
#include "sip/SipAccount.h"

#ifdef PJSIP_ENABLED
#include <pjsua-lib/pjsua.h>
#endif

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
    void hangupAllCalls();
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

#ifdef PJSIP_ENABLED
    pjsua_transport_id m_transportUdp = PJSUA_INVALID_ID;
    pjsua_transport_id m_transportTcp = PJSUA_INVALID_ID;
    pjsua_transport_id m_transportTls = PJSUA_INVALID_ID;

    /* ---- Static PJSIP callbacks (fire on PJSIP worker thread) ---- */
    static void onRegState2(pjsua_acc_id accId, pjsua_reg_info *info);
    static void onIncomingCall(pjsua_acc_id accId, pjsua_call_id callId,
                               pjsip_rx_data *rdata);
    static void onCallState(pjsua_call_id callId, pjsip_event *e);
    static void onCallMediaState(pjsua_call_id callId);
    static void onBuddyState(pjsua_buddy_id buddyId);
    static void onPager2(pjsua_call_id callId,
                         const pj_str_t *from, const pj_str_t *to,
                         const pj_str_t *contact,
                         const pj_str_t *mimeType, const pj_str_t *body,
                         pjsip_rx_data *rdata, pjsua_acc_id accId);
    static void onPagerStatus2(pjsua_call_id callId,
                               const pj_str_t *to, const pj_str_t *body,
                               void *userData, pjsip_status_code status,
                               const pj_str_t *reason,
                               pjsip_tx_data *tdata,
                               pjsip_rx_data *rdata,
                               pjsua_acc_id accId);
    static void onMwiInfo(pjsua_acc_id accId, pjsua_mwi_info *mwiInfo);

    // Helper: the singleton instance accessible from static callbacks
    static SipManager *s_instance;
#endif
};

} // namespace macrosip
