#include "blokitem.h"
#include <gluon/kgl/kglboxitem.h>
BlokItem::BlokItem(float w, float h,KGLEngine * parent)
    :KGLPhysicsItem(KGLPhysicsItem::PolygonShape,parent)
{
    createBox(w,h);
    setZIndex(LAYER_MIDDLE);
}
void BlokItem::setBlokType(ItemType newType)
{
    m_blokType = newType;
}

BlokItem::ItemType BlokItem::blokType()
{
    return m_blokType;
}

void BlokItem::paintGL()
{
    KGLPhysicsItem::paintGL();
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

//==================++EXPLOSE==========================
void ExploseBlok::explose(float Radius, float Force)
{
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


