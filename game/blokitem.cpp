#include "blokitem.h"
#include <gluon/kgl/kglboxitem.h>
#include <QMessageBox>
#include <KLocale>
#include <gluon/kgl/kglview.h>
BlokItem::BlokItem(float w, float h,KGLEngine * parent)
        :KGLPhysicsItem(parent,KGLPhysicsItem::PolygonShape)
{
    createBox(w,h);
    setZIndex(LAYER_MIDDLE);
    m_willRemove=false;
    m_exploseSound=new KALSound(KGlobal::dirs()->findResourceDir("appdata", "data/sounds/") + "data/sounds/explosion.wav");
}
void BlokItem::setBlokType(ItemType newType)
{
    m_blokType = newType;
}

BlokItem::ItemType BlokItem::blokType()
{
    return m_blokType;
}

void BlokItem::resize(float w, float h)
{
    m_width = w;
    m_height = h;
    createBox(w, h);
}

void BlokItem::paintGL()
{
    KGLPhysicsItem::paintGL();

    if ( objectName() != "TOTEM_BLOCK")
    {
        glPushMatrix();
        glLoadMatrixd(matrix().data());
        glEnable( GL_LINE_SMOOTH );
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glLineWidth(2);
        glBegin(GL_LINE_LOOP);
        glColor3d(0,0,0);

        glVertex2d(boundingBox().bottomLeft().x(),boundingBox().bottomLeft().y());
        glVertex2d(boundingBox().bottomRight().x(),boundingBox().bottomRight().y());
        glVertex2d(boundingBox().topRight().x(),boundingBox().topRight().y());
        glVertex2d(boundingBox().topLeft().x(),boundingBox().topLeft().y());


        glEnd();

        glPopMatrix();
    }

}

void BlokItem::explose(float Radius, float Force)
{
    setRemove(true);
    m_exploseSound->play();
    float Xpos = body()->GetPosition().x;
    float Ypos = body()->GetPosition().y;
    b2AABB Sector;
    Sector.lowerBound.Set(Xpos-Radius, Ypos-Radius);
    Sector.upperBound.Set(Xpos+Radius, Ypos+Radius);
    const int32 k_bufferSize = 512;
    b2Shape *buffer[k_bufferSize];


    int32 count = body()->GetWorld()->Query(Sector, buffer, k_bufferSize);
    b2Body* Body;
    b2Vec2 HitVector;
    b2Vec2 HitPoint;
    b2Vec2 BodyPos;
    float a;
    float b;
    float c;
    float HitForce;
    float Distance;
    for (int32 i = 0; i < count; ++i)
    {
        Body = buffer[i]->GetBody();
        BodyPos = Body->GetWorldCenter();
        Distance=sqrt(pow((BodyPos.x)-Xpos,2)+pow((BodyPos.y)-Ypos,2));
        if ((Body->IsDynamic()) & (Distance<=Radius))
        {
            HitForce=(Radius-Distance)*Force;
            a=BodyPos.x-Xpos;
            b=BodyPos.y-Ypos;
            c=sqrt(pow(a,2)+pow(b,2));
            HitVector.Set(HitForce*(a/c), HitForce*(b/c));
            HitPoint=Body->GetWorldCenter();
            Body->ApplyImpulse(HitVector, HitPoint);
        };
    }
}

//==================CHIMIC=========================


void ChimicBlok::collidesWithItem(KGLPhysicsItem * item)
{

    if ( item->objectName()=="CHIMIC_BLOCK")
    {
        explose(5,3);
        setRemove(true);
    }

}

//==================++EXPLOSE==========================


void TotemBlok::collidesWithItem(KGLPhysicsItem * item)
{

    if ( item->objectName() == "GROUND_OBJECT")
    {
        setColor(Qt::red);
        QMessageBox::information(0, i18n("You Lost"), i18n("The totem has touched the floor...sorry"));
        KGLEngine * engine = qobject_cast<KGLEngine*>(parent());
        KGLView * view = qobject_cast<KGLView*>(engine->parent());
        view->stop();
    }
}
