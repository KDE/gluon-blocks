#include "editor.h"

#include <QToolBar>

#include <KApplication>
#include <KAction>
#include <KLocale>
#include <KActionCollection>
#include <KStandardAction>

#include "editorview.h"
#include "itemsdock.h"
#include "optionsdock.h"

Editor::Editor(QWidget * parent) : KXmlGuiWindow(parent)
{
    m_editorView = new EditorView;
    setCentralWidget(m_editorView);

    m_itemsDock = new ItemsDock;
    m_optionsDock = new OptionsDock;
    addDockWidget(Qt::LeftDockWidgetArea, m_optionsDock);
    addDockWidget(Qt::RightDockWidgetArea, m_itemsDock);

    setupActions();
    
    m_editorView->setWallpaperTexture(m_optionsDock->wallPaperTexturePath());
    m_editorView->setGroundTexture(m_optionsDock->groundTexturePath());
    m_editorView->setItemTexture(m_optionsDock->itemTexturePath());

    connect(m_optionsDock, SIGNAL(itemPathChanged(QString)), m_editorView, SLOT(setItemTexture(QString)));
    connect(m_optionsDock, SIGNAL(geometryChanged(double,double)), m_editorView, SLOT(setItemSize(double,double)));
    connect(m_editorView , SIGNAL(updateProperties(const QMap<QString, QString>&)), m_optionsDock, SLOT(updateProperties(const QMap<QString, QString>&)));
}

void Editor::setupActions()
{
    KAction* startAction = new KAction(this);
    startAction->setText(i18n("Star Engine"));
    startAction->setIcon(KIcon("system-run"));

    actionCollection()->addAction("startengine", startAction);
    connect(startAction, SIGNAL(triggered()), m_editorView, SLOT(start()));

    KAction* stopAction = new KAction(this);
    stopAction->setText(i18n("Stop Engine"));
    stopAction->setIcon(KIcon("window-close"));

    actionCollection()->addAction("stopengine", startAction);
    connect(stopAction, SIGNAL(triggered()), m_editorView, SLOT(stop()));

    QToolBar * toolBar = addToolBar("toolbar");
    toolBar->addAction(startAction);
    toolBar->addAction(stopAction);

    setupGUI();
}
