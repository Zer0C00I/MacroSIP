#pragma once
#include <QString>
#include <QDateTime>

namespace macrosip {

enum class CallType { Outgoing, Incoming, Missed, Other };

struct CallRecord {
    QString id;
    QString name;
    QString number;
    CallType type = CallType::Other;
    int duration = 0;  // seconds
    QDateTime time;
    QString info;

    bool isValid() const;
    QString durationString() const;
    QString typeString() const;
};

} // namespace macrosip
