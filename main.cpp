#include <QApplication>
#include "welcomemenu.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WelcomeMenu* Menu = new WelcomeMenu;
    Menu->show();
    return a.exec();
}
