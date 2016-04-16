/********************************************************************************
** Form generated from reading UI file 'homeshow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOMESHOW_H
#define UI_HOMESHOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HomeShow
{
public:
    QWidget *centralwidget;
    QOpenGLWidget *openGLWidget;
    QMenuBar *menubar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *HomeShow)
    {
        if (HomeShow->objectName().isEmpty())
            HomeShow->setObjectName(QStringLiteral("HomeShow"));
        HomeShow->resize(800, 600);
        centralwidget = new QWidget(HomeShow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        openGLWidget = new QOpenGLWidget(centralwidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(0, 20, 801, 541));
        HomeShow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(HomeShow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 28));
        HomeShow->setMenuBar(menubar);
        toolBar = new QToolBar(HomeShow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        HomeShow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(HomeShow);

        QMetaObject::connectSlotsByName(HomeShow);
    } // setupUi

    void retranslateUi(QMainWindow *HomeShow)
    {
        HomeShow->setWindowTitle(QApplication::translate("HomeShow", "MainWindow", 0));
        toolBar->setWindowTitle(QApplication::translate("HomeShow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class HomeShow: public Ui_HomeShow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMESHOW_H
