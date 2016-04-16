#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "game.h"
#include "playerinfowidget.h"
#include <QGridLayout>
#include <QLabel>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setWindowTitle("小二定主");
    this->resize(800, 600);

    widget_main = new QWidget(this);
    this->setCentralWidget(widget_main);
    widget_central = new QWidget();

    layout_main = new QGridLayout(this);
    widget_main->setLayout(layout_main);
    QHBoxLayout *layout_central = new QHBoxLayout();
    widget_central->setLayout(layout_central);

    layout_main->setColumnStretch(0, 1);
    layout_main->setColumnStretch(1, 2);
    layout_main->setColumnStretch(2, 1);
    layout_main->setRowStretch(0, 2);
    layout_main->setRowStretch(1, 5);
    layout_main->setRowStretch(2, 3);
    layout_main->addWidget(widget_central, 1, 1);

    GAME->set_mainwindow(this);

    GAME->start();
}

GameWindow::~GameWindow()
{
    delete widget_central;
    delete layout_main;
    delete widget_main;
}

void GameWindow::game_start(){
    PlayerInfoWidget *player0 = new PlayerInfoWidget("Human", ":/new/res/0.jpg", this);
    layout_main->addWidget(player0, 2, 0);
}

void GameWindow::game_deal(short player_id){

}
