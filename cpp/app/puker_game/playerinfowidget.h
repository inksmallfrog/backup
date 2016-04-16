#ifndef PLAYERINFOWIDGET_H
#define PLAYERINFOWIDGET_H

#include <QWidget>
#include <QString>

class QHBoxLayout;
class QVBoxLayout;
class QImage;
class QLabel;

enum PlayerState{
    PlayerState_Banker,
    PlayerState_Normal,
    PlayerState_BankerOp
};

class PlayerInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerInfoWidget(const QString &player_name, const QString &icon_filename, QWidget *parent = 0);
    ~PlayerInfoWidget();
    void set_state(PlayerState state);

signals:

public slots:

private:
    QHBoxLayout *layout_main;

    QLabel *image_playericon;
    QWidget *widget_right;
    QVBoxLayout *layout_right;
    QLabel *label_state;
    QLabel *label_name;
};

#endif // PLAYERINFOWIDGET_H
