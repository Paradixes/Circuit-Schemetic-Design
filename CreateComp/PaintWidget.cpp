#include "PaintWidget.h"

PaintWidget::PaintWidget(QWidget* parent)
    : QGraphicsScene(parent), currShapeCode(LINE),
      currItem(NULL), perm(false)
{
    setSceneRect(0,0,300,300);

    QPolygonF myPolygon1;
    myPolygon1 << QPointF(0,10) << QPointF(20,10);
    QPolygonF myPolygon2;
    myPolygon2 << QPointF(10,0) << QPointF(10,20);
    QPixmap pixmap(20, 20);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);

    QVector<qreal> dashes;
    qreal space = 2;
    dashes << 2 << space << 2 <<space;
    QPen pen(Qt::lightGray,1);
    pen.setDashPattern(dashes);
    pen.setWidth(1);

    painter.setPen(pen);
    painter.translate(0, 0);
    painter.drawPolyline(myPolygon1);
    painter.drawPolyline(myPolygon2);
    setBackgroundBrush(pixmap);
}

void PaintWidget::saveItems(std::ofstream &fout)
{
    fout << sceneRect().topLeft().x() << "\t"
         << sceneRect().topLeft().y() << "\t"
         << sceneRect().bottomRight().x() << "\t"
         << sceneRect().bottomRight().y() << "\r\n";

    for (int i = 0; i < items().length(); i++) {
        QGraphicsItem* curritm = items()[i];

        if (dynamic_cast<Shape*>(curritm)->shapeCode() == Shape::TEXT)
            if (dynamic_cast<QGraphicsTextItem*>(curritm)->toPlainText() == NULL)
                continue;

        QPointF topleft(curritm->sceneBoundingRect().topLeft().x() - sceneRect().topLeft().x(),
                        curritm->sceneBoundingRect().topLeft().y() - sceneRect().topLeft().y());
        QPointF bottomright(curritm->sceneBoundingRect().bottomRight().x() - sceneRect().topLeft().x(),
                            curritm->sceneBoundingRect().bottomRight().y() - sceneRect().topLeft().y());

        if (topleft == bottomright)
            continue;

        dynamic_cast<Shape*>(curritm)->setRectBounding(QRectF(topleft, bottomright));
        dynamic_cast<Shape*>(curritm)->writeFile(fout);
    }
    fout << "End" << "\r\n";
    fout.close();
}

void PaintWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch(currShapeCode)
    {
        case LINE:
        {
            Line *line = new Line;
            currItem = line;
            addItem(line);
            break;
        }
        case RECT:
        {
            Rect* rect = new Rect;
            currItem = rect;
            addItem(rect);
            break;
        }
        case ELLIPSE:
        {
            Ellipse* ellip = new Ellipse;
            currItem = ellip;
            addItem(ellip);
            break;
        }
        case DRAGE:
        {
            currItem = nullptr;
            break;
        }
        case TEXT:
        {
            Text* text = new Text;
            currItem = nullptr;
            addItem(text);
            text->startDraw(event);
            break;
        }
        case SEMICIR:
        {
            SemiCircle* semicir = new SemiCircle;
            currItem = semicir;
            addItem(semicir);
            break;
        }
        case PIN:
        {
            Text* text = new Text;
            text->startDraw(event);
            Pin* pin = new Pin(text);
            currItem = pin;
            addItem(text);
            addItem(pin);
            break;
        }
    }
    if(currItem) {
        currItem->startDraw(event);
        perm = false;
    }
    QGraphicsScene::mousePressEvent(event);
}

void PaintWidget::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit sendMessage(QString(tr("mouse pos: %1, %2")).arg(event->scenePos().x()).arg(event->scenePos().y()));

    QGraphicsItem* itm = itemAt(event->scenePos(), QTransform());

    if (currItem && !perm){
        if(itm)
            itm->setFlag(QGraphicsItem::ItemIsMovable, false);
        currItem->drawing(event);
    }
    else if (itm){
        itm->setFlag(QGraphicsItem::ItemIsMovable, true);
        itm->setCursor(Qt::SizeAllCursor);
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void PaintWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    perm = true;
    currItem = nullptr;
    QGraphicsScene::mouseReleaseEvent(event);
}

void PaintWidget::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QGraphicsItem* itm = itemAt(event->scenePos(), QTransform());
    if(!itm) return;
    QMenu menu;
    QAction* deleteAction = menu.addAction(tr("&delete the item"));
    QAction* rotateAction = menu.addAction(tr("&rotate the item"));
    QAction* hideAction = menu.addAction(tr("&hide the item"));

    deleteAction->setShortcut(QKeySequence(tr("Ctrl+D")));
    rotateAction->setShortcut(QKeySequence(tr("Ctrl+R")));
    hideAction->setShortcut(QKeySequence(tr("Ctrl+H")));
    QAction* action = menu.exec(event->screenPos());

    if (action == deleteAction) {
        emit sendMessage(tr("delete the %1").arg(dynamic_cast<Shape*>(itm)->strshapeCode()));
        removeItem(itm);
        delete itm;
    }
    else if (action == rotateAction) {
        emit sendMessage(tr("rotate the %1").arg(dynamic_cast<Shape*>(itm)->strshapeCode()));
        itm->setTransformOriginPoint(itm->boundingRect().center());
        itm->setRotation(itm->rotation() + 90);
    }
    else if (action == hideAction) {
        emit sendMessage(tr("hide the %1").arg(dynamic_cast<Shape*>(itm)->strshapeCode()));
        itm->hide();
    }
}
