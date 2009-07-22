#include "mainwindow.h"

Mainwindow::Mainwindow(QWidget * parent)
        :KXmlGuiWindow(parent)
{

m_view = new KGLView(parent);
m_engine = new BlokEngine();
m_view->setEngine(m_engine);
setCentralWidget(m_view);

    setMouseTracking(true);



BlokItem * test = new BlokItem;
m_engine->addItem(test);

BlokItem * test1 = new BlokItem;
m_engine->addItem(test1);

BlokItem * test2 = new BlokItem;
m_engine->addItem(test2);

BlokItem * test3 = new BlokItem;
m_engine->addItem(test3);

BlokItem * test4 = new BlokItem;
m_engine->addItem(test4);

BlokItem * test5 = new BlokItem;
m_engine->addItem(test5);









m_view->setInfoShow(true);
m_view->setAxisShow(true);

m_view->start();
    setupGUI();

}

void Mainwindow::mousePressEvent(QMouseEvent * event)
{

  kDebug()<<m_view->mapToGL(event->pos());

    QPointF pos = m_view->mapToGL(event->pos());
    
    KGLPhysicsItem * item = m_engine->itemAt(pos) ;
    
   if ( item == NULL)
   {
    kDebug()<<"NULL";
     return;
   }
   else
   {
     
    kDebug()<<"yes"; 
    m_engine->removeItem(item);
     
   }
  
  
  
  
  
  
}
