#include <QPainter>

#include "x_grid_impl.h"
#include "x_grid_control.h"

#include "x_paint_manager.h"

x_paint_manager::x_paint_manager()
{

}

void x_paint_manager::draw_whole_grid()
{
    if(!m_grid_impl || !m_grid_control) return;

    QPainter painter(m_grid_control);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QRect rc = m_grid_control->rect();

    QPainterPath path;

    QPoint start_point(rc.topLeft());
    QPoint end_point(rc.bottomRight());

    QFont ft;

    path.moveTo(start_point);
    path.lineTo(end_point);
    path.addText(10,10, ft, "123456");
    path.closeSubpath();
    painter.setPen(Qt::black);
    painter.setBrush(QColor(50,50,50));
    painter.drawPath(path);


}
