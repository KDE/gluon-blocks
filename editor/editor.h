#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMouseEvent>

#include <KXmlGuiWindow>

#include <gluon/kgl/kglview.h>
#include <gluon/kgl/kglphysicsitem.h>
#include <gluon/kgl/kglphysicsengine.h>

class EditorView;
class OptionsDock;

class Editor : public KXmlGuiWindow
{
Q_OBJECT
public:
    Editor(QWidget *parent=0);
    void setupActions();
private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void saveFileAs(const QString &outputFileName);
private:
    EditorView *m_editorView;
    OptionsDock *m_optionsDock;
    QString m_currentFile;
};

#endif // MAINWINDOW_H
