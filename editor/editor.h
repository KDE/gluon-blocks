#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMouseEvent>

#include <KXmlGuiWindow>

#include <gluon/kgl/kglview.h>
#include <gluon/kgl/kglphysicsengine.h>
#include <gluon/kgl/kglphysicsitem.h>

class EditorView;
class ItemsDock;
class OptionsDock;

class Editor : public KXmlGuiWindow
{
public:
    Editor(QWidget *parent=0);
    void setupActions();
private:
    EditorView *m_editorView;
    ItemsDock *m_itemsDock;
    OptionsDock *m_optionsDock;
};

#endif // MAINWINDOW_H
