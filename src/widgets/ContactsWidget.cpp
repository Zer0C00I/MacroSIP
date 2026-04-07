#include "ContactsWidget.h"
#include "models/Contact.h"
#include "sip/SipTypes.h"

#include <QAction>
#include <QHeaderView>

namespace macrosip {

ContactsWidget::ContactsWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
}

void ContactsWidget::loadContacts(const QList<Contact> &contacts)
{
    m_contactTree->clear();
    for (const auto &c : contacts)
        addContact(c);
}

void ContactsWidget::addContact(const Contact &contact)
{
    auto *item = new QTreeWidgetItem;
    item->setText(0, contact.name);
    item->setText(1, contact.number);
    // Show initial "Unknown" when presence monitoring is enabled;
    // updatePresence() will replace it once the server responds.
    item->setText(2, contact.presence
                         ? presenceToString(PresenceStatus::Unknown)
                         : QString());
    item->setData(0, Qt::UserRole, contact.number);
    item->setData(0, Qt::UserRole + 1, contact.firstname);
    item->setData(0, Qt::UserRole + 2, contact.lastname);
    item->setData(0, Qt::UserRole + 3, contact.phone);
    item->setData(0, Qt::UserRole + 4, contact.mobile);
    item->setData(0, Qt::UserRole + 5, contact.email);
    item->setData(0, Qt::UserRole + 6, contact.presence);
    item->setData(0, Qt::UserRole + 7, contact.starred);
    m_contactTree->addTopLevelItem(item);
}

void ContactsWidget::removeContact(const QString &number)
{
    QTreeWidgetItem *item = findItemByNumber(number);
    if (item)
        delete item;
}

void ContactsWidget::updatePresence(const QString &number,
                                     PresenceStatus status)
{
    QTreeWidgetItem *item = findItemByNumber(number);
    if (item)
        item->setText(2, presenceToString(status));
}

void ContactsWidget::onSearchTextChanged(const QString &text)
{
    const QString filter = text.trimmed().toLower();
    for (int i = 0; i < m_contactTree->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = m_contactTree->topLevelItem(i);
        if (filter.isEmpty()) {
            item->setHidden(false);
        } else {
            const bool match =
                item->text(0).toLower().contains(filter) ||
                item->text(1).toLower().contains(filter);
            item->setHidden(!match);
        }
    }
}

void ContactsWidget::onItemDoubleClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    if (!item)
        return;
    Q_EMIT callContact(item->text(1));
}

void ContactsWidget::onContextMenu(const QPoint &pos)
{
    QTreeWidgetItem *item = m_contactTree->itemAt(pos);
    if (!item)
        return;

    QMenu menu(this);
    auto *callAction = menu.addAction(tr("Call"));
    auto *editAction = menu.addAction(tr("Edit"));
    auto *deleteAction = menu.addAction(tr("Delete"));

    QAction *chosen = menu.exec(m_contactTree->viewport()->mapToGlobal(pos));
    if (!chosen)
        return;

    if (chosen == callAction) {
        Q_EMIT callContact(item->text(1));
    } else if (chosen == editAction) {
        Q_EMIT editContact(contactFromItem(item));
    } else if (chosen == deleteAction) {
        Q_EMIT deleteContact(item->text(1));
    }
}

void ContactsWidget::setupUi()
{
    auto *layout = new QVBoxLayout(this);

    m_searchEdit = new QLineEdit(this);
    m_searchEdit->setPlaceholderText(tr("Search contacts..."));
    m_searchEdit->setClearButtonEnabled(true);
    connect(m_searchEdit, &QLineEdit::textChanged,
            this, &ContactsWidget::onSearchTextChanged);
    layout->addWidget(m_searchEdit);

    m_contactTree = new QTreeWidget(this);
    m_contactTree->setHeaderLabels({tr("Name"), tr("Number"), tr("Status")});
    m_contactTree->setRootIsDecorated(false);
    m_contactTree->setAlternatingRowColors(true);
    m_contactTree->setSortingEnabled(true);
    m_contactTree->sortByColumn(0, Qt::AscendingOrder);
    m_contactTree->header()->setStretchLastSection(true);
    m_contactTree->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(m_contactTree, &QTreeWidget::itemDoubleClicked,
            this, &ContactsWidget::onItemDoubleClicked);
    connect(m_contactTree, &QTreeWidget::customContextMenuRequested,
            this, &ContactsWidget::onContextMenu);

    layout->addWidget(m_contactTree);
}

QTreeWidgetItem *ContactsWidget::findItemByNumber(const QString &number) const
{
    for (int i = 0; i < m_contactTree->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = m_contactTree->topLevelItem(i);
        if (item->text(1) == number)
            return item;
    }
    return nullptr;
}

QString ContactsWidget::presenceToString(PresenceStatus status)
{
    switch (status) {
    case PresenceStatus::Online:     return tr("Online");
    case PresenceStatus::Offline:    return tr("Offline");
    case PresenceStatus::Away:       return tr("Away");
    case PresenceStatus::Busy:       return tr("Busy");
    case PresenceStatus::OnThePhone: return tr("On the Phone");
    case PresenceStatus::Idle:       return tr("Idle");
    case PresenceStatus::Unknown:    return tr("Unknown");
    }
    return {};
}

Contact ContactsWidget::contactFromItem(QTreeWidgetItem *item) const
{
    Contact c;
    c.name      = item->text(0);
    c.number    = item->text(1);
    c.firstname = item->data(0, Qt::UserRole + 1).toString();
    c.lastname  = item->data(0, Qt::UserRole + 2).toString();
    c.phone     = item->data(0, Qt::UserRole + 3).toString();
    c.mobile    = item->data(0, Qt::UserRole + 4).toString();
    c.email     = item->data(0, Qt::UserRole + 5).toString();
    c.presence  = item->data(0, Qt::UserRole + 6).toBool();
    c.starred   = item->data(0, Qt::UserRole + 7).toBool();
    return c;
}

} // namespace macrosip
