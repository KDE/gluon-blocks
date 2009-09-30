#ifndef ITEMSDOCK_H
#define ITEMSDOCK_H

#include <QDockWidget>

#include <gluon/kgl/kglengine.h>

class QListWidget;

class ItemsDock : public QDockWidget
{
public:
    ItemsDock(QWidget *parent=0);
private:
    QListWidget *m_itemsListWidget;
};

#endif // ITEMSDOCK_H
