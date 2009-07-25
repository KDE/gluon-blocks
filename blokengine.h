#ifndef BLOKENGINE_H
#define BLOKENGINE_H
#include <gluon/kgl/kglphysicsengine.h>
#include <gluon/kal/kalengine.h>
#include <gluon/kal/kalsource.h>
#include <gluon/kgl/kglparticlesitem.h>
#define LAYER_0 0
#define LAYER_1 1
#define LAYER_2 2


class BlokEngine : public KGLPhysicsEngine
{
  Q_OBJECT
public:
    BlokEngine(KGLPhysicsEngine * parent=0);
    ~BlokEngine();
void setBkGround();
void setGround();
void mainLoop(float ff);
void addFlower(const float &x);
    private:
    KGLBoxItem * m_bkground;
    KGLPhysicsItem * m_ground;
    QString m_bkPic;
    QString m_gdPic;
    QString m_flowerPic;
    QString m_grassPic;

    KGLBoxItem * cloud;





        KALSource * m_musicSource;
 KALSource * m_fallSource;

        };

#endif // BLOKENGINE_H
