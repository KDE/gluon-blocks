#ifndef BLOCKITEM_H
#define BLOCKITEM_H
#include <gluon/kgl/kglphysicsitem.h>
#include <gluon/kgl/kglphysicsengine.h>
class BlockItem : public KGLPhysicsItem
{
public:
    BlockItem(float w,float h,KGLPhysicsEngine * parent=0);
    void paintGL();
};

#endif // BLOCK_H
