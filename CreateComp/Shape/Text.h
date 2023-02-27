#ifndef TEXT_H
#define TEXT_H

#include "Shape.h"

#include <QFont>

class Text : public Shape, public QGraphicsTextItem {
public:
    Text();
    Text(const Text& rhs);

    void startDraw(QGraphicsSceneMouseEvent *event) override;
    void drawing(QGraphicsSceneMouseEvent *event) override;
    void writeFile(std::ofstream &fout) override;
    void readFile(std::ifstream &fin) override;
    void setRectBounding(QRectF rect) override;
    void setcolor(QString color) override;
protected:
    void initial() override;
};

#endif // TEXT_H
