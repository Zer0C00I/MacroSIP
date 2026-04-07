#include "models/CallRecord.h"

namespace macrosip {

bool CallRecord::isValid() const
{
    return !number.isEmpty() && time.isValid();
}

QString CallRecord::durationString() const
{
    if (duration < 0) {
        return QStringLiteral("00:00:00");
    }
    int total = duration;
    int hours = total / 3600;
    total %= 3600;
    int minutes = total / 60;
    int seconds = total % 60;
    return QStringLiteral("%1:%2:%3")
        .arg(hours, 2, 10, QLatin1Char('0'))
        .arg(minutes, 2, 10, QLatin1Char('0'))
        .arg(seconds, 2, 10, QLatin1Char('0'));
}

QString CallRecord::typeString() const
{
    switch (type) {
    case CallType::Outgoing: return QStringLiteral("outgoing");
    case CallType::Incoming: return QStringLiteral("incoming");
    case CallType::Missed:   return QStringLiteral("missed");
    case CallType::Other:    return QStringLiteral("other");
    }
    return QStringLiteral("other");
}

} // namespace macrosip
