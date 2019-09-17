//
// Created by misterm on 11/05/19.
//

#include "Player.h"
#include <QTimer>
#include <QMediaPlayer>

Player::Player() : QObject(), metronome(new Metronome()), timer(new QTimer()), mediaPlayer(new QMediaPlayer()), actualStep(0) {
    firstStep = true;
    timer->stop();
    setStatus(OFF);
    setBpm(60);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(PLAY()));
    qDebug() << "Player constructed";
}

void Player::notify() {
    for (Observer *observer : observers)
        observer->obsUpdate();
    qDebug() << "PlayerWidget notified";
}

void Player::addObserver(Observer *o) {
    qDebug() << "Observer added";
    observers.push_back(o);
}

void Player::removeObserver(Observer *o) {
    qDebug() << "Observer removed";
    observers.remove(o);
}


int Player::fromBpmToMillisec() {
    return 60000 / getBpm();
}


void Player::playPauseTimer() {
    if (!getStatus()) {
        setStatus(ON);
        qDebug() << "State to ON";
        timer->start(fromBpmToMillisec());
        qDebug() << "Timer Start";
    } else {
        setStatus(OFF);
        qDebug() << "State to OFF";
        timer->stop();
        qDebug() << "Timer Stop";
    }
}

void Player::stopTimer() {
    setStatus(OFF);
    qDebug() << "State to OFF";
    timer->stop();
    setFirstStep(true);
    setActualStep(0);
}

void Player::PLAY() {
    //int temp = getActualStep();
    for (auto i : drumKit->getDrums()) {
        if (i->isActive(actualStep))
            i->playDrum();
    }
    if (metronome->getStatus())
        metronome->doBeep();
    setActualStep(((this->actualStep + 1) % 16));
    /*if (!isFirstStep())
        setActualStep(((this->actualStep + 1) % 16));
    else {
        setFirstStep(false);
        actualStep = actualStep + 1;
    }*/
}



