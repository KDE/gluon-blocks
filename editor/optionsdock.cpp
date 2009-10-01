#include "optionsdock.h"

#include <QTableWidget>
#include <QHeaderView>
#include <QListWidget>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTreeWidgetItem>
#include <QLabel>
#include <QDir>
#include <QToolButton>
#include <KIcon>
#include <KDebug>
#include <KLocale>
#include <KStandardDirs>
#include <QMessageBox>
#include "blockitem.h"

OptionsDock::OptionsDock(EditorView * view,QWidget * parent)
    : QDockWidget(parent),
    m_editorView(view)
{
    setObjectName("option");
    
    QLabel *bkgroundLabel = new QLabel(i18n("Level background: "));
    m_bkgroundCombo = new QComboBox;
    QHBoxLayout *bkgroundLayout = new QHBoxLayout;
    bkgroundLayout->addWidget(bkgroundLabel);
    bkgroundLayout->addWidget(m_bkgroundCombo);
    
    QLabel *groundLabel = new QLabel(i18n("Level ground: "));
    m_groundCombo = new QComboBox;
    QHBoxLayout *groundLayout = new QHBoxLayout;
    groundLayout->addWidget(groundLabel);
    groundLayout->addWidget(m_groundCombo);
    
    QGroupBox *globalPropertiesGroupBox = new QGroupBox(i18n("Global Properties"));
    QVBoxLayout *propertiesLayout = new QVBoxLayout;
    propertiesLayout->addLayout(bkgroundLayout);
    propertiesLayout->addLayout(groundLayout);
    globalPropertiesGroupBox->setLayout(propertiesLayout);
    
    m_propertiesTableWidget = new QTableWidget(1, 2);
    m_propertiesTableWidget->setHorizontalHeaderLabels(QStringList() << i18n("Property") << i18n("Value"));
    m_propertiesTableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    m_propertiesTableWidget->horizontalHeader()->setResizeMode(0, QHeaderView::Interactive);
    m_propertiesTableWidget->verticalHeader()->hide();
    m_propertiesTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    QGroupBox *propertyEditorGroupBox = new QGroupBox(i18n("Block Properties Editor"));
    QGridLayout *propertyEditorLayout = new QGridLayout;
    propertyEditorLayout->addWidget(m_propertiesTableWidget);
    propertyEditorGroupBox->setLayout(propertyEditorLayout);
    
    m_itemTypeCombo = new QComboBox;
    m_blokListWidget = new QListWidget;
    m_delButton = new QToolButton;
    m_delButton->setIcon(KIcon("list-remove.png"));
    m_blokListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    QGroupBox *blockTypesGroupBox = new QGroupBox(i18n("Block Types"));
    QGridLayout *blockTypesLayout = new QGridLayout;
    QHBoxLayout * buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(m_itemTypeCombo);
    buttonLayout->addWidget(m_delButton);
    QWidget * buttonWidget = new QWidget;
    buttonWidget->setLayout(buttonLayout);

    blockTypesLayout->addWidget(buttonWidget);
    blockTypesLayout->addWidget(m_blokListWidget);

    blockTypesGroupBox->setLayout(blockTypesLayout);
    
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(globalPropertiesGroupBox);
    mainLayout->addWidget(propertyEditorGroupBox);
    mainLayout->addWidget(blockTypesGroupBox);
    
    QWidget *mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);
    
    setWidget(mainWidget);
    m_blokListWidget->setEnabled(false);
    setupCombo();
    setupPropertyTable();
    setCurrentItemTexture(m_itemTypeCombo->currentIndex());

    connect(m_bkgroundCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(setWalpaperTexture(int)));
    connect(m_groundCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(setGroundTexture(int)));
    connect(m_itemTypeCombo,SIGNAL(currentIndexChanged(int)),this,SLOT(setCurrentItemTexture(int)));
    connect(m_editorView,SIGNAL(itemAdded()),this,SLOT(refreshList()));
    connect(m_delButton,SIGNAL(clicked()),this,SLOT(removeItem()));
    connect(m_editorView,SIGNAL(itemSelected(int)),this,SLOT(setSelectedItem(int)));



    
}
OptionsDock::~OptionsDock()
{
    delete m_propertiesTableWidget;
    delete m_blokListWidget;
    delete m_bkgroundCombo;
    delete m_groundCombo;
    delete m_itemTypeCombo;
    delete m_delButton;
}
QString OptionsDock::wallpaperTexturePath() const{
    return m_bkgroundCombo->itemData(m_bkgroundCombo->currentIndex(), Qt::UserRole).toString();
}

QString OptionsDock::groundTexturePath() const{
    return m_groundCombo->itemData(m_groundCombo->currentIndex(), Qt::UserRole).toString();
}

QString OptionsDock::itemTexturePath() const{
    return m_itemTypeCombo->itemData(m_itemTypeCombo->currentIndex(), Qt::UserRole).toString();
}

void OptionsDock::setupCombo()
{
    //-------First setup wallpaper and ground combo
    QDir spriteDir (KGlobal::dirs()->findResourceDir("appdata", "data/sprites/") + "data/sprites/");
    
    foreach (QString file, spriteDir.entryList())
    {
        if (file.contains("wallpaper.png"))
            m_bkgroundCombo->addItem(file, QVariant(KGlobal::dirs()->findResourceDir("appdata", "data/sprites/") + "data/sprites/" + file));
        if (file.contains("ground.png"))
            m_groundCombo->addItem(file, QVariant(KGlobal::dirs()->findResourceDir("appdata", "data/sprites/") + "data/sprites/" + file));
    }
    //--------second setup itemTypeCombo
    QString spritePath = KGlobal::dirs()->findResourceDir("appdata", "data/sprites/") + "data/sprites/";
    
    m_itemTypeCombo->addItem(KIcon(QPixmap(spritePath + "normal_block.png")),"Normal",QVariant(spritePath + "normal_block.png"));
    m_itemTypeCombo->addItem(KIcon(QPixmap(spritePath + "solid_block.png")),"solid",QVariant(spritePath + "solid_block.png"));
    m_itemTypeCombo->addItem(KIcon(QPixmap(spritePath + "chimic_block.png")),"chimic",QVariant(spritePath + "chimic_block.png"));
    m_itemTypeCombo->addItem(KIcon(QPixmap(spritePath + "explode_block.png")),"explode",QVariant(spritePath + "explode_block.png"));
}
void OptionsDock::setupPropertyTable()
{
    QDoubleSpinBox * spinW = new QDoubleSpinBox;
    QDoubleSpinBox * spinH = new QDoubleSpinBox;
    spinW->setMinimum(1);
    spinH->setMinimum(1);
    insertPropertyWidget("width",spinH);
    insertPropertyWidget("height",spinW);
    insertPropertyWidget("static",new QSpinBox);

    connect(spinH,SIGNAL(valueChanged(double)),this,SLOT(setCurrentItemProperty(double)));
    connect(spinW,SIGNAL(valueChanged(double)),this,SLOT(setCurrentItemProperty(double)));
}

void OptionsDock::setCurrentItemTexture(int index)
{ 
    m_editorView->setItemTexture(m_itemTypeCombo->itemData(index,Qt::UserRole).toString());
    refreshList();
}

void OptionsDock::setWalpaperTexture(int index)
{
    m_editorView->setWallpaperTexture(m_bkgroundCombo->itemData(index,Qt::UserRole).toString());
}

void OptionsDock::setGroundTexture(int index)
{
    m_editorView->setGroundTexture(m_groundCombo->itemData(index,Qt::UserRole).toString());
}

void OptionsDock::refreshList()
{
    m_blokListWidget->clear();
    int id=0;
    foreach ( BlockItem* item, m_editorView->blockList())
    {
        QListWidgetItem * item = new QListWidgetItem;
        item->setText("item"+QString::number(id));
        m_blokListWidget->addItem(item);
        ++id;
    }
}
void OptionsDock::insertPropertyWidget(const QString& name, QWidget * widget)
{

    int lastRow = m_propertiesTableWidget->rowCount()-1 ;
    m_propertiesTableWidget->setItem(lastRow,0,new QTableWidgetItem(name));
    m_propertiesTableWidget->setCellWidget(lastRow,1,widget);
    m_propertiesTableWidget->insertRow(lastRow+1);
}
QWidget * OptionsDock::propertyWidget(const QString& name)
{
    for ( int row = 0; row<m_propertiesTableWidget->rowCount(); ++row)
    {
        if ( m_propertiesTableWidget->item(row,0)->text() == name)
            return m_propertiesTableWidget->cellWidget(row,1);

    }
    return 0;
}
void OptionsDock::setCurrentItemProperty(double value)
{

    Q_UNUSED(value)
            float w = qobject_cast<QDoubleSpinBox*>(propertyWidget("width"))->value();
    float h = qobject_cast<QDoubleSpinBox*>(propertyWidget("height"))->value();

    m_editorView->setItemSize(QSizeF(w,h));
}
void OptionsDock::removeItem()
{

    int index=m_blokListWidget->currentRow();
    if ( index!=-1)
    {
        m_editorView->removeBlock(m_editorView->blockList().at(index));
        refreshList();
    }
}
void OptionsDock::setSelectedItem(int id)
{
    m_blokListWidget->setCurrentRow(id);
}
