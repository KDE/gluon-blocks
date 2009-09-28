#include "blockengine.h"

BlockCore::BlockCore(QWidget * parent)
    :KGLView(parent)
{
    grabMouse();
    m_engine= new KGLPhysicsEngine;
    setEngine(m_engine);
    m_wallPaperItem =new KGLBoxItem(20,20);
    m_wallPaperItem->setPosition(-10,-10);
    m_wallPaperItem->updateTransform();

    m_engine->addItem(m_wallPaperItem);


    m_groundItem= new KGLPhysicsItem;
    m_groundItem->createBox(20,1);
    m_groundItem->setPosition(-10,-10);
    m_groundItem->updateTransform();
    m_groundItem->setStatic(true);

    m_engine->addItem(m_groundItem);

    m_currentItem=new KGLBoxItem;
    m_currentItem->setColor(QColor(255,255,255,100));
    m_engine->addItem(m_currentItem);

//    start();
}




void BlockCore::mouseMoveEvent(QMouseEvent *event)
{


    m_currentItem->setPosition(mapToGL(event->pos()));
    m_currentItem->updateTransform();

updateGL();

}

void BlockCore::mousePressEvent(QMouseEvent *event)
{

    if ( event->button() == Qt::LeftButton)
    {
        kDebug()<<"click..";
        BlockItem * item =new BlockItem(m_currentItem->width(),m_currentItem->height());
       item->setTexture(m_currentItem->texture()->glId());
       item->texture()->setScale(m_currentItem->width(),m_currentItem->height());
       item->setPosition(m_currentItem->position());
       item->updateTransform();
        m_engine->addItem(item);
    }

}


void BlockCore::wheelEvent(QWheelEvent*event)
{

    //m_currentItem->rotate(event->delta()/80);
    //m_currentItem->updateTransform();

    m_currentItem->setColor(Qt::red);


}
