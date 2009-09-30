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
    QString wallPaperTexturePath() const;
    QString groundTexturePath() const;
    QString itemTexturePath() const;
signals:
    void itemPathChanged(QString texturePath);
    void geometryChanged(double w, double h);
protected:
    void setupInfoTable();
    void setupItemTree();
    void setupCombo();
protected slots:
    void setCurrentItemPath(QListWidgetItem *item);
    void spinChanged(double value);
    void updateProperties(const QMap<QString, QString> &properties);
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
