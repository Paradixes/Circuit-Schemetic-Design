#ifndef CIRCUITMAINWINDOW_H
#define CIRCUITMAINWINDOW_H

#include <QtDebug>
#include <QtWidgets/QtWidgets>
#include <QtWidgets/QMainWindow>
#include <QString>
#include <QFileInfo>
#include <fstream>
#include <vector>

#include "CreateComp/CompMainWindow.h"
#include "Component.h"
#include "CircuitWidget.h"

class CircuitMainWindow : public QMainWindow {
    Q_OBJECT
public:
    CircuitMainWindow(QWidget* parent = 0);

signals:
    void getComponent(QString name);
    void sendInfo(QString newInfo, int row);
    void sendColorInfo(QString newColor, int row);
    void sendSizeInfo(QString newSize, int row);

public slots:
    void openCircuit();

private slots:
    void createLibDock();
    void setLib();
    void createComp(QListWidgetItem* item);
    void InfoChanged(QTableWidgetItem* item);
    void compColorChanged(QString info);
    void compSizeChanged(QString info);
    void newCircuit();
    void newComp();
    void showCompInfoTriggered(QStringList info);
    void saveCircuit();
    void showMessageTriggered(QString msg);

private:
    void createMenu();
    void createStatusBar();
    void createCentral();
    void createCompInfoDock();
    void setCircuitPath();

private:
    QMenu* file;
    QLabel* statusMsg;
    QGraphicsView* view;
    QAction* saveAction;
    QAction* openLibAction;
    QAction* openCircuitAction;
    QAction* newCircuitAction;
    QAction* newCompAction;
    CircuitWidget* circuitWidget;
    QDockWidget* libDock;
    QDockWidget* infoDock;

    QListWidget* compList;
    QTableWidget* infoList;
    QString lib;
    QString circuitPath;
};

#endif // CIRCUITMAINWINDOW_H
