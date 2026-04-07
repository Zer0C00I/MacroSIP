#pragma once
#include <QMainWindow>
#include <QSystemTrayIcon>
#include "sip/SipManager.h"

class QTabWidget;
class QStatusBar;
class QMenu;
class QAction;
class QCloseEvent;

namespace macrosip {

class DialerWidget;
class ContactsWidget;
class CallsWidget;
class MessagesDialog;
class SettingsDialog;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    SipManager *sipManager() const;

    void makeCall(const QString &number);
    void showRingingDialog(int callId, const QString &name, const QString &number);

public slots:
    void onAccountSettings();
    void onSettings();
    void onAbout();
    void onQuit();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onSipInitialized();
    void onIncomingCall(int callId, const QString &from, const QString &name);
    void onCallStateChanged(int callId, CallState state);
    void onRegistrationStateChanged(int accountId, RegistrationState state,
                                    int code, const QString &reason);
    void onTrayActivated(QSystemTrayIcon::ActivationReason reason);
    void onCallRequested(const QString &number);
    void onHangupRequested();

private:
    void setupUi();
    void setupMenuBar();
    void setupTrayIcon();
    void setupSip();
    void connectSignals();
    void updateStatusBar(const QString &text);
    void updateTrayIcon(RegistrationState state);

    SipManager *m_sipManager = nullptr;
    QTabWidget *m_tabWidget = nullptr;
    DialerWidget *m_dialer = nullptr;
    ContactsWidget *m_contacts = nullptr;
    CallsWidget *m_calls = nullptr;
    MessagesDialog *m_messagesDialog = nullptr;
    QSystemTrayIcon *m_trayIcon = nullptr;
    QMenu *m_trayMenu = nullptr;
    QStatusBar *m_statusBar = nullptr;
};

} // namespace macrosip
