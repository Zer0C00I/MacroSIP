#pragma once
#include <QList>
#include <QString>
#include "models/Contact.h"

namespace macrosip {

/**
 * Persists contacts to a CSV file.
 *
 * CSV columns: name, number, firstname, lastname, phone, mobile,
 *              email, address, city, state, zip, comment,
 *              presence, starred, directory, image
 */
class ContactStore {
public:
    explicit ContactStore(const QString &filePath);

    QList<Contact> load() const;
    bool save(const QList<Contact> &contacts) const;

    // Import/export with an arbitrary CSV path
    static QList<Contact> importCsv(const QString &filePath);
    static bool exportCsv(const QString &filePath,
                          const QList<Contact> &contacts);

private:
    QString m_filePath;

    static QStringList contactToRow(const Contact &c);
    static Contact rowToContact(const QStringList &row);
    static QStringList headerRow();
};

} // namespace macrosip
