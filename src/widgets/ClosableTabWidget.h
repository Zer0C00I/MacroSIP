#pragma once

#include <QTabWidget>
#include <QIcon>

namespace macrosip {

class ClosableTabWidget : public QTabWidget {
    Q_OBJECT

public:
    explicit ClosableTabWidget(QWidget *parent = nullptr);
    ~ClosableTabWidget() override = default;

    int addClosableTab(QWidget *widget, const QString &title,
                       const QIcon &icon = QIcon());
    void setTabIcon(int index, const QIcon &icon);

Q_SIGNALS:
    void tabCloseClicked(int index);

private Q_SLOTS:
    void onTabCloseRequested(int index);
};

} // namespace macrosip
