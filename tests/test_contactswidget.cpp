#include <QtTest>
#include <QSignalSpy>
#include <QTreeWidget>
#include <QLineEdit>
#include "widgets/ContactsWidget.h"

using namespace macrosip;

class TestContactsWidget : public QObject {
    Q_OBJECT
private:
    static Contact makeContact(const QString &name, const QString &number,
                               bool presence = false, bool starred = false)
    {
        Contact c;
        c.name = name;
        c.number = number;
        c.firstname = name.section(QLatin1Char(' '), 0, 0);
        c.lastname = name.section(QLatin1Char(' '), 1, 1);
        c.presence = presence;
        c.starred = starred;
        return c;
    }

private slots:
    void testDefaultEmpty();
    void testAddContact();
    void testLoadContacts();
    void testLoadContactsReplacesOld();
    void testRemoveContact();
    void testRemoveNonExistent();
    void testUpdatePresence();
    void testUpdatePresenceNonExistent();
    void testCallContactOnDoubleClick();
    void testSearchFilter();
    void testSearchFilterClear();
};

void TestContactsWidget::testDefaultEmpty()
{
    ContactsWidget w;
    QCOMPARE(w.contactCount(), 0);
}

void TestContactsWidget::testAddContact()
{
    ContactsWidget w;

    w.addContact(makeContact(QStringLiteral("Alice Smith"),
                             QStringLiteral("100")));
    QCOMPARE(w.contactCount(), 1);

    w.addContact(makeContact(QStringLiteral("Bob Jones"),
                             QStringLiteral("200")));
    QCOMPARE(w.contactCount(), 2);
}

void TestContactsWidget::testLoadContacts()
{
    ContactsWidget w;
    QList<Contact> contacts;
    contacts.append(makeContact(QStringLiteral("Alice"), QStringLiteral("100")));
    contacts.append(makeContact(QStringLiteral("Bob"), QStringLiteral("200")));
    contacts.append(makeContact(QStringLiteral("Charlie"), QStringLiteral("300")));

    w.loadContacts(contacts);
    QCOMPARE(w.contactCount(), 3);
}

void TestContactsWidget::testLoadContactsReplacesOld()
{
    ContactsWidget w;

    QList<Contact> first;
    first.append(makeContact(QStringLiteral("Alice"), QStringLiteral("100")));
    w.loadContacts(first);
    QCOMPARE(w.contactCount(), 1);

    QList<Contact> second;
    second.append(makeContact(QStringLiteral("Bob"), QStringLiteral("200")));
    second.append(makeContact(QStringLiteral("Charlie"), QStringLiteral("300")));
    w.loadContacts(second);
    QCOMPARE(w.contactCount(), 2);
}

void TestContactsWidget::testRemoveContact()
{
    ContactsWidget w;
    w.addContact(makeContact(QStringLiteral("Alice"), QStringLiteral("100")));
    w.addContact(makeContact(QStringLiteral("Bob"), QStringLiteral("200")));
    QCOMPARE(w.contactCount(), 2);

    w.removeContact(QStringLiteral("100"));
    QCOMPARE(w.contactCount(), 1);

    // Remaining contact should be Bob
    auto *tree = w.findChild<QTreeWidget *>();
    QVERIFY(tree != nullptr);
    QCOMPARE(tree->topLevelItem(0)->text(1), QStringLiteral("200"));
}

void TestContactsWidget::testRemoveNonExistent()
{
    ContactsWidget w;
    w.addContact(makeContact(QStringLiteral("Alice"), QStringLiteral("100")));
    QCOMPARE(w.contactCount(), 1);

    w.removeContact(QStringLiteral("999"));
    QCOMPARE(w.contactCount(), 1); // unchanged
}

void TestContactsWidget::testUpdatePresence()
{
    ContactsWidget w;
    w.addContact(makeContact(QStringLiteral("Alice"), QStringLiteral("100"), true));

    auto *tree = w.findChild<QTreeWidget *>();
    QVERIFY(tree != nullptr);

    // Initially presence column shows "Unknown" (monitoring enabled)
    // After updatePresence it should change
    w.updatePresence(QStringLiteral("100"), PresenceStatus::Online);
    QCOMPARE(tree->topLevelItem(0)->text(2), QObject::tr("Online"));

    w.updatePresence(QStringLiteral("100"), PresenceStatus::Busy);
    QCOMPARE(tree->topLevelItem(0)->text(2), QObject::tr("Busy"));

    w.updatePresence(QStringLiteral("100"), PresenceStatus::Away);
    QCOMPARE(tree->topLevelItem(0)->text(2), QObject::tr("Away"));
}

void TestContactsWidget::testUpdatePresenceNonExistent()
{
    ContactsWidget w;
    w.addContact(makeContact(QStringLiteral("Alice"), QStringLiteral("100")));

    // Updating a number that doesn't exist should not crash or change count
    w.updatePresence(QStringLiteral("999"), PresenceStatus::Online);
    QCOMPARE(w.contactCount(), 1);
}

void TestContactsWidget::testCallContactOnDoubleClick()
{
    ContactsWidget w;
    w.addContact(makeContact(QStringLiteral("Alice"), QStringLiteral("100")));

    QSignalSpy spy(&w, &ContactsWidget::callContact);

    auto *tree = w.findChild<QTreeWidget *>();
    QVERIFY(tree != nullptr);
    QVERIFY(tree->topLevelItemCount() == 1);

    // Simulate double-click
    QTreeWidgetItem *item = tree->topLevelItem(0);
    Q_EMIT tree->itemDoubleClicked(item, 0);

    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toString(), QStringLiteral("100"));
}

void TestContactsWidget::testSearchFilter()
{
    ContactsWidget w;
    w.addContact(makeContact(QStringLiteral("Alice"), QStringLiteral("100")));
    w.addContact(makeContact(QStringLiteral("Bob"), QStringLiteral("200")));
    w.addContact(makeContact(QStringLiteral("Charlie"), QStringLiteral("300")));

    QCOMPARE(w.contactCount(), 3);

    auto *searchEdit = w.findChild<QLineEdit *>();
    QVERIFY(searchEdit != nullptr);

    // Type "Bob" into search → only Bob should be visible
    searchEdit->setText(QStringLiteral("Bob"));

    auto *tree = w.findChild<QTreeWidget *>();
    QVERIFY(tree != nullptr);

    int visibleCount = 0;
    for (int i = 0; i < tree->topLevelItemCount(); ++i) {
        if (!tree->topLevelItem(i)->isHidden())
            ++visibleCount;
    }
    QCOMPARE(visibleCount, 1);
}

void TestContactsWidget::testSearchFilterClear()
{
    ContactsWidget w;
    w.addContact(makeContact(QStringLiteral("Alice"), QStringLiteral("100")));
    w.addContact(makeContact(QStringLiteral("Bob"), QStringLiteral("200")));

    auto *searchEdit = w.findChild<QLineEdit *>();
    QVERIFY(searchEdit != nullptr);

    // Filter, then clear → all visible again
    searchEdit->setText(QStringLiteral("Alice"));
    searchEdit->clear();

    auto *tree = w.findChild<QTreeWidget *>();
    QVERIFY(tree != nullptr);
    int visibleCount = 0;
    for (int i = 0; i < tree->topLevelItemCount(); ++i) {
        if (!tree->topLevelItem(i)->isHidden())
            ++visibleCount;
    }
    QCOMPARE(visibleCount, 2);
}

QTEST_MAIN(TestContactsWidget)
#include "test_contactswidget.moc"
