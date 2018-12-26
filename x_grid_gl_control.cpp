
#include <QPaintEvent>
#include <QPainter>

#include "x_grid_impl.h"
#include "x_grid_gl_control.h"



x_grid_gl_control::x_grid_gl_control()
{
    QLinearGradient gradient(QPointF(50, -20), QPointF(80, 20));
    gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(1.0, QColor(0xa6, 0xce, 0x39));

    background = QBrush(QColor(250, 250, 250));
    textPen = QPen(Qt::black);
    textFont.setPixelSize(12);

    m_data.set_default_value();
}

void x_grid_gl_control::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(event->rect(), background);
    painter.translate(100, 100);

    painter.save();

    painter.setPen(textPen);
    painter.setFont(textFont);

    if (m_data.m_cells_values.empty())return;
    size_t row_num = m_data.m_cells_values.size();
    size_t col_num = m_data.m_cells_values.front().size();

    const int cell_width = m_data.m_cell_width;
    const int cell_height = m_data.m_cell_height;

    int right_x = int(col_num *cell_width);
    int bottom_y = int(row_num * cell_height);

    QPainterPath path;
   // 划横线
    for (size_t row = 0; row <row_num;++row)
    {
        int tmp_height = row * cell_height;

        QPoint start_point(0, tmp_height);
        QPoint end_point(right_x, tmp_height);

        path.moveTo(start_point);
        path.lineTo(end_point);
    }

    const int height_rc = row_num * cell_height;

    path.moveTo(0, height_rc);
    path.lineTo(right_x, height_rc);

    // 划竖线
    for(size_t col = 0; col <col_num; ++col)
    {
        int tmp_width = col * cell_width;

        QPoint start_point(tmp_width, 0);
        QPoint end_point(tmp_width, bottom_y);

        path.moveTo(start_point);
        path.lineTo(end_point);
    }

    const int width_rc = col_num * cell_width;
    path.moveTo(width_rc, 0);
    path.lineTo(width_rc, bottom_y);


    path.closeSubpath();

    // 绘制文字
    for (size_t row = 0; row < row_num; ++row)
    {
        const int row_height = (int)cell_height * row;
        std::vector<QString>& row_data = m_data.m_cells_values[row];
        for (size_t col = 0; col < col_num; ++col)
        {
            const int col_width = (int)cell_width * col;

            QRect rc(col_width, row_height, cell_width, cell_height);
            painter.drawText(rc, Qt::AlignHCenter | Qt::AlignVCenter, (row_data[col]));
        }
    }

    painter.setPen(Qt::black);
    painter.setBrush(QColor(50,50,50));
    painter.drawPath(path);

    painter.restore();

    painter.end();


}
