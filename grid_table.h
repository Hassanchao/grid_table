#ifndef GRID_TABLE_H
#define GRID_TABLE_H

#include <QMainWindow>

namespace Ui {
class grid_table;
}

class grid_table : public QMainWindow
{
    Q_OBJECT

public:
    explicit grid_table(QWidget *parent = 0);
    ~grid_table();

private:
    Ui::grid_table *ui;
};

#endif // GRID_TABLE_H
