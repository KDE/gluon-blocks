#include "blokengine.h"
#include <gluon/kgl/kglview.h>
BlokEngine::BlokEngine(KGLPhysicsEngine * parent)
    : KGLPhysicsEngine(parent)
{
    m_ambianceSound = new KALSound();
    m_backGround= new KGLBoxItem(20, 20);
    m_ground = new KGLPhysicsItem(KGLPhysicsItem::PolygonShape,this);

    m_backGround->setPosition(-m_backGround->center());
    m_backGround->setTexture(m_backGroundPath);
    m_backGround->updateTransform();
    m_backGround->setZIndex(LAYER_BEHIND);

    m_ground->createBox(20, 1);
    m_ground->setZIndex(LAYER_BEHIND);
    m_ground->setTexture(m_groundPath);
    m_ground->texture()->scale(QPoint(1,1));
    m_ground->setPosition(-10, -10);
    m_ground->setStatic();
    m_ground->setObjectName("GROUND_OBJECT");

    QString spritesResourceDir, soundsResourceDir;
    spritesResourceDir = KGlobal::dirs()->findResourceDir("appdata", "data/sprites/") + "data/sprites/";
    soundsResourceDir = KGlobal::dirs()->findResourceDir("appdata", "data/sounds/") + "data/sounds/";

    m_emptyClickSound = new KALSound(soundsResourceDir + "empty-click.wav");
    m_removeCLickSound = new KALSound(soundsResourceDir + "remove-click.ogg");


    init();
}

void BlokEngine::init()
{
    QString spritesResourceDir, soundsResourceDir;
    spritesResourceDir = KGlobal::dirs()->findResourceDir("appdata", "data/sprites/") + "data/sprites/";
    soundsResourceDir = KGlobal::dirs()->findResourceDir("appdata", "data/sounds/") + "data/sounds/";

    addItem(m_backGround);
    addItem(m_ground);
    setBackGround(spritesResourceDir + "sky_wallpaper.png");
    setGround(spritesResourceDir + "green_ground.png");
}

BlokEngine::~BlokEngine()
{
    m_ambianceSound->stop();
    delete m_ambianceSound;
    delete m_ground;
    delete m_backGround;
    delete m_emptyClickSound;
    delete m_removeCLickSound;
}



void BlokEngine ::mainLoop(float ff)
{
    KGLPhysicsEngine::mainLoop(ff);
}

void BlokEngine::mousePressed(QPointF pos, Qt::MouseButton button)
{
    if ( button == Qt::LeftButton)
    {
        KGLPhysicsItem * item = itemAt(pos) ;
        if (item == NULL) { kDebug() << "Nenhum item no cursor"; return;}

        BlokItem * blok = dynamic_cast<BlokItem*>(item);
        if (blok != NULL && blok->blokType() == BlokItem::Normal)
        {
            removeItem(item);
            m_removeCLickSound->play();
            return;
        }

        if (blok != NULL && blok->blokType() == BlokItem::Explode)
        {
            dynamic_cast<ExploseBlok*>(blok)->explose(10,5);
            removeItem(item);
            return;
        }

        else m_emptyClickSound->play();

    }
}

