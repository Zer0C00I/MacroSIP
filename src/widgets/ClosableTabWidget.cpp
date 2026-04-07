#include "ClosableTabWidget.h"

namespace macrosip {

ClosableTabWidget::ClosableTabWidget(QWidget *parent)
    : QTabWidget(parent)
{
    setTabsClosable(true);
    connect(this, &QTabWidget::tabCloseRequested,
            this, &ClosableTabWidget::onTabCloseRequested);
}

int ClosableTabWidget::addClosableTab(QWidget *widget, const QString &title,
                                       const QIcon &icon)
{
    const int idx = addTab(widget, icon, title);
    return idx;
}

void ClosableTabWidget::setTabIcon(int index, const QIcon &icon)
{
    QTabWidget::setTabIcon(index, icon);
}

void ClosableTabWidget::onTabCloseRequested(int index)
{
    Q_EMIT tabCloseClicked(index);
}

} // namespace macrosip
