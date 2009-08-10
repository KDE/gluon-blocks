#ifndef BLOKITEM_H
#define BLOKITEM_H
#include <gluon/kgl/kglphysicsitem.h>
#include <gluon/kal/kalsource.h>
#include <gluon/kgl/kglparticlesitem.h>
class BlokItem : public KGLPhysicsItem
{
    Q_OBJECT
public:
	enum ItemType
	{
		Standard = 0,
		Totem = 1
	};
    BlokItem(float w = 1, float = 1, KGLEngine * parent = 0);

private:
   ItemType m_blokType;
   QString m_texPic;
   KALSource * dropSound ;
   KGLParticlesItem * m_partItem;

public slots:
    void drop();
};

#endif // BLOKITEM_H
