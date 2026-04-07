#pragma once

#include <QWidget>
#include <QComboBox>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QList>

#include "models/CallRecord.h"

namespace macrosip {

class CallsWidget : public QWidget {
    Q_OBJECT

public:
    explicit CallsWidget(QWidget *parent = nullptr);
    ~CallsWidget() override = default;

    void loadCalls(const QList<CallRecord> &calls);
    void addCall(const CallRecord &call);
    void clearHistory();

Q_SIGNALS:
    void callSelected(const macrosip::CallRecord &record);
    void redial(const QString &number);

private Q_SLOTS:
    void onFilterChanged(int index);
    void onItemDoubleClicked(QTreeWidgetItem *item, int column);
    void onContextMenu(const QPoint &pos);

private:
    void setupUi();
    void applyFilter();
    static int callTypeToInt(CallType type);

    QComboBox *m_filterCombo = nullptr;
    QTreeWidget *m_callTree = nullptr;
    QList<CallRecord> m_allCalls;
};

} // namespace macrosip
