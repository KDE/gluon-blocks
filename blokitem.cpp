#include "blokitem.h"
#include <gluon/kgl/kglboxitem.h>
BlokItem::BlokItem(float w, float h,KGLEngine * parent)
     :KGLPhysicsItem(parent)
{

createBox(w,h);
setZIndex(2);
m_texPic = "sprites/text01.png";
setTexture(m_texPic);
 m_partItem = new KGLParticlesItem;

 m_partItem->createExplose(20,QPixmap());

    dropSound = new KALSound("bounce.ogg");

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
