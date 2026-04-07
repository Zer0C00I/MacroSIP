#include "utils/Crypto.h"
#include <QCryptographicHash>
#include <QRandomGenerator>

#ifdef OPENSSL_ENABLED
#include <openssl/evp.h>
#include <openssl/rand.h>
#endif

namespace macrosip {

namespace {

constexpr int kKeySize = 32;
constexpr int kIvSize = 16;

const QByteArray kObfuscationKey = QByteArrayLiteral("MacroSIP_Obfusc");

QByteArray xorTransform(const QByteArray &data, const QByteArray &key)
{
    QByteArray result(data.size(), '\0');
    for (qsizetype i = 0; i < data.size(); ++i) {
        result[i] = static_cast<char>(data.at(i) ^ key.at(i % key.size()));
    }
    return result;
}

} // anonymous namespace

QByteArray Crypto::encrypt(const QString &plaintext, const QByteArray &key)
{
    const QByteArray input = plaintext.toUtf8();

#ifdef OPENSSL_ENABLED
    QByteArray iv(kIvSize, '\0');
    RAND_bytes(reinterpret_cast<unsigned char *>(iv.data()), kIvSize);

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (ctx == nullptr) {
        return {};
    }

    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr,
                           reinterpret_cast<const unsigned char *>(key.constData()),
                           reinterpret_cast<const unsigned char *>(iv.constData())) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return {};
    }

    const int blockSize = EVP_CIPHER_block_size(EVP_aes_256_cbc());
    QByteArray ciphertext(input.size() + blockSize, '\0');
    int outLen = 0;

    if (EVP_EncryptUpdate(ctx,
                          reinterpret_cast<unsigned char *>(ciphertext.data()),
                          &outLen,
                          reinterpret_cast<const unsigned char *>(input.constData()),
                          static_cast<int>(input.size())) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return {};
    }

    int finalLen = 0;
    if (EVP_EncryptFinal_ex(ctx,
                            reinterpret_cast<unsigned char *>(ciphertext.data()) + outLen,
                            &finalLen) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return {};
    }

    EVP_CIPHER_CTX_free(ctx);
    ciphertext.resize(outLen + finalLen);
    return iv + ciphertext;
#else
    return xorTransform(input, key);
#endif
}

QString Crypto::decrypt(const QByteArray &ciphertext, const QByteArray &key)
{
#ifdef OPENSSL_ENABLED
    if (ciphertext.size() <= kIvSize) {
        return {};
    }

    const QByteArray iv = ciphertext.left(kIvSize);
    const QByteArray encrypted = ciphertext.mid(kIvSize);

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (ctx == nullptr) {
        return {};
    }

    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr,
                           reinterpret_cast<const unsigned char *>(key.constData()),
                           reinterpret_cast<const unsigned char *>(iv.constData())) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return {};
    }

    QByteArray plaintext(encrypted.size(), '\0');
    int outLen = 0;

    if (EVP_DecryptUpdate(ctx,
                          reinterpret_cast<unsigned char *>(plaintext.data()),
                          &outLen,
                          reinterpret_cast<const unsigned char *>(encrypted.constData()),
                          static_cast<int>(encrypted.size())) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return {};
    }

    int finalLen = 0;
    if (EVP_DecryptFinal_ex(ctx,
                            reinterpret_cast<unsigned char *>(plaintext.data()) + outLen,
                            &finalLen) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return {};
    }

    EVP_CIPHER_CTX_free(ctx);
    plaintext.resize(outLen + finalLen);
    return QString::fromUtf8(plaintext);
#else
    const QByteArray decrypted = xorTransform(ciphertext, key);
    return QString::fromUtf8(decrypted);
#endif
}

QByteArray Crypto::generateKey()
{
    QByteArray key(kKeySize, '\0');
    QRandomGenerator *rng = QRandomGenerator::global();
    for (int i = 0; i < kKeySize; ++i) {
        key[i] = static_cast<char>(static_cast<unsigned char>(rng->bounded(256)));
    }
    return key;
}

QByteArray Crypto::hash(const QString &data)
{
    return QCryptographicHash::hash(data.toUtf8(), QCryptographicHash::Sha256);
}

QString Crypto::obfuscate(const QString &password)
{
    const QByteArray raw = password.toUtf8();
    const QByteArray transformed = xorTransform(raw, kObfuscationKey);
    return QString::fromLatin1(transformed.toBase64());
}

QString Crypto::deobfuscate(const QString &obfuscated)
{
    const QByteArray transformed = QByteArray::fromBase64(obfuscated.toLatin1());
    const QByteArray raw = xorTransform(transformed, kObfuscationKey);
    return QString::fromUtf8(raw);
}

} // namespace macrosip
