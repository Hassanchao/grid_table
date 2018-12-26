#ifndef X_GRID_IMPL_H
#define X_GRID_IMPL_H

#include <array>

#include "impl_grid_cell_values.hpp"
#include "x_grid_control.h"
#include "x_paint_manager.h"


class x_grid_cell
{
public:
    x_grid_cell();
    ~x_grid_cell();
public:
    std::string m_grid_data;

};

class x_grid_impl
{
public:
    x_grid_impl();
    ~x_grid_impl();

public:
    x_grid_control* m_grid = nullptr;
    x_paint_manager m_paint_mana;




public:
    impl_grid_cell_values<std::string> m_cell_text;

public:
    // 行高、列宽数据相关/////////////////////////////////////////////

    int m_default_row_height = 20; // 不考虑高分屏适配，为物理分辨率像素值
    int m_default_col_widht = 70; // 不考虑高分屏适配，为物理分辨率像素值

    enum height_widht_block_size
    {
        height_block_size = 50,
        width_block_size = 30,
    };

    std::vector<std::pair<int, std::array<int, height_block_size>>> m_rows_height;	// <块总高, <行高, 块中总行数>>
    std::vector<std::pair<int, std::array<int, width_block_size>>> m_cols_width;	// <块总宽, <列宽, 块中总列数>>

    int m_cells_width = 0;
    int m_cells_height = 0;

};

#endif // X_GRID_IMPL_H
