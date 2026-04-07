#include "sip/SipCall.h"
#include <QDebug>

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

bool SipCall::answer(int code)
{
    if (m_callId < 0) {
        return false;
    }

#ifdef PJSIP_ENABLED
    // pj_status_t st = pjsua_call_answer(
    //     static_cast<pjsua_call_id>(m_callId),
    //     static_cast<unsigned>(code), nullptr, nullptr);
    // return st == PJ_SUCCESS;
    Q_UNUSED(code)
    return false;
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
    // pj_status_t st = pjsua_call_hangup(
    //     static_cast<pjsua_call_id>(m_callId),
    //     static_cast<unsigned>(code), nullptr, nullptr);
    // return st == PJ_SUCCESS;
    Q_UNUSED(code)
    return false;
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
    // pj_status_t st = pjsua_call_set_hold(
    //     static_cast<pjsua_call_id>(m_callId), nullptr);
    // return st == PJ_SUCCESS;
    return false;
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
    // pj_status_t st = pjsua_call_reinvite(
    //     static_cast<pjsua_call_id>(m_callId), PJ_TRUE, nullptr);
    // return st == PJ_SUCCESS;
    return false;
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
    // pj_str_t dest = pj_str(target.toUtf8().data());
    // pj_status_t st = pjsua_call_xfer(
    //     static_cast<pjsua_call_id>(m_callId), &dest, nullptr);
    // return st == PJ_SUCCESS;
    Q_UNUSED(target)
    return false;
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
    // pj_str_t d = pj_str(digits.toUtf8().data());
    // pj_status_t st = pjsua_call_dial_dtmf(
    //     static_cast<pjsua_call_id>(m_callId), &d);
    // return st == PJ_SUCCESS;
    Q_UNUSED(digits)
    return false;
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
    // Create WAV recorder, connect call audio
    Q_UNUSED(path)
    return false;
#else
    qDebug() << "SipCall::startRecording (stub):" << path;
    m_recorderId = 1;
    return true;
#endif
}

void SipCall::stopRecording()
{
    if (m_recorderId < 0) {
        return;
    }

#ifdef PJSIP_ENABLED
    // Destroy WAV recorder
#endif

    qDebug() << "SipCall::stopRecording (stub)";
    m_recorderId = -1;
}

} // namespace macrosip
