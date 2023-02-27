#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QtWidgets/QGraphicsScene>
#include <QPainter>
#include <QCursor>
#include <QMenu>
#include <QWidget>

#include "Shape/Shape.h"
#include "Shape/Line.h"
#include "Shape/Rect.h"
#include "Shape/Ellipse.h"
#include "Shape/Text.h"
#include "Shape/SemiCircle.h"
#include "Shape/Pin.h"

class PaintWidget : public QGraphicsScene {
    Q_OBJECT
public:
    enum Code { LINE, RECT, ELLIPSE, DRAGE, TEXT, SEMICIR, PIN };
    explicit PaintWidget(QWidget *parent = 0);
    void saveItems(std::ofstream& fout);

signals:
    void sendMessage(QString);

public slots:
    void setCurrentStatus(PaintWidget::Code s) {
        if (s != currShapeCode)
            currShapeCode = s;
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

private:
    Code currShapeCode;
    Shape* currItem;
    bool perm;
};

#endif // PAINTWIDGET_H
