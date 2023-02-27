#include "Wire.h"

Wire::Wire()
{
    initial();
}

void Wire::initial()
{
    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::black);
    pen.setCapStyle(Qt::RoundCap);
    setPen(pen);
    setData(0, "Wire");
}

void Wire::horizonFirstConnect(QPointF p1, QPointF p2)
{
    start = p1; end = p2;
    QPainterPath path;
    path.moveTo(p1);
    path.lineTo(p2.x(), p1.y());
    path.lineTo(p2);
    setPath(path);
}

void Wire::verticalFirstConnect(QPointF p1, QPointF p2)
{
    start = p1; end = p2;
    QPainterPath path;
    path.moveTo(p1);
    path.lineTo(p1.x(), p2.y());
    path.lineTo(p2);
    setPath(path);
}

void Wire::horizonCenterConnect(QPointF p1, QPointF p2)
{
    start = p1; end = p2;
    qreal center = (p1.y() + p2.y())/2;
    QPainterPath path;
    path.moveTo(p1);
    path.lineTo(p1.x(), center);
    path.lineTo(p2.x(), center);
    path.lineTo(p2);
    setPath(path);
}

void Wire::verticalCenterConnect(QPointF p1, QPointF p2)
{
    start = p1; end = p2;
    qreal center = (p1.x() + p2.x())/2;
    QPainterPath path;
    path.moveTo(p1);
    path.lineTo(center, p1.y());
    path.lineTo(center, p2.y());
    path.lineTo(p2);
    setPath(path);
}

void Wire::setConnectComp(QString comp, QString pin)
{
    CompPinMap[comp] = pin;
}

void Wire::startDraw(QPointF point, method m)
{
    start = point;
    code = m;
}

void Wire::drawing(QPointF point)
{
    end = point;

    switch(code) {
    case(HORIZONF): horizonFirstConnect(start, end);
    case(HORIZONC): horizonCenterConnect(start, end);
    case(VERTICALF):verticalFirstConnect(start, end);
    case(VERTICALC):verticalCenterConnect(start, end);
    default:        horizonFirstConnect(start, end);
    }
}

void Wire::setMethod(method m)
{
    code = m;
}

void Wire::saveConnection(std::ofstream &fout)
{
    fout << CompPinMap.keys()[0].toStdString() << " ";
    fout << CompPinMap[CompPinMap.keys()[0]].toStdString();
    fout << " =" << code << "= ";
    fout << CompPinMap.keys()[1].toStdString() << " ";
    fout << CompPinMap[CompPinMap.keys()[1]].toStdString() << "\r\n";
}

void Wire::setConnection(std::ifstream &fin)
{
    std::string strMethod;
    fin >> strMethod;
    method m = method(strMethod[1] - '0');
    setMethod(m);
}
