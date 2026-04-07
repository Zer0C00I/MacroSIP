#pragma once
#include <QList>
#include <QString>
#include "models/CallRecord.h"

namespace macrosip {

/**
 * Persists call history to a CSV file.
 *
 * CSV columns: id, name, number, type, duration, time, info
 */
class CallHistoryStore {
public:
    explicit CallHistoryStore(const QString &filePath);

    QList<CallRecord> load() const;
    bool save(const QList<CallRecord> &records) const;
    bool append(const CallRecord &record) const;

private:
    QString m_filePath;

    static QStringList recordToRow(const CallRecord &r);
    static CallRecord rowToRecord(const QStringList &row);
    static CallType typeFromString(const QString &s);
};

} // namespace macrosip
