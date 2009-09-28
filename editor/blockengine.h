#ifndef BLOCKENGINE_H
#define BLOCKENGINE_H
#include <QMouseEvent>
#include <QWheelEvent>
#include <gluon/kgl/kglphysicsengine.h>
#include <gluon/kgl/kglview.h>

#include "blockitem.h"

class BlockCore : public KGLView
{
    Q_OBJECT
    public:
BlockCore(QWidget * parent=0);
void setWallpaperTexture(const QString &path){
    m_wallPaperItem->setTexture(path);

}
void setGroundTexture(const QString & path){
    m_groundItem->setTexture(path);
}

public slots:
void setItemTexture(QString path){
m_currentItem->setTexture(path);
m_currentItem->texture()->setScale(m_currentItem->width(),m_currentItem->height());
}
void setItemSize(double w,double h){
m_currentItem->resize(w,h);
m_currentItem->texture()->setScale(w,h);
}


protected:
void mouseMoveEvent(QMouseEvent *event);
void mousePressEvent(QMouseEvent * event);
void wheelEvent(QWheelEvent*event);

private:
KGLPhysicsEngine * m_engine;
KGLBoxItem * m_wallPaperItem;
 KGLPhysicsItem * m_groundItem;
 KGLBoxItem * m_currentItem;


};




#endif // BLOCKENGINE_H
