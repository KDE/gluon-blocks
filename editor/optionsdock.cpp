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

    setupInfoTable();
    setupItemTree();
    setupCombo();

    connect(m_blokTypesListWidget,SIGNAL(itemActivated(QListWidgetItem *)),this,SLOT(setCurrentItemPath(QListWidgetItem *)));
}

QString OptionsDock::wallPaperTexturePath() const
{
    return QString("data/sprites/") + m_bkgroundCombo->currentText();
}

QString OptionsDock::groundTexturePath() const
{
    return QString("data/sprites/") + m_groundCombo->currentText();
}

QString OptionsDock::itemTexturePath() const
{
    return m_blokTypesListWidget->selectedItems()[0]->data(TexturePathRole).toString();
}

void OptionsDock::setupInfoTable()
{
    m_propertiesTableWidget->setAlternatingRowColors(true);
    m_propertiesTableWidget->setItem(0, 0, new QTableWidgetItem("Width"));
    m_propertiesTableWidget->setItem(1, 0, new QTableWidgetItem("Height"));
    m_propertiesTableWidget->setItem(2, 0, new QTableWidgetItem("Angle"));

    m_spinW = new QDoubleSpinBox;
    m_spinW->setObjectName("width");
    m_propertiesTableWidget->setCellWidget (0, 1, m_spinW);
    m_spinW->setValue(1);

    m_spinH = new QDoubleSpinBox;
    m_spinH->setObjectName("height");
    m_propertiesTableWidget->setCellWidget (1, 1, m_spinH);
    m_spinH->setValue(1);

    m_angle = new QDoubleSpinBox;
    m_angle->setObjectName("angle");
    m_propertiesTableWidget->setCellWidget (2, 1, m_angle);

    connect(m_spinW, SIGNAL(valueChanged(double)), this, SLOT(spinChanged(double)));
    connect(m_spinH, SIGNAL(valueChanged(double)), this, SLOT(spinChanged(double)));
    connect(m_angle, SIGNAL(valueChanged(double)), this, SLOT(spinChanged(double)));
}

void OptionsDock::setupItemTree()
{
    QString spritePath ="";
    m_blokTypesListWidget->setIconSize(QSize(32, 32));

    QListWidgetItem * normalItem = new QListWidgetItem(m_blokTypesListWidget);
    normalItem->setIcon(KIcon(QPixmap(spritePath + "data/sprites/normal_block.png")));
    normalItem->setData(TexturePathRole, QVariant("data/sprites/normal_block.png"));
    normalItem->setText(i18n("Normal Block"));

    QListWidgetItem * solidItem = new QListWidgetItem(m_blokTypesListWidget);
    solidItem->setIcon(KIcon(QPixmap(spritePath + "data/sprites/solid_block.png")));
    solidItem->setData(TexturePathRole, QVariant("data/sprites/solid_block.png"));
    solidItem->setText(i18n("Solid Block"));

    QListWidgetItem * chimicItem = new QListWidgetItem(m_blokTypesListWidget);
    chimicItem->setIcon(KIcon(QPixmap(spritePath + "data/sprites/chimic_block.png")));
    chimicItem->setData(TexturePathRole, QVariant("data/sprites/chimic_block.png"));
    chimicItem->setText(i18n("Chimic Block"));

    QListWidgetItem * explodeItem = new QListWidgetItem(m_blokTypesListWidget);
    explodeItem->setIcon(KIcon(QPixmap(spritePath + "data/sprites/explode_block.png")));
    explodeItem->setData(TexturePathRole, QVariant("data/sprites/explode_block.png"));
    explodeItem->setText(i18n("Explode Block"));

    m_blokTypesListWidget->setCurrentItem(normalItem);
    setCurrentItemPath(normalItem);
}

void OptionsDock::setupCombo()
{
    QDir spriteDir ("data/sprites/");

    foreach (QString file, spriteDir.entryList())
    {
        if (file.contains("wallpaper.png"))
            m_bkgroundCombo->addItem(file);
        if (file.contains("ground.png"))
            m_groundCombo->addItem(file);
    }
}

void OptionsDock::setCurrentItemPath(QListWidgetItem *item)
{
    emit itemPathChanged(item->data(TexturePathRole).toString());
}

void OptionsDock::spinChanged(double value)
{
    Q_UNUSED(value);
    emit geometryChanged(m_spinW->value(), m_spinH->value());
}

void OptionsDock::updateProperties(const QMap<QString, QString> &properties)
{
    for (int row = 0; row < m_propertiesTableWidget->rowCount(); ++row)
    {
	QString property = m_propertiesTableWidget->item(row, 0)->text();
	if (properties.contains(property))
	{
	    if (property == "Width" || property == "Height" || property == "Angle")
	    {
		QDoubleSpinBox *spinBox = qobject_cast<QDoubleSpinBox *>(m_propertiesTableWidget->cellWidget(row, 1));
		if (spinBox)
		    spinBox->setValue(properties[property].toDouble());
	    }
	    else
		m_propertiesTableWidget->item(row, 1)->setText(properties[property]);
	}
    }
}
