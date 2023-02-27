#include "CircuitWidget.h"

CircuitWidget::CircuitWidget(QWidget* parent)
    : QGraphicsScene(parent)
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

void CircuitWidget::setLib(QString path)
{
    std::string head;
    libPath = path;
    std::ifstream fin(libPath.toStdString());
    fin >> head;
    while(!fin.eof()) {
        Component* currcomp = new Component;
        currcomp->readFile(fin);
        if (!currcomp->getName().isEmpty())
            compLib.push_back(currcomp);
    }
}

void CircuitWidget::addComponent(QString name)
{
    foreach (Component* tmp, compLib) {
        if(tmp->getName() == name) {
            Component* newComp = new Component(*tmp);
            newComp->setSize("Small");
            newComp->setColor("Black");
            newComp->setFlag(QGraphicsItem::ItemIsMovable, true);
            newComp->setFlag(QGraphicsItem::ItemIsSelectable, true);
            addItem(newComp);
        }
    }
}

void CircuitWidget::saveComps(std::ofstream& fout)
{
    fout << "Definition\r\n";
    for (int i = 0; i < items().length(); i++) {
        QGraphicsItem* curritem = items()[i];
        if (curritem->data(0) == "Comp")
            dynamic_cast<Component*>(curritem)->saveComp(fout);
    }

    fout << "EndDefinition\r\n";

    fout << "Circuit\r\n";
    for (int i = 0; i < items().length(); i++) {
        QGraphicsItem* curritem = items()[i];
        if (curritem->data(0) == "Wire")
            dynamic_cast<Wire*>(curritem)->saveConnection(fout);
    }
    fout << "EndCircuit";
}

void CircuitWidget::setCircuit(std::ifstream& fin)
{
    std::string tmp;
    fin >> tmp;
    if (tmp != "Definition") return;

    while (tmp != "EndDefinition") {
        fin >> tmp;
        foreach (Component* comp, compLib) {
            if (comp->getName().toStdString() == tmp) {
                Component* newComp = new Component(*comp);
                newComp->setParameter(fin);
                newComp->setFlag(QGraphicsItem::ItemIsMovable, true);
                newComp->setFlag(QGraphicsItem::ItemIsSelectable, true);
                addItem(newComp);
            }
        }
    }
    fin >> tmp;
    if (tmp != "Circuit") return;
    while (tmp != "EndCircuit") {
        fin >> tmp;
        foreach (QGraphicsItem* item, items()) {
            if (item->data(0) != "Comp") continue;
            Component* comp = dynamic_cast<Component*>(item);
            if (comp->getShortName().toStdString() == tmp) {
                fin >> tmp;
                currwire = new Wire;
                comp->setCurrPin(QString::fromStdString(tmp));
                comp->initialWire(currwire);
                break;
            }
        }

        currwire->setConnection(fin);

        fin >> tmp;
        foreach (QGraphicsItem* item, items()) {
            if (item->data(0) != "Comp") continue;
            Component* comp = dynamic_cast<Component*>(item);
            if (comp->getShortName().toStdString() == tmp) {
                fin >> tmp;
                comp->setCurrPin(QString::fromStdString(tmp));
                comp->finishWire(currwire);
                break;
            }
        }
        addItem(currwire);
        qDebug() << 2;
    }
    qDebug() << 1;
}

void CircuitWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
    if (item == nullptr) return;
    while (item->parentItem() != nullptr)
        item = item->parentItem();

    if (!Wiring && dynamic_cast<Component*>(item)->isAtPin(event->scenePos()) && item->data(0) == "Comp") {
        currwire = new Wire;
        dynamic_cast<Component*>(item)->addConnection(currwire);
        dynamic_cast<Component*>(item)->initialWire(currwire);
        Wiring = true;
        addItem(currwire);
    }

    else if (Wiring && dynamic_cast<Component*>(item)->isAtPin(event->scenePos()) && item->data(0) == "Comp") {
        dynamic_cast<Component*>(item)->addConnection(currwire);
        dynamic_cast<Component*>(item)->finishWire(currwire);
        Wiring = false;
    }
    QStringList data = dynamic_cast<Component*>(item)->getInfo();

    emit sendCompInfo(data);
    QGraphicsScene::mousePressEvent(event);
}

void CircuitWidget::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
//    if (Wiring) {
//        item->setFlag(QGraphicsItem::ItemIsMovable, false);
//        currwire->drawing(event->scenePos());
//    }
    if (item) {
        while (item->parentItem() != NULL)
            item = item->parentItem();

        if (item->data(0) != "Comp")
            return;

        if (dynamic_cast<Component*>(item)->isAtPin(event->scenePos()))
            item->setCursor(Qt::CrossCursor);
        else
            item->setCursor(Qt::SizeAllCursor);
    }
    emit sendMessage(QString(tr("mouse pos: %1, %2")).arg(event->scenePos().x()).arg(event->scenePos().y()));
    QGraphicsScene::mouseMoveEvent(event);
}

void CircuitWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
}

void CircuitWidget::changeInfo(QString newInfo, int row)
{
    Component* currComp = dynamic_cast<Component*>(selectedItems()[0]);

    switch (row) {
    case 0: currComp->setName(newInfo);
    case 1: currComp->setShortName(newInfo);
    case 2: currComp->setSize(newInfo);
    case 3: currComp->setColor(newInfo);
    case 4: currComp->setPos(newInfo.mid(0, newInfo.indexOf(",")).toInt(),
                             newInfo.mid(newInfo.indexOf(",")+1).toInt());
    case 5: currComp->setRotation(newInfo.toInt());
    default: return; break;
    }
}

void CircuitWidget::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
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
        //itm->setTransformOriginPoint(itm->boundingRect().center());
        itm->setRotation(itm->rotation() + 90);
    }
    else if (action == hideAction) {
        emit sendMessage(tr("hide the %1").arg(dynamic_cast<Shape*>(itm)->strshapeCode()));
        itm->hide();
    }
}
