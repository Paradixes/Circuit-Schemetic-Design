#ifndef COMPMAINWINDOW_H
#define COMPMAINWINDOW_H

#include <QtWidgets/QtWidgets>
#include <QtWidgets/QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QImage>
#include <QFileInfo>
#include <fstream>
#include <CircuitDesign/CircuitMainWindow.h>

#include "PaintWidget.h"
//#include "Library.h"

class CompMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	CompMainWindow(QWidget* parent = 0);

signals:
    void changeCurrentStatus(PaintWidget::Code newWidget);

private slots:
	void drawLineActionTriggered();
	void drawRectActionTriggered();
    void drawEllipActionTriggered();
    void dragActionTriggered();
    void editTextActionTriggered();
    void drawSemiActionTriggered();
    void drawPinActionTriggered();
    void showMessageTriggered(QString msg);
    void setLib();
    void savePNG();
    void saveComp();
    void setName();
    void newComp();
    void newCircuit();
    //void readFile();

private:
    void createMenu();
    void createBar();
    void createStatusBar();
    void createCentral();
    void setAction(QAction* &action, QString name, QString filePath, const char* act);

private:
    QMenu* file;
    QLabel* statusMsg;
    QGraphicsView* view;
    QToolBar* bar;
    QActionGroup* group;
    QAction* saveAction;
    QAction* openLibAction;
    QAction* newCompAction;
    QAction* dragAction;
    QAction* drawLineAction;
    QAction* drawRectAction;
    QAction* drawEllipAction;
    QAction* editTextAction;
    QAction* drawSemiAction;
    QAction* drawPinAction;
    QAction* createCircuit;
    PaintWidget* paintWidget;
    QString pngPath;
    QString libPath;
    QString compName;
    QString compShortHand;
};

#endif // !COMPMAINWINDOW_H

