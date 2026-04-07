#pragma once
#include <QString>
#include <QDateTime>

namespace macrosip {

enum class CallState {
    Idle,
    Calling,
    Incoming,
    Early,
    Connecting,
    Confirmed,
    Disconnected,
    Unknown
};

enum class CallDirection { Outgoing, Incoming };

enum class MediaStatus {
    None,
    Active,
    LocalHold,
    RemoteHold,
    Error
};

enum class TransportType { UDP, TCP, TLS };

enum class SrtpType { Disabled, Optional, Mandatory };

enum class PresenceStatus {
    Unknown,
    Online,
    Offline,
    Away,
    Busy,
    OnThePhone,
    Idle
};

enum class RegistrationState {
    Unregistered,
    Registering,
    Registered,
    Error
};

struct CallUserData {
    int callId = -1;
    QString name;
    QString number;
    QString userAgent;
    QString diversion;
    QString callerID;
    bool inConference = false;
    bool autoAnswer = false;
    bool forwarding = false;
    bool hidden = false;
    int holdFrom = -1;
    SrtpType srtp = SrtpType::Disabled;
    float mos = 0.0f;
};

} // namespace macrosip
