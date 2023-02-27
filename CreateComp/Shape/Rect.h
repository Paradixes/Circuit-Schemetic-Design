#ifndef RECT_H
#define RECT_H

#include "Shape.h"

class Rect : public Shape, public QGraphicsRectItem {
public:
    Rect();
    Rect(const Rect& rhs);

    void startDraw(QGraphicsSceneMouseEvent *event) override;
    void drawing(QGraphicsSceneMouseEvent *event) override;
    void writeFile(std::ofstream &fout) override;
    void readFile(std::ifstream &fin) override;
    void setRectBounding(QRectF rect) override;
    void setcolor(QString color) override;

protected:
    void initial() override;
};

#endif // !RECT_H
