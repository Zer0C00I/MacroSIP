#include "models/Contact.h"

namespace macrosip {

bool Contact::isValid() const
{
    return !number.isEmpty() || !name.isEmpty();
}

QString Contact::displayName() const
{
    if (!firstname.isEmpty() || !lastname.isEmpty()) {
        QString dn;
        if (!firstname.isEmpty()) {
            dn = firstname;
        }
        if (!lastname.isEmpty()) {
            if (!dn.isEmpty()) {
                dn += QLatin1Char(' ');
            }
            dn += lastname;
        }
        return dn;
    }
    return name;
}

QJsonObject Contact::toJson() const
{
    QJsonObject obj;
    obj[QStringLiteral("name")] = name;
    obj[QStringLiteral("number")] = number;
    obj[QStringLiteral("firstname")] = firstname;
    obj[QStringLiteral("lastname")] = lastname;
    obj[QStringLiteral("phone")] = phone;
    obj[QStringLiteral("mobile")] = mobile;
    obj[QStringLiteral("email")] = email;
    obj[QStringLiteral("address")] = address;
    obj[QStringLiteral("city")] = city;
    obj[QStringLiteral("state")] = state;
    obj[QStringLiteral("zip")] = zip;
    obj[QStringLiteral("comment")] = comment;
    obj[QStringLiteral("presence")] = presence;
    obj[QStringLiteral("starred")] = starred;
    obj[QStringLiteral("directory")] = directory;
    obj[QStringLiteral("image")] = image;
    return obj;
}

Contact Contact::fromJson(const QJsonObject &obj)
{
    Contact c;
    c.name = obj.value(QStringLiteral("name")).toString();
    c.number = obj.value(QStringLiteral("number")).toString();
    c.firstname = obj.value(QStringLiteral("firstname")).toString();
    c.lastname = obj.value(QStringLiteral("lastname")).toString();
    c.phone = obj.value(QStringLiteral("phone")).toString();
    c.mobile = obj.value(QStringLiteral("mobile")).toString();
    c.email = obj.value(QStringLiteral("email")).toString();
    c.address = obj.value(QStringLiteral("address")).toString();
    c.city = obj.value(QStringLiteral("city")).toString();
    c.state = obj.value(QStringLiteral("state")).toString();
    c.zip = obj.value(QStringLiteral("zip")).toString();
    c.comment = obj.value(QStringLiteral("comment")).toString();
    c.presence = obj.value(QStringLiteral("presence")).toBool();
    c.starred = obj.value(QStringLiteral("starred")).toBool();
    c.directory = obj.value(QStringLiteral("directory")).toBool();
    c.image = obj.value(QStringLiteral("image")).toInt();
    return c;
}

} // namespace macrosip
