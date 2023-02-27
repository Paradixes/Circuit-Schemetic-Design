#ifndef PIN_H
#define PIN_H

#include "Shape.h"

#include <QPainter>
#include "Text.h"

class Pin : public Shape, public QGraphicsPathItem {
public:
    Pin(Text*);
    Pin();
    Pin(const Pin& rhs);

    void startDraw(QGraphicsSceneMouseEvent *event) override;
    void drawing(QGraphicsSceneMouseEvent *event) override;
    void writeFile(std::ofstream &fout) override;
    void readFile(std::ifstream &fin) override;
    void setRectBounding(QRectF rect) override;
    void setcolor(QString color) override;
    QPointF getPoint() { return point; }
    QString getName()const { return name->toPlainText(); }

protected:
    void initial() override;

private:
    void setShape();

private:
    QPointF start;
    QPointF point;
    Text* name;
};

#endif // PIN_H
