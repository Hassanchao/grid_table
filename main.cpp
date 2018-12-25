#include <QApplication>

#include "x_grid_control.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    x_grid_control w;
    w.show();

    return a.exec();
}
