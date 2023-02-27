#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "Shape.h"

class Ellipse : public Shape, public QGraphicsEllipseItem {
public:
    Ellipse();
    Ellipse(const Ellipse& rhs);

    void startDraw(QGraphicsSceneMouseEvent *event) override;
    void drawing(QGraphicsSceneMouseEvent *event) override;
    void writeFile(std::ofstream &fout) override;
    void readFile(std::ifstream &fin) override;
    void setRectBounding(QRectF rect) override;
    void setcolor(QString color) override;

protected:
    void initial() override;
};

#endif // !ELLIPSE_H
