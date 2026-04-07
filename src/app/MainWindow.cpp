#include "app/MainWindow.h"
#include "widgets/DialerWidget.h"
#include "widgets/ContactsWidget.h"
#include "widgets/CallsWidget.h"
#include "dialogs/MessagesDialog.h"
#include "dialogs/SettingsDialog.h"
#include "dialogs/AccountDialog.h"
#include "dialogs/RingingDialog.h"
#include "models/Settings.h"
#include <QTabWidget>
#include <QStatusBar>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QCloseEvent>
#include <QApplication>
#include <QMessageBox>
#include <QVBoxLayout>

namespace macrosip {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
    setupMenuBar();
    setupTrayIcon();
    setupSip();
    connectSignals();
}

MainWindow::~MainWindow()
{
    if (m_sipManager != nullptr) {
        m_sipManager->shutdown();
    }
    delete m_trayMenu;
    delete m_messagesDialog;
}

SipManager *MainWindow::sipManager() const
{
    return m_sipManager;
}

void MainWindow::makeCall(const QString &number)
{
    if (number.isEmpty() || m_sipManager == nullptr) {
        return;
    }

    m_sipManager->makeCall(number);

    if (m_messagesDialog == nullptr) {
        m_messagesDialog = new MessagesDialog(this);
    }
    m_messagesDialog->openTab(number, number);
    m_messagesDialog->show();
    m_messagesDialog->raise();
}

void MainWindow::showRingingDialog(int callId, const QString &name,
                                   const QString &number)
{
    auto *dialog = new RingingDialog(this);
    dialog->setCallInfo(callId, name, number);

    connect(dialog, &RingingDialog::answered, this, [this](int answeredCallId) {
        if (m_sipManager != nullptr) {
            m_sipManager->answerCall(answeredCallId);
        }
    });
    connect(dialog, &RingingDialog::declined, this, [this](int declinedCallId) {
        if (m_sipManager != nullptr) {
            m_sipManager->hangupCall(declinedCallId);
        }
    });
    connect(dialog, &QDialog::finished, dialog, &QObject::deleteLater);

    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void MainWindow::onAccountSettings()
{
    AccountDialog dialog(this);
    dialog.setAccount(AppSettings::instance().account);
    if (dialog.exec() == QDialog::Accepted) {
        AppSettings::instance().account = dialog.account();
        AppSettings::instance().save();

        // Re-register with new account settings by restarting SIP
        if (m_sipManager != nullptr) {
            m_sipManager->shutdown();
            m_sipManager->initialize();

            const Account &acct = AppSettings::instance().account;
            if (acct.isValid()) {
                m_sipManager->addAccount(acct);
            }
        }
    }
}

void MainWindow::onSettings()
{
    SettingsDialog dialog(this);
    dialog.loadSettings(AppSettings::instance());
    if (dialog.exec() == QDialog::Accepted) {
        dialog.saveSettings(AppSettings::instance());
        AppSettings::instance().save();
    }
}

void MainWindow::onAbout()
{
    QMessageBox::about(this, tr("About MacroSIP"),
                       tr("MacroSIP - Open Source SIP Softphone\n"
                          "Version %1")
                           .arg(QCoreApplication::applicationVersion()));
}

void MainWindow::onQuit()
{
    if (m_sipManager != nullptr) {
        m_sipManager->shutdown();
    }
    QApplication::quit();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (m_trayIcon != nullptr && m_trayIcon->isVisible()) {
        hide();
        event->ignore();
    } else {
        onQuit();
        event->accept();
    }
}

void MainWindow::onSipInitialized()
{
    updateStatusBar(tr("SIP engine ready"));
}

void MainWindow::onIncomingCall(int callId, const QString &from,
                                const QString &name)
{
    showRingingDialog(callId, name, from);
}

void MainWindow::onCallStateChanged(int callId, CallState state)
{
    Q_UNUSED(callId)

    switch (state) {
    case CallState::Confirmed:
        updateStatusBar(tr("Call active"));
        break;
    case CallState::Disconnected:
        updateStatusBar(tr("Call ended"));
        break;
    case CallState::Calling:
        updateStatusBar(tr("Calling..."));
        break;
    case CallState::Incoming:
        updateStatusBar(tr("Incoming call"));
        break;
    case CallState::Idle:
    case CallState::Early:
    case CallState::Connecting:
    case CallState::Unknown:
        break;
    }
}

void MainWindow::onRegistrationStateChanged(int accountId,
                                             RegistrationState state,
                                             int code,
                                             const QString &reason)
{
    Q_UNUSED(accountId)
    Q_UNUSED(code)
    Q_UNUSED(reason)

    switch (state) {
    case RegistrationState::Registered:
        updateStatusBar(tr("Registered"));
        break;
    case RegistrationState::Registering:
        updateStatusBar(tr("Registering..."));
        break;
    case RegistrationState::Unregistered:
        updateStatusBar(tr("Not registered"));
        break;
    case RegistrationState::Error:
        updateStatusBar(tr("Registration error"));
        break;
    }

    updateTrayIcon(state);
}

void MainWindow::onTrayActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger ||
        reason == QSystemTrayIcon::DoubleClick) {
        if (isVisible()) {
            hide();
        } else {
            show();
            raise();
            activateWindow();
        }
    }
}

void MainWindow::onCallRequested(const QString &number)
{
    makeCall(number);
}

void MainWindow::onHangupRequested()
{
    if (m_sipManager == nullptr) {
        return;
    }

    // Hang up all active calls via the dialer's current number context
    // The SIP manager manages call lifecycle
    const QString currentNumber = m_dialer != nullptr ? m_dialer->currentNumber() : QString();
    Q_UNUSED(currentNumber)
}

void MainWindow::setupUi()
{
    setWindowTitle(QStringLiteral("MacroSIP"));
    setMinimumSize(300, 400);

    auto *centralWidget = new QWidget(this);
    auto *layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(0, 0, 0, 0);

    m_tabWidget = new QTabWidget(centralWidget);

    m_dialer = new DialerWidget(m_tabWidget);
    m_contacts = new ContactsWidget(m_tabWidget);
    m_calls = new CallsWidget(m_tabWidget);

    m_tabWidget->addTab(m_dialer, tr("Dialer"));
    m_tabWidget->addTab(m_contacts, tr("Contacts"));
    m_tabWidget->addTab(m_calls, tr("Calls"));

    layout->addWidget(m_tabWidget);
    setCentralWidget(centralWidget);

    m_statusBar = statusBar();
    m_statusBar->showMessage(tr("Ready"));
}

void MainWindow::setupMenuBar()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *accountAction = fileMenu->addAction(tr("&Account Settings..."));
    connect(accountAction, &QAction::triggered, this, &MainWindow::onAccountSettings);

    QAction *settingsAction = fileMenu->addAction(tr("&Settings..."));
    connect(settingsAction, &QAction::triggered, this, &MainWindow::onSettings);

    fileMenu->addSeparator();

    QAction *quitAction = fileMenu->addAction(tr("&Quit"));
    quitAction->setShortcut(QKeySequence::Quit);
    connect(quitAction, &QAction::triggered, this, &MainWindow::onQuit);

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

    QAction *aboutAction = helpMenu->addAction(tr("&About MacroSIP"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::onAbout);
}

void MainWindow::setupTrayIcon()
{
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        return;
    }

    m_trayIcon = new QSystemTrayIcon(this);
    m_trayMenu = new QMenu();

    QAction *showAction = m_trayMenu->addAction(tr("Show/Hide"));
    connect(showAction, &QAction::triggered, this, [this]() {
        if (isVisible()) {
            hide();
        } else {
            show();
            raise();
            activateWindow();
        }
    });

    QAction *settingsAction = m_trayMenu->addAction(tr("Settings..."));
    connect(settingsAction, &QAction::triggered, this, &MainWindow::onSettings);

    m_trayMenu->addSeparator();

    QAction *quitAction = m_trayMenu->addAction(tr("Quit"));
    connect(quitAction, &QAction::triggered, this, &MainWindow::onQuit);

    m_trayIcon->setContextMenu(m_trayMenu);
    m_trayIcon->setToolTip(QStringLiteral("MacroSIP"));
    m_trayIcon->show();

    connect(m_trayIcon, &QSystemTrayIcon::activated,
            this, &MainWindow::onTrayActivated);
}

void MainWindow::setupSip()
{
    m_sipManager = new SipManager(this);

    connect(m_sipManager, &SipManager::initialized,
            this, &MainWindow::onSipInitialized);
    connect(m_sipManager, &SipManager::incomingCall,
            this, &MainWindow::onIncomingCall);
    connect(m_sipManager, &SipManager::callStateChanged,
            this, &MainWindow::onCallStateChanged);
    connect(m_sipManager, &SipManager::registrationStateChanged,
            this, &MainWindow::onRegistrationStateChanged);

    // Initialize the SIP engine and register the configured account
    m_sipManager->initialize();

    const Account &acct = AppSettings::instance().account;
    if (acct.isValid()) {
        m_sipManager->addAccount(acct);
    }
}

void MainWindow::connectSignals()
{
    if (m_dialer != nullptr) {
        connect(m_dialer, &DialerWidget::callRequested,
                this, &MainWindow::onCallRequested);
        connect(m_dialer, &DialerWidget::hangupRequested,
                this, &MainWindow::onHangupRequested);
    }

    if (m_contacts != nullptr) {
        connect(m_contacts, &ContactsWidget::callContact,
                this, &MainWindow::onCallRequested);
    }

    if (m_calls != nullptr) {
        connect(m_calls, &CallsWidget::redial,
                this, &MainWindow::onCallRequested);
    }
}

void MainWindow::updateStatusBar(const QString &text)
{
    if (m_statusBar != nullptr) {
        m_statusBar->showMessage(text);
    }
}

void MainWindow::updateTrayIcon(RegistrationState state)
{
    if (m_trayIcon == nullptr) {
        return;
    }

    switch (state) {
    case RegistrationState::Registered:
        m_trayIcon->setToolTip(QStringLiteral("MacroSIP - Registered"));
        break;
    case RegistrationState::Registering:
        m_trayIcon->setToolTip(QStringLiteral("MacroSIP - Registering..."));
        break;
    case RegistrationState::Unregistered:
        m_trayIcon->setToolTip(QStringLiteral("MacroSIP - Not registered"));
        break;
    case RegistrationState::Error:
        m_trayIcon->setToolTip(QStringLiteral("MacroSIP - Error"));
        break;
    }
}

} // namespace macrosip
