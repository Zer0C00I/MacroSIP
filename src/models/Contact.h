#pragma once
#include <QString>
#include <QList>
#include <QJsonObject>

namespace macrosip {

struct Contact {
    QString name;
    QString number;
    QString firstname;
    QString lastname;
    QString phone;
    QString mobile;
    QString email;
    QString address;
    QString city;
    QString state;
    QString zip;
    QString comment;
    bool presence = false;
    bool starred = false;
    bool directory = false;
    int image = 0;

    bool isValid() const;
    QString displayName() const;
    QJsonObject toJson() const;
    static Contact fromJson(const QJsonObject &obj);
};

} // namespace macrosip
