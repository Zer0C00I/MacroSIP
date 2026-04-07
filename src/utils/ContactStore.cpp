#include "utils/ContactStore.h"
#include "utils/CsvFile.h"
#include <QFile>
#include <QDir>
#include <QFileInfo>

namespace macrosip {

ContactStore::ContactStore(const QString &filePath)
    : m_filePath(filePath)
{
}

QList<Contact> ContactStore::load() const
{
    return importCsv(m_filePath);
}

bool ContactStore::save(const QList<Contact> &contacts) const
{
    // Ensure parent directory exists
    QDir().mkpath(QFileInfo(m_filePath).absolutePath());
    return exportCsv(m_filePath, contacts);
}

QList<Contact> ContactStore::importCsv(const QString &filePath)
{
    QList<Contact> result;

    const QList<QStringList> rows = CsvFile::read(filePath);
    for (const QStringList &row : rows) {
        // Skip header row
        if (!row.isEmpty() && row.first().compare(
                QStringLiteral("name"), Qt::CaseInsensitive) == 0) {
            continue;
        }
        Contact c = rowToContact(row);
        if (c.isValid()) {
            result.append(c);
        }
    }

    return result;
}

bool ContactStore::exportCsv(const QString &filePath,
                              const QList<Contact> &contacts)
{
    QDir().mkpath(QFileInfo(filePath).absolutePath());

    QList<QStringList> rows;
    rows.append(headerRow());

    for (const Contact &c : contacts) {
        rows.append(contactToRow(c));
    }

    return CsvFile::write(filePath, rows);
}

QStringList ContactStore::headerRow()
{
    return {
        QStringLiteral("name"), QStringLiteral("number"),
        QStringLiteral("firstname"), QStringLiteral("lastname"),
        QStringLiteral("phone"), QStringLiteral("mobile"),
        QStringLiteral("email"), QStringLiteral("address"),
        QStringLiteral("city"), QStringLiteral("state"),
        QStringLiteral("zip"), QStringLiteral("comment"),
        QStringLiteral("presence"), QStringLiteral("starred"),
        QStringLiteral("directory"), QStringLiteral("image")
    };
}

QStringList ContactStore::contactToRow(const Contact &c)
{
    return {
        c.name, c.number,
        c.firstname, c.lastname,
        c.phone, c.mobile,
        c.email, c.address,
        c.city, c.state,
        c.zip, c.comment,
        c.presence  ? QStringLiteral("1") : QStringLiteral("0"),
        c.starred   ? QStringLiteral("1") : QStringLiteral("0"),
        c.directory ? QStringLiteral("1") : QStringLiteral("0"),
        QString::number(c.image)
    };
}

Contact ContactStore::rowToContact(const QStringList &row)
{
    Contact c;
    const qsizetype sz = row.size();
    if (sz < 2) {
        return c;
    }

    c.name      = row.at(0);
    c.number    = row.at(1);
    if (sz > 2)  c.firstname = row.at(2);
    if (sz > 3)  c.lastname  = row.at(3);
    if (sz > 4)  c.phone     = row.at(4);
    if (sz > 5)  c.mobile    = row.at(5);
    if (sz > 6)  c.email     = row.at(6);
    if (sz > 7)  c.address   = row.at(7);
    if (sz > 8)  c.city      = row.at(8);
    if (sz > 9)  c.state     = row.at(9);
    if (sz > 10) c.zip       = row.at(10);
    if (sz > 11) c.comment   = row.at(11);
    if (sz > 12) c.presence  = row.at(12) == QStringLiteral("1");
    if (sz > 13) c.starred   = row.at(13) == QStringLiteral("1");
    if (sz > 14) c.directory = row.at(14) == QStringLiteral("1");
    if (sz > 15) c.image     = row.at(15).toInt();

    return c;
}

} // namespace macrosip
