#include "mainwindow.h"
Mainwindow::Mainwindow(QWidget * parent)
    : GluonMainWindow(parent)
{

    m_engine = new BlokEngine();

    setMinimumSize(500,500);
    view()->setEngine(m_engine);
    setMouseTracking(true);

    for (int i = 0; i < 5; ++i) {
        BlokItem * test = new BlokItem;
        test->setPosition(-3, test->position().y());
        test->setBlokType(BlokItem::Standard);
	m_engine->addItem(test);
    }

    for (int i = 0; i < 5; ++i) {
        BlokItem * test = new BlokItem;
        test->setPosition(2, test->position().y());
	test->setBlokType(BlokItem::Standard);
        m_engine->addItem(test);


    }
    //
    BlokItem * roof = new BlokItem;
    roof->setTexture("data/sprites/solid_block.png");
    roof->texture()->scale(QPointF(6, 1));
    roof->createBox(6, 1);
    roof->setBlokType(BlokItem::Solid);
    roof->setPosition(-3, 4);

    m_engine->addItem(roof);

    BlokItem * totem = new BlokItem;
    totem->setTexture("data/sprites/totem1.png");
    totem->createBox(1.5, 1.5);
    totem->setPosition(-0.75, 6);
    totem->setBlokType(BlokItem::Totem);
    m_engine->addItem(totem);


    view()->start();


}

void Mainwindow::mousePressEvent(QMouseEvent * event)
{

    kDebug() << view()->mapToGL(event->pos());

    QPointF pos = view()->mapToGL(event->pos());

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
