#include "itemsdock.h"

#include <QComboBox>
#include <QListWidget>

#include <KLocale>

ItemsDock::ItemsDock(QWidget *parent) : QDockWidget(parent)
{
    setObjectName("bloklist");
    setWindowTitle(i18n("Block List"));
    m_itemsListWidget = new QListWidget;
    setWidget(m_itemsListWidget);
}
