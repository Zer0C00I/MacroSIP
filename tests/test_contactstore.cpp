#include <QTest>
#include <QTemporaryDir>
#include "utils/ContactStore.h"

using namespace macrosip;

class TestContactStore : public QObject {
    Q_OBJECT

private slots:
    void testSaveAndLoad()
    {
        QTemporaryDir tmpDir;
        QVERIFY(tmpDir.isValid());
        const QString path = tmpDir.path() + QStringLiteral("/contacts.csv");

        ContactStore store(path);

        QList<Contact> contacts;
        Contact c1;
        c1.name = QStringLiteral("Alice");
        c1.number = QStringLiteral("100");
        c1.firstname = QStringLiteral("Alice");
        c1.lastname = QStringLiteral("Smith");
        c1.email = QStringLiteral("alice@test.com");
        c1.presence = true;
        c1.starred = true;
        contacts.append(c1);

        Contact c2;
        c2.name = QStringLiteral("Bob");
        c2.number = QStringLiteral("200");
        c2.mobile = QStringLiteral("+1234567890");
        c2.city = QStringLiteral("New York");
        contacts.append(c2);

        QVERIFY(store.save(contacts));

        QList<Contact> loaded = store.load();
        QCOMPARE(loaded.size(), 2);
        QCOMPARE(loaded[0].name, QStringLiteral("Alice"));
        QCOMPARE(loaded[0].number, QStringLiteral("100"));
        QCOMPARE(loaded[0].firstname, QStringLiteral("Alice"));
        QCOMPARE(loaded[0].lastname, QStringLiteral("Smith"));
        QCOMPARE(loaded[0].email, QStringLiteral("alice@test.com"));
        QVERIFY(loaded[0].presence);
        QVERIFY(loaded[0].starred);

        QCOMPARE(loaded[1].name, QStringLiteral("Bob"));
        QCOMPARE(loaded[1].number, QStringLiteral("200"));
        QCOMPARE(loaded[1].mobile, QStringLiteral("+1234567890"));
        QCOMPARE(loaded[1].city, QStringLiteral("New York"));
        QVERIFY(!loaded[1].presence);
        QVERIFY(!loaded[1].starred);
    }

    void testImportExport()
    {
        QTemporaryDir tmpDir;
        QVERIFY(tmpDir.isValid());
        const QString exportPath = tmpDir.path() + QStringLiteral("/export.csv");

        QList<Contact> contacts;
        Contact c;
        c.name = QStringLiteral("Test User");
        c.number = QStringLiteral("555");
        c.comment = QStringLiteral("Has a comma, in comment");
        contacts.append(c);

        QVERIFY(ContactStore::exportCsv(exportPath, contacts));

        QList<Contact> imported = ContactStore::importCsv(exportPath);
        QCOMPARE(imported.size(), 1);
        QCOMPARE(imported[0].name, QStringLiteral("Test User"));
        QCOMPARE(imported[0].number, QStringLiteral("555"));
        QCOMPARE(imported[0].comment, QStringLiteral("Has a comma, in comment"));
    }

    void testLoadEmpty()
    {
        ContactStore store(QStringLiteral("/tmp/nonexistent_contacts.csv"));
        QList<Contact> loaded = store.load();
        QVERIFY(loaded.isEmpty());
    }

    void testAllFields()
    {
        QTemporaryDir tmpDir;
        QVERIFY(tmpDir.isValid());
        const QString path = tmpDir.path() + QStringLiteral("/full.csv");

        Contact c;
        c.name      = QStringLiteral("Full Contact");
        c.number    = QStringLiteral("999");
        c.firstname = QStringLiteral("First");
        c.lastname  = QStringLiteral("Last");
        c.phone     = QStringLiteral("111");
        c.mobile    = QStringLiteral("222");
        c.email     = QStringLiteral("full@test.com");
        c.address   = QStringLiteral("123 Main St");
        c.city      = QStringLiteral("TestCity");
        c.state     = QStringLiteral("TS");
        c.zip       = QStringLiteral("12345");
        c.comment   = QStringLiteral("A comment");
        c.presence  = true;
        c.starred   = false;
        c.directory = true;
        c.image     = 42;

        ContactStore store(path);
        QVERIFY(store.save({c}));

        QList<Contact> loaded = store.load();
        QCOMPARE(loaded.size(), 1);
        const Contact &l = loaded[0];
        QCOMPARE(l.name,      QStringLiteral("Full Contact"));
        QCOMPARE(l.number,    QStringLiteral("999"));
        QCOMPARE(l.firstname, QStringLiteral("First"));
        QCOMPARE(l.lastname,  QStringLiteral("Last"));
        QCOMPARE(l.phone,     QStringLiteral("111"));
        QCOMPARE(l.mobile,    QStringLiteral("222"));
        QCOMPARE(l.email,     QStringLiteral("full@test.com"));
        QCOMPARE(l.address,   QStringLiteral("123 Main St"));
        QCOMPARE(l.city,      QStringLiteral("TestCity"));
        QCOMPARE(l.state,     QStringLiteral("TS"));
        QCOMPARE(l.zip,       QStringLiteral("12345"));
        QCOMPARE(l.comment,   QStringLiteral("A comment"));
        QVERIFY(l.presence);
        QVERIFY(!l.starred);
        QVERIFY(l.directory);
        QCOMPARE(l.image, 42);
    }
};

QTEST_GUILESS_MAIN(TestContactStore)
#include "test_contactstore.moc"
