#include <QApplication>

#include "grid_ui.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    grid_ui w;
    w.show();

    return a.exec();
}
