#include "Line.h"

Line::Line()
{
    initial();
}

Line::Line(const Line& rhs)
{
    initial();
    setLine(rhs.line());
    setRotation(rhs.rotation());
}

void Line::initial()
{
    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::black);
    pen.setCapStyle(Qt::RoundCap);
    setPen(pen);
    code = LINE;
}

void Line::startDraw(QGraphicsSceneMouseEvent *event)
{
    QLineF linef(round(event->scenePos().x()/20)*20 + 10, round(event->scenePos().y()/20)*20 + 10,
                 round(event->scenePos().x()/20)*20 + 10, round(event->scenePos().y()/20)*20 + 10);
    setLine(linef);
}

void Line::drawing(QGraphicsSceneMouseEvent *event)
{
    QPointF end(round(event->scenePos().x()/20)*20 + 10,
                round(event->scenePos().y()/20)*20 + 10);
    QLineF newLine(line().p1(), end);
    setLine(newLine);

    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

void Line::writeFile(std::ofstream &fout)
{
    fout << shapeCode() << "\t" << rotation() << "\r\n";
    fout << line().p1().x() << "\t" << line().p1().y() << "\t"
         << line().p2().x() << "\t" << line().p2().y() << "\r\n";
}

void Line::readFile(std::ifstream &fin)
{
    qreal r, p1x, p1y, p2x, p2y;
    fin >> r >> p1x >> p1y >> p2x >> p2y;
    setLine(QLineF(p1x, p1y, p2x, p2y));
    setRotation(r);
}

void Line::setRectBounding(QRectF rect)
{
    qreal p1x, p1y, p2x, p2y;
    p1x = line().p1().x() > line().p2().x() ? rect.right() : rect.left();
    p1y = line().p1().y() > line().p2().y() ? rect.bottom() : rect.top();
    p2x = line().p1().x() < line().p2().x() ? rect.right() : rect.left();
    p2y = line().p1().y() < line().p2().y() ? rect.bottom() : rect.top();
    qDebug() << p1x << "\t" << p1y << "\t" << "\t" << p2x << "\t" << p2y << "\n";
    setLine(QLineF(p1x, p1y, p2x, p2y));
}

void Line::setcolor(QString color)
{
    QPen newPen = pen();
    newPen.setColor(setColorPen(color));
    setPen(newPen);
}
