#ifndef GRID_UI_H
#define GRID_UI_H

#include <QWidget>

class grid_ui : public QWidget
{
    Q_OBJECT
public:
    explicit grid_ui(QWidget *parent = nullptr);

protected:
void paintEvent(QPaintEvent *event);

signals:

public slots:


public:
	std::vector<std::vector<QString>> m_cells;
};



#endif // GRID_UI_H
