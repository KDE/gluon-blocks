#include "editor.h"

#include <QToolBar>

#include <KActionCollection>
#include <KStandardAction>
#include <KApplication>
#include <KFileDialog>
#include <KSaveFile>
#include <KAction>
#include <KLocale>

#include "blockitem.h"
#include "editorview.h"
#include "optionsdock.h"

Editor::Editor(QWidget * parent)
    : KXmlGuiWindow(parent),
    m_editorView (new EditorView),
    m_currentFile(QString())
{
    m_optionsDock= new OptionsDock(m_editorView);
    setCentralWidget(m_editorView);
    addDockWidget(Qt::LeftDockWidgetArea, m_optionsDock);

    setupActions();

    newFile();
}

void Editor::setupActions()
{
    KStandardAction::openNew    (this, SLOT(newFile()),    actionCollection());
    KStandardAction::open       (this, SLOT(openFile()),   actionCollection());
    KStandardAction::openRecent (this, SLOT(openFile()),   actionCollection());
    KStandardAction::save       (this, SLOT(saveFile()),   actionCollection());
    KStandardAction::saveAs     (this, SLOT(saveFileAs()), actionCollection());
    KStandardAction::quit       (kapp, SLOT(quit()),       actionCollection());

    KAction* startAction = new KAction(this);
    startAction->setText(i18n("Start Engine"));
    startAction->setIcon(KIcon("system-run"));
    actionCollection()->addAction("startengine", startAction);
    connect(startAction, SIGNAL(triggered()), m_editorView, SLOT(start()));
    connect(startAction,SIGNAL(triggered(bool)),m_optionsDock,SLOT(setEnabled(bool)));
    connect(startAction,SIGNAL(triggered(bool)),m_editorView,SLOT(setEnabled(bool)));

    KAction* stopAction = new KAction(this);
    stopAction->setText(i18n("Stop Engine"));
    stopAction->setIcon(KIcon("window-close"));
    actionCollection()->addAction("stopengine", stopAction);
    connect(stopAction, SIGNAL(triggered()), m_editorView, SLOT(stop()));
    connect(stopAction,SIGNAL(triggered(bool)),m_optionsDock,SLOT(setDisabled(bool)));
    connect(stopAction,SIGNAL(triggered(bool)),m_editorView,SLOT(setDisabled(bool)));
    setupGUI();
}

void Editor::newFile()
{
    m_editorView->initEngine();
    m_currentFile.clear();
    m_editorView->setWallpaperTexture(m_optionsDock->wallpaperTexturePath());
    m_editorView->setGroundTexture(m_optionsDock->groundTexturePath());
    m_optionsDock->refreshList();
}

void Editor::openFile()
{
    QString fileNameFromDialog = KFileDialog::getOpenFileName();
    QFile file(fileNameFromDialog);
    file.open(QIODevice::ReadOnly);

    QDataStream in(&file);

    newFile();

    QString wallpaperTexture, groundTexture;
    in >> wallpaperTexture >> groundTexture;

    m_editorView->setWallpaperTexture(wallpaperTexture);
    m_editorView->setGroundTexture(groundTexture);

    KGLPhysicsEngine *engine = qobject_cast<KGLPhysicsEngine *>(m_editorView->engine());
    while (!in.atEnd())
    {
        qreal x, y, width, height;
        QString texturePath;
        in >> x >> y >> width >> height >> texturePath;

        BlockItem *item = new BlockItem(width, height);
        item->setTexture(texturePath);
        item->setPosition(x, y);
        item->updateTransform();
        engine->addItem(item);
        m_editorView->blockList().append(item);
    }
    m_optionsDock->refreshList();
    file.close();

    m_currentFile = fileNameFromDialog;
}

void Editor::saveFile()
{
    if(!m_currentFile.isEmpty())
        saveFileAs(m_currentFile);
    else
        saveFileAs();
}

void Editor::saveFileAs()
{
    saveFileAs(KFileDialog::getSaveFileName());
}

void Editor::saveFileAs(const QString &outputFileName)
{
    KSaveFile file(outputFileName);
    file.open();

    QDataStream out(&file);

    out << m_editorView->wallpaperTexture();
    out << m_editorView->groundTexture();

    BlockItem *blockItem;
    foreach (KGLItemList itemList, m_editorView->engine()->items().values())
        foreach (KGLItem *item, itemList)
        {
        if ((blockItem = dynamic_cast<BlockItem *>(item)))
        {
            out << blockItem->position().x() << item->position().y();
            out << blockItem->boundingBox().width() << item->boundingBox().height();
            out << blockItem->texturePath();
        }
    }

    file.close();
    m_currentFile = outputFileName;
}

