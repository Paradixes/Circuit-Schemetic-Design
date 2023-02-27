#ifndef LIBRARY_H
#define LIBRARY_H

#include <QList>
#include <QGraphicsItem>
#include <QFileDialog>
#include <QImage>
#include <QMainWindow>
#include <QMessageBox>

#include "PaintWidget.h"

class Library : public QMainWindow {
    Q_OBJECT
public:
    Library(PaintWidget*&);

public slots:
    void saveImage();
    void createLib();

protected:
    PaintWidget* paintWidget;
    //QList<QGraphicsItem*> items;

private:
    QString libName;
    QString pngName;
};

#endif // LIBRARY_H
