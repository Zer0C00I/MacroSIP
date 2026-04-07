#pragma once

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QTimer>

namespace macrosip {

class RingingDialog : public QDialog {
    Q_OBJECT

public:
    explicit RingingDialog(QWidget *parent = nullptr);
    ~RingingDialog() override = default;

    void setCallInfo(int callId, const QString &name, const QString &number);
    void setAutoCloseTimeout(int seconds);

Q_SIGNALS:
    void answered(int callId);
    void declined(int callId);

private Q_SLOTS:
    void onAnswer();
    void onDecline();
    void onTimeout();

private:
    void setupUi();

    QLabel *m_nameLabel = nullptr;
    QLabel *m_numberLabel = nullptr;
    QPushButton *m_answerButton = nullptr;
    QPushButton *m_declineButton = nullptr;
    QTimer *m_autoCloseTimer = nullptr;
    int m_callId = -1;
};

} // namespace macrosip
