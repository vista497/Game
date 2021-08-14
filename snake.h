#ifndef SNAKE_H
#define SNAKE_H
#include <QWidget>

class QLCDNumber;
class SnakeBoard;
class QPushButton;

class SnakeGame:public QWidget
{
    Q_OBJECT
    SnakeBoard *board;
    QPushButton *startButton;
    QPushButton *quitButton;
    QLCDNumber *scoreLcd;

public:
    SnakeGame(QWidget *parent = nullptr);
protected:
    void resizeEvent(QResizeEvent *) override;
};

#endif // SNAKE_H
