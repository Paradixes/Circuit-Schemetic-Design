#include "CircuitMainWindow.h"

CircuitMainWindow::CircuitMainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    createMenu();
    createStatusBar();
    createCentral();
    showMaximized();

    setWindowIcon(QIcon("images/circuit.png"));
}

void CircuitMainWindow::createMenu()
{
    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip("Save a file.");

    openLibAction = new QAction(tr("Open a &Library"), this);
    openLibAction->setShortcut(QKeySequence(tr("Ctrl+L")));
    openLibAction->setStatusTip("Open a library.");

    newCircuitAction = new QAction(tr("New &Circuit"), this);
    newCircuitAction->setShortcut(QKeySequence(tr("Ctrl+N")));
    newCircuitAction->setStatusTip("Create a circuit.");

    newCompAction = new QAction(tr("New &Component"), this);
    newCompAction->setShortcut(QKeySequence(tr("Ctrl+N")));
    newCompAction->setStatusTip("Create a component.");

    openCircuitAction = new QAction(tr("&Open a Circuit"), this);
    openCircuitAction->setShortcut(QKeySequence::Open);
    openCircuitAction->setStatusTip("Open a component.");

    file = menuBar()->addMenu(tr("&File"));
    file->addAction(saveAction);
    file->addAction(openLibAction);
    file->addAction(newCircuitAction);
    file->addAction(newCompAction);
    file->addAction(openCircuitAction);

    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveCircuit()));
    connect(openLibAction, SIGNAL(triggered()), this, SLOT(setLib()));
    connect(newCircuitAction, SIGNAL(triggered()), this, SLOT(newCircuit()));
    connect(newCompAction, SIGNAL(triggered()), this, SLOT(newComp()));
    connect(openCircuitAction, SIGNAL(triggered()), this, SLOT(openCircuit()));
}

void CircuitMainWindow::createStatusBar()
{
    statusMsg = new QLabel;
    statusBar()->addWidget(statusMsg);
}

void CircuitMainWindow::createCentral()
{
    circuitWidget = new CircuitWidget(this);
    view = new QGraphicsView(circuitWidget, this);
    view->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(view);

    connect(circuitWidget, SIGNAL(sendCompInfo(QStringList)), this, SLOT(showCompInfoTriggered(QStringList)));
    connect(circuitWidget, SIGNAL(sendMessage(QString)), this, SLOT(showMessageTriggered(QString)));
}

void CircuitMainWindow::createLibDock()
{
    compList = new QListWidget;
    compList->setViewMode(QListView::ListMode);
    compList->setIconSize(QSize(100, 100));
    compList->setSpacing(10);
    compList->setResizeMode(QListWidget::Adjust);
    compList->setMovement(QListWidget::Static);

    QList<Component*>comp = circuitWidget->getComps();

    foreach (Component* tmp, comp) {
        QListWidgetItem* imageItem = new QListWidgetItem;
        imageItem->setIcon(QIcon(tmp->getIcon()));
        imageItem->setSizeHint(QSize(100, 120));
        imageItem->setText(tmp->getName());
        compList->addItem(imageItem);
    }

    libDock = new QDockWidget("Library", this);
    libDock->setWidget(compList);
    addDockWidget(Qt::LeftDockWidgetArea, libDock);

    connect(compList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(createComp(QListWidgetItem*)));
    connect(this, SIGNAL(getComponent(QString)), circuitWidget, SLOT(addComponent(QString)));
}

void CircuitMainWindow::createCompInfoDock()
{
    removeDockWidget(infoDock);
    infoDock = new QDockWidget("Infomation of component", this);
    infoDock->setWidget(infoList);
    addDockWidget(Qt::RightDockWidgetArea, infoDock);

    connect(infoList, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(InfoChanged(QTableWidgetItem*)));
    connect(this, SIGNAL(sendInfo(QString, int)), circuitWidget, SLOT(changeInfo(QString, int)));
}

void CircuitMainWindow::showMessageTriggered(QString msg)
{
    statusBar()->showMessage(msg);
}

void CircuitMainWindow::setLib()
{
    std::ifstream fin;
    QString Libpath;
    Libpath = QFileDialog::getOpenFileName(this, tr("Choose Lib"), ".", tr("txt Files(*.txt)"));
    fin.open(Libpath.toStdString());
    std::string head;
    fin >> head;
    if (head != "ComponentLib_CopyRight©Paradixe") {
        QMessageBox::critical(NULL, "Wrong", "Wrong lib!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        fin.close();
        return;
    }
    fin.close();
    circuitWidget->setLib(Libpath);
    createLibDock();
}

void CircuitMainWindow::createComp(QListWidgetItem* item)
{
    QString name = item->text();
    emit getComponent(name);
}

void CircuitMainWindow::newCircuit()
{
    CircuitMainWindow* circuitMainWindow = new CircuitMainWindow;
    circuitMainWindow->show();
}

void CircuitMainWindow::newComp()
{
    CompMainWindow* compMainWindow = new CompMainWindow;
    compMainWindow->show();
    close();
}

void CircuitMainWindow::showCompInfoTriggered(QStringList info)
{
    QStringList header;
    QComboBox *size = new QComboBox;
    QComboBox *color = new QComboBox;
    QStringList sizeList, colorList;

    sizeList << "Large" << "Medium" << "Small";
    colorList << "Blue" << "Red" << "Yellow" << "Black" << "Green";
    size->addItems(sizeList);
    color->addItems(colorList);

    size->setCurrentIndex(sizeList.indexOf(info[2]));
    color->setCurrentIndex(colorList.indexOf(info[3]));

    infoList = new QTableWidget(6, 1);
    header << "Name" << "ShortName" << "Size" << "Color" << "Position" << "Rotation";
    infoList->setVerticalHeaderLabels(header);
    infoList->horizontalHeader()->setVisible(false);

    infoList->setItem(0, 0, new QTableWidgetItem(info[0]));
    infoList->setItem(1, 0, new QTableWidgetItem(info[1]));
    infoList->setCellWidget(2, 0, size);
    infoList->setCellWidget(3, 0, color);
    infoList->setItem(4, 0, new QTableWidgetItem(info[4]));
    infoList->setItem(5, 0, new QTableWidgetItem(info[5]));

    infoList->resizeColumnsToContents();
    infoList->resizeRowsToContents();
    createCompInfoDock();

    connect(size, SIGNAL(currentIndexChanged(QString)), this, SLOT(compSizeChanged(QString)));
    connect(this, SIGNAL(sendSizeInfo(QString, int)), circuitWidget, SLOT(changeInfo(QString, int)));

    connect(color, SIGNAL(currentIndexChanged(QString)), this, SLOT(compColorChanged(QString)));
    connect(this, SIGNAL(sendColorInfo(QString, int)), circuitWidget, SLOT(changeInfo(QString, int)));
}

void CircuitMainWindow::InfoChanged(QTableWidgetItem* item)
{
    QString newinfo = item->text();
    int row = item->row();
    emit sendInfo(newinfo, row);
}

void CircuitMainWindow::compSizeChanged(QString info)
{
    emit sendSizeInfo(info, 2);
}

void CircuitMainWindow::compColorChanged(QString info)
{
    emit sendColorInfo(info, 3);
}

void CircuitMainWindow::setCircuitPath()
{
    circuitPath = QFileDialog::getSaveFileName(this, tr("Save Circuit"), "C:\\", tr("txt Files(*.txt)"));
    std::ifstream fin(circuitPath.toStdString());
    std::string check;
    fin >> check;
    if (check == "ComponentLib_CopyRight©Paradixe")
        QMessageBox::critical(NULL, "Wrong", "Wrong Circuit!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    else {
        std::ofstream fout(circuitPath.toStdString());
        fout << "CircuitDesign_CopyRight©Paradixe" << "\r\n";
        fout.close();
    }
    fin.close();
}

void CircuitMainWindow::saveCircuit()
{
    if (circuitPath == NULL)
        setCircuitPath();
    std::ifstream fin(circuitPath.toStdString());
    std::string check;
    fin >> check;
    if (check == "ComponentLib_CopyRight©Paradixe") return;
    fin.close();
    std::ofstream fout(circuitPath.toStdString(), std::ofstream::app);
    circuitWidget->saveComps(fout);
    fout.close();
}

void CircuitMainWindow::openCircuit()
{
    if (lib == NULL)
        setLib();
    circuitPath = QFileDialog::getOpenFileName(this, tr("Choose Circuit"), "C:\\", tr("txt Files(*.txt)"));
    std::ifstream fin(circuitPath.toStdString());
    std::string check;
    fin >> check;
    if (check != "CircuitDesign_CopyRight©Paradixe") {
        QMessageBox::critical(NULL, "Wrong", "Wrong Circuit!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    circuitWidget->setCircuit(fin);
    fin.close();
}
