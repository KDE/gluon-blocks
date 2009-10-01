#ifndef BLOCKENGINE_H
#define BLOCKENGINE_H

#include <QMouseEvent>
#include <QWheelEvent>

#include <gluon/kgl/kglview.h>

class KGLPhysicsItem;
class BlockItem;

class EditorView : public KGLView
{
Q_OBJECT
public:
    EditorView(QWidget * parent = 0);
    void initEngine();
    const QMap<QString, QWidget *> &propertiesMap() const;
signals:
    void updateProperties(const QMap<QString, QWidget *> &properties);
public slots:
    void setItemTexture(QString path);
    void setWallpaperTexture(QString path);
    void setGroundTexture(QString path);
    void widthChanged(double value);
    void staticChanged(int value);
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
private:
    void initPropertiesMap();
    KGLPhysicsEngine *m_engine;
    KGLPhysicsItem *m_groundItem;
    KGLBoxItem *m_wallPaperItem;
    BlockItem *m_selectedItem;
    QString m_currentBlockTexture;
    QString m_wallpaperTexture;
    QString m_groundTexture;
    QMap<QString, QWidget *> m_propertiesMap;
    bool m_moving;
};

#endif // BLOCKENGINE_H
