#ifndef CIRCUITWIDGET_H
#define CIRCUITWIDGET_H

#include <QGraphicsScene>
#include <QList>
#include <QTableWidgetItem>

#include "Component.h"

class CircuitWidget : public QGraphicsScene {
    Q_OBJECT
public:
    CircuitWidget(QWidget* parent = 0);
    void setLib(QString path);

    QList<Component*>& getComps() { return compLib; }

signals:
    void sendCompInfo(QStringList vstr);
    void sendMessage(QString);

public slots:
    void addComponent(QString name);
    void changeInfo(QString newInfo, int row);
    void saveComps(std::ofstream& fout);
    void setCircuit(std::ifstream& fin);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

private:
    QString libPath;
    QList<Component*> compLib;
    bool Wiring = false;
    Wire* currwire;
};

#endif // CIRCUITWIDGET_H
