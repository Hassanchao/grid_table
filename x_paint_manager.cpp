#include <vector>
#include <string>
#include <QPainter>

#include "x_grid_impl.h"
#include "x_grid_control.h"

#include "x_paint_manager.h"

using namespace std;

x_grid_ui_data::x_grid_ui_data()
{

}

void x_grid_ui_data::set_default_value()
{
    m_cells_values.clear();

    const size_t row_num = 100;
    const size_t col_num = 100;

    m_cells_values.resize(row_num);
    for (size_t row = 0;row < row_num; ++row)
    {
        std::vector<string>& row_vlues = m_cells_values[row];
        row_vlues.resize(col_num);
        for (size_t col = 0; col < col_num; ++col)
        {
            string& cell = row_vlues[col];
            cell = std::to_string(row) + "row" + std::to_string(col) + "line";
        }
    }
}

/////////////////////////////////////////////////////////
x_paint_manager::x_paint_manager()
{
    m_ui_data.set_default_value();
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


//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing, true);

//    QRect rc = this->rect();

//    QPainterPath path;

//    QPoint start_point(rc.topLeft());
//	QPoint end_point(rc.bottomRight());

//	QFont ft;

//	path.moveTo(start_point);
//	path.lineTo(end_point);
//	path.addText(10,10, ft, "123456");
//	path.closeSubpath();
//	painter.setPen(Qt::black);
//	painter.setBrush(QColor(50,50,50));
//	painter.drawPath(path);

//void grid_ui::paintEvent(QPaintEvent *event)
//{
//    QPainter painter(this);
//       painter.setRenderHint(QPainter::Antialiasing, true);

//       QPainterPath path;

//       // 起始点（矩形左上角坐标）
//       QPoint startPoint(50, 10);
//       // 外部矩形宽度的1/2（外部圆半径）
//       int nOuterRadius = 150;
//       // 内部矩形宽度的1/2（内部圆半径）
//       int nInnerRadius = 150;
//       int nInnerHeightRadius = 120;
//       // 间距
//       int nSpacing = nOuterRadius - nInnerHeightRadius;

//       QPointF rightPoint(startPoint.x() + nOuterRadius * 2, startPoint.y() + nOuterRadius);
//       QRect outerRect(startPoint.x(), startPoint.y(), nOuterRadius * 2, nOuterRadius * 2);
//       QPointF leftPoint(startPoint.x(), startPoint.y() + nInnerHeightRadius + nSpacing);
//       QRect innerRect(startPoint.x(), startPoint.y() + nSpacing, nInnerRadius * 2, nInnerHeightRadius * 2);

//       // 1.绘制外圆（绿色部分）
//       path.moveTo(rightPoint);
//       path.arcTo(outerRect, 180, 180);
//       path.closeSubpath();
//       painter.setPen(Qt::black);
//       painter.setBrush(QColor(5, 150, 60));
//       painter.drawPath(path);

//       path = QPainterPath();
//       // 2.绘制内圆（红色部分）
//       path.moveTo(leftPoint);
//       path.arcTo(innerRect, 180, 180);
//       path.closeSubpath();
//       painter.setPen(Qt::black);
//       painter.setBrush(Qt::red);
//       painter.drawPath(path);

//       // 3.生成椭圆（西瓜子）
//       QPainterPath seedsPath = QPainterPath();

//       qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

//       // 用来判断椭圆范围
//       for (int i = innerRect.left(); i < innerRect.left() + innerRect.width(); i += 30)
//       {
//           for(int j = innerRect.top() + nInnerHeightRadius; j < innerRect.top() + nInnerHeightRadius * 2; j += 20)
//           {
//               // 随机数（西瓜子随机分布在西瓜中）
//               int nX = qrand() % 30;
//               int nY = qrand() % 30;
//               // 当椭圆在内部路径内时，添加至绘制路径（西瓜子肯定要在西瓜内O__O"…）
//               QRect rect(i + nX, j + nY, 6, 10);
//               if (path.contains(rect))
//                   seedsPath.addEllipse(rect);
//           }
//       }

//       painter.setPen(Qt::NoPen);
//       painter.setBrush(Qt::black);
//       painter.drawPath(seedsPath);
//}

