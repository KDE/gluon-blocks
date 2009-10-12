#ifndef OPTIONDOCK_H
#define OPTIONDOCK_H

#include <QDockWidget>
#include "editorview.h"
class QTableWidget;
class QListWidget;
class QListWidgetItem;
class QDoubleSpinBox;
class QComboBox;
class QToolButton;


class OptionsDock : public QDockWidget
{
    Q_OBJECT
public:
    OptionsDock(EditorView * view, QWidget * parent=0);
~OptionsDock();
    QString wallpaperTexturePath() const;
    QString groundTexturePath() const;
    QString itemTexturePath() const;


protected:
    void setupCombo(); //setup wallpaper,ground and blocktype combo
    void setupPropertyTable();//setup the propertyTable with all widget

    //helpfull function to insert a custom widget inside the table
    void insertPropertyWidget(const QString& name, QWidget * widget);
    //retyrn the widget in the table by his name
    QWidget * propertyWidget(const QString& name);

public Q_SLOTS:
    void setCurrentItemTexture(int index); //activate by m_itemTypeCombo
    void setCurrentItemProperty(double value);//activate by all widgets inside Table.
    void setWalpaperTexture(int index);//actiate by m_bkcombo
    void setGroundTexture(int index);//activta by m_groundcombo
    void removeItem();
    void setSelectedItem(int id);

    void refreshList();//refresh the block list of the editorView

private:
    QTableWidget *m_propertiesTableWidget;
    QListWidget *m_blokListWidget;
    QComboBox *m_bkgroundCombo;
    QComboBox *m_groundCombo;
    QComboBox *m_itemTypeCombo;
    EditorView * m_editorView; //point to the view
    QToolButton * m_delButton;
    enum BlockTypeRoles {TexturePathRole = Qt::UserRole};
};

#endif // OPTIONBLOCK_H
