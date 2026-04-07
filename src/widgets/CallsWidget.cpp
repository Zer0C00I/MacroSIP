#include "CallsWidget.h"
#include "models/CallRecord.h"

#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QHeaderView>
#include <QMenu>

namespace macrosip {

CallsWidget::CallsWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
}

void CallsWidget::loadCalls(const QList<CallRecord> &calls)
{
    m_allCalls = calls;
    applyFilter();
}

void CallsWidget::addCall(const CallRecord &call)
{
    m_allCalls.prepend(call);
    applyFilter();
}

void CallsWidget::clearHistory()
{
    m_allCalls.clear();
    m_callTree->clear();
}

void CallsWidget::onFilterChanged([[maybe_unused]] int index)
{
    applyFilter();
}

void CallsWidget::onItemDoubleClicked(QTreeWidgetItem *item,
                                       [[maybe_unused]] int column)
{
    if (!item)
        return;
    Q_EMIT redial(item->data(0, Qt::UserRole).toString());
}

void CallsWidget::onContextMenu(const QPoint &pos)
{
    QTreeWidgetItem *item = m_callTree->itemAt(pos);
    if (!item)
        return;

    QMenu menu(this);
    auto *callAction = menu.addAction(tr("Call"));
    auto *copyAction = menu.addAction(tr("Copy Number"));
    auto *deleteAction = menu.addAction(tr("Delete"));

    QAction *chosen = menu.exec(m_callTree->viewport()->mapToGlobal(pos));
    if (!chosen)
        return;

    const QString number = item->data(0, Qt::UserRole).toString();
    if (chosen == callAction) {
        Q_EMIT redial(number);
    } else if (chosen == copyAction) {
        QApplication::clipboard()->setText(number);
    } else if (chosen == deleteAction) {
        const QString id = item->data(0, Qt::UserRole + 1).toString();
        m_allCalls.erase(
            std::remove_if(m_allCalls.begin(), m_allCalls.end(),
                           [&id](const CallRecord &r) { return r.id == id; }),
            m_allCalls.end());
        delete item;
    }
}

void CallsWidget::setupUi()
{
    auto *layout = new QVBoxLayout(this);

    m_filterCombo = new QComboBox(this);
    m_filterCombo->addItem(tr("All"), -1);
    m_filterCombo->addItem(tr("Incoming"), callTypeToInt(CallType::Incoming));
    m_filterCombo->addItem(tr("Outgoing"), callTypeToInt(CallType::Outgoing));
    m_filterCombo->addItem(tr("Missed"), callTypeToInt(CallType::Missed));
    connect(m_filterCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &CallsWidget::onFilterChanged);
    layout->addWidget(m_filterCombo);

    m_callTree = new QTreeWidget(this);
    m_callTree->setHeaderLabels(
        {tr("Type"), tr("Name/Number"), tr("Duration"), tr("Time")});
    m_callTree->setRootIsDecorated(false);
    m_callTree->setAlternatingRowColors(true);
    m_callTree->header()->setStretchLastSection(true);
    m_callTree->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(m_callTree, &QTreeWidget::itemDoubleClicked,
            this, &CallsWidget::onItemDoubleClicked);
    connect(m_callTree, &QTreeWidget::customContextMenuRequested,
            this, &CallsWidget::onContextMenu);

    layout->addWidget(m_callTree);
}

void CallsWidget::applyFilter()
{
    m_callTree->clear();

    const int filterVal = m_filterCombo->currentData().toInt();

    for (const auto &rec : std::as_const(m_allCalls)) {
        if (filterVal >= 0 && callTypeToInt(rec.type) != filterVal)
            continue;

        auto *item = new QTreeWidgetItem;
        item->setText(0, rec.typeString());
        item->setText(1, rec.name.isEmpty() ? rec.number : rec.name);
        item->setText(2, rec.durationString());
        item->setText(3, rec.time.toString(QStringLiteral("yyyy-MM-dd hh:mm")));
        item->setData(0, Qt::UserRole, rec.number);
        item->setData(0, Qt::UserRole + 1, rec.id);
        m_callTree->addTopLevelItem(item);
    }
}

int CallsWidget::callTypeToInt(CallType type)
{
    return static_cast<int>(type);
}

} // namespace macrosip
