#ifndef BLOKITEM_H
#define BLOKITEM_H
#include <gluon/kgl/kglphysicsitem.h>


class BlokItem : public KGLPhysicsItem
{
public:
   BlokItem(float w=1, float=1, KGLEngine * parent=0);



   private:
   QString m_texPic;


};

#endif // BLOKITEM_H
