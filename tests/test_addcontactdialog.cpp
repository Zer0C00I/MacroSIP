#include <QtTest>
#include "dialogs/AddContactDialog.h"
#include "models/Contact.h"

using namespace macrosip;

class TestAddContactDialog : public QObject {
    Q_OBJECT
private slots:
    void testConstruction();
    void testSetContactGetContact();
    void testRoundTrip();
};

void TestAddContactDialog::testConstruction()
{
    AddContactDialog dlg;
    Contact c = dlg.contact();
    QVERIFY(c.name.isEmpty());
    QVERIFY(c.number.isEmpty());
}

void TestAddContactDialog::testSetContactGetContact()
{
    AddContactDialog dlg;
    Contact c;
    c.name = QStringLiteral("Alice");
    c.number = QStringLiteral("100");
    c.firstname = QStringLiteral("Alice");
    c.lastname = QStringLiteral("Smith");
    c.phone = QStringLiteral("555-1234");
    c.mobile = QStringLiteral("555-5678");
    c.email = QStringLiteral("alice@example.com");

    dlg.setContact(c);
    Contact result = dlg.contact();

    QCOMPARE(result.name, QStringLiteral("Alice"));
    QCOMPARE(result.number, QStringLiteral("100"));
    QCOMPARE(result.firstname, QStringLiteral("Alice"));
    QCOMPARE(result.lastname, QStringLiteral("Smith"));
    QCOMPARE(result.phone, QStringLiteral("555-1234"));
    QCOMPARE(result.mobile, QStringLiteral("555-5678"));
    QCOMPARE(result.email, QStringLiteral("alice@example.com"));
}

void TestAddContactDialog::testRoundTrip()
{
    AddContactDialog dlg;
    Contact c;
    c.name = QStringLiteral("Bob");
    c.number = QStringLiteral("200");
    c.address = QStringLiteral("123 Main St");
    c.city = QStringLiteral("Anytown");
    c.state = QStringLiteral("CA");
    c.zip = QStringLiteral("12345");
    c.comment = QStringLiteral("VIP client");
    c.presence = true;
    c.starred = true;

    dlg.setContact(c);
    Contact result = dlg.contact();

    QCOMPARE(result.name, c.name);
    QCOMPARE(result.number, c.number);
    QCOMPARE(result.address, c.address);
    QCOMPARE(result.city, c.city);
    QCOMPARE(result.state, c.state);
    QCOMPARE(result.zip, c.zip);
    QCOMPARE(result.comment, c.comment);
    QCOMPARE(result.presence, c.presence);
    QCOMPARE(result.starred, c.starred);
}

QTEST_MAIN(TestAddContactDialog)
#include "test_addcontactdialog.moc"
