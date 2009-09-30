#ifndef BLOCKITEM_H
#define BLOCKITEM_H

#include <gluon/kgl/kglphysicsitem.h>

class KGLPhysicsEngine;

class BlockItem : public KGLPhysicsItem
{
public:
    BlockItem(float w, float h, KGLPhysicsEngine *parent = 0);
    void resize(float w, float h);
    float width() { return m_width; }
    float height() { return m_height; }
    void paintGL();
private:
    float m_width;
    float m_height;
};

#endif // BLOCK_H
