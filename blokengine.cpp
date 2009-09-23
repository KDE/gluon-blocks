#include "blokengine.h"

BlokEngine::BlokEngine(KGLPhysicsEngine * parent)
        : KGLPhysicsEngine(parent)
{
    KALEngine::instance();

    m_musicSource =  new KALSound("sounds/sober.ogg");
    m_fallSource =   new KALSound("sounds/bonebounce.ogg");
    m_musicSource->setLoop(true);
    m_musicSource->play();
    m_bkPic = "sprites/back.png";
    m_gdPic = "sprites/text03.png";
    m_flowerPic = "sprites/text05.png";
    m_grassPic = "sprites/text05.png";
    m_bkground = new KGLBoxItem(20, 20);
    m_ground = new KGLPhysicsItem(this);

    setBkGround();
    setGround();
    addFlower(-3);
    addFlower(6);
    addItem(m_bkground);
    addItem(m_ground);




}

BlokEngine::~BlokEngine()
{
}

void BlokEngine::setBkGround()
{


    m_bkground->setPosition(-m_bkground->center());
    m_bkground->setTexture(m_bkPic);
    m_bkground->updateTransform();
    m_bkground->setZIndex(LAYER_0);

    cloud = new KGLBoxItem(20, 10);
    cloud->setTexture("sprites/cloud.png");
    cloud->setZIndex(LAYER_1);
    cloud->setPosition(-10, 0);
    cloud->updateTransform();

    addItem(cloud);
}

void BlokEngine::setGround()
{

    m_ground->createBox(20, 1);
    m_ground->setZIndex(LAYER_1);
    m_ground->setTexture(m_gdPic);
    m_ground->texture()->setScale(QPointF(10, 1));
    m_ground->setPosition(-10, -10);
    m_ground->setStatic();


}
void BlokEngine::addFlower(const float &x)
{

    KGLBoxItem * flower = new KGLBoxItem(2, 2);
    flower->setTexture(m_flowerPic);
    flower->setPosition(x, -9);
    flower->updateTransform();
    flower->setZIndex(LAYER_1);
    addItem(flower);


}
void BlokEngine ::mainLoop(float ff)
{



    KGLPhysicsEngine::mainLoop(ff);


    cloud->texture()->translate(QPointF(0.001, 0));
    cloud->updateTransform();



}

