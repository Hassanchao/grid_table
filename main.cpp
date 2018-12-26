#include <QApplication>

#include "x_grid_control.h"
#include "x_grid_gl_control.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // x_grid_control w;
   // w.show();

    x_grid_gl_control w_gl;
    w_gl.show();

    return a.exec();
}
