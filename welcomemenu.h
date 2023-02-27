#ifndef WELCOMEMENU_H
#define WELCOMEMENU_H

#include <QWidget>

#include "CircuitDesign/CircuitMainWindow.h"
#include "CreateComp/CompMainWindow.h"

namespace Ui {
class WelcomeMenu;
}

class WelcomeMenu : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeMenu(QWidget *parent = nullptr);
    ~WelcomeMenu();

private:
    Ui::WelcomeMenu *ui;

public slots:
    void createComp();
    void circuitDesign();
    void openCircuitFile();
};

#endif // WELCOMEMENU_H
