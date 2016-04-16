#include "playerinfowidget.h"
#include <QImage>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <assert.h>

PlayerInfoWidget::PlayerInfoWidget(const QString &player_name, const QString &icon_filename, QWidget *parent) : QWidget(parent)
{
    image_playericon = new QLabel();
    image_playericon->setPixmap(QPixmap::fromImage(*(new QImage(icon_filename))));
    assert(image_playericon != NULL);

    widget_right = new QWidget();
    label_state = new QLabel("普通");
    label_name = new QLabel(player_name);
    layout_right = new QVBoxLayout();
    layout_right->addWidget(label_state);
    layout_right->addWidget(label_name);
    widget_right->setLayout(layout_right);

    layout_main = new QHBoxLayout();
    layout_main->addWidget(image_playericon);
    //layout_main->addItem(image_playericon);
    layout_main->addWidget(widget_right);

    this->setLayout(layout_main);
}

PlayerInfoWidget::~PlayerInfoWidget(){

}

void PlayerInfoWidget::set_state(PlayerState state){
    switch(state){
    case PlayerState_Banker:
        label_state->setText("庄家");
        break;
    case PlayerState_BankerOp:
        label_state->setText("对家");
        break;
    case PlayerState_Normal:
        label_state->setText("普通");
        break;
    }
}

