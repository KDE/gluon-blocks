#include "blokitem.h"

BlokItem::BlokItem(float w, float h,KGLEngine * parent)
     :KGLPhysicsItem(parent)
{

createBox(w,h);
setZIndex(2);
m_texPic = "sprites/text01.png";
setTexture(m_texPic);

dropSound = new KALSource("bounce.ogg");

connect(this,SIGNAL(collided()),this, SLOT(drop()));

}

    void BlokItem::drop()
    {


    }
