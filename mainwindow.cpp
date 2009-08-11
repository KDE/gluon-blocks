#include "mainwindow.h"

Mainwindow::Mainwindow(QWidget * parent)
        : KXmlGuiWindow(parent)
{

    m_view = new KGLView(parent);
    m_engine = new BlokEngine();
    m_view->setEngine(m_engine);
    setCentralWidget(m_view);

    setMouseTracking(true);




    for (int i = 0; i < 5; ++i) {
        BlokItem * test = new BlokItem;
		test->setPosition(-3, test->position().y());
        m_engine->addItem(test);
    }


    for (int i = 0; i < 5; ++i) {
        BlokItem * test = new BlokItem;
        test->setPosition(2, test->position().y());
        m_engine->addItem(test);


    }


    KGLPhysicsItem * roof = new KGLPhysicsItem;
    roof->setTexture("sprites/text02.png");
    roof->texture()->scale(QPointF(6, 1));
    roof->createBox(6, 1);
    roof->setPosition(-3, 4);

    m_engine->addItem(roof);


    BlokItem * totem = new BlokItem;
    totem->setTexture("sprites/totem1.png");
    totem->createBox(1.5, 1.5);
    totem->setPosition(-0.75, 6);
    totem->setBlokType(BlokItem::Totem);
    m_engine->addItem(totem);







    m_view->setInfoShow(true);
    m_view->setAxisShow(true);

    m_view->start();
    setupGUI();

}

void Mainwindow::mousePressEvent(QMouseEvent * event)
{

    kDebug() << m_view->mapToGL(event->pos());

    QPointF pos = m_view->mapToGL(event->pos());

    KGLPhysicsItem * item = m_engine->itemAt(pos) ;

    if (item == NULL) {
        kDebug() << "NULL";
        return;
    } else {
        kDebug() << "yes";

        BlokItem * blok = dynamic_cast<BlokItem*>(item);
        if (blok == NULL || (blok != NULL && blok->blokType() == BlokItem::Standard))
            m_engine->removeItem(item);
    }






}
