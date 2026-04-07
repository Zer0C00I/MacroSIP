#pragma once
#include <QObject>
#include "sip/SipTypes.h"

#ifdef PJSIP_ENABLED
#include <pjsua-lib/pjsua.h>
#endif

namespace macrosip {

class SipCall : public QObject {
    Q_OBJECT
public:
    explicit SipCall(QObject *parent = nullptr);
    ~SipCall() override;

    int callId() const;
    CallState state() const;
    MediaStatus mediaStatus() const;
    const CallUserData &userData() const;

    void setCallId(int id);
    void setUserData(const CallUserData &data);

    bool answer(int code = 200);
    bool hangup(int code = 0);
    bool hold();
    bool unhold();
    bool transfer(const QString &target);
    bool sendDtmf(const QString &digits);
    bool startRecording(const QString &path);
    void stopRecording();

    /// Called from SipManager callbacks to update internal state
    void handleStateChange(CallState newState);
    void handleMediaStatusChange(MediaStatus newStatus);

signals:
    void stateChanged(CallState newState);
    void mediaStatusChanged(MediaStatus status);
    void dtmfReceived(const QString &digit);
    void transferStatusChanged(int statusCode, const QString &reason);

private:
    int m_callId = -1;
    CallState m_state = CallState::Idle;
    MediaStatus m_mediaStatus = MediaStatus::None;
    CallUserData m_userData;

#ifdef PJSIP_ENABLED
    pjsua_recorder_id m_recorderId = PJSUA_INVALID_ID;
#else
    int m_recorderId = -1;
#endif
};

} // namespace macrosip
