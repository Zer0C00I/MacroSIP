#include "MessagesDialog.h"
#include "widgets/ClosableTabWidget.h"
#include "sip/SipTypes.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDateTime>

namespace macrosip {

MessagesDialog::MessagesDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Messages"));
    setupUi();
}

void MessagesDialog::openTab(const QString &number, const QString &name)
{
    if (m_tabMap.contains(number)) {
        const int idx = m_tabs->indexOf(m_tabMap[number].widget);
        if (idx >= 0)
            m_tabs->setCurrentIndex(idx);
        return;
    }

    TabData td;
    td.number = number;

    td.widget = new QWidget(this);
    auto *tabLayout = new QVBoxLayout(td.widget);

    // Message history
    td.history = new QTextEdit(td.widget);
    td.history->setReadOnly(true);
    td.history->setAcceptRichText(true);
    tabLayout->addWidget(td.history);

    // Input row
    auto *inputLayout = new QHBoxLayout;
    td.input = new QLineEdit(td.widget);
    td.input->setPlaceholderText(tr("Type a message..."));
    inputLayout->addWidget(td.input);

    auto *sendBtn = new QPushButton(tr("Send"), td.widget);
    connect(sendBtn, &QPushButton::clicked,
            this, &MessagesDialog::onSendMessage);
    connect(td.input, &QLineEdit::returnPressed,
            this, &MessagesDialog::onSendMessage);
    inputLayout->addWidget(sendBtn);
    tabLayout->addLayout(inputLayout);

    // Call control buttons
    auto *ctrlLayout = new QHBoxLayout;
    auto createCtrlBtn = [&](const QString &text) -> QPushButton * {
        auto *btn = new QPushButton(text, td.widget);
        ctrlLayout->addWidget(btn);
        return btn;
    };

    auto *holdBtn = createCtrlBtn(tr("Hold"));
    auto *transferBtn = createCtrlBtn(tr("Transfer"));
    auto *confBtn = createCtrlBtn(tr("Conference"));
    auto *recordBtn = createCtrlBtn(tr("Record"));
    auto *endBtn = createCtrlBtn(tr("End"));

    connect(holdBtn, &QPushButton::clicked, this, [this, number]() {
        if (m_tabMap.contains(number))
            Q_EMIT holdRequested(m_tabMap[number].callId);
    });
    connect(transferBtn, &QPushButton::clicked, this, [this, number]() {
        if (m_tabMap.contains(number))
            Q_EMIT transferRequested(m_tabMap[number].callId);
    });
    connect(confBtn, &QPushButton::clicked, this, [this, number]() {
        if (m_tabMap.contains(number))
            Q_EMIT conferenceRequested(m_tabMap[number].callId);
    });
    connect(recordBtn, &QPushButton::clicked, this, [this, number]() {
        if (m_tabMap.contains(number))
            Q_EMIT recordRequested(m_tabMap[number].callId);
    });
    connect(endBtn, &QPushButton::clicked, this, [this, number]() {
        if (m_tabMap.contains(number))
            Q_EMIT hangupRequested(m_tabMap[number].callId);
    });

    tabLayout->addLayout(ctrlLayout);

    const QString title = name.isEmpty() ? number : name;
    m_tabs->addClosableTab(td.widget, title);

    m_tabMap.insert(number, td);
    m_tabs->setCurrentWidget(td.widget);
}

void MessagesDialog::closeTab(int index)
{
    QWidget *w = m_tabs->widget(index);
    if (!w)
        return;

    // Find and remove from map
    for (auto it = m_tabMap.begin(); it != m_tabMap.end(); ++it) {
        if (it.value().widget == w) {
            m_tabMap.erase(it);
            break;
        }
    }
    m_tabs->removeTab(index);
    w->deleteLater();
}

void MessagesDialog::appendMessage(const QString &number, const QString &text,
                                    bool incoming)
{
    if (!m_tabMap.contains(number))
        return;

    TabData &td = m_tabMap[number];
    const QString timestamp =
        QDateTime::currentDateTime().toString(QStringLiteral("hh:mm:ss"));
    const QString color = incoming ? QStringLiteral("#2196F3")
                                   : QStringLiteral("#4CAF50");
    const QString direction = incoming ? tr("Incoming") : tr("Outgoing");
    const QString html = QStringLiteral(
        "<p><span style=\"color:%1\">[%2] %3:</span> %4</p>")
        .arg(color, timestamp, direction, text.toHtmlEscaped());
    td.history->append(html);
}

void MessagesDialog::setCallState(const QString &number, CallState state)
{
    if (!m_tabMap.contains(number))
        return;

    const int idx = m_tabs->indexOf(m_tabMap[number].widget);
    if (idx < 0)
        return;

    QString suffix;
    switch (state) {
    case CallState::Idle:         break;
    case CallState::Calling:      suffix = QStringLiteral(" [Calling]"); break;
    case CallState::Incoming:     suffix = QStringLiteral(" [Incoming]"); break;
    case CallState::Early:        suffix = QStringLiteral(" [Ringing]"); break;
    case CallState::Connecting:   suffix = QStringLiteral(" [Connecting]"); break;
    case CallState::Confirmed:    suffix = QStringLiteral(" [Active]"); break;
    case CallState::Disconnected: suffix = QStringLiteral(" [Ended]"); break;
    case CallState::Unknown:      break;
    }

    const QString base = number;
    m_tabs->setTabText(idx, base + suffix);
}

void MessagesDialog::onTabCloseClicked(int index)
{
    closeTab(index);
}

void MessagesDialog::onSendMessage()
{
    const int idx = m_tabs->currentIndex();
    QWidget *w = m_tabs->widget(idx);
    if (!w)
        return;

    for (auto it = m_tabMap.begin(); it != m_tabMap.end(); ++it) {
        if (it.value().widget == w) {
            const QString text = it.value().input->text().trimmed();
            if (!text.isEmpty()) {
                Q_EMIT messageSent(it.key(), text);
                appendMessage(it.key(), text, false);
                it.value().input->clear();
            }
            break;
        }
    }
}

void MessagesDialog::setupUi()
{
    auto *layout = new QVBoxLayout(this);

    m_tabs = new ClosableTabWidget(this);
    connect(m_tabs, &ClosableTabWidget::tabCloseClicked,
            this, &MessagesDialog::onTabCloseClicked);
    layout->addWidget(m_tabs);

    resize(600, 450);
}

} // namespace macrosip
