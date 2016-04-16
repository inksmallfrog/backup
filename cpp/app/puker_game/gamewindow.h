#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();
    void game_start();
    void game_deal(short player_id);

private:
    QWidget *widget_main;
    QWidget *widget_central;
    QWidget *widget_player0;
    QWidget *widget_player1;
    QWidget *widget_player2;
    QWidget *widget_player3;
    QGridLayout *layout_main;
    QPushButton *button_start;


};

#endif // MAINWINDOW_H
