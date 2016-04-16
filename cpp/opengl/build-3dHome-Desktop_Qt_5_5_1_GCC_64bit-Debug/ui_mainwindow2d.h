/********************************************************************************
** Form generated from reading UI file 'mainwindow2d.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW2D_H
#define UI_MAINWINDOW2D_H

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

class Ui_MainWindow2D
{
public:
    QWidget *centralwidget;
    QWidget *leftwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *toolboxlayout;
    QPushButton *wall_button;
    QWidget *rightwidget;
    HomeViewer *home_design_widget;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow2D)
    {
        if (MainWindow2D->objectName().isEmpty())
            MainWindow2D->setObjectName(QStringLiteral("MainWindow2D"));
        MainWindow2D->resize(800, 600);
        centralwidget = new QWidget(MainWindow2D);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        leftwidget = new QWidget(centralwidget);
        leftwidget->setObjectName(QStringLiteral("leftwidget"));
        leftwidget->setGeometry(QRect(-1, -1, 141, 571));
        gridLayoutWidget = new QWidget(leftwidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, -1, 141, 581));
        toolboxlayout = new QGridLayout(gridLayoutWidget);
        toolboxlayout->setSpacing(6);
        toolboxlayout->setContentsMargins(11, 11, 11, 11);
        toolboxlayout->setObjectName(QStringLiteral("toolboxlayout"));
        toolboxlayout->setContentsMargins(0, 0, 0, 0);
        wall_button = new QPushButton(gridLayoutWidget);
        wall_button->setObjectName(QStringLiteral("wall_button"));

        toolboxlayout->addWidget(wall_button, 0, 0, 1, 1);

        rightwidget = new QWidget(centralwidget);
        rightwidget->setObjectName(QStringLiteral("rightwidget"));
        rightwidget->setGeometry(QRect(139, 0, 661, 571));
        home_design_widget = new HomeViewer(rightwidget);
        home_design_widget->setObjectName(QStringLiteral("home_design_widget"));
        home_design_widget->setGeometry(QRect(0, 0, 661, 571));
        MainWindow2D->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow2D);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 28));
        MainWindow2D->setMenuBar(menubar);

        retranslateUi(MainWindow2D);

        QMetaObject::connectSlotsByName(MainWindow2D);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow2D)
    {
        MainWindow2D->setWindowTitle(QApplication::translate("MainWindow2D", "MainWindow", 0));
        wall_button->setText(QApplication::translate("MainWindow2D", "Wall", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow2D: public Ui_MainWindow2D {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW2D_H
