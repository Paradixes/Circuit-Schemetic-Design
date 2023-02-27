#include "CompMainWindow.h"

#include <iostream>

CompMainWindow::CompMainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    createMenu();
    createBar();
    createStatusBar();
    createCentral();
    showMaximized();

    setWindowIcon(QIcon("images/chip.png"));
}

void CompMainWindow::createMenu()
{
    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip("Save a file.");

    openLibAction = new QAction(tr("Open a &Library"), this);
    openLibAction->setShortcut(QKeySequence(tr("Ctrl+L")));
    openLibAction->setStatusTip("Open a library.");

    newCompAction = new QAction(tr("New &Component"), this);
    newCompAction->setShortcut(QKeySequence(tr("Ctrl+N")));
    newCompAction->setStatusTip("Create a component.");

    createCircuit = new QAction(tr("&New Circuit"), this);
    createCircuit->setShortcut(QKeySequence::New);
    createCircuit->setStatusTip("Create a circuit.");

    file = menuBar()->addMenu(tr("&File"));
    file->addAction(saveAction);
    file->addAction(openLibAction);
    file->addAction(newCompAction);
    file->addAction(createCircuit);

    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveComp()));
    connect(openLibAction, SIGNAL(triggered()), this, SLOT(setLib()));
    connect(newCompAction, SIGNAL(triggered()), this, SLOT(newComp()));
    connect(createCircuit, SIGNAL(triggered()), this, SLOT(newCircuit()));
}

void CompMainWindow::createBar()
{
    bar = this->addToolBar("Tools");
    group = new QActionGroup(bar);

    setAction(dragAction, "Drag", "Cursor.png", "drag a shape");
    setAction(drawLineAction, "Line", "line.png", "Draw a line");
    setAction(drawRectAction, "Rectangle", "rectangle.png", "Draw a rectangle");
    setAction(editTextAction, "Text", "text.png", "Edit a text");
    setAction(drawEllipAction, "Ellipse", "ellipse.png", "Draw a ellipse");
    setAction(drawSemiAction, "SemiCircle", "arc.png", "Draw a SemiCircle");
    setAction(drawPinAction, "Pin", "pin.png", "Set a Pin");

    connect(dragAction, SIGNAL(triggered()), this, SLOT(dragActionTriggered()));
    connect(drawLineAction, SIGNAL(triggered()), this, SLOT(drawLineActionTriggered()));
    connect(drawRectAction, SIGNAL(triggered()), this, SLOT(drawRectActionTriggered()));
    connect(editTextAction, SIGNAL(triggered()), this, SLOT(editTextActionTriggered()));
    connect(drawEllipAction,SIGNAL(triggered()), this, SLOT(drawEllipActionTriggered()));
    connect(drawSemiAction,SIGNAL(triggered()), this, SLOT(drawSemiActionTriggered()));
    connect(drawPinAction,SIGNAL(triggered()), this, SLOT(drawPinActionTriggered()));
}

void CompMainWindow::createStatusBar()
{
    statusMsg = new QLabel;
    statusBar()->addWidget(statusMsg);
}

void CompMainWindow::createCentral()
{
    paintWidget = new PaintWidget(this);
    view = new QGraphicsView(paintWidget, this);
    view->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(view);

    connect(this, SIGNAL(changeCurrentStatus(PaintWidget::Code)), paintWidget, SLOT(setCurrentStatus(PaintWidget::Code)));
    connect(paintWidget, SIGNAL(sendMessage(QString)), this, SLOT(showMessageTriggered(QString)));
}

void CompMainWindow::setAction(QAction* &action, QString name, QString filePath, const char* act)
{
    action = new QAction(name, bar);
    action->setIcon(QIcon("images/" + filePath));
    action->setToolTip(tr(act));
    action->setStatusTip(tr(act));
    action->setCheckable(true);
    action->setChecked(false);
    group->addAction(action);
    bar->addAction(action);
}

void CompMainWindow::drawLineActionTriggered()
{
    emit changeCurrentStatus(PaintWidget::LINE);
}

void CompMainWindow::drawRectActionTriggered()
{
    emit changeCurrentStatus(PaintWidget::RECT);
}

void CompMainWindow::drawEllipActionTriggered()
{
    emit changeCurrentStatus(PaintWidget::ELLIPSE);
}

void CompMainWindow::dragActionTriggered()
{
    emit changeCurrentStatus(PaintWidget::DRAGE);
}

void CompMainWindow::editTextActionTriggered()
{
    emit changeCurrentStatus(PaintWidget::TEXT);
}

void CompMainWindow::drawSemiActionTriggered()
{
    emit changeCurrentStatus(PaintWidget::SEMICIR);
}

void CompMainWindow::drawPinActionTriggered()
{
    emit changeCurrentStatus(PaintWidget::PIN);
}

void CompMainWindow::showMessageTriggered(QString msg)
{
    statusBar()->showMessage(msg);
}

void CompMainWindow::setLib()
{
    libPath = QFileDialog::getOpenFileName(this, tr("Choose Lib"), ".", tr("txt Files(*.txt)"));
    std::ifstream fin(libPath.toStdString());
    std::string check;
    fin >> check;
    if(check != "ComponentLib_CopyRight©Paradixe") {
        std::ofstream fout(libPath.toStdString());
        fout << "ComponentLib_CopyRight©Paradixe" << "\r\n";
        fout.close();
    }
    fin.close();
}

void CompMainWindow::savePNG()
{
    pngPath = "LibPNG/" + compName + ".png";
    std::cout << pngPath.toStdString();
    if(pngPath.isEmpty())
        return;
//    QRectF rect = paintWidget->items()[0]->boundingRect();

//    for(int i = 1; i < paintWidget->items().length(); i++) {
//        paintWidget->items()[i]->setFlag(QGraphicsItem::ItemIsSelectable, false);
//        QRectF temp = paintWidget->items()[i]->sceneBoundingRect();
//        rect.setTop(temp.top() < rect.top() ? temp.top() : rect.top());
//        rect.setBottom(temp.bottom() > rect.bottom() ? temp.bottom() : rect.bottom());
//        rect.setRight(temp.right() > rect.right() ? temp.right() : rect.right());
//        rect.setLeft(temp.left() < rect.left() ? temp.left() : rect.left());

//    }
    paintWidget->setSceneRect(paintWidget->itemsBoundingRect());

    QImage image(300 * paintWidget->width() / paintWidget->height(), 300, QImage::Format_ARGB32);

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    paintWidget->setBackgroundBrush(Qt::white);
    paintWidget->render(&painter);
    image.save(pngPath);
}

void CompMainWindow::setName()
{
    bool isOK;
    compName = QInputDialog::getText(NULL, "Set Component name",
                                           "Component name",
                                           QLineEdit::Normal,
                                           "name",
                                           &isOK);
    if(isOK) {
        compShortHand = QInputDialog::getText(NULL, "Set ShortHand",
                                                    "ShortHand",
                                                    QLineEdit::Normal,
                                                    "ShortHand",
                                                    &isOK);
    }
}

void CompMainWindow::saveComp()
{
    if (libPath.isEmpty())
        setLib();
    if (compName.isEmpty())
        setName();
    if (pngPath.isEmpty())
        savePNG();
    std::ofstream fout(libPath.toStdString(), std::ofstream::app);
    fout << "Begin" << "\r\n";
    fout << "Name" << "\t" << compName.toStdString() << "\r\n";
    fout << "Short" << "\t" << compShortHand.toStdString() << "\r\n";
    fout << "ImgPath" << "\t" << pngPath.toStdString() << "\r\n";
    fout << "Paints" << "\r\n";
    paintWidget->saveItems(fout);
    close();
    CompMainWindow* compMainWindow = new CompMainWindow;
    compMainWindow->show();
}

void CompMainWindow::newComp()
{
    CompMainWindow* compMainWindow = new CompMainWindow;
    compMainWindow->show();
}

void CompMainWindow::newCircuit()
{
    CircuitMainWindow* circuitMainWindow = new CircuitMainWindow;
    circuitMainWindow->show();
}
