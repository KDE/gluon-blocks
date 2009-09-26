#ifndef BLOKITEM_H
#define BLOKITEM_H
#include <gluon/kgl/kglphysicsitem.h>
#include <gluon/kal/kalsound.h>
#include <gluon/kgl/kglparticlesitem.h>
class BlokItem : public KGLPhysicsItem
{
    Q_OBJECT
public:
	enum ItemType
	{
		Standard = 0,
		Totem = 1,
		Solid = 2
	};
    BlokItem(float w = 1, float = 1, KGLEngine * parent = 0);
    ItemType blokType();
    void setBlokType(ItemType newType);


private:
   ItemType m_blokType;
   QString m_texPic;
   KALSound * dropSound ;
   KGLParticlesItem * m_partItem;

   protected:
   void paintGL();
public slots:
    void drop();
};

#endif // BLOKITEM_H
