#pragma once
#include <QString>
#include <QMap>

namespace macrosip {

class LangPack {
public:
    static LangPack &instance();

    bool load(const QString &filePath);
    QString translate(const QString &key) const;
    QString translate(const QString &key, const QString &defaultValue) const;
    bool isLoaded() const;
    QString currentLanguage() const;

private:
    LangPack() = default;
    QMap<QString, QString> m_translations;
    QString m_language;
    bool m_loaded = false;
};

#define TR(key) macrosip::LangPack::instance().translate(QStringLiteral(key))
#define TR_DEFAULT(key, def) macrosip::LangPack::instance().translate(QStringLiteral(key), QStringLiteral(def))

} // namespace macrosip
