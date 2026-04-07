#include "sip/SipCall.h"
#include <QDebug>

#ifdef PJSIP_ENABLED
#include <pjsua-lib/pjsua.h>
#endif

namespace macrosip {

SipCall::SipCall(QObject *parent)
    : QObject(parent)
{
}

SipCall::~SipCall()
{
    if (m_state != CallState::Idle && m_state != CallState::Disconnected) {
        hangup();
    }
}

int SipCall::callId() const
{
    return m_callId;
}

CallState SipCall::state() const
{
    return m_state;
}

MediaStatus SipCall::mediaStatus() const
{
    return m_mediaStatus;
}

const CallUserData &SipCall::userData() const
{
    return m_userData;
}

void SipCall::setCallId(int id)
{
    m_callId = id;
}

void SipCall::setUserData(const CallUserData &data)
{
    m_userData = data;
}

void SipCall::handleStateChange(CallState newState)
{
    m_state = newState;
    emit stateChanged(newState);
}

void SipCall::handleMediaStatusChange(MediaStatus newStatus)
{
    m_mediaStatus = newStatus;
    emit mediaStatusChanged(newStatus);
}

bool SipCall::answer(int code)
{
    if (m_callId < 0) {
        return false;
    }

#ifdef PJSIP_ENABLED
    pj_status_t st = pjsua_call_answer(
        static_cast<pjsua_call_id>(m_callId),
        static_cast<unsigned>(code), nullptr, nullptr);
    return st == PJ_SUCCESS;
#else
    Q_UNUSED(code)
    m_state = CallState::Confirmed;
    m_mediaStatus = MediaStatus::Active;
    emit stateChanged(m_state);
    emit mediaStatusChanged(m_mediaStatus);
    return true;
#endif
}

bool SipCall::hangup(int code)
{
    if (m_callId < 0) {
        return false;
    }

#ifdef PJSIP_ENABLED
    pj_status_t st = pjsua_call_hangup(
        static_cast<pjsua_call_id>(m_callId),
        static_cast<unsigned>(code), nullptr, nullptr);
    if (st == PJ_SUCCESS) {
        m_state = CallState::Disconnected;
        m_mediaStatus = MediaStatus::None;
    }
    return st == PJ_SUCCESS;
#else
    Q_UNUSED(code)
    m_state = CallState::Disconnected;
    m_mediaStatus = MediaStatus::None;
    emit stateChanged(m_state);
    emit mediaStatusChanged(m_mediaStatus);
    return true;
#endif
}

bool SipCall::hold()
{
    if (m_callId < 0) {
        return false;
    }

#ifdef PJSIP_ENABLED
    pj_status_t st = pjsua_call_set_hold(
        static_cast<pjsua_call_id>(m_callId), nullptr);
    return st == PJ_SUCCESS;
#else
    m_mediaStatus = MediaStatus::LocalHold;
    emit mediaStatusChanged(m_mediaStatus);
    return true;
#endif
}

bool SipCall::unhold()
{
    if (m_callId < 0) {
        return false;
    }

#ifdef PJSIP_ENABLED
    pj_status_t st = pjsua_call_reinvite(
        static_cast<pjsua_call_id>(m_callId), PJ_TRUE, nullptr);
    return st == PJ_SUCCESS;
#else
    m_mediaStatus = MediaStatus::Active;
    emit mediaStatusChanged(m_mediaStatus);
    return true;
#endif
}

bool SipCall::transfer(const QString &target)
{
    if (m_callId < 0 || target.isEmpty()) {
        return false;
    }

#ifdef PJSIP_ENABLED
    QByteArray destBytes = target.toUtf8();
    pj_str_t dest = pj_str(destBytes.data());
    pj_status_t st = pjsua_call_xfer(
        static_cast<pjsua_call_id>(m_callId), &dest, nullptr);
    return st == PJ_SUCCESS;
#else
    emit transferStatusChanged(200, QStringLiteral("Transfer OK (stub)"));
    return true;
#endif
}

bool SipCall::sendDtmf(const QString &digits)
{
    if (m_callId < 0 || digits.isEmpty()) {
        return false;
    }

#ifdef PJSIP_ENABLED
    QByteArray dtmfBytes = digits.toUtf8();
    pj_str_t d = pj_str(dtmfBytes.data());
    pj_status_t st = pjsua_call_dial_dtmf(
        static_cast<pjsua_call_id>(m_callId), &d);
    return st == PJ_SUCCESS;
#else
    for (const QChar &ch : digits) {
        emit dtmfReceived(QString(ch));
    }
    return true;
#endif
}

bool SipCall::startRecording(const QString &path)
{
    if (m_callId < 0 || path.isEmpty()) {
        return false;
    }

#ifdef PJSIP_ENABLED
    if (m_recorderId != PJSUA_INVALID_ID) {
        return false;  // Already recording
    }

    QByteArray pathBytes = path.toUtf8();
    pj_str_t filename = pj_str(pathBytes.data());

    pj_status_t st = pjsua_recorder_create(&filename, 0, nullptr, 0, 0,
                                             &m_recorderId);
    if (st != PJ_SUCCESS) {
        qWarning() << "SipCall::startRecording: recorder create failed:" << st;
        return false;
    }

    // Connect call audio to the recorder
    pjsua_call_info ci;
    if (pjsua_call_get_info(static_cast<pjsua_call_id>(m_callId), &ci) ==
        PJ_SUCCESS) {
        pjsua_conf_port_id recPort = pjsua_recorder_get_conf_port(m_recorderId);
        pjsua_conf_connect(ci.conf_slot, recPort);
        pjsua_conf_connect(0, recPort);  // Also record local mic
    }

    return true;
#else
    qDebug() << "SipCall::startRecording (stub):" << path;
    m_recorderId = 1;
    return true;
#endif
}

void SipCall::stopRecording()
{
#ifdef PJSIP_ENABLED
    if (m_recorderId == PJSUA_INVALID_ID) {
        return;
    }
    pjsua_recorder_destroy(m_recorderId);
    m_recorderId = PJSUA_INVALID_ID;
#else
    if (m_recorderId < 0) {
        return;
    }
    qDebug() << "SipCall::stopRecording (stub)";
    m_recorderId = -1;
#endif
}

} // namespace macrosip
