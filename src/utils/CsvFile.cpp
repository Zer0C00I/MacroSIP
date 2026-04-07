#include "utils/CsvFile.h"
#include <QFile>
#include <QTextStream>

namespace macrosip {

QList<QStringList> CsvFile::read(const QString &filePath)
{
    QList<QStringList> rows;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return rows;
    }

    QTextStream stream(&file);

    while (!stream.atEnd()) {
        const QString line = stream.readLine();
        if (!line.isEmpty()) {
            rows.append(parseLine(line));
        }
    }

    file.close();
    return rows;
}

bool CsvFile::write(const QString &filePath, const QList<QStringList> &rows)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        return false;
    }

    QTextStream stream(&file);

    for (const QStringList &row : rows) {
        stream << formatLine(row) << QStringLiteral("\n");
    }

    file.close();
    return true;
}

QStringList CsvFile::parseLine(const QString &line)
{
    QStringList fields;
    QString field;
    bool inQuotes = false;
    const qsizetype length = line.length();

    for (qsizetype i = 0; i < length; ++i) {
        const QChar ch = line.at(i);

        if (inQuotes) {
            if (ch == QLatin1Char('"')) {
                // Check for escaped quote (RFC 4180: "" inside quoted field)
                if (i + 1 < length && line.at(i + 1) == QLatin1Char('"')) {
                    field.append(QLatin1Char('"'));
                    ++i;
                } else {
                    inQuotes = false;
                }
            } else {
                field.append(ch);
            }
        } else {
            if (ch == QLatin1Char('"')) {
                inQuotes = true;
            } else if (ch == QLatin1Char(',')) {
                fields.append(field);
                field.clear();
            } else {
                field.append(ch);
            }
        }
    }

    fields.append(field);
    return fields;
}

QString CsvFile::formatLine(const QStringList &fields)
{
    QStringList formatted;
    formatted.reserve(fields.size());

    for (const QString &field : fields) {
        if (field.contains(QLatin1Char(',')) ||
            field.contains(QLatin1Char('"')) ||
            field.contains(QLatin1Char('\n'))) {
            QString escaped = field;
            escaped.replace(QLatin1Char('"'), QStringLiteral("\"\""));
            formatted.append(QLatin1Char('"') + escaped + QLatin1Char('"'));
        } else {
            formatted.append(field);
        }
    }

    return formatted.join(QLatin1Char(','));
}

} // namespace macrosip
