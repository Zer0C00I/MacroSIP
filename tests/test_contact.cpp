#include <QtTest>
#include <QJsonObject>
#include "models/Contact.h"

using namespace macrosip;

class TestContact : public QObject {
    Q_OBJECT
private slots:
    void testDefaultValues();
    void testIsValid();
    void testDisplayNameFromFirstLast();
    void testDisplayNameFromName();
    void testDisplayNameFirstOnly();
    void testDisplayNameLastOnly();
    void testJsonRoundTrip();
};

void TestContact::testDefaultValues()
{
    Contact c;
    QVERIFY(c.name.isEmpty());
    QVERIFY(c.number.isEmpty());
    QVERIFY(c.firstname.isEmpty());
    QVERIFY(c.lastname.isEmpty());
    QVERIFY(!c.presence);
    QVERIFY(!c.starred);
    QVERIFY(!c.directory);
    QCOMPARE(c.image, 0);
}

void TestContact::testIsValid()
{
    Contact c;
    QVERIFY(!c.isValid());

    c.name = QStringLiteral("Alice");
    QVERIFY(c.isValid());

    c.name.clear();
    QVERIFY(!c.isValid());

    c.number = QStringLiteral("100");
    QVERIFY(c.isValid());

    // Both set is also valid
    c.name = QStringLiteral("Alice");
    QVERIFY(c.isValid());
}

void TestContact::testDisplayNameFromFirstLast()
{
    Contact c;
    c.firstname = QStringLiteral("John");
    c.lastname = QStringLiteral("Doe");
    c.name = QStringLiteral("JD");
    // firstname + lastname takes priority over name
    QCOMPARE(c.displayName(), QStringLiteral("John Doe"));
}

void TestContact::testDisplayNameFromName()
{
    Contact c;
    c.name = QStringLiteral("Alice Smith");
    // No firstname/lastname set, falls back to name
    QCOMPARE(c.displayName(), QStringLiteral("Alice Smith"));
}

void TestContact::testDisplayNameFirstOnly()
{
    Contact c;
    c.firstname = QStringLiteral("Jane");
    QCOMPARE(c.displayName(), QStringLiteral("Jane"));
}

void TestContact::testDisplayNameLastOnly()
{
    Contact c;
    c.lastname = QStringLiteral("Smith");
    QCOMPARE(c.displayName(), QStringLiteral("Smith"));
}

void TestContact::testJsonRoundTrip()
{
    Contact original;
    original.name = QStringLiteral("Test User");
    original.number = QStringLiteral("1234567890");
    original.firstname = QStringLiteral("Test");
    original.lastname = QStringLiteral("User");
    original.phone = QStringLiteral("+1-555-0100");
    original.mobile = QStringLiteral("+1-555-0101");
    original.email = QStringLiteral("test@example.com");
    original.address = QStringLiteral("123 Main St");
    original.city = QStringLiteral("Springfield");
    original.state = QStringLiteral("IL");
    original.zip = QStringLiteral("62701");
    original.comment = QStringLiteral("VIP contact");
    original.presence = true;
    original.starred = true;
    original.directory = false;
    original.image = 42;

    const QJsonObject json = original.toJson();
    const Contact restored = Contact::fromJson(json);

    QCOMPARE(restored.name, original.name);
    QCOMPARE(restored.number, original.number);
    QCOMPARE(restored.firstname, original.firstname);
    QCOMPARE(restored.lastname, original.lastname);
    QCOMPARE(restored.phone, original.phone);
    QCOMPARE(restored.mobile, original.mobile);
    QCOMPARE(restored.email, original.email);
    QCOMPARE(restored.address, original.address);
    QCOMPARE(restored.city, original.city);
    QCOMPARE(restored.state, original.state);
    QCOMPARE(restored.zip, original.zip);
    QCOMPARE(restored.comment, original.comment);
    QCOMPARE(restored.presence, original.presence);
    QCOMPARE(restored.starred, original.starred);
    QCOMPARE(restored.directory, original.directory);
    QCOMPARE(restored.image, original.image);
}

QTEST_MAIN(TestContact)
#include "test_contact.moc"
