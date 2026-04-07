#pragma once
#include <QString>
#include <QStringList>
#include <QList>

namespace macrosip {

class CsvFile {
public:
    static QList<QStringList> read(const QString &filePath);
    static bool write(const QString &filePath, const QList<QStringList> &rows);
    static QStringList parseLine(const QString &line);
    static QString formatLine(const QStringList &fields);
};

} // namespace macrosip
