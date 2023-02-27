#ifndef SHAPE_H
#define SHAPE_H

#include <QtWidgets/QGraphicsSceneEvent>
#include <QtWidgets/QGraphicsItem>
#include <QPen>
#include <fstream>
#include <QDebug>

class Shape {
public:
    enum Code { ELLIPSE, LINE, PIN, RECT, ARC, TEXT };
    Shape();

    virtual void startDraw(QGraphicsSceneMouseEvent* event) = 0;
    virtual void drawing(QGraphicsSceneMouseEvent* event) = 0;
    virtual void writeFile(std::ofstream &fout) = 0;
    virtual void readFile(std::ifstream &fin) = 0;
    virtual void setRectBounding(QRectF rect) = 0;
    virtual void setcolor(QString color) = 0;
    Shape::Code shapeCode()const { return code; }
    QString strshapeCode() const;

protected:
    virtual void initial() = 0;
    Qt::GlobalColor setColorPen(QString color);
    Code code;
};

#endif // !SHAPE_H

