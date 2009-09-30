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
    void setWallpaperTexture(const QString &path);
    void setGroundTexture(const QString & path);
signals:
    void updateProperties(const QMap<QString, QString> &properties);
public slots:
    void setItemTexture(QString path);
    void setItemSize(double w, double h);
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
private:
    KGLPhysicsEngine *m_engine;
    KGLPhysicsItem *m_groundItem;
    KGLBoxItem *m_wallPaperItem;
    BlockItem *m_selectedItem;
    QString m_currentTexture;
    bool m_moving;
};

#endif // BLOCKENGINE_H
