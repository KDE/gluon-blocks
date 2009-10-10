#include "blokengine.h"
#include <gluon/kgl/kglview.h>
#include <KLocale>
#include <QMessageBox>
BlokEngine::BlokEngine(KGLPhysicsEngine * parent)
    : KGLPhysicsEngine(parent)
{
    m_ambianceSound = new KALSound();
    m_backGround= new KGLBoxItem(20, 20);
    m_ground = new KGLPhysicsItem(KGLPhysicsItem::PolygonShape,this);

    m_backGround->setPosition(-m_backGround->center());

    m_backGround->updateTransform();
    m_backGround->setZIndex(LAYER_BEHIND);

    m_ground->createBox(20, 1);
    m_ground->setZIndex(LAYER_BEHIND);
    m_ground->setTexture(m_groundPath);
    m_ground->texture()->scale(QPoint(1,1));
    m_ground->setPosition(-10, -10);
    m_ground->setStatic();
    m_ground->setObjectName("GROUND_OBJECT");


    m_wallLeft = new KGLPhysicsItem;
    m_wallRight = new KGLPhysicsItem;
    m_wallTop = new KGLPhysicsItem;


    QString spritesResourceDir, soundsResourceDir;
    spritesResourceDir = KGlobal::dirs()->findResourceDir("appdata", "data/sprites/") + "data/sprites/";
    soundsResourceDir = KGlobal::dirs()->findResourceDir("appdata", "data/sounds/") + "data/sounds/";

    m_emptyClickSound = new KALSound(soundsResourceDir + "empty-click.wav");
    m_removeCLickSound = new KALSound(soundsResourceDir + "remove-click.ogg");

    m_nbNormalBlock=0;
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


    m_wallLeft->createBox(0.1,20);
    m_wallLeft->setPosition(-10,-10);
    m_wallLeft->updateTransform();
    m_wallLeft->setStatic(true);

    m_wallRight->createBox(0.1,20);
    m_wallRight->setPosition(9.9,-10);
    m_wallRight->updateTransform();
    m_wallRight->setStatic(true);

    m_wallTop->createBox(20,0.1);
    m_wallTop->setPosition(-10,9.9);
    m_wallTop->updateTransform();
    m_wallTop->setStatic(true);

    addItem(m_wallLeft);
    addItem(m_wallRight);
    addItem(m_wallTop);
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

foreach ( BlokItem * item, m_blokList)
    {
    if ( item->remove()==true)
    {
 remBlok(item);
    }
}
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
            m_nbNormalBlock--;
            removeItem(item);
            m_removeCLickSound->play();

            if ( m_nbNormalBlock<=1)
                QMessageBox::information(0, i18n("You Win"), i18n("You destroyed all normal items!!"));
            return;
        }

        if ( blok->blokType() == BlokItem::Explode)
        {
        blok->explose(10,20);
        }






        else m_emptyClickSound->play();

    }
}

void BlokEngine::addBlok(BlokItem * item)
{
    addItem(item);
    m_blokList.append(item);
}
void BlokEngine::remBlok(BlokItem * item)
{
    removeItem(item);
    m_blokList.removeOne(item);

}
