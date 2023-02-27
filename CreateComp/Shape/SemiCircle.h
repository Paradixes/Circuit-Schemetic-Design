#ifndef SEMICIRCLE_H
#define SEMICIRCLE_H

#include "Shape.h"
#include <QPainter>

class SemiCircle : public Shape, public QGraphicsPathItem {
public:
    SemiCircle();
    SemiCircle(const SemiCircle& rhs);

    void startDraw(QGraphicsSceneMouseEvent *event) override;
    void drawing(QGraphicsSceneMouseEvent *event) override;
    void writeFile(std::ofstream &fout) override;
    void readFile(std::ifstream &fin) override;
    void setRectBounding(QRectF rect) override;
    void setcolor(QString color) override;

protected:
    void initial() override;

private:
    void setShape();

private:
    QPointF start;
    QSizeF  size;
};

#endif // SEMICIRCLE_H
