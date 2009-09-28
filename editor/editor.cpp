#include "editor.h"
#include <KApplication>
#include <KAction>
#include <KLocale>
#include <KActionCollection>
#include <KStandardAction>
#include <QToolBar>
Editor::Editor(QWidget * parent)
    :KXmlGuiWindow(parent)
{
    m_blockCore = new BlockCore;

    setCentralWidget(m_blockCore);

    m_itemsDock=new ItemsDock;
    m_optionDock= new OptionDock(m_blockCore);
    addDockWidget(Qt::LeftDockWidgetArea, m_optionDock);
    addDockWidget(Qt::RightDockWidgetArea, m_itemsDock);
    setupActions();
    m_blockCore->setWallpaperTexture(m_optionDock->wallPaperTexturePath());
    m_blockCore->setGroundTexture(m_optionDock->groundTexturePath());



    connect(m_optionDock,SIGNAL(itemPathChanged(QString)),m_blockCore,SLOT(setItemTexture(QString)));
    connect(m_optionDock,SIGNAL(geometryChanged(double,double)),m_blockCore,SLOT(setItemSize(double,double)));
}

void Editor::setupActions()
{

    KAction* startAction = new KAction(this);
    startAction->setText(i18n("start"));
    startAction->setIcon(KIcon("system-run"));

    actionCollection()->addAction("start", startAction);
    connect(startAction,SIGNAL(triggered()),m_blockCore,SLOT(start()));

     KAction* stopAction = new KAction(this);
    stopAction->setText(i18n("stop"));
    stopAction->setIcon(KIcon("window-close"));

    actionCollection()->addAction("stop", startAction);
    connect(stopAction,SIGNAL(triggered()),m_blockCore,SLOT(stop()));


QToolBar * toolBar = addToolBar("toolbar");
toolBar->addAction(startAction);
toolBar->addAction(stopAction);


    setupGUI();
}
