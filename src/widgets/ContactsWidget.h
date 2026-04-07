#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QMenu>
#include <QList>

#include "models/Contact.h"
#include "sip/SipTypes.h"

namespace macrosip {

class ContactsWidget : public QWidget {
    Q_OBJECT

public:
    explicit ContactsWidget(QWidget *parent = nullptr);
    ~ContactsWidget() override = default;

    void loadContacts(const QList<Contact> &contacts);
    void addContact(const Contact &contact);
    void removeContact(const QString &number);
    void updatePresence(const QString &number, PresenceStatus status);

Q_SIGNALS:
    void contactSelected(const macrosip::Contact &contact);
    void callContact(const QString &number);
    void editContact(const macrosip::Contact &contact);
    void deleteContact(const QString &number);

private Q_SLOTS:
    void onSearchTextChanged(const QString &text);
    void onItemDoubleClicked(QTreeWidgetItem *item, int column);
    void onContextMenu(const QPoint &pos);

private:
    void setupUi();
    QTreeWidgetItem *findItemByNumber(const QString &number) const;
    static QString presenceToString(PresenceStatus status);
    Contact contactFromItem(QTreeWidgetItem *item) const;

    QLineEdit *m_searchEdit = nullptr;
    QTreeWidget *m_contactTree = nullptr;
};

} // namespace macrosip
