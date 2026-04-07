#include "app/MacroSipApp.h"
#include "app/MainWindow.h"
#include "models/Settings.h"
#include "utils/LangPack.h"
#include <QDir>

namespace macrosip {

MacroSipApp::MacroSipApp(int &argc, char **argv)
    : QApplication(argc, argv)
{
    setApplicationName(QStringLiteral("MacroSIP"));
    setApplicationVersion(QStringLiteral("1.0.0"));
    setOrganizationName(QStringLiteral("MacroSIP"));
    setOrganizationDomain(QStringLiteral("macrosip.org"));
}

MacroSipApp::~MacroSipApp()
{
    delete m_mainWindow;
}

MacroSipApp *MacroSipApp::instance()
{
    return qobject_cast<MacroSipApp *>(QCoreApplication::instance());
}

bool MacroSipApp::init()
{
    setupPaths();
    loadSettings();
    loadLanguage();

    m_mainWindow = new MainWindow();
    m_mainWindow->show();
    return true;
}

MainWindow *MacroSipApp::mainWindow() const
{
    return m_mainWindow;
}

void MacroSipApp::setupPaths()
{
    const QString configPath = AppSettings::instance().configDir();
    QDir dir;
    if (!dir.exists(configPath)) {
        dir.mkpath(configPath);
    }
}

void MacroSipApp::loadSettings()
{
    AppSettings::instance().load();
}

void MacroSipApp::loadLanguage()
{
    const QString &langFile = AppSettings::instance().langPack;
    if (!langFile.isEmpty()) {
        LangPack::instance().load(langFile);
    }
}

} // namespace macrosip
