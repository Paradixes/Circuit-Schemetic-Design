/********************************************************************************
** Form generated from reading UI file 'welcomemenu.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELCOMEMENU_H
#define UI_WELCOMEMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WelcomeMenu
{
public:
    QPushButton *pBtComponent;
    QPushButton *pBtCircuit;
    QPushButton *pBtCircuitText;
    QLabel *label;

    void setupUi(QWidget *WelcomeMenu)
    {
        if (WelcomeMenu->objectName().isEmpty())
            WelcomeMenu->setObjectName(QStringLiteral("WelcomeMenu"));
        WelcomeMenu->resize(704, 554);
        WelcomeMenu->setCursor(QCursor(Qt::ArrowCursor));
        pBtComponent = new QPushButton(WelcomeMenu);
        pBtComponent->setObjectName(QStringLiteral("pBtComponent"));
        pBtComponent->setGeometry(QRect(170, 170, 341, 71));
        pBtComponent->setAutoFillBackground(false);
        pBtCircuit = new QPushButton(WelcomeMenu);
        pBtCircuit->setObjectName(QStringLiteral("pBtCircuit"));
        pBtCircuit->setGeometry(QRect(170, 280, 341, 71));
        pBtCircuit->setAutoFillBackground(false);
        pBtCircuitText = new QPushButton(WelcomeMenu);
        pBtCircuitText->setObjectName(QStringLiteral("pBtCircuitText"));
        pBtCircuitText->setGeometry(QRect(170, 390, 341, 71));
        label = new QLabel(WelcomeMenu);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(120, 40, 451, 111));

        retranslateUi(WelcomeMenu);

        QMetaObject::connectSlotsByName(WelcomeMenu);
    } // setupUi

    void retranslateUi(QWidget *WelcomeMenu)
    {
        WelcomeMenu->setWindowTitle(QApplication::translate("WelcomeMenu", "Form", nullptr));
        pBtComponent->setText(QApplication::translate("WelcomeMenu", "Create Component", nullptr));
        pBtCircuit->setText(QApplication::translate("WelcomeMenu", "Create Circuit", nullptr));
        pBtCircuitText->setText(QApplication::translate("WelcomeMenu", "Open Circuit File", nullptr));
        label->setText(QApplication::translate("WelcomeMenu", "<html><head/><body><h2 align=\"center\" style=\" margin-top:16px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:x-large; font-weight:600;\">Welcome to Circuit Design!</span></h2></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WelcomeMenu: public Ui_WelcomeMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOMEMENU_H
