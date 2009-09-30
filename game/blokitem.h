#ifndef BLOKITEM_H
#define BLOKITEM_H
#include <gluon/kgl/kglphysicsitem.h>
#include <gluon/kal/kalsound.h>
#include <gluon/kgl/kglparticlesitem.h>
#define LAYER_BEHIND 0
#define LAYER_MIDDLE 1
#define LAYER_END 2

class BlokItem : public KGLPhysicsItem
{
    Q_OBJECT
public:
    enum ItemType
    {
        Normal = 0,
        Solid = 1,
        Chimic = 2,
        Explode=3,
        Totem=4
          };
    BlokItem(float w = 1.5, float = 1.5, KGLEngine * parent = 0);
    ItemType blokType();
    void setBlokType(ItemType newType);


private:
    ItemType m_blokType;
protected:
    void paintGL();

};

//=========NORMAL BLOCK =======================
class NormalBlok : public BlokItem
{
public:
    NormalBlok()
        :BlokItem(){
        setTexture("data/sprites/normal_block.png");
        setBlokType(Normal);
    }
};

//=========SOLID BLOCK =======================
class SolidBlok : public BlokItem
{
public:
    SolidBlok()
        :BlokItem(){
        setTexture("data/sprites/solid_block.png");
        setBlokType(Solid);
    }
};

//=========NORMAL BLOCK =======================
class ChimicBlok : public BlokItem
{
public:
    ChimicBlok()
        :BlokItem(){
        setTexture("data/sprites/chimic_block.png");
        setBlokType(Chimic);
    }
};

//=========NORMAL BLOCK =======================
class ExploseBlok : public BlokItem
{
public:
    ExploseBlok()
        :BlokItem(){
        setTexture("data/sprites/explode_block.png");
        setBlokType(Explode);
        m_exploseSound=new KALSound("data/sounds/explosion.wav");
    }
    void explose(float Radius, float Force);
    KALSound * m_exploseSound;
};








#endif // BLOKITEM_H
