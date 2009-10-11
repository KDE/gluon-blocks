#include "mainwindow.h"

#include <KLocale>
#include <KFileDialog>

Mainwindow::Mainwindow(QWidget * parent)
    : GluonMainWindow(parent)
{
    m_engine = new BlokEngine;
    setMinimumSize(500,500);
    view()->setEngine(m_engine);
    setMouseTracking(true);
    view()->start();
    setupActions();
    setupGluon();
}

void Mainwindow::setupActions()
{
    KAction* loadLevelAction = new KAction(this);
    loadLevelAction->setText(i18n("Load a Single Level"));
    loadLevelAction->setIcon(KIcon("document-open"));
    actionCollection()->addAction("loadLevel", loadLevelAction);
    connect(loadLevelAction, SIGNAL(triggered()), this, SLOT(loadLevel()));

    KAction* loadLevelsAction = new KAction(this);
    loadLevelsAction->setText(i18n("Load Multiple Levels"));
    loadLevelsAction->setIcon(KIcon("document-open-folder"));
    actionCollection()->addAction("loadLevels", loadLevelsAction);
    connect(loadLevelsAction, SIGNAL(triggered()), this, SLOT(loadLevels()));

    KStandardAction::quit(this, SLOT(close()), actionCollection());
}


void Mainwindow::loadLevel(const QString &fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);

    QDataStream in(&file);

    view()->stop();
    delete m_engine;
    m_engine = new BlokEngine;
    view()->setEngine(m_engine);
 m_engine->m_nbNormalBlock++;
    while (!in.atEnd())
    {
        qreal x, y, width, height;
        QString texturePath;
        in >> x >> y >> width >> height >> texturePath;

        BlokItem *item = 0;
        if (texturePath.contains("normal_block")){
            item = new NormalBlok;
        m_engine->m_nbNormalBlock++;
        }
        if (texturePath.contains("solid_block"))
            item = new SolidBlok;
        if (texturePath.contains("chimic_block"))
            item = new ChimicBlok;
        if (texturePath.contains("explode_block"))
            item = new ExploseBlok;
                if (texturePath.contains("totem"))
            item = new TotemBlok;

        item->resize(width, height);
        item->setPosition(x, y);
        item->texture()->setScale(item->width(), item->height());
        item->updateTransform();
        m_engine->addBlok(item);
    }
    file.close();
    view()->updateGL();
    m_engine->setMusic(KGlobal::dirs()->findResourceDir("appdata", "data/sounds/") + "data/sounds/sober.ogg");

    view()->start();
}

void Mainwindow::loadLevel()
{
    QString fileNameFromDialog = KFileDialog::getOpenFileName();
    if (fileNameFromDialog.isEmpty())
        return;
    loadLevel(fileNameFromDialog);
}

void Mainwindow::loadLevels()
{
}
