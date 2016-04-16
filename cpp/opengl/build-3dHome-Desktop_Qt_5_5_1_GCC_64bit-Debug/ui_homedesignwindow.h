/********************************************************************************
** Form generated from reading UI file 'homedesignwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOMEDESIGNWINDOW_H
#define UI_HOMEDESIGNWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HomeDesignWindow
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *HomeDesignWindow)
    {
        if (HomeDesignWindow->objectName().isEmpty())
            HomeDesignWindow->setObjectName(QStringLiteral("HomeDesignWindow"));
        HomeDesignWindow->resize(800, 600);
        menubar = new QMenuBar(HomeDesignWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        HomeDesignWindow->setMenuBar(menubar);
        centralwidget = new QWidget(HomeDesignWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        HomeDesignWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(HomeDesignWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        HomeDesignWindow->setStatusBar(statusbar);

        retranslateUi(HomeDesignWindow);

        QMetaObject::connectSlotsByName(HomeDesignWindow);
    } // setupUi

    void retranslateUi(QMainWindow *HomeDesignWindow)
    {
        HomeDesignWindow->setWindowTitle(QApplication::translate("HomeDesignWindow", "MainWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class HomeDesignWindow: public Ui_HomeDesignWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMEDESIGNWINDOW_H
