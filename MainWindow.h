//
// Created by Guglielmo Fratticioli on 09/07/19.
//

#ifndef MYTEST_MAINWINDOW_H
#define MYTEST_MAINWINDOW_H

#include <QMainWindow>

class QGridLayout;
class QWidget;
class DrumKitWidget;
class MetronomeWidget;

class MainWindow : public QMainWindow {
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QWidget * mainWidget;
    QWidget* drumbackWidget;
    DrumKitWidget* drumKitWidget;
    MetronomeWidget* metronomeWidget;
    QGridLayout* mainLayout;
};


#endif //MYTEST_MAINWINDOW_H