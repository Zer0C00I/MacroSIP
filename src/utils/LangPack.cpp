#include "utils/LangPack.h"
#include <QFile>
#include <QTextStream>
#include <QFileInfo>

namespace macrosip {

LangPack &LangPack::instance()
{
    static LangPack pack;
    return pack;
}

bool LangPack::load(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    m_translations.clear();

    QTextStream stream(&file);
    stream.setCodec("UTF-8");

    while (!stream.atEnd()) {
        const QString line = stream.readLine().trimmed();

        if (line.isEmpty() || line.startsWith(QLatin1Char('#')) ||
            line.startsWith(QLatin1Char(';'))) {
            continue;
        }

        const int separatorPos = line.indexOf(QLatin1Char('='));
        if (separatorPos <= 0) {
            continue;
        }

        const QString key = line.left(separatorPos).trimmed();
        const QString value = line.mid(separatorPos + 1).trimmed();

        if (!key.isEmpty()) {
            m_translations.insert(key, value);
        }
    }

    file.close();

    const QFileInfo info(filePath);
    m_language = info.baseName();
    m_loaded = true;
    return true;
}

QString LangPack::translate(const QString &key) const
{
    return m_translations.value(key, key);
}

QString LangPack::translate(const QString &key, const QString &defaultValue) const
{
    return m_translations.value(key, defaultValue);
}

bool LangPack::isLoaded() const
{
    return m_loaded;
}

QString LangPack::currentLanguage() const
{
    return m_language;
}

} // namespace macrosip
