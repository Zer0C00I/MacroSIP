#pragma once
#include <QString>
#include <QByteArray>

namespace macrosip {

class Crypto {
public:
    static QByteArray encrypt(const QString &plaintext, const QByteArray &key);
    static QString decrypt(const QByteArray &ciphertext, const QByteArray &key);
    static QByteArray generateKey();
    static QByteArray hash(const QString &data);
    static QString obfuscate(const QString &password);
    static QString deobfuscate(const QString &obfuscated);
};

} // namespace macrosip
