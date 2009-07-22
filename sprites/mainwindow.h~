#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <KXmlGuiWindow>
#include <gluon/kgl/kglview.h>
#include "blokengine.h"
#include "blokitem.h"

class Mainwindow : public KXmlGuiWindow
{
public:
    Mainwindow(QWidget * parent=0);

void mousePressEvent(QMouseEvent * event);
    private:
    BlokEngine * m_engine;
    KGLView * m_view;
};

#endif // MAINWINDOW_H
