#ifndef BLOKITEM_H
#define BLOKITEM_H
#include <gluon/kgl/kglphysicsitem.h>
#include <gluon/kal/kalsource.h>
#include <gluon/kgl/kglparticlesitem.h>
class BlokItem : public KGLPhysicsItem
{
    Q_OBJECT
public:
   BlokItem(float w=1, float=1, KGLEngine * parent=0);

   private:
   QString m_texPic;
   KALSource * dropSound ;
KGLParticlesItem * m_partItem;
};

#endif // BLOKITEM_H
