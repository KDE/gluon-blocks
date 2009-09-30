#include "editorview.h"

#include <QCursor>

#include <gluon/kgl/kglphysicsengine.h>
#include "blockitem.h"

EditorView::EditorView(QWidget * parent) : KGLView(parent), m_selectedItem(0), m_moving(false)
{
    grabMouse();
    m_engine = new KGLPhysicsEngine;
    setEngine(m_engine);
    setMouseTracking(true);

    m_wallPaperItem = new KGLBoxItem(20, 20);
    m_wallPaperItem->setPosition(-10, -10);
    m_wallPaperItem->updateTransform();
    m_engine->addItem(m_wallPaperItem);

    m_groundItem = new KGLPhysicsItem;
    m_groundItem->createBox(20, 1);
    m_groundItem->setPosition(-10, -10);
    m_groundItem->updateTransform();
    m_groundItem->setStatic(true);
    m_engine->addItem(m_groundItem);

    setCursor(QCursor(Qt::CrossCursor));
}

void EditorView::setWallpaperTexture(const QString &path)
{
    m_wallPaperItem->setTexture(path);
}

void EditorView::setGroundTexture(const QString & path)
{
    m_groundItem->setTexture(path);
}

void EditorView::setItemTexture(QString path)
{
    m_currentTexture = path;
}

void EditorView::setItemSize(double w, double h)
{
    if (m_selectedItem)
    {
	m_selectedItem->resize(w, h);
	m_selectedItem->texture()->setScale(w, h);
	m_selectedItem->setColor(QColor(255, 255, 255, 100));
	updateGL();
    }
}

void EditorView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_moving)
    {
	m_selectedItem->setPosition(mapToGL(event->pos()));
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
	    item->setTexture(m_currentTexture);
	    item->texture()->setScale(item->width(), item->height());
	    item->setPosition(mapToGL(event->pos()));
	    item->updateTransform();
	    m_engine->addItem(item);
	    newSelectedItem = dynamic_cast<BlockItem *>(item);
	}
	if (m_selectedItem)
	    m_selectedItem->setColor(QColor(255, 255, 255, 255));
	newSelectedItem->setColor(QColor(255, 255, 255, 100));
	m_selectedItem = dynamic_cast<BlockItem *>(newSelectedItem);
	setCursor(QCursor(Qt::ClosedHandCursor));

	QMap<QString, QString> properties;
	properties["Width"] = QString::number(m_selectedItem->width());
	properties["Height"] = QString::number(m_selectedItem->height());

	emit updateProperties(properties);
    }
    updateGL();
}

void EditorView::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_moving = false;
}

void EditorView::wheelEvent(QWheelEvent*event)
{
    Q_UNUSED(event);
}
