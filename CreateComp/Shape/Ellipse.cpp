#include "Ellipse.h"

Ellipse::Ellipse()
{
    initial();
}

Ellipse::Ellipse(const Ellipse& rhs)
{
    initial();
    setRect(rhs.rect());
    setRotation(rhs.rotation());
}

void Ellipse::initial()
{
    setPen(QPen(Qt::black, 3));
    setBrush(Qt::white);
    code = ELLIPSE;
    qDebug() << brush();
}

void Ellipse::startDraw(QGraphicsSceneMouseEvent *event)
{
    setRect(QRectF(event->scenePos(), QSizeF(0, 0)));
}

void Ellipse::drawing(QGraphicsSceneMouseEvent *event)
{
    QRectF newRect(QPointF(rect().topLeft()),
                   QPointF(event->scenePos().x(),
                           event->scenePos().y()));

    setRect(newRect);

    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

void Ellipse::writeFile(std::ofstream &fout)
{
    fout << shapeCode() << "\t" << rotation() << "\r\n";
    fout << rect().top() << "\t" << rect().left() << "\t"
         << rect().bottom() << "\t" << rect().right() << "\r\n";
}

void Ellipse::readFile(std::ifstream &fin)
{
    qreal r, top, left, bottom, right;
    fin >> r;
    fin >> top >> left >> bottom >> right;
    setRect(QRectF(QPointF(left, top), QPointF(right, bottom)));
    setRotation(r);
}

void Ellipse::setRectBounding(QRectF rect)
{
    setRect(rect);
}

void Ellipse::setcolor(QString color)
{
    QPen newPen = pen();
    newPen.setColor(setColorPen(color));
    setPen(newPen);
}
