#include "editorview.h"

#include <QCursor>
#include <QDoubleSpinBox>
#include <QCheckBox>

#include <gluon/kgl/kglphysicsengine.h>
#include "blockitem.h"

EditorView::EditorView(QWidget * parent)
    : KGLView(parent),
    m_engine(0),
    m_selectedItem(0),
    m_moving(false),
    m_grid(true),
    m_gridSize(1)
{
    grabMouse();
    setMouseTracking(true);
    m_engine= new KGLPhysicsEngine;
    setEngine(m_engine);
    m_wallPaperItem = new KGLBoxItem(20, 20);
    m_groundItem = new KGLPhysicsItem;
    initEngine();
}
EditorView::~EditorView(){
    delete m_groundItem;
    delete m_wallPaperItem;
    delete m_selectedItem;


}

void EditorView::paintGL()
{
    KGLView::paintGL();
    if (m_grid)
    {
            glPushMatrix();
            glBegin(GL_LINES);
            glColor3ub(200, 200, 200);

            int x, y;
            for (x = -10; x <= 10; x+=m_gridSize)
            {
                glVertex2d(x, -10);
                glVertex2d(x, 10);
            }
            for (y = -10; y <= 10; y+=m_gridSize)
            {
                glVertex2d(-10, y);
                glVertex2d(10, y);
            }

            glEnd();
            glPopMatrix();
    }
}

void EditorView::initEngine()
{
    stop();
    removeAll();
    m_wallPaperItem->setPosition(-10, -10);
    m_wallPaperItem->updateTransform();
    m_engine->addItem(m_wallPaperItem);
    m_groundItem->createBox(20, 1);
    m_groundItem->setPosition(-10, -10);
    m_groundItem->updateTransform();
    m_groundItem->setStatic(true);
    m_engine->addItem(m_groundItem);

    setCursor(QCursor(Qt::CrossCursor));
    m_blockList.clear();
    updateGL();
    m_selectedItem = 0;
}


void EditorView::setItemTexture(QString path)
{
    m_currentBlockTexture = path;
}

void EditorView::setWallpaperTexture(QString path)
{
    m_wallpaperTexture = path;
    m_wallPaperItem->setTexture(m_wallpaperTexture);
    updateGL();
}

void EditorView::setGroundTexture(QString path)
{
    m_groundTexture = path;
    m_groundItem->setTexture(m_groundTexture);
    updateGL();
}

void EditorView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_moving)
    {
        QPointF newPos = mapToGL(event->pos()-m_selectedItem->center());
        if (m_grid)
        {
            newPos /= m_gridSize;
            newPos = newPos.toPoint() * m_gridSize;
        }
        m_selectedItem->setPosition(newPos);
        m_selectedItem->updateTransform();
        m_engine->world()->DestroyBody(m_selectedItem->body());
        m_selectedItem->setup(m_engine->world());
    }
    else
    {
        QPointF pos = mapToGL(event->pos());
        KGLPhysicsItem *item = m_engine->itemAt(pos);
        if (item)
            setCursor(QCursor(Qt::OpenHandCursor));
        else
            setCursor(QCursor(Qt::CrossCursor));
    }

    updateGL();
}

void EditorView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF pos = mapToGL(event->pos());
        KGLPhysicsItem *newSelectedItem = m_engine->itemAt(pos);

        if (newSelectedItem)
        {
            m_moving = true;
        }
        else
        {
            BlockItem *item = new BlockItem(1, 1);
            item->setTexture(m_currentBlockTexture);
            QPointF position = mapToGL(event->pos()-item->center());
            if (m_grid)
            {
                position /= m_gridSize;
                position = position.toPoint() * m_gridSize;
            }
            item->setPosition(position);
            item->updateTransform();
            m_engine->addItem(item);
            m_blockList.append(item);
            emit itemAdded();
            newSelectedItem = dynamic_cast<BlockItem *>(item);
        }
        if (m_selectedItem)
            m_selectedItem->setColor(QColor(255, 255, 255, 255));
        
        newSelectedItem->setColor(QColor(255, 255, 255, 100));
        m_selectedItem = dynamic_cast<BlockItem *>(newSelectedItem);
        updateGL();
        emit itemSelected(m_blockList.indexOf(m_selectedItem));
        setCursor(QCursor(Qt::ClosedHandCursor));
    }
}

void EditorView::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_moving = false;
    setCursor(QCursor(Qt::OpenHandCursor));
}

void EditorView::wheelEvent(QWheelEvent*event)
{
    Q_UNUSED(event);
}


void EditorView::setItemSize(const QSizeF& size)
{
    if (m_selectedItem)
    {
        m_selectedItem->resize(size.width(), size.height());
        m_selectedItem->texture()->setScale(size.width(), size.height());
        m_selectedItem->setColor(QColor(255, 255, 255, 100));
        updateGL();
    }
}
void EditorView::removeBlock(BlockItem * item)
{

    m_engine->removeItem(item);
    m_blockList.removeOne(item);
    updateGL();

}
void EditorView::removeAll()
{

    foreach (   BlockItem* item, m_blockList)
        m_engine->removeItem(item);
    m_blockList.clear();


}

void EditorView::enableGrid(int enabled)
{
    m_grid = (enabled == Qt::Checked) ? true:false;
    updateGL();
}

void EditorView::updateGridSize(int size)
{
    m_gridSize = size;
    updateGL();
}
