#include "sip/SipManager.h"
#include <QDebug>
#include <QMutexLocker>

namespace macrosip {

SipManager::SipManager(QObject *parent)
    : QObject(parent)
{
}

SipManager::~SipManager()
{
    shutdown();
}

// ---------------------------------------------------------------------------
// Initialization / Shutdown
// ---------------------------------------------------------------------------

bool SipManager::initialize()
{
    if (m_running) {
        return true;
    }

    initPjsip();
    setupCallbacks();

    m_running = true;
    emit initialized();
    return true;
}

void SipManager::shutdown()
{
    if (!m_running) {
        return;
    }

    // Hang up all active calls
    {
        QMutexLocker locker(&m_mutex);
        for (auto *call : std::as_const(m_calls)) {
            call->hangup();
        }
        qDeleteAll(m_calls);
        m_calls.clear();
    }

    // Remove all accounts
    {
        QMutexLocker locker(&m_mutex);
        for (auto *acc : std::as_const(m_accounts)) {
            acc->unregisterAccount();
        }
        qDeleteAll(m_accounts);
        m_accounts.clear();
    }

    cleanupPjsip();
    m_running = false;
    emit shutdownComplete();
}

bool SipManager::isRunning() const
{
    return m_running;
}

// ---------------------------------------------------------------------------
// Account management
// ---------------------------------------------------------------------------

SipAccount *SipManager::addAccount(const Account &config)
{
    auto *acc = new SipAccount(this);
    if (!acc->configure(config)) {
        delete acc;
        return nullptr;
    }

    if (!acc->registerAccount()) {
        delete acc;
        return nullptr;
    }

    int id = acc->accountId();
    {
        QMutexLocker locker(&m_mutex);
        m_accounts.insert(id, acc);
    }

    connect(acc, &SipAccount::registrationStateChanged, this,
            [this, id](RegistrationState st, int code, const QString &reason) {
                emit registrationStateChanged(id, st, code, reason);
            });

    return acc;
}

void SipManager::removeAccount(int accountId)
{
    QMutexLocker locker(&m_mutex);
    auto it = m_accounts.find(accountId);
    if (it == m_accounts.end()) {
        return;
    }
    SipAccount *acc = it.value();
    m_accounts.erase(it);
    locker.unlock();

    acc->unregisterAccount();
    acc->deleteLater();
}

SipAccount *SipManager::findAccount(int accountId) const
{
    QMutexLocker locker(&m_mutex);
    return m_accounts.value(accountId, nullptr);
}

// ---------------------------------------------------------------------------
// Call management
// ---------------------------------------------------------------------------

SipCall *SipManager::makeCall(const QString &number, int accountId)
{
    if (number.isEmpty()) {
        return nullptr;
    }

#ifdef PJSIP_ENABLED
    Q_UNUSED(accountId)
    // Real PJSIP call:
    // pj_str_t uri = ...;
    // pjsua_call_id cid;
    // pjsua_call_make_call(accId, &uri, nullptr, nullptr, nullptr, &cid);
    return nullptr;
#else
    Q_UNUSED(accountId)
    static int nextCallId = 100;
    int cid = nextCallId++;

    auto *call = new SipCall(this);
    call->setCallId(cid);

    CallUserData ud;
    ud.callId = cid;
    ud.number = number;
    call->setUserData(ud);

    {
        QMutexLocker locker(&m_mutex);
        m_calls.insert(cid, call);
    }

    connect(call, &SipCall::stateChanged, this,
            [this, cid](CallState st) {
                emit callStateChanged(cid, st);
            });
    connect(call, &SipCall::mediaStatusChanged, this,
            [this, cid](MediaStatus ms) {
                emit callMediaStateChanged(cid, ms);
            });

    qDebug() << "SipManager::makeCall (stub) id:" << cid << "to:" << number;
    return call;
#endif
}

SipCall *SipManager::findCall(int callId) const
{
    QMutexLocker locker(&m_mutex);
    return m_calls.value(callId, nullptr);
}

void SipManager::answerCall(int callId, int code)
{
    SipCall *call = findCall(callId);
    if (call) {
        call->answer(code);
    }
}

void SipManager::hangupCall(int callId, int code)
{
    SipCall *call = findCall(callId);
    if (call) {
        call->hangup(code);
    }
}

void SipManager::holdCall(int callId)
{
    SipCall *call = findCall(callId);
    if (call) {
        call->hold();
    }
}

void SipManager::unholdCall(int callId)
{
    SipCall *call = findCall(callId);
    if (call) {
        call->unhold();
    }
}

void SipManager::transferCall(int callId, const QString &target)
{
    SipCall *call = findCall(callId);
    if (call) {
        call->transfer(target);
    }
}

void SipManager::sendDtmf(int callId, const QString &digits)
{
    SipCall *call = findCall(callId);
    if (call) {
        call->sendDtmf(digits);
    }
}

void SipManager::mergeConference(int callId1, int callId2)
{
#ifdef PJSIP_ENABLED
    Q_UNUSED(callId1)
    Q_UNUSED(callId2)
    // pjsua_conf_connect / pjsua_call_get_info for conference bridging
#else
    qDebug() << "SipManager::mergeConference (stub)"
             << callId1 << callId2;

    SipCall *c1 = findCall(callId1);
    SipCall *c2 = findCall(callId2);
    if (c1 && c2) {
        CallUserData ud1 = c1->userData();
        ud1.inConference = true;
        c1->setUserData(ud1);

        CallUserData ud2 = c2->userData();
        ud2.inConference = true;
        c2->setUserData(ud2);
    }
#endif
}

// ---------------------------------------------------------------------------
// Media
// ---------------------------------------------------------------------------

void SipManager::setInputVolume(int level)
{
#ifdef PJSIP_ENABLED
    Q_UNUSED(level)
    // pjsua_conf_adjust_rx_level(0, static_cast<float>(level) / 100.0f);
#else
    qDebug() << "SipManager::setInputVolume (stub):" << level;
#endif
}

void SipManager::setOutputVolume(int level)
{
#ifdef PJSIP_ENABLED
    Q_UNUSED(level)
    // pjsua_conf_adjust_tx_level(0, static_cast<float>(level) / 100.0f);
#else
    qDebug() << "SipManager::setOutputVolume (stub):" << level;
#endif
}

void SipManager::setMuteInput(bool mute)
{
#ifdef PJSIP_ENABLED
    Q_UNUSED(mute)
#else
    qDebug() << "SipManager::setMuteInput (stub):" << mute;
#endif
}

void SipManager::setMuteOutput(bool mute)
{
#ifdef PJSIP_ENABLED
    Q_UNUSED(mute)
#else
    qDebug() << "SipManager::setMuteOutput (stub):" << mute;
#endif
}

QStringList SipManager::audioInputDevices() const
{
#ifdef PJSIP_ENABLED
    // Enumerate via pjmedia_aud_dev_info
    return {};
#else
    return {QStringLiteral("Default Input (stub)")};
#endif
}

QStringList SipManager::audioOutputDevices() const
{
#ifdef PJSIP_ENABLED
    return {};
#else
    return {QStringLiteral("Default Output (stub)")};
#endif
}

bool SipManager::setAudioInputDevice(const QString &device)
{
#ifdef PJSIP_ENABLED
    Q_UNUSED(device)
    return false;
#else
    qDebug() << "SipManager::setAudioInputDevice (stub):" << device;
    return true;
#endif
}

bool SipManager::setAudioOutputDevice(const QString &device)
{
#ifdef PJSIP_ENABLED
    Q_UNUSED(device)
    return false;
#else
    qDebug() << "SipManager::setAudioOutputDevice (stub):" << device;
    return true;
#endif
}

// ---------------------------------------------------------------------------
// Presence
// ---------------------------------------------------------------------------

void SipManager::subscribePresence(const QString &uri)
{
#ifdef PJSIP_ENABLED
    Q_UNUSED(uri)
    // pjsua_buddy_config / pjsua_buddy_add
#else
    qDebug() << "SipManager::subscribePresence (stub):" << uri;
    QMetaObject::invokeMethod(this, [this, uri]() {
        emit buddyStateChanged(uri, PresenceStatus::Online);
    }, Qt::QueuedConnection);
#endif
}

void SipManager::unsubscribePresence(const QString &uri)
{
#ifdef PJSIP_ENABLED
    Q_UNUSED(uri)
#else
    qDebug() << "SipManager::unsubscribePresence (stub):" << uri;
#endif
}

void SipManager::publishPresence(PresenceStatus status)
{
#ifdef PJSIP_ENABLED
    Q_UNUSED(status)
    // pjsua_acc_set_online_status2
#else
    qDebug() << "SipManager::publishPresence (stub):"
             << static_cast<int>(status);
#endif
}

// ---------------------------------------------------------------------------
// Codec configuration
// ---------------------------------------------------------------------------

void SipManager::setCodecPriority(const QString &codecId, int priority)
{
#ifdef PJSIP_ENABLED
    Q_UNUSED(codecId)
    Q_UNUSED(priority)
    // pj_str_t cid = ...;
    // pjsua_codec_set_priority(&cid, static_cast<pj_uint8_t>(priority));
#else
    qDebug() << "SipManager::setCodecPriority (stub):"
             << codecId << priority;
#endif
}

QStringList SipManager::availableCodecs() const
{
#ifdef PJSIP_ENABLED
    // pjsua_codec_info info[64];
    // unsigned count = 64;
    // pjsua_enum_codecs(info, &count);
    return {};
#else
    return {
        QStringLiteral("PCMA/8000/1"),
        QStringLiteral("PCMU/8000/1"),
        QStringLiteral("opus/48000/2"),
        QStringLiteral("G722/16000/1"),
    };
#endif
}

// ---------------------------------------------------------------------------
// PJSIP init / cleanup / callbacks
// ---------------------------------------------------------------------------

void SipManager::initPjsip()
{
#ifdef PJSIP_ENABLED
    // pjsua_create();
    // pjsua_config cfg; pjsua_config_default(&cfg);
    // pjsua_logging_config logCfg; pjsua_logging_config_default(&logCfg);
    // pjsua_media_config mediaCfg; pjsua_media_config_default(&mediaCfg);
    // pjsua_init(&cfg, &logCfg, &mediaCfg);
    // pjsua_transport_config tpCfg; pjsua_transport_config_default(&tpCfg);
    // pjsua_transport_create(PJSIP_TRANSPORT_UDP, &tpCfg, nullptr);
    // pjsua_start();
#else
    qDebug() << "SipManager::initPjsip (stub)";
#endif
}

void SipManager::cleanupPjsip()
{
#ifdef PJSIP_ENABLED
    // pjsua_destroy();
#else
    qDebug() << "SipManager::cleanupPjsip (stub)";
#endif
}

void SipManager::setupCallbacks()
{
#ifdef PJSIP_ENABLED
    // Register PJSIP callbacks (on_incoming_call, on_call_state, etc.)
    // Use QMetaObject::invokeMethod with Qt::QueuedConnection
    // to marshal callbacks from PJSIP thread to Qt main thread.
#else
    qDebug() << "SipManager::setupCallbacks (stub)";
#endif
}

} // namespace macrosip
