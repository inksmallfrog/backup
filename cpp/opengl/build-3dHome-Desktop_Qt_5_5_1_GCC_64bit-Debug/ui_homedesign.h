/********************************************************************************
** Form generated from reading UI file 'homedesign.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOMEDESIGN_H
#define UI_HOMEDESIGN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <homedesignview.h>
#include <rulerhorizental.h>
#include <rulervertical.h>
#include "qrulertipwidget.h"

QT_BEGIN_NAMESPACE

class Ui_HomeDesign
{
public:
    QAction *actionSave;
    QAction *actionLoad;
    QAction *actionExit;
    QWidget *centralwidget;
    RulerHorizental *horizontalRuler;
    RulerVertical *verticalRuler;
    QRulerTipWidget *tipWidget;
    HomeDesignView *designView;
    QMenuBar *menubar;
    QMenu *menuMenu;
    QToolBar *toolBar;

    void setupUi(QMainWindow *HomeDesign)
    {
        if (HomeDesign->objectName().isEmpty())
            HomeDesign->setObjectName(QStringLiteral("HomeDesign"));
        HomeDesign->resize(1024, 800);
        HomeDesign->setMinimumSize(QSize(800, 50));
        actionSave = new QAction(HomeDesign);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionLoad = new QAction(HomeDesign);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        actionExit = new QAction(HomeDesign);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralwidget = new QWidget(HomeDesign);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalRuler = new RulerHorizental(centralwidget);
        horizontalRuler->setObjectName(QStringLiteral("horizontalRuler"));
        horizontalRuler->setGeometry(QRect(32, 50, 992, 32));
        verticalRuler = new RulerVertical(centralwidget);
        verticalRuler->setObjectName(QStringLiteral("verticalRuler"));
        verticalRuler->setGeometry(QRect(0, 82, 32, 681));
        tipWidget = new QRulerTipWidget(centralwidget);
        tipWidget->setObjectName(QStringLiteral("tipWidget"));
        tipWidget->setGeometry(QRect(0, 50, 32, 32));
        designView = new HomeDesignView(centralwidget);
        designView->setObjectName(QStringLiteral("designView"));
        designView->setGeometry(QRect(30, 80, 992, 681));
        HomeDesign->setCentralWidget(centralwidget);
        menubar = new QMenuBar(HomeDesign);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1024, 28));
        menuMenu = new QMenu(menubar);
        menuMenu->setObjectName(QStringLiteral("menuMenu"));
        HomeDesign->setMenuBar(menubar);
        toolBar = new QToolBar(HomeDesign);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        toolBar->setMovable(false);
        toolBar->setFloatable(false);
        HomeDesign->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuMenu->menuAction());
        menuMenu->addAction(actionSave);
        menuMenu->addAction(actionLoad);
        menuMenu->addSeparator();
        menuMenu->addAction(actionExit);

        retranslateUi(HomeDesign);

        QMetaObject::connectSlotsByName(HomeDesign);
    } // setupUi

    void retranslateUi(QMainWindow *HomeDesign)
    {
        HomeDesign->setWindowTitle(QApplication::translate("HomeDesign", "MainWindow", 0));
        actionSave->setText(QApplication::translate("HomeDesign", "Save", 0));
        actionLoad->setText(QApplication::translate("HomeDesign", "Load", 0));
        actionExit->setText(QApplication::translate("HomeDesign", "Exit", 0));
        menuMenu->setTitle(QApplication::translate("HomeDesign", "Menu", 0));
        toolBar->setWindowTitle(QApplication::translate("HomeDesign", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class HomeDesign: public Ui_HomeDesign {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMEDESIGN_H
