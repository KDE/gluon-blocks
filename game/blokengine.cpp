#include "blokengine.h"
#include <gluon/kgl/kglview.h>
BlokEngine::BlokEngine(KGLPhysicsEngine * parent)
    : KGLPhysicsEngine(parent)
{
    m_ambianceSound=  new KALSound();
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


    addItem(m_backGround);
    addItem(m_ground);

    m_emptyClickSound = new KALSound("data/sounds/empty-click.wav");
    m_removeCLickSound = new KALSound("data/sounds/remove-click.ogg");



    setBackGround("data/sprites/sky_wallpaper.png");
    setGround("data/sprites/green_ground.png");
    setMusic("data/sounds/sober.ogg");


    addItem(new SolidBlok());
    addItem(new NormalBlok());
    addItem(new ChimicBlok());
    addItem(new ExploseBlok());
}



BlokEngine::~BlokEngine()
{
    delete m_ground;
    delete m_backGround;
    delete m_emptyClickSound;
    delete m_removeCLickSound;
}



void BlokEngine ::mainLoop(float ff)
{
    KGLPhysicsEngine::mainLoop(ff);
}

void BlokEngine::mousePress(QMouseEvent * event)
{
    KGLView * view  = qobject_cast<KGLView*>(parent());
    QPointF pos = view->mapToGL(event->pos());

    if ( event->button() == Qt::LeftButton)
    {
        KGLPhysicsItem * item = itemAt(pos) ;
        if (item == NULL) { return;}

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

