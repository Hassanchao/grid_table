#include <QPainter>
#include <QTime>

#include "x_grid_impl.h"

#include "x_grid_control.h"


x_grid_control::x_grid_control(QWidget *parent) : QWidget(parent)
{
    x_grid_impl* impl = new x_grid_impl;
    impl->m_grid = this;
    impl->m_paint_mana.m_grid_control = this;

    m_grid_impl = impl;
}

void x_grid_control::paintEvent(QPaintEvent *event)
{
	if (!event) return;

    x_grid_impl* impl = (x_grid_impl*)m_grid_impl;
    impl->m_paint_mana.draw_whole_grid();
}

