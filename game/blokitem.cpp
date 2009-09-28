#include "blokitem.h"
#include <gluon/kgl/kglboxitem.h>
BlokItem::BlokItem(float w, float h,KGLEngine * parent)
    :KGLPhysicsItem(KGLPhysicsItem::PolygonShape,parent)
{

    createBox(w,h);
    setZIndex(2);
    m_texPic = "data/sprites/normal_block.png";
    setTexture(m_texPic);
    dropSound = new KALSound("data/sounds/bounce.ogg");
    connect(this, SIGNAL(collided()), this, SLOT(drop()));
}

void BlokItem::drop()
{


}

void BlokItem::setBlokType(ItemType newType)
{
    m_blokType = newType;
}

BlokItem::ItemType BlokItem::blokType()
{
    return m_blokType;
}

void BlokItem::paintGL()
{
    KGLPhysicsItem::paintGL();
    glPushMatrix();
    glLoadMatrixd(matrix().data());
    glEnable( GL_LINE_SMOOTH );
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glColor3d(0,0,0);

    glVertex2d(boundingBox().bottomLeft().x(),boundingBox().bottomLeft().y());
    glVertex2d(boundingBox().bottomRight().x(),boundingBox().bottomRight().y());
    glVertex2d(boundingBox().topRight().x(),boundingBox().topRight().y());
    glVertex2d(boundingBox().topLeft().x(),boundingBox().topLeft().y());


    glEnd();

    glPopMatrix();


}
