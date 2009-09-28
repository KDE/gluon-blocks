#include "optiondock.h"
#include <QVBoxLayout>

#include <KIcon>
#include <QDir>
#include <KDebug>

OptionDock::OptionDock(QWidget * parent)
    :QDockWidget(parent)
{
    setObjectName("option");
    QWidget * mainWidget = new QWidget;
    QVBoxLayout * mainLayout = new QVBoxLayout;

    m_infoTableWidget= new QTableWidget(5,2);
    m_itemTreeWidget= new QTreeWidget;
    m_bkgroundCombo= new QComboBox;
    m_groundCombo = new QComboBox;

    mainLayout->addWidget(m_infoTableWidget);
    mainLayout->addWidget(m_itemTreeWidget);
    mainLayout->addWidget(m_bkgroundCombo);
    mainLayout->addWidget(m_groundCombo);
    mainWidget->setLayout(mainLayout);
    setWidget(mainWidget);

    setupInfoTable();
    setupItemTree();
    setupCombo();
    connect(m_itemTreeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(setCurrentItemPath(QTreeWidgetItem*,int)));


}
void OptionDock::setupInfoTable()
{
    m_infoTableWidget->setAlternatingRowColors(true);
    m_infoTableWidget->setItem(0,0,new QTableWidgetItem("width"));
    m_infoTableWidget->setItem(1,0,new QTableWidgetItem("height"));
    m_infoTableWidget->setItem(2,0,new QTableWidgetItem("angle"));


    m_spinW = new QDoubleSpinBox;
    m_spinW->setObjectName("width");
    m_infoTableWidget->setCellWidget (0,1,m_spinW);
    m_spinW->setValue(5);

    m_spinH = new QDoubleSpinBox;
    m_spinH->setObjectName("height");
    m_infoTableWidget->setCellWidget (1,1,m_spinH);
m_spinH->setValue(5);

    m_angle = new QDoubleSpinBox;
    m_angle->setObjectName("angle");
    m_infoTableWidget->setCellWidget (2,1,m_angle);

    connect(m_spinW,SIGNAL(valueChanged(double)),this,SLOT(spinChanged(double)));
    connect(m_spinH,SIGNAL(valueChanged(double)),this,SLOT(spinChanged(double)));
    connect(m_angle,SIGNAL(valueChanged(double)),this,SLOT(spinChanged(double)));




}
void OptionDock::setupItemTree()
{
    QString spritePath ="";
    m_itemTreeWidget->setIconSize(QSize(32,32));
    m_itemTreeWidget->setRootIsDecorated(false);

    QTreeWidgetItem * normalItem =new QTreeWidgetItem(m_itemTreeWidget);
    normalItem->setIcon(0,KIcon(QPixmap(spritePath+"data/sprites/normal_block.png")));
    normalItem->setText(0,spritePath+"data/sprites/normal_block.png");


    QTreeWidgetItem * solidItem =new QTreeWidgetItem(m_itemTreeWidget);
    solidItem ->setIcon(0,KIcon(QPixmap(spritePath+"data/sprites/solid_block.png")));
    solidItem ->setText(0,spritePath+"data/sprites/solid_block.png");


    QTreeWidgetItem * chimicItem =new QTreeWidgetItem(m_itemTreeWidget);
    chimicItem ->setIcon(0,KIcon(QPixmap(spritePath+"data/sprites/chimic_block.png")));
    chimicItem ->setText(0,spritePath+"data/sprites/chimic_block.png");


    QTreeWidgetItem * explodeItem =new QTreeWidgetItem(m_itemTreeWidget);
    explodeItem ->setIcon(0,KIcon(QPixmap(spritePath+"data/sprites/explode_block.png")));
    explodeItem ->setText(0,spritePath+"data/sprites/explode_block.png");


}
void OptionDock::setupCombo()
{

    QDir spriteDir ("data/sprites/");

    foreach (QString file,spriteDir.entryList())
    {

        if ( file.contains("wallpaper.png"))
            m_bkgroundCombo->addItem(file);

        if ( file.contains("ground.png"))
            m_groundCombo->addItem(file);

    }



}
void OptionDock::setCurrentItemPath(QTreeWidgetItem*item,int col)
{
    Q_UNUSED(col);
    m_currentItemPath=item->text(0);
    emit itemPathChanged(m_currentItemPath);
    kDebug()<<"item Changed...";

}
void OptionDock::spinChanged(double value)
{
emit geometryChanged(m_spinW->value(),m_spinH->value());
}
