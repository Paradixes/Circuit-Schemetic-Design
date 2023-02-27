#ifndef COMPONENT_H
#define COMPONENT_H

#include "CreateComp/PaintWidget.h"
#include "Wire.h"

#include <fstream>

class Component : public QGraphicsItemGroup {
public:
    explicit Component(const Component& comp);
    explicit Component();
    explicit Component(std::ifstream& fin) { readFile(fin); }
    void readFile(std::ifstream& fin);
    void setName(QString newName);
    void setShortName(QString newShortName);
    void setColor(QString color);
    void setSize(QString size);
    bool isAtPin(QPointF currPos);
    QString getIcon()const { return imgPath; }
    QString getName()const { return name; }
    QString getShortName()const { return shortName; }
    QStringList getInfo();
//    QPointF getPinPoint(QString PinName);
    void setCurrPin(QString PinName);
    void addConnection(Wire*& wire);
    void initialWire(Wire*& wire);
    void finishWire(Wire*& wire);
    void saveComp(std::ofstream& fout);
    void setParameter(std::ifstream& fin);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    //void mousePressEvent(QGraphicsSceneMouseEvent* event);
    //void hoverMoveEvent(QGraphicsSceneHoverEvent* event);

private:
    void getShape(std::ifstream& fin);
    QGraphicsItem* createShape(QGraphicsItem* item);
    qreal getScaleRate();

private:
    QString name;
    QString shortName;
    QString imgPath;
    QRectF boundingrect;
    QString strColor = "Black";
    QString strSize = "Small";
    QMap<QString, QPointF> PinMap;
    //QMap<QString, Wire*> wiremap;
    QPointF currPin;
    QString currPinName;
};

#endif // COMPONENT_H
