#include "DialerWidget.h"

#include <QFont>
#include <QSizePolicy>

namespace macrosip {

DialerWidget::DialerWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
}

QString DialerWidget::currentNumber() const
{
    return m_numberInput->text();
}

void DialerWidget::setNumber(const QString &number)
{
    m_numberInput->setText(number);
}

void DialerWidget::setStatusText(const QString &text)
{
    m_statusLabel->setText(text);
}

void DialerWidget::clear()
{
    m_numberInput->clear();
}

void DialerWidget::onDigitClicked()
{
    auto *button = qobject_cast<QPushButton *>(sender());
    if (!button)
        return;
    const QString digit = button->property("digit").toString();
    m_numberInput->insert(digit);
    Q_EMIT dtmfPressed(digit);
}

void DialerWidget::onCallClicked()
{
    const QString num = m_numberInput->text().trimmed();
    if (!num.isEmpty())
        Q_EMIT callRequested(num);
}

void DialerWidget::onHangupClicked()
{
    Q_EMIT hangupRequested();
}

void DialerWidget::setupUi()
{
    auto *mainLayout = new QVBoxLayout(this);

    // Number input
    m_numberInput = new QLineEdit(this);
    m_numberInput->setPlaceholderText(tr("Enter number..."));
    QFont inputFont = m_numberInput->font();
    inputFont.setPointSize(16);
    m_numberInput->setFont(inputFont);
    m_numberInput->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(m_numberInput);

    // Status label
    m_statusLabel = new QLabel(this);
    m_statusLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(m_statusLabel);

    // Dialpad grid
    m_dialpadLayout = new QGridLayout;

    struct DialButton {
        const char *digit;
        const char *letters;
        int row;
        int col;
    };

    static constexpr DialButton buttons[] = {
        {"1", "",     0, 0}, {"2", "ABC",  0, 1}, {"3", "DEF",  0, 2},
        {"4", "GHI",  1, 0}, {"5", "JKL",  1, 1}, {"6", "MNO",  1, 2},
        {"7", "PQRS", 2, 0}, {"8", "TUV",  2, 1}, {"9", "WXYZ", 2, 2},
        {"*", "",     3, 0}, {"0", "+",    3, 1}, {"#", "",     3, 2}
    };

    for (const auto &btn : buttons) {
        QPushButton *pb = createDigitButton(
            QString::fromLatin1(btn.digit),
            QString::fromLatin1(btn.letters));
        m_dialpadLayout->addWidget(pb, btn.row, btn.col);
    }

    mainLayout->addLayout(m_dialpadLayout);

    // Call / Hangup buttons
    auto *buttonLayout = new QHBoxLayout;

    m_callButton = new QPushButton(tr("Call"), this);
    m_callButton->setStyleSheet(
        QStringLiteral("QPushButton { background-color: #4CAF50; color: white; "
                        "font-size: 14px; padding: 8px; border-radius: 4px; }"));
    connect(m_callButton, &QPushButton::clicked,
            this, &DialerWidget::onCallClicked);
    buttonLayout->addWidget(m_callButton);

    m_hangupButton = new QPushButton(tr("Hangup"), this);
    m_hangupButton->setStyleSheet(
        QStringLiteral("QPushButton { background-color: #F44336; color: white; "
                        "font-size: 14px; padding: 8px; border-radius: 4px; }"));
    connect(m_hangupButton, &QPushButton::clicked,
            this, &DialerWidget::onHangupClicked);
    buttonLayout->addWidget(m_hangupButton);

    mainLayout->addLayout(buttonLayout);
}

QPushButton *DialerWidget::createDigitButton(const QString &digit,
                                              const QString &letters)
{
    auto *button = new QPushButton(this);
    QString text = digit;
    if (!letters.isEmpty())
        text += QStringLiteral("\n") + letters;
    button->setText(text);
    button->setProperty("digit", digit);
    button->setMinimumSize(60, 50);
    QFont f = button->font();
    f.setPointSize(14);
    button->setFont(f);
    connect(button, &QPushButton::clicked,
            this, &DialerWidget::onDigitClicked);
    return button;
}

} // namespace macrosip
