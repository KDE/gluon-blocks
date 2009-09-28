#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMouseEvent>
#include <KXmlGuiWindow>
#include <gluon/kgl/kglview.h>
#include <gluon/kgl/kglphysicsengine.h>
#include <gluon/kgl/kglphysicsitem.h>

#include "blockengine.h"
#include "itemsdock.h"
#include "optiondock.h"
class Editor : public KXmlGuiWindow

{
public:
    Editor(QWidget *parent=0);
    void setupActions();

private:
    KGLView * m_view;
    BlockCore * m_blockCore;
    ItemsDock * m_itemsDock;
    OptionDock * m_optionDock;

};



#endif // MAINWINDOW_H
