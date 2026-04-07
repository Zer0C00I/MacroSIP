#include "utils/CallHistoryStore.h"
#include "utils/CsvFile.h"
#include <QFile>
#include <QDir>
#include <QFileInfo>

namespace macrosip {

CallHistoryStore::CallHistoryStore(const QString &filePath)
    : m_filePath(filePath)
{
}

QList<CallRecord> CallHistoryStore::load() const
{
    QList<CallRecord> result;

    const QList<QStringList> rows = CsvFile::read(m_filePath);
    for (const QStringList &row : rows) {
        // Skip header row if present
        if (!row.isEmpty() && row.first().compare(
                QStringLiteral("id"), Qt::CaseInsensitive) == 0) {
            continue;
        }
        CallRecord r = rowToRecord(row);
        if (r.isValid()) {
            result.append(r);
        }
    }

    return result;
}

bool CallHistoryStore::save(const QList<CallRecord> &records) const
{
    // Ensure parent directory exists
    QDir().mkpath(QFileInfo(m_filePath).absolutePath());

    QList<QStringList> rows;
    // Header
    rows.append({QStringLiteral("id"), QStringLiteral("name"),
                 QStringLiteral("number"), QStringLiteral("type"),
                 QStringLiteral("duration"), QStringLiteral("time"),
                 QStringLiteral("info")});

    for (const CallRecord &r : records) {
        rows.append(recordToRow(r));
    }

    return CsvFile::write(m_filePath, rows);
}

bool CallHistoryStore::append(const CallRecord &record) const
{
    // If file doesn't exist, create with header
    if (!QFile::exists(m_filePath)) {
        return save({record});
    }

    // Append a single row
    QFile file(m_filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        return false;
    }

    QTextStream stream(&file);
    stream << CsvFile::formatLine(recordToRow(record))
           << QStringLiteral("\n");
    file.close();
    return true;
}

QStringList CallHistoryStore::recordToRow(const CallRecord &r)
{
    return {
        r.id,
        r.name,
        r.number,
        r.typeString(),
        QString::number(r.duration),
        r.time.toString(Qt::ISODate),
        r.info
    };
}

CallRecord CallHistoryStore::rowToRecord(const QStringList &row)
{
    CallRecord r;
    if (row.size() < 6) {
        return r;
    }

    r.id       = row.at(0);
    r.name     = row.at(1);
    r.number   = row.at(2);
    r.type     = typeFromString(row.at(3));
    r.duration = row.at(4).toInt();
    r.time     = QDateTime::fromString(row.at(5), Qt::ISODate);
    if (row.size() > 6) {
        r.info = row.at(6);
    }
    return r;
}

CallType CallHistoryStore::typeFromString(const QString &s)
{
    if (s == QStringLiteral("outgoing")) return CallType::Outgoing;
    if (s == QStringLiteral("incoming")) return CallType::Incoming;
    if (s == QStringLiteral("missed"))   return CallType::Missed;
    return CallType::Other;
}

} // namespace macrosip
