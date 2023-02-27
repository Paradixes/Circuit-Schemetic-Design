#include "welcomemenu.h"
#include "ui_welcomemenu.h"

WelcomeMenu::WelcomeMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeMenu)
{
    ui->setupUi(this);
    QFont font;
    font.setBold(true);
    font.setPointSize(15);

    QString backgroundcolor("QPushButton{background-color: rgb(0, 82, 204);color:white;}"
                            "QPushButton:hover{background-color: rgb(0, 101, 255);color:white;}");

    ui->pBtCircuit->setStyleSheet(backgroundcolor);
    ui->pBtComponent->setStyleSheet(backgroundcolor);
    ui->pBtCircuitText->setStyleSheet(backgroundcolor);

    ui->pBtCircuit->setFont(font);
    ui->pBtComponent->setFont(font);
    ui->pBtCircuitText->setFont(font);

    setStyleSheet("background-color: rgb(255, 255, 255);");

    connect(ui->pBtCircuit, SIGNAL(clicked()), this, SLOT(circuitDesign()));
    connect(ui->pBtComponent, SIGNAL(clicked()), this, SLOT(createComp()));
    connect(ui->pBtCircuitText, SIGNAL(clicked()), this, SLOT(openCircuitFile()));

    setWindowIcon(QIcon("images/window.png"));
}

WelcomeMenu::~WelcomeMenu()
{
    delete ui;
}

void WelcomeMenu::circuitDesign()
{
    CircuitMainWindow* MainWindow = new CircuitMainWindow;
    MainWindow->show();
    close();
}

void WelcomeMenu::createComp()
{
    CompMainWindow* MainWindow = new CompMainWindow;
    MainWindow->show();
    close();
}

void WelcomeMenu::openCircuitFile()
{
    CircuitMainWindow* MainWindow = new CircuitMainWindow;
    MainWindow->openCircuit();
    MainWindow->show();
    close();
}
