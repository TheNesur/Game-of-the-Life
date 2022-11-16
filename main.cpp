#include "GameoftheLife.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameoftheLife w;
    w.setFixedSize(500, 500); //21x21
    w.show();
    return a.exec();
}
