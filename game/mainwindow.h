#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMouseEvent>
// QMouseEvent must be included before KXmlGuiWindow because X11 headers
// (indirectly included by KXMLGuiWindow) define the symbol None, also
// present in qcoreevent.h
#include <KXmlGuiWindow>
#include <gluon/kgl/kglview.h>
#include <gluon/kgl/kgltextitem.h>
#include <gluon/gluonmainwindow.h>
#include "blokengine.h"
#include "blokitem.h"

class Mainwindow : public GluonMainWindow
{
Q_OBJECT
public:
    Mainwindow(QWidget * parent = 0);
    ~Mainwindow() {
        delete m_engine;
    }


public slots:
    void loadLevel();
    void loadLevels();
private:
    void setupActions();
    BlokEngine * m_engine;
    BlokItem * bomb;


};

#endif // MAINWINDOW_H
