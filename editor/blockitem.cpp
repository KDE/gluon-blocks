#include "blockitem.h"

BlockItem::BlockItem(float w, float h,KGLPhysicsEngine* parent)
        :KGLPhysicsItem(KGLPhysicsItem::PolygonShape,parent)
{
createBox(w,h);
}
void BlockItem::paintGL()
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