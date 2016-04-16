/********************************************************************************
** Form generated from reading UI file 'trianglewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRIANGLEWINDOW_H
#define UI_TRIANGLEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TriangleWIndow
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TriangleWIndow)
    {
        if (TriangleWIndow->objectName().isEmpty())
            TriangleWIndow->setObjectName(QStringLiteral("TriangleWIndow"));
        TriangleWIndow->resize(400, 300);
        menuBar = new QMenuBar(TriangleWIndow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        TriangleWIndow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TriangleWIndow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        TriangleWIndow->addToolBar(mainToolBar);
        centralWidget = new QWidget(TriangleWIndow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        TriangleWIndow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TriangleWIndow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        TriangleWIndow->setStatusBar(statusBar);

        retranslateUi(TriangleWIndow);

        QMetaObject::connectSlotsByName(TriangleWIndow);
    } // setupUi

    void retranslateUi(QMainWindow *TriangleWIndow)
    {
        TriangleWIndow->setWindowTitle(QApplication::translate("TriangleWIndow", "TriangleWIndow", 0));
    } // retranslateUi

};

namespace Ui {
    class TriangleWIndow: public Ui_TriangleWIndow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRIANGLEWINDOW_H
