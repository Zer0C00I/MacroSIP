#include <QtTest>
#include <QSignalSpy>
#include "widgets/ContactsWidget.h"

using namespace macrosip;

class TestContactsWidget : public QObject {
    Q_OBJECT
private slots:
    void testDefaultState();
    void testLoadContacts();
    void testAddContact();
    void testRemoveContact();
    void testUpdatePresence();
    void testCallContactSignal();
    void testDeleteContactSignal();
};

void TestContactsWidget::testDefaultState()
{
    ContactsWidget w;
    // Should not crash; widget is empty
    QVERIFY(true);
}

void TestContactsWidget::testLoadContacts()
{
    ContactsWidget w;
    QList<Contact> contacts;

    Contact c1;
    c1.name = QStringLiteral("Alice");
    c1.number = QStringLiteral("100");
    contacts.append(c1);

    Contact c2;
    c2.name = QStringLiteral("Bob");
    c2.number = QStringLiteral("200");
    contacts.append(c2);

    w.loadContacts(contacts);
    // Should not crash
    QVERIFY(true);
}

void TestContactsWidget::testAddContact()
{
    ContactsWidget w;
    Contact c;
    c.name = QStringLiteral("Charlie");
    c.number = QStringLiteral("300");

    w.addContact(c);
    QVERIFY(true);
}

void TestContactsWidget::testRemoveContact()
{
    ContactsWidget w;
    Contact c;
    c.name = QStringLiteral("Charlie");
    c.number = QStringLiteral("300");
    w.addContact(c);

    w.removeContact(QStringLiteral("300"));
    // Removing non-existent should not crash
    w.removeContact(QStringLiteral("999"));
    QVERIFY(true);
}

void TestContactsWidget::testUpdatePresence()
{
    ContactsWidget w;
    Contact c;
    c.name = QStringLiteral("Alice");
    c.number = QStringLiteral("100");
    w.addContact(c);

    w.updatePresence(QStringLiteral("100"), PresenceStatus::Online);
    w.updatePresence(QStringLiteral("100"), PresenceStatus::Busy);
    w.updatePresence(QStringLiteral("999"), PresenceStatus::Away);  // no crash
    QVERIFY(true);
}

void TestContactsWidget::testCallContactSignal()
{
    ContactsWidget w;
    QSignalSpy spy(&w, &ContactsWidget::callContact);
    QVERIFY(spy.isValid());
}

void TestContactsWidget::testDeleteContactSignal()
{
    ContactsWidget w;
    QSignalSpy spy(&w, &ContactsWidget::deleteContact);
    QVERIFY(spy.isValid());
}

QTEST_MAIN(TestContactsWidget)
#include "test_contactswidget.moc"
