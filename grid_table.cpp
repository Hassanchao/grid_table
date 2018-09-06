#include "grid_table.h"
#include "ui_grid_table.h"

grid_table::grid_table(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::grid_table)
{
    ui->setupUi(this);
}

grid_table::~grid_table()
{
    delete ui;
}
