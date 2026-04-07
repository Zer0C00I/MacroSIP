#include "app/MacroSipApp.h"
#include "app/MainWindow.h"

int main(int argc, char *argv[])
{
    macrosip::MacroSipApp app(argc, argv);
    if (!app.init()) {
        return 1;
    }
    return app.exec();
}
