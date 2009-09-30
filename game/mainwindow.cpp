#include "mainwindow.h"
Mainwindow::Mainwindow(QWidget * parent)
    : GluonMainWindow(parent)
{

    m_engine = new BlokEngine();

    setMinimumSize(500,500);
    view()->setEngine(m_engine);
    setMouseTracking(true);
   view()->start();


}

void Mainwindow::mousePressEvent(QMouseEvent * event)
{

    m_engine->mousePress(event);



}
