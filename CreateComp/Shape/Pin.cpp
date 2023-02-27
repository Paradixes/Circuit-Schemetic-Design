#include "Pin.h"

Pin::Pin()
{
    initial();
}

Pin::Pin(Text* text)
{
    initial();
    name = text;
}

Pin::Pin(const Pin& rhs)
{
    initial();

    start = rhs.start;
    point = rhs.point;

    setShape();
    setRotation(rhs.rotation());
    name = rhs.name;
}

void Pin::initial()
{
    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::darkBlue);
    pen.setCapStyle(Qt::RoundCap);
    setPen(pen);

    name = new Text;
    name->setParentItem(this);
    code = PIN;
}

void Pin::startDraw(QGraphicsSceneMouseEvent *event)
{
    start = QPointF(int(event->scenePos().x())/20*20 + 10, int(event->scenePos().y())/20*20 + 10);
}

void Pin::drawing(QGraphicsSceneMouseEvent *event)
{
    if (fabs(event->scenePos().x() - start.x()) > fabs(event->scenePos().y() - start.y()))
        point = QPointF(int(event->scenePos().x())/20*20 + 10, start.y());
    else if (fabs(event->scenePos().x() - start.x()) < fabs(event->scenePos().y() - start.y()))
        point = QPointF(start.x(), int(event->scenePos().y())/20*20 + 10);
    
    setShape();

    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

void Pin::writeFile(std::ofstream &fout)
{
    fout << shapeCode() << "\t" << rotation() << "\r\n";
    fout << start.x() << "\t" << start.y() << "\t"
         << point.x() << "\t" << point.y() << "\r\n";
}

void Pin::readFile(std::ifstream &fin)
{
    qreal r, sx, sy, px, py;
    fin >> r >> sx >> sy >> px >> py;

    start = QPointF(sx, sy);
    point = QPointF(px, py);

    setShape();
    setRotation(r);

    int c;
    fin >> c;
    if (c == Shape::TEXT) {
        name->readFile(fin);
    }
}

void Pin::setRectBounding(QRectF rect)
{
    qreal sx, sy, px, py;
    sx = start.x() > point.x() ? rect.right() : rect.left();
    sy = start.y() > point.y() ? rect.bottom() : rect.top();
    px = start.x() < point.x() ? rect.right() : rect.left();
    py = start.y() < point.y() ? rect.bottom() : rect.top();
    start.setX(sx); start.setY(sy);
    point.setX(px); point.setY(py);

    setShape();
}

void Pin::setcolor(QString color)
{
    QPen newPen = pen();
    newPen.setColor(setColorPen(color));
    setPen(newPen);
}

void Pin::setShape()
{
    QPainterPath path;
    path.moveTo(start);
    path.lineTo(point);
    setPath(path);
}
