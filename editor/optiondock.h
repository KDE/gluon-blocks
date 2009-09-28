#ifndef OPTIONDOCK_H
#define OPTIONDOCK_H

#include <QDockWidget>
#include <QLineEdit>
#include <QLabel>
#include <QToolButton>
#include <QTableWidget>
#include <QTreeWidget>
#include <QDoubleSpinBox>
#include <QComboBox>

class OptionDock : public QDockWidget
{
    Q_OBJECT
public:
    OptionDock(QWidget * parent=0);
    QString wallPaperTexturePath(){
        return QString("data/sprites/")+m_bkgroundCombo->currentText();
    }
    QString groundTexturePath(){
        return QString("data/sprites/")+m_groundCombo->currentText();
    }



signals:
    void itemPathChanged(QString texturePath);
    void geometryChanged(double w, double h);

protected:
    void setupInfoTable();
    void setupItemTree();
    void setupCombo();


protected slots:
    void setCurrentItemPath(QTreeWidgetItem*item,int col);
    void spinChanged(double value);


private:
    QTableWidget * m_infoTableWidget;
    QTreeWidget *m_itemTreeWidget;
    QComboBox * m_bkgroundCombo;
    QComboBox * m_groundCombo;
    QString m_currentItemPath;
    QDoubleSpinBox * m_spinW;
    QDoubleSpinBox * m_spinH;
    QDoubleSpinBox * m_angle;

};

#endif // OPTIONBLOCK_H
