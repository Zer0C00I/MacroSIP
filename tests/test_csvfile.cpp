#include <QtTest>
#include <QTemporaryFile>
#include "utils/CsvFile.h"

using namespace macrosip;

class TestCsvFile : public QObject {
    Q_OBJECT
private slots:
    void testParseLine();
    void testParseLineQuoted();
    void testFormatLine();
    void testFormatLineWithSpecialChars();
    void testReadWrite();
    void testEmptyFields();
};

void TestCsvFile::testParseLine()
{
    const QStringList fields = CsvFile::parseLine(QStringLiteral("alice,100,sip.example.com"));
    QCOMPARE(fields.size(), 3);
    QCOMPARE(fields.at(0), QStringLiteral("alice"));
    QCOMPARE(fields.at(1), QStringLiteral("100"));
    QCOMPARE(fields.at(2), QStringLiteral("sip.example.com"));
}

void TestCsvFile::testParseLineQuoted()
{
    // Field containing comma
    const QStringList fields1 = CsvFile::parseLine(QStringLiteral("\"Doe, John\",200,server"));
    QCOMPARE(fields1.size(), 3);
    QCOMPARE(fields1.at(0), QStringLiteral("Doe, John"));
    QCOMPARE(fields1.at(1), QStringLiteral("200"));

    // Field containing escaped double-quote (RFC 4180: "" → ")
    const QStringList fields2 = CsvFile::parseLine(QStringLiteral("\"He said \"\"hello\"\"\",300"));
    QCOMPARE(fields2.size(), 2);
    QCOMPARE(fields2.at(0), QStringLiteral("He said \"hello\""));
    QCOMPARE(fields2.at(1), QStringLiteral("300"));
}

void TestCsvFile::testFormatLine()
{
    const QStringList fields = {
        QStringLiteral("alice"),
        QStringLiteral("100"),
        QStringLiteral("active")
    };
    QCOMPARE(CsvFile::formatLine(fields), QStringLiteral("alice,100,active"));
}

void TestCsvFile::testFormatLineWithSpecialChars()
{
    // Field with comma gets quoted
    const QStringList fields1 = {
        QStringLiteral("Doe, John"),
        QStringLiteral("200")
    };
    QCOMPARE(CsvFile::formatLine(fields1), QStringLiteral("\"Doe, John\",200"));

    // Field with double-quote gets escaped and quoted
    const QStringList fields2 = {
        QStringLiteral("He said \"hello\""),
        QStringLiteral("300")
    };
    QCOMPARE(CsvFile::formatLine(fields2),
             QStringLiteral("\"He said \"\"hello\"\"\",300"));
}

void TestCsvFile::testReadWrite()
{
    QTemporaryFile tempFile;
    QVERIFY(tempFile.open());
    const QString path = tempFile.fileName();
    tempFile.close();

    const QList<QStringList> original = {
        {QStringLiteral("name"), QStringLiteral("number"), QStringLiteral("status")},
        {QStringLiteral("Alice"), QStringLiteral("100"), QStringLiteral("online")},
        {QStringLiteral("Bob"), QStringLiteral("200"), QStringLiteral("offline")}
    };

    QVERIFY(CsvFile::write(path, original));

    const QList<QStringList> loaded = CsvFile::read(path);
    QCOMPARE(loaded.size(), original.size());

    for (int i = 0; i < original.size(); ++i) {
        QCOMPARE(loaded.at(i), original.at(i));
    }
}

void TestCsvFile::testEmptyFields()
{
    // Parse line with empty fields
    const QStringList fields = CsvFile::parseLine(QStringLiteral(",hello,,world,"));
    QCOMPARE(fields.size(), 5);
    QCOMPARE(fields.at(0), QString());
    QCOMPARE(fields.at(1), QStringLiteral("hello"));
    QCOMPARE(fields.at(2), QString());
    QCOMPARE(fields.at(3), QStringLiteral("world"));
    QCOMPARE(fields.at(4), QString());

    // Format and re-parse preserves empty fields
    const QStringList input = {QString(), QStringLiteral("data"), QString()};
    const QString line = CsvFile::formatLine(input);
    const QStringList reparsed = CsvFile::parseLine(line);
    QCOMPARE(reparsed, input);
}

QTEST_MAIN(TestCsvFile)
#include "test_csvfile.moc"
