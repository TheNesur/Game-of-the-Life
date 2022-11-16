#include "GameoftheLife.h"
#include <Windows.h>

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    if (AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole()) {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }

    QApplication a(argc, argv);
    GameoftheLife w;
    //w.setFixedSize(500, 500); //21x21
    w.show();
    return a.exec();
}
