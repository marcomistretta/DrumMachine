//
// Created by misterm on 12/09/19.
//

#ifndef MYTEST_PLAYERWIDGET_H
#define MYTEST_PLAYERWIDGET_H

class QHBoxLayout;
class QPushButton;
class Player;

#include "Observer.h"
#include <QWidget>


class PlayerWidget : public QWidget, public Observer {
Q_OBJECT
public:
    explicit PlayerWidget(Player* player, QWidget *parent = nullptr);
    ~PlayerWidget();
    void obsUpdate();

    Player *getPlayer() const {
        return player;
    }
    QPushButton * getplayButton() const {
        return  playButton;
    }
    QPushButton * getstopButton() const {
        return stopButton;
    };

    void setPlayer(Player *play) {
        PlayerWidget::player = play;
    }

private slots:
    void on_Play_pressed();
    void on_Stop_pressed();

private:
    Player *player;
    QPushButton * playButton;
    QPushButton * stopButton;
    QHBoxLayout *boxLayout;
};


#endif //DRUM_MACHINE_METRONOMEWIDGET_H
