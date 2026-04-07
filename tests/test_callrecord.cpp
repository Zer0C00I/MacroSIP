#include <QtTest>
#include <QDateTime>
#include "models/CallRecord.h"

using namespace macrosip;

class TestCallRecord : public QObject {
    Q_OBJECT
private slots:
    void testDefaultValues();
    void testIsValid();
    void testDurationStringZero();
    void testDurationStringComplex();
    void testDurationStringNegative();
    void testTypeString();
};

void TestCallRecord::testDefaultValues()
{
    CallRecord rec;
    QVERIFY(rec.id.isEmpty());
    QVERIFY(rec.name.isEmpty());
    QVERIFY(rec.number.isEmpty());
    QVERIFY(rec.info.isEmpty());
    QCOMPARE(rec.type, CallType::Other);
    QCOMPARE(rec.duration, 0);
    QVERIFY(!rec.time.isValid());
}

void TestCallRecord::testIsValid()
{
    CallRecord rec;
    QVERIFY(!rec.isValid());

    rec.number = QStringLiteral("100");
    QVERIFY(!rec.isValid());

    rec.time = QDateTime::currentDateTime();
    QVERIFY(rec.isValid());

    // Clear number — invalid again
    rec.number.clear();
    QVERIFY(!rec.isValid());
}

void TestCallRecord::testDurationStringZero()
{
    CallRecord rec;
    rec.duration = 0;
    QCOMPARE(rec.durationString(), QStringLiteral("00:00:00"));
}

void TestCallRecord::testDurationStringComplex()
{
    CallRecord rec;
    rec.duration = 3661;
    QCOMPARE(rec.durationString(), QStringLiteral("01:01:01"));

    rec.duration = 59;
    QCOMPARE(rec.durationString(), QStringLiteral("00:00:59"));

    rec.duration = 3600;
    QCOMPARE(rec.durationString(), QStringLiteral("01:00:00"));

    rec.duration = 86399; // 23:59:59
    QCOMPARE(rec.durationString(), QStringLiteral("23:59:59"));
}

void TestCallRecord::testDurationStringNegative()
{
    CallRecord rec;
    rec.duration = -5;
    QCOMPARE(rec.durationString(), QStringLiteral("00:00:00"));
}

void TestCallRecord::testTypeString()
{
    CallRecord rec;

    rec.type = CallType::Outgoing;
    QCOMPARE(rec.typeString(), QStringLiteral("outgoing"));

    rec.type = CallType::Incoming;
    QCOMPARE(rec.typeString(), QStringLiteral("incoming"));

    rec.type = CallType::Missed;
    QCOMPARE(rec.typeString(), QStringLiteral("missed"));

    rec.type = CallType::Other;
    QCOMPARE(rec.typeString(), QStringLiteral("other"));
}

QTEST_MAIN(TestCallRecord)
#include "test_callrecord.moc"
