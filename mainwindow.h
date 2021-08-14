#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "tetris.h"
#include "snake.h"
class QPushButton;
//class TetrisGame;


class MainWindow : public QWidget
{
    Q_OBJECT
    QPushButton *tetrisButton;
    QPushButton *snakeButton;
    TetrixGame tetris;
    SnakeGame snake;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void click();
private slots:
    void tetrisShow();
    void snakeShow();
};
#endif // MAINWINDOW_H
