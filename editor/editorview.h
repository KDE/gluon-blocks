#ifndef BLOCKENGINE_H
#define BLOCKENGINE_H

#include <QMouseEvent>
#include <QWheelEvent>
#include <QList>
#include <gluon/kgl/kglview.h>

class KGLPhysicsItem;
class KGLPhysicsEngine;
class BlockItem;

class EditorView : public KGLView
{
Q_OBJECT
public:
    EditorView(QWidget * parent = 0);
    ~EditorView();
    void initEngine();
    QList <BlockItem*> blockList(){
        return m_blockList;
        }
    BlockItem * selectedItem(){
        return m_selectedItem;
    }
    void removeAll();
signals:
    void updateProperties(const QMap<QString, QWidget *> &properties);
    void itemAdded();
    void itemSelected(int id);
public:
    void setItemTexture(QString path);
    void setWallpaperTexture(QString path);
    void setGroundTexture(QString path);
    void setItemSize(const QSizeF& size);
    void removeBlock(BlockItem * item);
    QString wallpaperTexture() { return m_wallpaperTexture; }
    QString groundTexture() { return m_groundTexture; }
public slots:
    void enableGrid(int enabled);
    void updateGridSize(int size);
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void paintGL();
private:
    void initPropertiesMap();
    KGLPhysicsEngine *m_engine;
    KGLPhysicsItem *m_groundItem;
    KGLBoxItem *m_wallPaperItem;
    BlockItem *m_selectedItem;
    QString m_currentBlockTexture;
    QString m_wallpaperTexture;
    QString m_groundTexture;
    QList<BlockItem*> m_blockList;
    bool m_moving;
    bool m_grid;
    int m_gridSize;
    double m_ratio;
    QPointF m_deltaMove;
};

#endif // BLOCKENGINE_H
