#include "RingingDialog.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

namespace macrosip {

RingingDialog::RingingDialog(QWidget *parent)
    : QDialog(parent, Qt::Tool | Qt::WindowStaysOnTopHint)
{
    setWindowTitle(tr("Incoming Call"));
    setupUi();
}

void RingingDialog::setCallInfo(int callId, const QString &name,
                                 const QString &number)
{
    m_callId = callId;
    m_nameLabel->setText(name.isEmpty() ? tr("Unknown Caller") : name);
    m_numberLabel->setText(number);
}

void RingingDialog::setAutoCloseTimeout(int seconds)
{
    if (seconds <= 0) {
        m_autoCloseTimer->stop();
        return;
    }
    m_autoCloseTimer->start(seconds * 1000);
}

void RingingDialog::onAnswer()
{
    m_autoCloseTimer->stop();
    Q_EMIT answered(m_callId);
    accept();
}

void RingingDialog::onDecline()
{
    m_autoCloseTimer->stop();
    Q_EMIT declined(m_callId);
    reject();
}

void RingingDialog::onTimeout()
{
    m_autoCloseTimer->stop();
    Q_EMIT declined(m_callId);
    reject();
}

void RingingDialog::setupUi()
{
    auto *mainLayout = new QVBoxLayout(this);

    m_nameLabel = new QLabel(this);
    QFont nameFont = m_nameLabel->font();
    nameFont.setPointSize(16);
    nameFont.setBold(true);
    m_nameLabel->setFont(nameFont);
    m_nameLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(m_nameLabel);

    m_numberLabel = new QLabel(this);
    QFont numFont = m_numberLabel->font();
    numFont.setPointSize(12);
    m_numberLabel->setFont(numFont);
    m_numberLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(m_numberLabel);

    mainLayout->addSpacing(16);

    auto *btnLayout = new QHBoxLayout;

    m_answerButton = new QPushButton(tr("Answer"), this);
    m_answerButton->setStyleSheet(
        QStringLiteral("QPushButton { background-color: #4CAF50; color: white; "
                        "font-size: 14px; padding: 10px 24px; "
                        "border-radius: 4px; }"));
    connect(m_answerButton, &QPushButton::clicked,
            this, &RingingDialog::onAnswer);
    btnLayout->addWidget(m_answerButton);

    m_declineButton = new QPushButton(tr("Decline"), this);
    m_declineButton->setStyleSheet(
        QStringLiteral("QPushButton { background-color: #F44336; color: white; "
                        "font-size: 14px; padding: 10px 24px; "
                        "border-radius: 4px; }"));
    connect(m_declineButton, &QPushButton::clicked,
            this, &RingingDialog::onDecline);
    btnLayout->addWidget(m_declineButton);

    mainLayout->addLayout(btnLayout);

    m_autoCloseTimer = new QTimer(this);
    m_autoCloseTimer->setSingleShot(true);
    connect(m_autoCloseTimer, &QTimer::timeout,
            this, &RingingDialog::onTimeout);

    resize(320, 180);
}

} // namespace macrosip
