#ifndef BLOKENGINE_H
#define BLOKENGINE_H

#include <QMouseEvent>
#include <gluon/kgl/kglphysicsengine.h>
#include <gluon/kal/kalengine.h>
#include <gluon/kal/kalsound.h>
#include <gluon/kgl/kglparticlesitem.h>
#include <gluon/kgl/kglboxitem.h>

#include "blokitem.h"

class BlokEngine;


class BlokEngine : public KGLPhysicsEngine
{
    Q_OBJECT
public:
    BlokEngine(KGLPhysicsEngine * parent = 0);
    ~BlokEngine();
    void init();
    void addBlok(BlokItem * item);
    void remBlok(BlokItem * item);
    void setBackGround(const QString& path){
    m_backGroundPath = path;
    m_backGround->setTexture(path);
    }
    void setGround(const QString& path){
        m_groundPath = path;
        m_ground->setTexture(path);

    }
void setMusic(const QString& path){
m_ambianceSound->load(path);
m_ambianceSound->play();
m_ambianceSound->setLoop(true);

}
    void mainLoop(float ff);

    int m_nbNormalBlock;

protected:
    void mousePressed(const QPointF &pos, Qt::MouseButton button);

private:
    KGLBoxItem * m_backGround;
    KGLPhysicsItem * m_ground;
    QString m_backGroundPath;
    QString m_groundPath;
    KALSound * m_ambianceSound;
    KALSound * m_emptyClickSound;
    KALSound * m_removeCLickSound;
    KGLPhysicsItem * m_wallLeft;
    KGLPhysicsItem * m_wallRight;
    KGLPhysicsItem * m_wallTop;
    QList <BlokItem*> m_blokList;

public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

#endif // BLOKENGINE_H
