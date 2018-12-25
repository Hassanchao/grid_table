#ifndef X_PAINT_MANAGER_H
#define X_PAINT_MANAGER_H

class x_grid_impl;
class x_grid_control;

class x_paint_manager
{
public:
    x_paint_manager();

public:
    void draw_whole_grid();

public:
    x_grid_impl* m_grid_impl = nullptr;
    x_grid_control* m_grid_control = nullptr;
};

#endif // X_PAINT_MANAGER_H
