#include "grid_table.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    grid_table w;
    w.show();

    return a.exec();
}
