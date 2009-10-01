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
  m_optionsDock(new OptionsDock),
  m_currentFile(QString())
{
    setCentralWidget(m_editorView);
    addDockWidget(Qt::LeftDockWidgetArea, m_optionsDock);

    setupActions();

    newFile();

    connect(m_optionsDock, SIGNAL(itemTextureChanged(QString)), m_editorView, SLOT(setItemTexture(QString)));
    connect(m_optionsDock, SIGNAL(wallpaperTextureChanged(QString)), m_editorView, SLOT(setWallpaperTexture(QString)));
    connect(m_optionsDock, SIGNAL(groundTextureChanged(QString)), m_editorView, SLOT(setGroundTexture(QString)));
    connect(m_editorView , SIGNAL(updateProperties(const QMap<QString, QWidget *>&)), m_optionsDock, SLOT(updateProperties(const QMap<QString, QWidget *>&)));
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

    KAction* stopAction = new KAction(this);
    stopAction->setText(i18n("Stop Engine"));
    stopAction->setIcon(KIcon("window-close"));
    actionCollection()->addAction("stopengine", stopAction);
    connect(stopAction, SIGNAL(triggered()), m_editorView, SLOT(stop()));

    setupGUI();
}

void Editor::newFile()
{
    m_editorView->initEngine();
    m_currentFile.clear();
    m_editorView->setWallpaperTexture(m_optionsDock->wallpaperTexturePath());
    m_editorView->setGroundTexture(m_optionsDock->groundTexturePath());
    m_editorView->setItemTexture(m_optionsDock->itemTexturePath());
    m_optionsDock->initPropertyEditor(m_editorView->propertiesMap());
}

void Editor::openFile()
{
    QString fileNameFromDialog = KFileDialog::getOpenFileName();
    QFile file(fileNameFromDialog);
    file.open(QIODevice::ReadOnly);

    QDataStream in(&file);

    newFile();
    while (!in.atEnd())
    {
        qreal x, y, width, height;
        QImage texture;
        in >> x >> y >> width >> height >> texture;

        BlockItem *item = new BlockItem(1, 1);
        item->resize(width, height);
        item->setTexture(texture);
        item->texture()->setScale(item->width(), item->height());
        item->setPosition(x, y);
        item->updateTransform();
        m_editorView->engine()->addItem(item);
        kDebug() << "Agora a engine tem " << m_editorView->engine()->itemsCount();
    }
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

    foreach (KGLItemList itemList, m_editorView->engine()->items().values())
        foreach (KGLItem *item, itemList)
        {
            if (dynamic_cast<BlockItem *>(item))
            {
                out << item->position().x() << item->position().y();
                out << item->boundingBox().width() << item->boundingBox().height();
                out << item->texture()->image();
            }
        }

    file.close();
    m_currentFile = outputFileName;
}
