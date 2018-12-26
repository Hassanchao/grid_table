#ifndef X_PAINT_MANAGER_H
#define X_PAINT_MANAGER_H

#include <vector>
#include <string>
#include <QRect>
#include <QPainter>

class x_grid_impl;
class x_grid_control;



class x_grid_ui_data
{
public:
    x_grid_ui_data();


public:
    void set_default_value();

public:
    std::vector<std::vector<std::string>> m_cells_values;

	QRect m_client_rect;
};



class x_paint_manager
{
public:
    x_paint_manager();

public:
    void draw_whole_grid();



public:
    x_grid_impl* m_grid_impl = nullptr;
    x_grid_control* m_grid_control = nullptr;

public:
    void draw_line_h_v(QPainterPath& path);
    void draw_text(QPainter& painter);

public:
    x_grid_ui_data m_ui_data;
    
};

#endif // X_PAINT_MANAGER_H
