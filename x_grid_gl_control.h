#ifndef X_GRID_GL_CONTROL_H
#define X_GRID_GL_CONTROL_H

#include "x_paint_manager.h"

#include <QOpenGLWidget>
#include <QPen>


class x_grid_gl_control : public QOpenGLWidget
{
      Q_OBJECT
public:
    x_grid_gl_control();

public slots:

protected:
    void paintEvent(QPaintEvent *event) override;


private:
    QBrush background;
    QFont textFont;
    QPen textPen;

    x_grid_ui_data m_data;
};

#endif // X_GRID_GL_CONTROL_H
