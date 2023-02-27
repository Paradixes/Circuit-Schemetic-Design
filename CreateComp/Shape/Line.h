#ifndef LINE_H
#define LINE_H

#include "Shape.h"

class Line : public Shape, public QGraphicsLineItem {
public:
    Line();
    Line(const Line& rhs);

    void startDraw(QGraphicsSceneMouseEvent *event) override;
    void drawing(QGraphicsSceneMouseEvent *event) override;
    void writeFile(std::ofstream &fout) override;
    void readFile(std::ifstream &fin) override;
    void setRectBounding(QRectF rect) override;
    void setcolor(QString color) override;

protected:
    void initial() override;
};

#endif // LINE_H
