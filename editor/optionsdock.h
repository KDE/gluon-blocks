#ifndef OPTIONDOCK_H
#define OPTIONDOCK_H

#include <QDockWidget>

class QTableWidget;
class QListWidget;
class QListWidgetItem;
class QDoubleSpinBox;
class QComboBox;

class OptionsDock : public QDockWidget
{
Q_OBJECT
public:
    OptionsDock(QWidget * parent=0);
    QString wallpaperTexturePath() const;
    QString groundTexturePath() const;
    QString itemTexturePath() const;
    void initPropertyEditor(const QMap<QString, QWidget *> &propertiesMap);
signals:
    void itemTextureChanged(QString texturePath);
    void wallpaperTextureChanged(QString texturePath);
    void groundTextureChanged(QString texturePath);
    void geometryChanged(double w, double h);
protected:
    void setupItemTree();
    void setupCombo();
protected slots:
    void setCurrentItemTexture(QListWidgetItem *item);
    void setWalpaperTexture(int index);
    void setGroundTexture(int index);
    void spinChanged(double value);
    void updateProperties(const QMap<QString, QWidget *> &properties);
private:
    QTableWidget *m_propertiesTableWidget;
    QListWidget *m_blokTypesListWidget;
    QComboBox *m_bkgroundCombo;
    QComboBox *m_groundCombo;
    QString m_currentItemPath;
    QDoubleSpinBox *m_spinW;
    QDoubleSpinBox *m_spinH;
    QDoubleSpinBox *m_angle;
    
    enum BlockTypeRoles {TexturePathRole = Qt::UserRole};
};

#endif // OPTIONBLOCK_H
