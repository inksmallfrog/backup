/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "homeviewer.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *toolWIdget;
    QWidget *gridLayoutWidget;
    QGridLayout *toolLayout;
    QPushButton *door_button;
    QPushButton *wall_button;
    QPushButton *window_button;
    QPushButton *eraser_button;
    HomeViewer *homeWidget;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1024, 800);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        toolWIdget = new QWidget(centralWidget);
        toolWIdget->setObjectName(QStringLiteral("toolWIdget"));
        toolWIdget->setGeometry(QRect(-1, -1, 151, 801));
        gridLayoutWidget = new QWidget(toolWIdget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, -1, 151, 781));
        toolLayout = new QGridLayout(gridLayoutWidget);
        toolLayout->setSpacing(6);
        toolLayout->setContentsMargins(11, 11, 11, 11);
        toolLayout->setObjectName(QStringLiteral("toolLayout"));
        toolLayout->setContentsMargins(0, 0, 0, 0);
        door_button = new QPushButton(gridLayoutWidget);
        door_button->setObjectName(QStringLiteral("door_button"));

        toolLayout->addWidget(door_button, 0, 1, 1, 1);

        wall_button = new QPushButton(gridLayoutWidget);
        wall_button->setObjectName(QStringLiteral("wall_button"));

        toolLayout->addWidget(wall_button, 0, 0, 1, 1);

        window_button = new QPushButton(gridLayoutWidget);
        window_button->setObjectName(QStringLiteral("window_button"));

        toolLayout->addWidget(window_button, 1, 0, 1, 1);

        eraser_button = new QPushButton(gridLayoutWidget);
        eraser_button->setObjectName(QStringLiteral("eraser_button"));

        toolLayout->addWidget(eraser_button, 1, 1, 1, 1);

        homeWidget = new HomeViewer(centralWidget);
        homeWidget->setObjectName(QStringLiteral("homeWidget"));
        homeWidget->setGeometry(QRect(149, -1, 881, 781));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 28));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        door_button->setText(QApplication::translate("MainWindow", "Door", 0));
        wall_button->setText(QApplication::translate("MainWindow", "Wall", 0));
        window_button->setText(QApplication::translate("MainWindow", "Window", 0));
        eraser_button->setText(QApplication::translate("MainWindow", "Eraser", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
