#include "Component.h"

Component::Component(const Component& comp)
{
    name = comp.name;
    shortName = comp.shortName;
    imgPath = comp.imgPath;
    boundingrect = comp.boundingrect;
    PinMap = comp.PinMap;
    qDebug() << name << shortName << imgPath;
    foreach(QGraphicsItem* curritm, comp.childItems()) {
        addToGroup(createShape(curritm));
    }
    setColor("Black");
    setSize("Small");
    setData(0, "Comp");
    setHandlesChildEvents(true);
}

Component::Component()
{
    setColor("Black");
    setSize("Small");
}

void Component::readFile(std::ifstream& fin)
{
    std::string tmp;
    fin >> tmp;
    if (tmp != "Begin") return;

    fin >> tmp;
    if (tmp == "Name") {
        fin >> tmp;
        name = QString::fromStdString(tmp);
        qDebug() << name;
    }

    fin >> tmp;
    if (tmp == "Short") {
        fin >> tmp;
        shortName = QString::fromStdString(tmp);
        qDebug() << shortName;
    }

    fin >> tmp;
    if (tmp == "ImgPath") {
        fin >> tmp;
        imgPath = QString::fromStdString(tmp);
        qDebug() << imgPath;
    }
    fin >> tmp;
    if (tmp == "Paints") {
        getShape(fin);
    }
}

void Component::setName(QString newName)
{
    name = newName;
}

void Component::setShortName(QString newShortName)
{
    shortName = newShortName;
}

void Component::setColor(QString color)
{
    strColor = color;
    foreach (QGraphicsItem* var, childItems()) {
        dynamic_cast<Shape*>(var)->setcolor(strColor);
    }
}

void Component::setSize(QString size)
{
    strSize = size;
    if (strSize == "Large")
        setScale(1);
    else if (strSize == "Medium")
        setScale(0.7);
    else if (strSize == "Small")
        setScale(0.5);
}

void Component::getShape(std::ifstream &fin)
{
    std::string tmp;
    qreal l, t, r, b;
    fin >> l >> t >> r >> b;
    boundingrect.setCoords(l, t, r, b);

    while (tmp != "End") {
        fin >> tmp;
        Shape* curritm;
        if (tmp == "0") {
            curritm = new Ellipse;
            qDebug() << "0";
        }
        else if (tmp == "1") {
            curritm = new Line;
            qDebug() << "1";
        }
        else if (tmp == "2") {
            curritm = new Pin;
            qDebug() << "2";
        }
        else if (tmp == "3") {
            curritm = new Rect;
            qDebug() << "3";
        }
        else if (tmp == "4") {
            curritm = new SemiCircle;
            qDebug() << "4";
        }
        else if (tmp == "5") {
            curritm = new Text;
            qDebug() << "5";
        }
        else
            break;
        curritm->readFile(fin);
        dynamic_cast<QGraphicsItem*>(curritm)->setFlag(QGraphicsItem::ItemIsSelectable, false);

        if (curritm->shapeCode() == Shape::PIN)
            PinMap.insert(dynamic_cast<Pin*>(curritm)->getName(),dynamic_cast<Pin*>(curritm)->getPoint());

        addToGroup(dynamic_cast<QGraphicsItem*>(curritm));
    }
    qDebug() << PinMap;
}

QGraphicsItem* Component::createShape(QGraphicsItem* item)
{
    Shape* shape = dynamic_cast<Shape*>(item);
    Shape::Code code = shape->shapeCode();
    switch (code) {
    case Shape::ARC: return new SemiCircle((*dynamic_cast<SemiCircle*>(shape))); break;
    case Shape::PIN: return new Pin(*dynamic_cast<Pin*>(shape)); break;
    case Shape::LINE: return new Line(*dynamic_cast<Line*>(shape)); break;
    case Shape::RECT: return new Rect(*dynamic_cast<Rect*>(shape)); break;
    case Shape::TEXT: return new Text(*dynamic_cast<Text*>(shape)); break;
    case Shape::ELLIPSE: return new Ellipse(*dynamic_cast<Ellipse*>(shape)); break;
    default: return nullptr;
    }
}

QStringList Component::getInfo()
{
    QString pos;
    pos += QString::number(scenePos().x());
    pos += ",";
    pos += QString::number(scenePos().y());

    QString r = QString::number(rotation());

    QStringList info;
    //qDebug() << name << shortName << strSize << strColor;
    info << name << shortName << strSize << strColor << pos << r;

    return info;
}

//QPointF Component::getPinPoint(QString PinName)
//{
//    QPointF groupPos = PinMap[PinName];
//    return mapToScene(groupPos);
//}

void Component::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItemGroup::mouseMoveEvent(event);
}

qreal Component::getScaleRate()
{
    if (strSize == "Large")
        return 1;
    else if (strSize == "Medium")
        return 0.7;
    else
        return 0.5;
}

bool Component::isAtPin(QPointF currPos)
{
    QPointF leftTop(currPos.x()-20, currPos.y()-20);
    QPointF rightBottom(currPos.x()+20, currPos.y()+20);
    qreal r = rotation()/180*3.1415926;

    foreach(QPointF point, PinMap) {
        QPointF currpoint((point.x()*cos(r)-point.y()*sin(r))*getScaleRate() + scenePos().x(),
                          (point.x()*sin(r)+point.y()*cos(r))*getScaleRate() + scenePos().y());

        if (currpoint.x() > leftTop.x() && currpoint.x() < rightBottom.x())
            if (currpoint.y() > leftTop.y() && currpoint.y() < rightBottom.y()) {
                currPin = currpoint;
                currPinName = PinMap.key(point);
                return true;
            }
    }
    return false;
}

void Component::setCurrPin(QString PinName)
{
    if (PinMap.find(PinName) == PinMap.end()) return;
    QPointF point = PinMap[PinName];
    qreal r = rotation()/180*3.1415926;
    QPointF currpoint((point.x()*cos(r)-point.y()*sin(r))*getScaleRate() + scenePos().x(),
                      (point.x()*sin(r)+point.y()*cos(r))*getScaleRate() + scenePos().y());
    currPin = currpoint;
    currPinName = PinName;
}

void Component::addConnection(Wire *&wire)
{
    wire->setConnectComp(shortName, currPinName);
    qDebug() << currPinName << shortName;
    //wiremap.insert(currPinName, wire);
}

void Component::initialWire(Wire *&wire)
{
    int r = rotation();
    switch(r) {
    case(0):  wire->startDraw(currPin, Wire::HORIZONF);
    case(90): wire->startDraw(currPin, Wire::VERTICALF);
    case(180):wire->startDraw(currPin, Wire::HORIZONF);
    case(270):wire->startDraw(currPin, Wire::VERTICALF);
    default:  wire->startDraw(currPin, Wire::HORIZONF);
    }
}

void Component::finishWire(Wire *&wire)
{
    wire->setConnectComp(shortName, currPinName);
    wire->drawing(currPin);
}

void Component::saveComp(std::ofstream& fout)
{
    fout << name.toStdString() << "\t" << shortName.toStdString() << "\r\n";
    fout << "Size\t" << strSize.toStdString() << "\r\n";
    fout << "Rotation\t" << rotation() << "\r\n";
    fout << "Color\t" << strColor.toStdString() << "\r\n";
    fout << "Pos\r\n";
    fout << scenePos().x() << "\t" << scenePos().y() << "\r\n";
}

void Component::setParameter(std::ifstream &fin)
{
    std::string tmp;
    fin >> tmp;
    shortName = QString::fromStdString(tmp);
    fin >> tmp;
    if (tmp == "Size") {
        fin >> tmp;
        setSize(QString::fromStdString(tmp));
    }
    fin >> tmp;
    if (tmp == "Rotation") {
        fin >> tmp;
        setRotation(atoi(tmp.c_str()));
    }
    fin >> tmp;
    if (tmp == "Color") {
        fin >> tmp;
        setColor(QString::fromStdString(tmp));
    }
    fin >> tmp;
    if (tmp == "Pos") {
        qreal x, y;
        fin >> tmp;
        x = atoi(tmp.c_str());
        fin >> tmp;
        y = atoi(tmp.c_str());
        setPos(x, y);
    }
}
