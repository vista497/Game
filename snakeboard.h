#ifndef SNAKEBOARD_H
#define SNAKEBOARD_H

#include <QFrame>
#include <QBasicTimer>
#include <QVector>
class SnakeBoard:public QFrame
{
    Q_OBJECT
    int *xApple;
    int *yApple;
    int box=2;
    int *x;
    int *y;
    int score=box;
    bool isStarted;
    bool isPaused;
    bool apple=true;
    bool loose=false;
    bool left=false;
    bool right=false;
    bool down=false;
    bool up=false;
    int len=1;
    int sizeBox=10;
    QBasicTimer timer;
    enum{Width=40, Height=40};
    int timeoutTime() { return 1000 / 15; }
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
public:
    SnakeBoard(QWidget *parent = nullptr);
    ~SnakeBoard();
    void start();
    void pause();
    void runSnake();
    void draw(QPainter &painter, int x, int y, int xApple, int yApple,int t);
    int squareWidth() { return contentsRect().width() / Width; }
    int squareHeight() { return contentsRect().height() / Height; }
    void setApple();
    void chekApple();

signals:
    void scoreChanged(int score);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void resizeEvent(QResizeEvent *) override;

};

#endif // SNAKEBOARD_H
