#-------------------------------------------------
#
# Project created by QtCreator 2018-09-06T18:00:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = grid_table
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    x_grid_impl.cpp \
    x_grid_control.cpp \
    x_paint_manager.cpp \
    x_grid_gl_control.cpp

HEADERS += \
    x_grid_impl.h \
    x_grid_control.h \
    x_paint_manager.h \
    impl_grid_cell_values.hpp \
    x_grid_gl_control.h

FORMS += \
        grid_table.ui
