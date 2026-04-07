#include <QTest>
#include <QTemporaryDir>
#include "utils/CallHistoryStore.h"

using namespace macrosip;

class TestCallHistoryStore : public QObject {
    Q_OBJECT

private slots:
    void testSaveAndLoad()
    {
        QTemporaryDir tmpDir;
        QVERIFY(tmpDir.isValid());
        const QString path = tmpDir.path() + QStringLiteral("/calls.csv");

        CallHistoryStore store(path);

        QList<CallRecord> records;
        CallRecord r1;
        r1.id = QStringLiteral("id-001");
        r1.name = QStringLiteral("Alice");
        r1.number = QStringLiteral("100");
        r1.type = CallType::Outgoing;
        r1.duration = 120;
        r1.time = QDateTime(QDate(2025, 1, 15), QTime(10, 30, 0));
        r1.info = QStringLiteral("test call");
        records.append(r1);

        CallRecord r2;
        r2.id = QStringLiteral("id-002");
        r2.name = QStringLiteral("Bob");
        r2.number = QStringLiteral("200");
        r2.type = CallType::Missed;
        r2.duration = 0;
        r2.time = QDateTime(QDate(2025, 1, 16), QTime(14, 0, 0));
        records.append(r2);

        QVERIFY(store.save(records));

        QList<CallRecord> loaded = store.load();
        QCOMPARE(loaded.size(), 2);
        QCOMPARE(loaded[0].id, QStringLiteral("id-001"));
        QCOMPARE(loaded[0].name, QStringLiteral("Alice"));
        QCOMPARE(loaded[0].number, QStringLiteral("100"));
        QCOMPARE(loaded[0].type, CallType::Outgoing);
        QCOMPARE(loaded[0].duration, 120);
        QCOMPARE(loaded[0].info, QStringLiteral("test call"));

        QCOMPARE(loaded[1].id, QStringLiteral("id-002"));
        QCOMPARE(loaded[1].type, CallType::Missed);
    }

    void testAppend()
    {
        QTemporaryDir tmpDir;
        QVERIFY(tmpDir.isValid());
        const QString path = tmpDir.path() + QStringLiteral("/calls.csv");

        CallHistoryStore store(path);

        CallRecord r1;
        r1.id = QStringLiteral("id-100");
        r1.name = QStringLiteral("Charlie");
        r1.number = QStringLiteral("300");
        r1.type = CallType::Incoming;
        r1.duration = 60;
        r1.time = QDateTime(QDate(2025, 2, 1), QTime(9, 0, 0));

        // Append to non-existent file creates it
        QVERIFY(store.append(r1));

        CallRecord r2;
        r2.id = QStringLiteral("id-101");
        r2.name = QStringLiteral("Dave");
        r2.number = QStringLiteral("400");
        r2.type = CallType::Outgoing;
        r2.duration = 30;
        r2.time = QDateTime(QDate(2025, 2, 2), QTime(11, 0, 0));

        QVERIFY(store.append(r2));

        QList<CallRecord> loaded = store.load();
        QCOMPARE(loaded.size(), 2);
        QCOMPARE(loaded[0].number, QStringLiteral("300"));
        QCOMPARE(loaded[1].number, QStringLiteral("400"));
    }

    void testLoadEmpty()
    {
        QTemporaryDir tmpDir;
        QVERIFY(tmpDir.isValid());
        CallHistoryStore store(tmpDir.path() + QStringLiteral("/nonexistent.csv"));
        QList<CallRecord> loaded = store.load();
        QVERIFY(loaded.isEmpty());
    }

    void testRoundTripAllTypes()
    {
        QTemporaryDir tmpDir;
        QVERIFY(tmpDir.isValid());
        const QString path = tmpDir.path() + QStringLiteral("/calls.csv");

        CallHistoryStore store(path);

        QList<CallRecord> records;
        for (int i = 0; i < 4; ++i) {
            CallRecord r;
            r.id = QStringLiteral("type-%1").arg(i);
            r.number = QStringLiteral("55%1").arg(i);
            r.type = static_cast<CallType>(i);
            r.time = QDateTime::currentDateTime();
            records.append(r);
        }

        QVERIFY(store.save(records));
        QList<CallRecord> loaded = store.load();
        QCOMPARE(loaded.size(), 4);
        QCOMPARE(loaded[0].type, CallType::Outgoing);
        QCOMPARE(loaded[1].type, CallType::Incoming);
        QCOMPARE(loaded[2].type, CallType::Missed);
        QCOMPARE(loaded[3].type, CallType::Other);
    }
};

QTEST_GUILESS_MAIN(TestCallHistoryStore)
#include "test_callhistorystore.moc"
