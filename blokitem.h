#ifndef BLOKITEM_H
#define BLOKITEM_H
#include <gluon/kgl/kglphysicsitem.h>
#include <gluon/kal/kalsource.h>

class BlokItem : public KGLPhysicsItem
{
    Q_OBJECT
public:
   BlokItem(float w=1, float=1, KGLEngine * parent=0);

public slots:
    void drop();

   private:
   QString m_texPic;
   KALSource * dropSound ;

};

#endif // BLOKITEM_H
