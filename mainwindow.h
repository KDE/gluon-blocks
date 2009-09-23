#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMouseEvent>
// QMouseEvent must be included before KXmlGuiWindow because X11 headers
// (indirectly included by KXMLGuiWindow) define the symbol None, also
// present in qcoreevent.h
#include <KXmlGuiWindow>
#include <gluon/kgl/kglview.h>
#include "blokengine.h"
#include "blokitem.h"

class Mainwindow : public KXmlGuiWindow
{
public:
    Mainwindow(QWidget * parent = 0);
    ~Mainwindow() {
        delete m_engine;
    }
    void mousePressEvent(QMouseEvent * event);
private:
    BlokEngine * m_engine;
    KGLView * m_view;
};

#endif // MAINWINDOW_H
