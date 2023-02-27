#include "SemiCircle.h"

SemiCircle::SemiCircle()
{
    initial();
}

SemiCircle::SemiCircle(const SemiCircle& rhs)
{
    initial();
    start = rhs.start;
    size = rhs.size;

    setShape();
    setRotation(rhs.rotation());
}

void SemiCircle::initial()
{
    setPen(QPen(Qt::black, 3));

    code = ARC;
}

void SemiCircle::startDraw(QGraphicsSceneMouseEvent *event)
{
    start = QPointF(int(event->scenePos().x())/20*20 + 10,
                    int(event->scenePos().y())/20*20 + 10);
}

void SemiCircle::drawing(QGraphicsSceneMouseEvent *event)
{
    size = QSizeF(int(event->scenePos().x())/20*20 + 10 - start.x(),
                  2*(int(event->scenePos().y())/20*20 + 10 - start.y()));

    setShape();

    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

void SemiCircle::writeFile(std::ofstream &fout)
{
    fout << shapeCode() << "\t" << rotation() << "\r\n";
    fout << start.x() << "\t" << start.y() << "\t"
         << size.width() << "\t" << size.height() << "\r\n";

}

void SemiCircle::readFile(std::ifstream &fin)
{
    qreal r, sx, sy, sw, sh;
    fin >> r >> sx >> sy >> sw >> sh;

    start = QPointF(sx, sy);
    size = QSizeF(sw, sh);

    setShape();
    setRotation(r);
}

void SemiCircle::setRectBounding(QRectF rect)
{
    start.setX(rect.left()); start.setY(rect.top());

    setShape();
}

void SemiCircle::setcolor(QString color)
{
    QPen newPen = pen();
    newPen.setColor(setColorPen(color));
    setPen(newPen);
}

void SemiCircle::setShape()
{
    QPainterPath path;
    path.moveTo(start.x(), start.y() + size.height()/2);
    path.arcTo(QRectF(start, size), 180, -180);
    setPath(path);
}
