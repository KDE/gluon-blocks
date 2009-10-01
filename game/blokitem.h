#ifndef BLOKITEM_H
#define BLOKITEM_H
#include <gluon/kgl/kglphysicsitem.h>
#include <gluon/kal/kalsound.h>
#include <gluon/kgl/kglparticlesitem.h>

#include <KStandardDirs>

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
    void resize(float w, float h);
    float width() { return m_width; }
    float height() { return m_height; }
private:
    ItemType m_blokType;
    float m_width;
    float m_height;
protected:
    void paintGL();

};

//=========NORMAL BLOCK =======================
class NormalBlok : public BlokItem
{
public:
    NormalBlok()
        :BlokItem(){
        setTexture(KGlobal::dirs()->findResourceDir("appdata", "data/sprites/") + "data/sprites/normal_block.png");
        setBlokType(Normal);
        setObjectName("NORMAL_BLOCK");
    }
};

//=========SOLID BLOCK =======================
class SolidBlok : public BlokItem
{
public:
    SolidBlok()
        :BlokItem(){
        setTexture(KGlobal::dirs()->findResourceDir("appdata", "data/sprites/") + "data/sprites/solid_block.png");
        setBlokType(Solid);
        setObjectName("SOLID_BLOCK");
    }
};

//=========CHIMIC BLOCK =======================
class ChimicBlok : public BlokItem
{
public:
    ChimicBlok()
        :BlokItem(){
        setTexture(KGlobal::dirs()->findResourceDir("appdata", "data/sprites/") + "data/sprites/chimic_block.png");
        setBlokType(Chimic);
        setObjectName("CHIMIC_BLOCK");
        m_exploseSound=new KALSound(KGlobal::dirs()->findResourceDir("appdata", "data/sounds/") + "data/sounds/explosion.wav");
    }
    void explose(float Radius, float Force);
    void collidesWithItem(KGLPhysicsItem * item);
    KALSound * m_exploseSound;
};

//=========EXPLOSE BLOCK =======================
class ExploseBlok : public BlokItem
{
public:
    ExploseBlok()
        :BlokItem(){
        setTexture(KGlobal::dirs()->findResourceDir("appdata", "data/sprites/") + "data/sprites/explode_block.png");
        setBlokType(Explode);
        setObjectName("EXPLOSE_BLOCK");
        m_exploseSound=new KALSound(KGlobal::dirs()->findResourceDir("appdata", "data/sounds/") + "data/sounds/explosion.wav");
    }
    void explose(float Radius, float Force);
    KALSound * m_exploseSound;
};

//=========EXPLOSE BLOCK =======================

class TotemBlok : public BlokItem
{
public:
    TotemBlok()
        :BlokItem(){
        setTexture(KGlobal::dirs()->findResourceDir("appdata", "data/sprites/") + "data/sprites/totem1_block.png");
        setBlokType(Totem);
        setObjectName("TOTEM_BLOCK");
    }

    void collidesWithItem(KGLPhysicsItem * item);
};





#endif // BLOKITEM_H
