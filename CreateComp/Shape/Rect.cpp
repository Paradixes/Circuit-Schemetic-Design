#include "Rect.h"

Rect::Rect()
{
    initial();
}

Rect::Rect(const Rect& rhs)
{
    initial();
    setRect(rhs.rect());
    setRotation(rhs.rotation());
}

void Rect::initial()
{
    setPen(QPen(Qt::black, 3));

    code = RECT;
}

void Rect::startDraw(QGraphicsSceneMouseEvent *event)
{
    setRect(QRectF(QPointF(int(event->scenePos().x())/20*20 + 10,
                           int(event->scenePos().y())/20*20 + 10),
                   QSizeF(0, 0)));
}

void Rect::drawing(QGraphicsSceneMouseEvent *event)
{
    QRectF newRect(rect().topLeft(),
                   QSizeF(int(event->scenePos().x())/20*20 + 10 - rect().topLeft().x(),
                          int(event->scenePos().y())/20*20 + 10 - rect().topLeft().y()));
    setRect(newRect);

    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

void Rect::writeFile(std::ofstream &fout)
{
    fout << shapeCode() << "\t" << rotation() << "\r\n";
    fout << rect().top() << "\t" << rect().left() << "\t"
         << rect().bottom() << "\t" << rect().right() << "\r\n";
}

void Rect::readFile(std::ifstream &fin)
{
    qreal r, top, left, bottom, right;
    fin >> r;
    fin >> top >> left >> bottom >> right;
    setRect(QRectF(QPointF(left, top), QPointF(right, bottom)));
    setRotation(r);
}

void Rect::setRectBounding(QRectF rect)
{
    setRect(rect);
}

void Rect::setcolor(QString color)
{
    QPen newPen = pen();
    newPen.setColor(setColorPen(color));
    setPen(newPen);
}
