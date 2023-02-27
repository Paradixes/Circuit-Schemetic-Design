#include "Shape.h"

Shape::Shape()
{
}

QString Shape::strshapeCode() const
{
    switch(code) {
        case(ELLIPSE):    return "Ellipse"; break;
        case(LINE):       return "Line"; break;
        case(PIN):        return "Pin"; break;
        case(RECT):       return "Rect";break;
        case(ARC):        return "Arc";break;
        case(TEXT):       return "Text";break;
    }
}

Qt::GlobalColor Shape::setColorPen(QString color)
{
    if (color == "Blue")
        return Qt::blue;
    else if (color == "Red")
        return Qt::red;
    else if (color == "Yellow")
        return Qt::yellow;
    else if (color == "Black")
        return Qt::black;
    else if (color == "Green")
        return Qt::green;
    else
        return Qt::black;
}
