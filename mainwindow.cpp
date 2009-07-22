#include "mainwindow.h"

Mainwindow::Mainwindow(QWidget * parent)
        :KXmlGuiWindow(parent)
{

m_view = new KGLView(parent);
m_engine = new BlokEngine();
m_view->setEngine(m_engine);
setCentralWidget(m_view);

    setMouseTracking(true);



    
    for ( int i=0; i<5; ++i)
    {
BlokItem * test = new BlokItem;
m_engine->addItem(test);


    }


    for ( int i=0; i<5; ++i)
    {
BlokItem * test = new BlokItem;

test->setPosition(5,test->position().y());
m_engine->addItem(test);


    }
    
    
    KGLPhysicsItem * roof = new KGLPhysicsItem;
    roof->setTexture("sprites/text02.png");
    roof->texture()->scale(QPointF(6,1));
    roof->createBox(6,1);
    roof->setPosition(0,4);
    
    m_engine->addItem(roof);
    
    
        KGLPhysicsItem * totem = new KGLPhysicsItem;
   totem->setTexture("sprites/totem1.png");
    totem->createBox(2,2);
    totem->setPosition(3,6);
    
    m_engine->addItem(totem);







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
