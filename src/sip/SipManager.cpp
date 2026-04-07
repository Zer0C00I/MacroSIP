#include "sip/SipManager.h"
#include "models/Settings.h"
#include <QDebug>
#include <QMutexLocker>
#include <QRegularExpression>

#ifdef PJSIP_ENABLED
#include <pjsua-lib/pjsua.h>
#endif

namespace macrosip {

#ifdef PJSIP_ENABLED
SipManager *SipManager::s_instance = nullptr;
#endif

SipManager::SipManager(QObject *parent)
    : QObject(parent)
{
#ifdef PJSIP_ENABLED
    s_instance = this;
#endif
}

SipManager::~SipManager()
{
    shutdown();
#ifdef PJSIP_ENABLED
    if (s_instance == this) {
        s_instance = nullptr;
    }
#endif
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
    pjsua_acc_id accId = static_cast<pjsua_acc_id>(accountId);
    if (accId < 0) {
        accId = pjsua_acc_get_default();
    }
    if (!pjsua_acc_is_valid(accId)) {
        qWarning() << "SipManager::makeCall: no valid account";
        return nullptr;
    }

    QByteArray uriBytes = (QStringLiteral("sip:") + number).toUtf8();
    pj_str_t uri = pj_str(uriBytes.data());

    pjsua_call_id callId = PJSUA_INVALID_ID;
    pj_status_t status = pjsua_call_make_call(accId, &uri,
                                               nullptr, nullptr, nullptr,
                                               &callId);
    if (status != PJ_SUCCESS) {
        qWarning() << "SipManager::makeCall: pjsua_call_make_call failed"
                    << status;
        return nullptr;
    }

    auto *call = new SipCall(this);
    call->setCallId(static_cast<int>(callId));

    CallUserData ud;
    ud.callId = static_cast<int>(callId);
    ud.number = number;
    call->setUserData(ud);

    {
        QMutexLocker locker(&m_mutex);
        m_calls.insert(static_cast<int>(callId), call);
    }

    connect(call, &SipCall::stateChanged, this,
            [this, callId](CallState st) {
                emit callStateChanged(static_cast<int>(callId), st);
            });
    connect(call, &SipCall::mediaStatusChanged, this,
            [this, callId](MediaStatus ms) {
                emit callMediaStateChanged(static_cast<int>(callId), ms);
            });

    return call;
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

void SipManager::hangupAllCalls()
{
    QMutexLocker locker(&m_mutex);
    for (auto *call : std::as_const(m_calls)) {
        call->hangup();
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
    auto cid1 = static_cast<pjsua_call_id>(callId1);
    auto cid2 = static_cast<pjsua_call_id>(callId2);

    pjsua_call_info ci1;
    pjsua_call_info ci2;
    if (pjsua_call_get_info(cid1, &ci1) != PJ_SUCCESS ||
        pjsua_call_get_info(cid2, &ci2) != PJ_SUCCESS) {
        qWarning() << "SipManager::mergeConference: failed to get call info";
        return;
    }

    // Connect both calls' conference slots to the bridge (slot 0 = local mic/spk)
    pjsua_conf_connect(ci1.conf_slot, ci2.conf_slot);
    pjsua_conf_connect(ci2.conf_slot, ci1.conf_slot);
    pjsua_conf_connect(ci1.conf_slot, 0);
    pjsua_conf_connect(0, ci1.conf_slot);
    pjsua_conf_connect(ci2.conf_slot, 0);
    pjsua_conf_connect(0, ci2.conf_slot);

    SipCall *c1 = findCall(callId1);
    SipCall *c2 = findCall(callId2);
    if (c1) {
        CallUserData ud1 = c1->userData();
        ud1.inConference = true;
        c1->setUserData(ud1);
    }
    if (c2) {
        CallUserData ud2 = c2->userData();
        ud2.inConference = true;
        c2->setUserData(ud2);
    }
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
    float adj = static_cast<float>(level) / 100.0F;
    pjsua_conf_adjust_rx_level(0, adj);
#else
    qDebug() << "SipManager::setInputVolume (stub):" << level;
#endif
}

void SipManager::setOutputVolume(int level)
{
#ifdef PJSIP_ENABLED
    float adj = static_cast<float>(level) / 100.0F;
    pjsua_conf_adjust_tx_level(0, adj);
#else
    qDebug() << "SipManager::setOutputVolume (stub):" << level;
#endif
}

void SipManager::setMuteInput(bool mute)
{
#ifdef PJSIP_ENABLED
    pjsua_conf_adjust_rx_level(0, mute ? 0.0F : 1.0F);
#else
    qDebug() << "SipManager::setMuteInput (stub):" << mute;
#endif
}

void SipManager::setMuteOutput(bool mute)
{
#ifdef PJSIP_ENABLED
    pjsua_conf_adjust_tx_level(0, mute ? 0.0F : 1.0F);
#else
    qDebug() << "SipManager::setMuteOutput (stub):" << mute;
#endif
}

QStringList SipManager::audioInputDevices() const
{
#ifdef PJSIP_ENABLED
    QStringList devices;
    unsigned devCount = 64;
    pjmedia_aud_dev_info info[64];
    pjsua_enum_aud_devs(info, &devCount);
    for (unsigned i = 0; i < devCount; ++i) {
        if (info[i].input_count > 0) {
            devices.append(QString::fromUtf8(info[i].name));
        }
    }
    return devices;
#else
    return {QStringLiteral("Default Input (stub)")};
#endif
}

QStringList SipManager::audioOutputDevices() const
{
#ifdef PJSIP_ENABLED
    QStringList devices;
    unsigned devCount = 64;
    pjmedia_aud_dev_info info[64];
    pjsua_enum_aud_devs(info, &devCount);
    for (unsigned i = 0; i < devCount; ++i) {
        if (info[i].output_count > 0) {
            devices.append(QString::fromUtf8(info[i].name));
        }
    }
    return devices;
#else
    return {QStringLiteral("Default Output (stub)")};
#endif
}

bool SipManager::setAudioInputDevice(const QString &device)
{
#ifdef PJSIP_ENABLED
    unsigned devCount = 64;
    pjmedia_aud_dev_info info[64];
    pjsua_enum_aud_devs(info, &devCount);
    for (unsigned i = 0; i < devCount; ++i) {
        if (info[i].input_count > 0 &&
            QString::fromUtf8(info[i].name) == device) {
            int capDev = -1;
            int pbDev = -1;
            pjsua_get_snd_dev(&capDev, &pbDev);
            pj_status_t st = pjsua_set_snd_dev(static_cast<int>(i), pbDev);
            return st == PJ_SUCCESS;
        }
    }
    return false;
#else
    qDebug() << "SipManager::setAudioInputDevice (stub):" << device;
    return true;
#endif
}

bool SipManager::setAudioOutputDevice(const QString &device)
{
#ifdef PJSIP_ENABLED
    unsigned devCount = 64;
    pjmedia_aud_dev_info info[64];
    pjsua_enum_aud_devs(info, &devCount);
    for (unsigned i = 0; i < devCount; ++i) {
        if (info[i].output_count > 0 &&
            QString::fromUtf8(info[i].name) == device) {
            int capDev = -1;
            int pbDev = -1;
            pjsua_get_snd_dev(&capDev, &pbDev);
            pj_status_t st = pjsua_set_snd_dev(capDev, static_cast<int>(i));
            return st == PJ_SUCCESS;
        }
    }
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
    pjsua_buddy_config cfg;
    pjsua_buddy_config_default(&cfg);

    QByteArray uriBytes = uri.toUtf8();
    cfg.uri = pj_str(uriBytes.data());
    cfg.subscribe = PJ_TRUE;

    pjsua_buddy_id buddyId = PJSUA_INVALID_ID;
    pj_status_t st = pjsua_buddy_add(&cfg, &buddyId);
    if (st != PJ_SUCCESS) {
        qWarning() << "SipManager::subscribePresence failed:" << st;
    }
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
    // Find buddy by URI and remove
    pjsua_buddy_id ids[256];
    unsigned cnt = 256;
    if (pjsua_enum_buddies(ids, &cnt) == PJ_SUCCESS) {
        for (unsigned i = 0; i < cnt; ++i) {
            pjsua_buddy_info info;
            if (pjsua_buddy_get_info(ids[i], &info) == PJ_SUCCESS) {
                QString buddyUri = QString::fromUtf8(info.uri.ptr,
                                                     static_cast<int>(info.uri.slen));
                if (buddyUri.contains(uri)) {
                    pjsua_buddy_del(ids[i]);
                    return;
                }
            }
        }
    }
#else
    qDebug() << "SipManager::unsubscribePresence (stub):" << uri;
#endif
}

void SipManager::publishPresence(PresenceStatus status)
{
#ifdef PJSIP_ENABLED
    pj_bool_t online = PJ_FALSE;
    pjrpid_element rpid;
    pj_bzero(&rpid, sizeof(rpid));
    rpid.type = PJRPID_ELEMENT_TYPE_PERSON;

    switch (status) {
    case PresenceStatus::Online:
        online = PJ_TRUE;
        rpid.activity = PJRPID_ACTIVITY_UNKNOWN;
        break;
    case PresenceStatus::Away:
        online = PJ_TRUE;
        rpid.activity = PJRPID_ACTIVITY_AWAY;
        break;
    case PresenceStatus::Busy:
    case PresenceStatus::OnThePhone:
        online = PJ_TRUE;
        rpid.activity = PJRPID_ACTIVITY_BUSY;
        break;
    case PresenceStatus::Offline:
    case PresenceStatus::Unknown:
    case PresenceStatus::Idle:
    default:
        online = PJ_FALSE;
        rpid.activity = PJRPID_ACTIVITY_UNKNOWN;
        break;
    }

    pjsua_acc_id accId = pjsua_acc_get_default();
    if (pjsua_acc_is_valid(accId)) {
        pjsua_acc_set_online_status2(accId, online, &rpid);
    }
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
    QByteArray cidBytes = codecId.toUtf8();
    pj_str_t cid = pj_str(cidBytes.data());
    pjsua_codec_set_priority(&cid, static_cast<pj_uint8_t>(priority));
#else
    qDebug() << "SipManager::setCodecPriority (stub):"
             << codecId << priority;
#endif
}

QStringList SipManager::availableCodecs() const
{
#ifdef PJSIP_ENABLED
    QStringList list;
    pjsua_codec_info info[64];
    unsigned count = 64;
    if (pjsua_enum_codecs(info, &count) == PJ_SUCCESS) {
        for (unsigned i = 0; i < count; ++i) {
            list.append(QString::fromUtf8(info[i].codec_id.ptr,
                                          static_cast<int>(info[i].codec_id.slen)));
        }
    }
    return list;
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
    pj_status_t status;

    // 1. Create PJSUA instance
    status = pjsua_create();
    if (status != PJ_SUCCESS) {
        qCritical() << "pjsua_create() failed:" << status;
        return;
    }

    // 2. Configure
    pjsua_config uaCfg;
    pjsua_config_default(&uaCfg);

    QByteArray userAgent = QStringLiteral("MacroSIP/1.0").toUtf8();
    uaCfg.user_agent = pj_str(userAgent.data());
    uaCfg.srtp_secure_signaling = 0;

    // Register all callbacks
    uaCfg.cb.on_reg_state2         = &SipManager::onRegState2;
    uaCfg.cb.on_incoming_call      = &SipManager::onIncomingCall;
    uaCfg.cb.on_call_state         = &SipManager::onCallState;
    uaCfg.cb.on_call_media_state   = &SipManager::onCallMediaState;
    uaCfg.cb.on_buddy_state        = &SipManager::onBuddyState;
    uaCfg.cb.on_pager2             = &SipManager::onPager2;
    uaCfg.cb.on_pager_status2      = &SipManager::onPagerStatus2;
    uaCfg.cb.on_mwi_info           = &SipManager::onMwiInfo;

    pjsua_logging_config logCfg;
    pjsua_logging_config_default(&logCfg);
    logCfg.level = 4;
    logCfg.console_level = 3;

    pjsua_media_config mediaCfg;
    pjsua_media_config_default(&mediaCfg);
    mediaCfg.enable_ice = PJ_FALSE;
    mediaCfg.no_vad = PJ_TRUE;
    mediaCfg.ec_tail_len = 20;

    // 3. Init
    status = pjsua_init(&uaCfg, &logCfg, &mediaCfg);
    if (status != PJ_SUCCESS) {
        qCritical() << "pjsua_init() failed:" << status;
        pjsua_destroy();
        return;
    }

    // 4. Create transports (UDP, TCP, TLS)
    pjsua_transport_config tpCfg;

    // UDP
    pjsua_transport_config_default(&tpCfg);
    tpCfg.port = 0;  // auto-select
    status = pjsua_transport_create(PJSIP_TRANSPORT_UDP, &tpCfg,
                                     &m_transportUdp);
    if (status != PJ_SUCCESS) {
        qWarning() << "UDP transport creation failed:" << status;
    }

    // TCP
    pjsua_transport_config_default(&tpCfg);
    tpCfg.port = 0;
    status = pjsua_transport_create(PJSIP_TRANSPORT_TCP, &tpCfg,
                                     &m_transportTcp);
    if (status != PJ_SUCCESS) {
        qWarning() << "TCP transport creation failed:" << status;
    }

    // TLS (may fail if no TLS support compiled into PJSIP)
    pjsua_transport_config_default(&tpCfg);
    tpCfg.port = 0;
    status = pjsua_transport_create(PJSIP_TRANSPORT_TLS, &tpCfg,
                                     &m_transportTls);
    if (status != PJ_SUCCESS) {
        qDebug() << "TLS transport creation failed (optional):" << status;
        m_transportTls = PJSUA_INVALID_ID;
    }

    // 5. Start
    status = pjsua_start();
    if (status != PJ_SUCCESS) {
        qCritical() << "pjsua_start() failed:" << status;
        pjsua_destroy();
        return;
    }

    qDebug() << "PJSIP initialized successfully";
#else
    qDebug() << "SipManager::initPjsip (stub)";
#endif
}

void SipManager::cleanupPjsip()
{
#ifdef PJSIP_ENABLED
    pjsua_destroy();
    m_transportUdp = PJSUA_INVALID_ID;
    m_transportTcp = PJSUA_INVALID_ID;
    m_transportTls = PJSUA_INVALID_ID;
    qDebug() << "PJSIP destroyed";
#else
    qDebug() << "SipManager::cleanupPjsip (stub)";
#endif
}

void SipManager::setupCallbacks()
{
#ifdef PJSIP_ENABLED
    // Callbacks are registered in initPjsip() via uaCfg.cb.*
    // Thread marshaling is done inside each static callback using
    // QMetaObject::invokeMethod with Qt::QueuedConnection.
    qDebug() << "PJSIP callbacks registered";
#else
    qDebug() << "SipManager::setupCallbacks (stub)";
#endif
}

// ---------------------------------------------------------------------------
// Static PJSIP Callbacks — fire on PJSIP worker thread,
// marshal to Qt main thread via QMetaObject::invokeMethod.
// ---------------------------------------------------------------------------

#ifdef PJSIP_ENABLED

void SipManager::onRegState2(pjsua_acc_id accId, pjsua_reg_info *info)
{
    SipManager *self = s_instance;
    if (!self) {
        return;
    }

    int code = static_cast<int>(info->cbparam->code);
    QString reason;
    if (info->cbparam->reason.slen > 0) {
        reason = QString::fromUtf8(info->cbparam->reason.ptr,
                                   static_cast<int>(info->cbparam->reason.slen));
    }

    RegistrationState st;
    if (code >= 200 && code < 300) {
        st = RegistrationState::Registered;
    } else if (info->cbparam->expiration > 0) {
        st = RegistrationState::Registering;
    } else {
        st = RegistrationState::Error;
    }

    int aId = static_cast<int>(accId);
    QMetaObject::invokeMethod(self, [self, aId, st, code, reason]() {
        // Also update the SipAccount object if we have it
        SipAccount *acc = self->findAccount(aId);
        if (acc) {
            acc->handleRegistrationState(st, code, reason);
        }
        emit self->registrationStateChanged(aId, st, code, reason);
    }, Qt::QueuedConnection);
}

void SipManager::onIncomingCall(pjsua_acc_id accId, pjsua_call_id callId,
                                 pjsip_rx_data *rdata)
{
    Q_UNUSED(accId)
    SipManager *self = s_instance;
    if (!self) {
        return;
    }

    pjsua_call_info ci;
    if (pjsua_call_get_info(callId, &ci) != PJ_SUCCESS) {
        return;
    }

    QString from = QString::fromUtf8(ci.remote_info.ptr,
                                     static_cast<int>(ci.remote_info.slen));
    QString name;

    // Try to extract display name from "Name" <sip:...>
    if (from.contains(QLatin1Char('"'))) {
        int start = from.indexOf(QLatin1Char('"')) + 1;
        int end = from.indexOf(QLatin1Char('"'), start);
        if (end > start) {
            name = from.mid(start, end - start);
        }
    }

    // Extract User-Agent header if available
    QString userAgent;
    if (rdata) {
        static char userAgentHdr[] = "User-Agent";
        const pj_str_t hName = pj_str(userAgentHdr);
        auto *hdr = reinterpret_cast<pjsip_generic_string_hdr *>(
            pjsip_msg_find_hdr_by_name(rdata->msg_info.msg, &hName, nullptr));
        if (hdr) {
            userAgent = QString::fromUtf8(hdr->hvalue.ptr,
                                          static_cast<int>(hdr->hvalue.slen));
        }
    }

    int cid = static_cast<int>(callId);
    QMetaObject::invokeMethod(self, [self, cid, from, name, userAgent]() {
        // Create SipCall wrapper for this incoming call
        auto *call = new SipCall(self);
        call->setCallId(cid);

        CallUserData ud;
        ud.callId = cid;
        ud.number = from;
        ud.name = name;
        ud.userAgent = userAgent;
        ud.direction = CallDirection::Incoming;
        call->setUserData(ud);

        {
            QMutexLocker locker(&self->m_mutex);
            self->m_calls.insert(cid, call);
        }

        QObject::connect(call, &SipCall::stateChanged, self,
                [self, cid](CallState st) {
                    emit self->callStateChanged(cid, st);
                });
        QObject::connect(call, &SipCall::mediaStatusChanged, self,
                [self, cid](MediaStatus ms) {
                    emit self->callMediaStateChanged(cid, ms);
                });

        emit self->incomingCall(cid, from, name);
    }, Qt::QueuedConnection);
}

void SipManager::onCallState(pjsua_call_id callId, pjsip_event *e)
{
    Q_UNUSED(e)
    SipManager *self = s_instance;
    if (!self) {
        return;
    }

    pjsua_call_info ci;
    if (pjsua_call_get_info(callId, &ci) != PJ_SUCCESS) {
        return;
    }

    CallState state;
    switch (ci.state) {
    case PJSIP_INV_STATE_CALLING:     state = CallState::Calling;       break;
    case PJSIP_INV_STATE_INCOMING:    state = CallState::Incoming;      break;
    case PJSIP_INV_STATE_EARLY:       state = CallState::Early;         break;
    case PJSIP_INV_STATE_CONNECTING:  state = CallState::Connecting;    break;
    case PJSIP_INV_STATE_CONFIRMED:   state = CallState::Confirmed;     break;
    case PJSIP_INV_STATE_DISCONNECTED:state = CallState::Disconnected;  break;
    default:                          state = CallState::Unknown;       break;
    }

    int cid = static_cast<int>(callId);
    QMetaObject::invokeMethod(self, [self, cid, state]() {
        SipCall *call = self->findCall(cid);
        if (call) {
            call->handleStateChange(state);
        }
        emit self->callStateChanged(cid, state);

        // Clean up disconnected calls
        if (state == CallState::Disconnected) {
            QMutexLocker locker(&self->m_mutex);
            if (auto *c = self->m_calls.take(cid)) {
                c->deleteLater();
            }
        }
    }, Qt::QueuedConnection);
}

void SipManager::onCallMediaState(pjsua_call_id callId)
{
    SipManager *self = s_instance;
    if (!self) {
        return;
    }

    pjsua_call_info ci;
    if (pjsua_call_get_info(callId, &ci) != PJ_SUCCESS) {
        return;
    }

    // Connect/disconnect audio based on media status
    if (ci.media_status == PJSUA_CALL_MEDIA_ACTIVE ||
        ci.media_status == PJSUA_CALL_MEDIA_REMOTE_HOLD) {
        pjsua_conf_connect(ci.conf_slot, 0);
        pjsua_conf_connect(0, ci.conf_slot);
    } else {
        pjsua_conf_disconnect(ci.conf_slot, 0);
        pjsua_conf_disconnect(0, ci.conf_slot);
    }

    MediaStatus ms;
    switch (ci.media_status) {
    case PJSUA_CALL_MEDIA_ACTIVE:       ms = MediaStatus::Active;      break;
    case PJSUA_CALL_MEDIA_LOCAL_HOLD:   ms = MediaStatus::LocalHold;   break;
    case PJSUA_CALL_MEDIA_REMOTE_HOLD:  ms = MediaStatus::RemoteHold;  break;
    case PJSUA_CALL_MEDIA_NONE:         ms = MediaStatus::None;        break;
    default:                            ms = MediaStatus::Error;       break;
    }

    int cid = static_cast<int>(callId);
    QMetaObject::invokeMethod(self, [self, cid, ms]() {
        SipCall *call = self->findCall(cid);
        if (call) {
            call->handleMediaStatusChange(ms);
        }
        emit self->callMediaStateChanged(cid, ms);
    }, Qt::QueuedConnection);
}

void SipManager::onBuddyState(pjsua_buddy_id buddyId)
{
    SipManager *self = s_instance;
    if (!self) {
        return;
    }

    pjsua_buddy_info info;
    if (pjsua_buddy_get_info(buddyId, &info) != PJ_SUCCESS) {
        return;
    }

    QString uri = QString::fromUtf8(info.uri.ptr,
                                    static_cast<int>(info.uri.slen));

    PresenceStatus ps;
    switch (info.status) {
    case PJSUA_BUDDY_STATUS_ONLINE:  ps = PresenceStatus::Online;  break;
    case PJSUA_BUDDY_STATUS_OFFLINE: ps = PresenceStatus::Offline; break;
    default:                         ps = PresenceStatus::Unknown; break;
    }

    // Refine presence based on RPID activity
    if (info.rpid.activity == PJRPID_ACTIVITY_AWAY) {
        ps = PresenceStatus::Away;
    } else if (info.rpid.activity == PJRPID_ACTIVITY_BUSY) {
        ps = PresenceStatus::Busy;
    }

    QMetaObject::invokeMethod(self, [self, uri, ps]() {
        emit self->buddyStateChanged(uri, ps);
    }, Qt::QueuedConnection);
}

void SipManager::onPager2(pjsua_call_id callId,
                           const pj_str_t *from, const pj_str_t *to,
                           const pj_str_t * /*contact*/,
                           const pj_str_t * /*mimeType*/,
                           const pj_str_t *body,
                           pjsip_rx_data * /*rdata*/,
                           pjsua_acc_id /*accId*/)
{
    Q_UNUSED(callId)
    SipManager *self = s_instance;
    if (!self) {
        return;
    }

    QString fromStr = QString::fromUtf8(from->ptr, static_cast<int>(from->slen));
    QString toStr = QString::fromUtf8(to->ptr, static_cast<int>(to->slen));
    QString bodyStr = QString::fromUtf8(body->ptr, static_cast<int>(body->slen));

    QMetaObject::invokeMethod(self, [self, fromStr, toStr, bodyStr]() {
        emit self->messageReceived(fromStr, toStr, bodyStr);
    }, Qt::QueuedConnection);
}

void SipManager::onPagerStatus2(pjsua_call_id /*callId*/,
                                 const pj_str_t *to,
                                 const pj_str_t * /*body*/,
                                 void * /*userData*/,
                                 pjsip_status_code status,
                                 const pj_str_t * /*reason*/,
                                 pjsip_tx_data * /*tdata*/,
                                 pjsip_rx_data * /*rdata*/,
                                 pjsua_acc_id /*accId*/)
{
    SipManager *self = s_instance;
    if (!self) {
        return;
    }

    QString toStr = QString::fromUtf8(to->ptr, static_cast<int>(to->slen));
    int st = static_cast<int>(status);

    QMetaObject::invokeMethod(self, [self, toStr, st]() {
        emit self->messageStatus(toStr, st);
    }, Qt::QueuedConnection);
}

void SipManager::onMwiInfo(pjsua_acc_id accId, pjsua_mwi_info *mwiInfo)
{
    SipManager *self = s_instance;
    if (!self) {
        return;
    }

    // Parse MWI body for message counts
    int newMsgs = 0;
    int oldMsgs = 0;
    if (mwiInfo->rdata && mwiInfo->rdata->msg_info.msg &&
        mwiInfo->rdata->msg_info.msg->body) {
        QString body = QString::fromUtf8(
            static_cast<const char *>(mwiInfo->rdata->msg_info.msg->body->data),
            static_cast<int>(mwiInfo->rdata->msg_info.msg->body->len));
        // Parse "Messages-Waiting: yes\r\nVoice-Message: 2/1"
        static const QRegularExpression voiceMsgRx(
            QStringLiteral(R"(Voice-Message:\s*(\d+)/(\d+))"));
        QRegularExpressionMatch match = voiceMsgRx.match(body);
        if (match.hasMatch()) {
            newMsgs = match.captured(1).toInt();
            oldMsgs = match.captured(2).toInt();
        }
    }

    int aId = static_cast<int>(accId);
    QMetaObject::invokeMethod(self, [self, aId, newMsgs, oldMsgs]() {
        emit self->mwiNotification(aId, newMsgs, oldMsgs);
    }, Qt::QueuedConnection);
}

#endif // PJSIP_ENABLED

} // namespace macrosip
