#ifndef ITEMSDOCK_H
#define ITEMSDOCK_H

#include <QDockWidget>
#include <QTreeWidget>
#include <gluon/kgl/kglengine.h>
class ItemsDock : public QDockWidget
{
public:
    ItemsDock(QWidget * parent=0);
    QTreeWidget * treeWidget(){return m_treeWidget;}
private:
    QTreeWidget * m_treeWidget;

};

#endif // ITEMSDOCK_H
