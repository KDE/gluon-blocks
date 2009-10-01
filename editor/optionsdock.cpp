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
#include <QLabel>
#include <QDir>

#include <KIcon>
#include <KDebug>
#include <KLocale>
#include <KStandardDirs>

OptionsDock::OptionsDock(QWidget * parent) : QDockWidget(parent)
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

    m_propertiesTableWidget = new QTableWidget(3, 2);
    m_propertiesTableWidget->setHorizontalHeaderLabels(QStringList() << i18n("Property") << i18n("Value"));
    m_propertiesTableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    m_propertiesTableWidget->horizontalHeader()->setResizeMode(0, QHeaderView::Interactive);
    m_propertiesTableWidget->verticalHeader()->hide();
    m_propertiesTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    QGroupBox *propertyEditorGroupBox = new QGroupBox(i18n("Block Properties Editor"));
    QGridLayout *propertyEditorLayout = new QGridLayout;
    propertyEditorLayout->addWidget(m_propertiesTableWidget);
    propertyEditorGroupBox->setLayout(propertyEditorLayout);
    
    m_blokTypesListWidget = new QListWidget;
    m_blokTypesListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    QGroupBox *blockTypesGroupBox = new QGroupBox(i18n("Block Types"));
    QGridLayout *blockTypesLayout = new QGridLayout;
    blockTypesLayout->addWidget(m_blokTypesListWidget);
    blockTypesGroupBox->setLayout(blockTypesLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(globalPropertiesGroupBox);
    mainLayout->addWidget(propertyEditorGroupBox);
    mainLayout->addWidget(blockTypesGroupBox);

    QWidget *mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);

    setWidget(mainWidget);

    setupItemTree();
    setupCombo();

    connect(m_blokTypesListWidget, SIGNAL(itemActivated(QListWidgetItem *)), this, SLOT(setCurrentItemTexture(QListWidgetItem *)));
    connect(m_bkgroundCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(setWalpaperTexture(int)));
    connect(m_groundCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(setGroundTexture(int)));
}

QString OptionsDock::wallpaperTexturePath() const
{
    return m_bkgroundCombo->itemData(m_bkgroundCombo->currentIndex(), Qt::UserRole).toString();
}

QString OptionsDock::groundTexturePath() const
{
    return m_groundCombo->itemData(m_groundCombo->currentIndex(), Qt::UserRole).toString();
}

QString OptionsDock::itemTexturePath() const
{
    return m_blokTypesListWidget->selectedItems()[0]->data(TexturePathRole).toString();
}

void OptionsDock::initPropertyEditor(const QMap<QString, QWidget *> &propertiesMap)
{
    m_propertiesTableWidget->setAlternatingRowColors(true);
    int row = -1;
    foreach (QString key, propertiesMap.keys())
    {
        m_propertiesTableWidget->setItem(++row, 0, new QTableWidgetItem(key));
        m_propertiesTableWidget->setCellWidget (row, 1, propertiesMap[key]);
    }
    m_propertiesTableWidget->setRowCount(propertiesMap.keys().count());
}

void OptionsDock::setupItemTree()
{
    QString spritePath = KGlobal::dirs()->findResourceDir("appdata", "data/sprites/") + "data/sprites/";
    m_blokTypesListWidget->setIconSize(QSize(32, 32));

    QListWidgetItem * normalItem = new QListWidgetItem(m_blokTypesListWidget);
    normalItem->setIcon(KIcon(QPixmap(spritePath + "normal_block.png")));
    normalItem->setData(TexturePathRole, QVariant(spritePath + "normal_block.png"));
    normalItem->setText(i18n("Normal Block"));

    QListWidgetItem * solidItem = new QListWidgetItem(m_blokTypesListWidget);
    solidItem->setIcon(KIcon(QPixmap(spritePath + "solid_block.png")));
    solidItem->setData(TexturePathRole, QVariant(spritePath + "solid_block.png"));
    solidItem->setText(i18n("Solid Block"));

    QListWidgetItem * chimicItem = new QListWidgetItem(m_blokTypesListWidget);
    chimicItem->setIcon(KIcon(QPixmap(spritePath + "chimic_block.png")));
    chimicItem->setData(TexturePathRole, QVariant(spritePath + "chimic_block.png"));
    chimicItem->setText(i18n("Chimic Block"));

    QListWidgetItem * explodeItem = new QListWidgetItem(m_blokTypesListWidget);
    explodeItem->setIcon(KIcon(QPixmap(spritePath + "explode_block.png")));
    explodeItem->setData(TexturePathRole, QVariant(spritePath + "explode_block.png"));
    explodeItem->setText(i18n("Explode Block"));

    m_blokTypesListWidget->setCurrentItem(normalItem);
    setCurrentItemTexture(normalItem);
}

void OptionsDock::setupCombo()
{
    QDir spriteDir (KGlobal::dirs()->findResourceDir("appdata", "data/sprites/") + "data/sprites/");

    foreach (QString file, spriteDir.entryList())
    {
        if (file.contains("wallpaper.png"))
            m_bkgroundCombo->addItem(file, QVariant(KGlobal::dirs()->findResourceDir("appdata", "data/sprites/") + "data/sprites/" + file));
        if (file.contains("ground.png"))
            m_groundCombo->addItem(file, QVariant(KGlobal::dirs()->findResourceDir("appdata", "data/sprites/") + "data/sprites/" + file));
    }
}

void OptionsDock::setCurrentItemTexture(QListWidgetItem *item)
{
    emit itemTextureChanged(item->data(TexturePathRole).toString());
}

void OptionsDock::setWalpaperTexture(int index)
{
    emit wallpaperTextureChanged(m_bkgroundCombo->itemData(index, Qt::UserRole).toString());
}

void OptionsDock::setGroundTexture(int index)
{
    emit groundTextureChanged(m_groundCombo->itemData(index, Qt::UserRole).toString());
}

void OptionsDock::spinChanged(double value)
{
    Q_UNUSED(value);
    emit geometryChanged(m_spinW->value(), m_spinH->value());
}

void OptionsDock::updateProperties(const QMap<QString, QWidget *> &properties)
{
    for (int row = 0; row < m_propertiesTableWidget->rowCount(); ++row)
    {
	QString property = m_propertiesTableWidget->item(row, 0)->text();
	if (properties.contains(property))
	    m_propertiesTableWidget->setCellWidget(row, 1, properties[property]);
    }
}
