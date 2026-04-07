#pragma once
#include <QApplication>

namespace macrosip {

class MainWindow;

class MacroSipApp : public QApplication {
    Q_OBJECT
public:
    MacroSipApp(int &argc, char **argv);
    ~MacroSipApp() override;

    static MacroSipApp *instance();

    bool init();
    MainWindow *mainWindow() const;

private:
    MainWindow *m_mainWindow = nullptr;

    void setupPaths();
    void loadSettings();
    void loadLanguage();
};

} // namespace macrosip
