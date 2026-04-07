#include <QtTest>
#include <QTemporaryFile>
#include <QTextStream>
#include "utils/LangPack.h"

using namespace macrosip;

class TestLangPack : public QObject {
    Q_OBJECT
private slots:
    void testIsLoaded();
    void testLoadAndTranslate();
    void testDefaultValue();
    void testMissingKey();
    void testCommentsAndBlanks();
};

static QString writeLangFile(const QString &content)
{
    auto *file = new QTemporaryFile(QStringLiteral("langpack_XXXXXX"));
    file->setAutoRemove(true);
    file->open();

    QTextStream stream(file);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    stream.setCodec("UTF-8");
#endif
    stream << content;
    stream.flush();

    const QString path = file->fileName();
    file->close();
    // Prevent deletion while test uses the file; leaked intentionally (small, temp)
    file->setAutoRemove(false);
    return path;
}

void TestLangPack::testIsLoaded()
{
    // Create a fresh LangPack instance (not the singleton, so we don't pollute state)
    // Since LangPack::instance() is a singleton we test via its public API
    LangPack &lp = LangPack::instance();

    const QString path = writeLangFile(QStringLiteral("greeting=Hello\n"));
    QVERIFY(lp.load(path));
    QVERIFY(lp.isLoaded());
    QFile::remove(path);
}

void TestLangPack::testLoadAndTranslate()
{
    const QString content = QStringLiteral(
        "greeting=Hello\n"
        "farewell=Goodbye\n"
        "welcome=Welcome to MacroSIP\n"
    );
    const QString path = writeLangFile(content);

    LangPack &lp = LangPack::instance();
    QVERIFY(lp.load(path));

    QCOMPARE(lp.translate(QStringLiteral("greeting")), QStringLiteral("Hello"));
    QCOMPARE(lp.translate(QStringLiteral("farewell")), QStringLiteral("Goodbye"));
    QCOMPARE(lp.translate(QStringLiteral("welcome")), QStringLiteral("Welcome to MacroSIP"));

    QFile::remove(path);
}

void TestLangPack::testDefaultValue()
{
    const QString path = writeLangFile(QStringLiteral("key1=Value1\n"));
    LangPack &lp = LangPack::instance();
    QVERIFY(lp.load(path));

    // Existing key ignores default
    QCOMPARE(lp.translate(QStringLiteral("key1"), QStringLiteral("Fallback")),
             QStringLiteral("Value1"));

    // Missing key returns supplied default
    QCOMPARE(lp.translate(QStringLiteral("nonexistent"), QStringLiteral("DefaultVal")),
             QStringLiteral("DefaultVal"));

    QFile::remove(path);
}

void TestLangPack::testMissingKey()
{
    const QString path = writeLangFile(QStringLiteral("only=exists\n"));
    LangPack &lp = LangPack::instance();
    QVERIFY(lp.load(path));

    // Missing key with no default returns the key itself
    QCOMPARE(lp.translate(QStringLiteral("missing_key")), QStringLiteral("missing_key"));

    QFile::remove(path);
}

void TestLangPack::testCommentsAndBlanks()
{
    const QString content = QStringLiteral(
        "# This is a comment\n"
        "; Another comment\n"
        "\n"
        "real_key=real_value\n"
        "  \n"
        "another=data\n"
    );
    const QString path = writeLangFile(content);

    LangPack &lp = LangPack::instance();
    QVERIFY(lp.load(path));

    QCOMPARE(lp.translate(QStringLiteral("real_key")), QStringLiteral("real_value"));
    QCOMPARE(lp.translate(QStringLiteral("another")), QStringLiteral("data"));
    // Comment lines should not be parsed as keys
    QCOMPARE(lp.translate(QStringLiteral("# This is a comment")),
             QStringLiteral("# This is a comment"));

    QFile::remove(path);
}

QTEST_MAIN(TestLangPack)
#include "test_langpack.moc"
