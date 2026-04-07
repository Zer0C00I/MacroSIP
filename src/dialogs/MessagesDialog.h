#pragma once

#include <QDialog>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QHash>

namespace macrosip {

class ClosableTabWidget;
enum class CallState;

class MessagesDialog : public QDialog {
    Q_OBJECT

public:
    explicit MessagesDialog(QWidget *parent = nullptr);
    ~MessagesDialog() override = default;

    void openTab(const QString &number, const QString &name);
    void closeTab(int index);
    void appendMessage(const QString &number, const QString &text,
                       bool incoming);
    void setCallState(const QString &number, CallState state);

Q_SIGNALS:
    void messageSent(const QString &number, const QString &text);
    void holdRequested(int callId);
    void transferRequested(int callId);
    void recordRequested(int callId);
    void hangupRequested(int callId);
    void conferenceRequested(int callId);

private Q_SLOTS:
    void onTabCloseClicked(int index);
    void onSendMessage();

private:
    void setupUi();

    struct TabData {
        QWidget *widget = nullptr;
        QTextEdit *history = nullptr;
        QLineEdit *input = nullptr;
        QString number;
        int callId = -1;
    };

    ClosableTabWidget *m_tabs = nullptr;
    QHash<QString, TabData> m_tabMap;
};

} // namespace macrosip
