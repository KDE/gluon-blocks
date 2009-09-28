#include "itemsdock.h"
#include <QComboBox>
ItemsDock::ItemsDock(QWidget * parent)
        :QDockWidget(parent)
{
    setObjectName("blok list");
setWindowTitle("block list");
m_treeWidget=new QTreeWidget;
setWidget(m_treeWidget);



}
