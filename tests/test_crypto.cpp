#include <QtTest>
#include <QByteArray>
#include <QCryptographicHash>
#include "utils/Crypto.h"

using namespace macrosip;

class TestCrypto : public QObject {
    Q_OBJECT
private slots:
    void testHash();
    void testObfuscateDeobfuscate();
    void testEncryptDecrypt();
    void testGenerateKey();
    void testEncryptDecryptEmpty();
};

void TestCrypto::testHash()
{
    // SHA-256 known test vector: SHA256("") = e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855
    const QByteArray emptyHash = Crypto::hash(QString());
    QCOMPARE(emptyHash.toHex(),
             QByteArray("e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"));

    // SHA-256("hello") = 2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824
    const QByteArray helloHash = Crypto::hash(QStringLiteral("hello"));
    QCOMPARE(helloHash.toHex(),
             QByteArray("2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824"));

    // Deterministic: same input always gives same hash
    QCOMPARE(Crypto::hash(QStringLiteral("hello")), helloHash);
}

void TestCrypto::testObfuscateDeobfuscate()
{
    const QString original = QStringLiteral("MySecretPassword123!");
    const QString obfuscated = Crypto::obfuscate(original);

    // Obfuscated form should differ from original
    QVERIFY(obfuscated != original);

    // Roundtrip
    const QString restored = Crypto::deobfuscate(obfuscated);
    QCOMPARE(restored, original);

    // Empty string roundtrip
    QCOMPARE(Crypto::deobfuscate(Crypto::obfuscate(QString())), QString());
}

void TestCrypto::testEncryptDecrypt()
{
    const QByteArray key = Crypto::generateKey();
    const QString plaintext = QStringLiteral("Sensitive SIP credentials");

    const QByteArray ciphertext = Crypto::encrypt(plaintext, key);
    QVERIFY(!ciphertext.isEmpty());

    const QString decrypted = Crypto::decrypt(ciphertext, key);
    QCOMPARE(decrypted, plaintext);
}

void TestCrypto::testGenerateKey()
{
    const QByteArray key1 = Crypto::generateKey();
    const QByteArray key2 = Crypto::generateKey();

    // Keys should be 32 bytes
    QCOMPARE(key1.size(), 32);
    QCOMPARE(key2.size(), 32);

    // Two generated keys should differ (vanishingly small collision probability)
    QVERIFY(key1 != key2);
}

void TestCrypto::testEncryptDecryptEmpty()
{
    const QByteArray key = Crypto::generateKey();
    const QString plaintext;

    const QByteArray ciphertext = Crypto::encrypt(plaintext, key);
    const QString decrypted = Crypto::decrypt(ciphertext, key);
    QCOMPARE(decrypted, plaintext);
}

QTEST_MAIN(TestCrypto)
#include "test_crypto.moc"
