#ifndef WIRE_H
#define WIRE_H

#include <QGraphicsItem>
#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include <fstream>

class Wire : public QGraphicsPathItem {
public:
    enum method{ HORIZONF, VERTICALF, HORIZONC, VERTICALC};
    Wire();
    void horizonFirstConnect(QPointF p1, QPointF p2);
    void verticalFirstConnect(QPointF p1, QPointF p2);
    void horizonCenterConnect(QPointF p1, QPointF p2);
    void verticalCenterConnect(QPointF p1, QPointF p2);
    void setConnectComp(QString comp, QString pin);
    void startDraw(QPointF point, method m);
    void setMethod(method m);
    void drawing(QPointF point);
    void saveConnection(std::ofstream& fout);
    void setConnection(std::ifstream& fin);

private:
    void initial();
    QPointF start;
    QPointF end;
    method code;
    QMap<QString, QString> CompPinMap;
};

#endif // WIRE_H
