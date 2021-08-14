#include "snakeboard.h"

#include <QDebug>
#include <QKeyEvent>
#include <QPainter>
#include <QtCore>
SnakeBoard::SnakeBoard(QWidget *parent)
    : QFrame(parent), isStarted(false), isPaused(false)
{
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    xApple=new int[Height*Width];
    yApple=new int[Height*Width];
    x=new int[Height*Width];
    y=new int[Height*Width];
    for (int z = 0; z < box; z++) {
        x[z] = Width/2 - z;
        y[z] = Height/2;
/*        xApple[z] = 50 - z * 10;
        yApple[z] = 50*/
    }
    setApple();

}
QSize SnakeBoard::sizeHint()const{
    return QSize(Width * 15 + frameWidth() * 2,
                 Height * 15 + frameWidth() * 2);
}
QSize SnakeBoard::minimumSizeHint()const{
    return QSize(Width * 5 + frameWidth() * 2,
                 Height * 5 + frameWidth() * 2);
}

void SnakeBoard::resizeEvent(QResizeEvent* e)
{
    int h = e->size().height();
    int w = e->size().width();
    h=w;
    resize(w, h);

}

SnakeBoard:: ~SnakeBoard(){

}

void SnakeBoard::start(){
    qDebug()<<"start snake";

    if (isPaused)
        isPaused=false;
    if (loose){
        loose=false;
        for (int z = 0; z < box; z++) {
            x[z] = 50 - z * 10;
            y[z] = 50;
            xApple[z] = 50 - z * 10;
            yApple[z] = 50;
        }
    }
    score=0;
    emit scoreChanged(score);
    isStarted = true;
    timer.start(timeoutTime(), this);
    update();
}

void SnakeBoard::pause(){
    qDebug()<<"pause snake";
    if(loose||isPaused){
        isPaused=false;
        start();
        return;
    }
    isPaused=true;
    isStarted=false;
    timer.stop();

}
void SnakeBoard::keyPressEvent(QKeyEvent *event)
{
    if (!isStarted || isPaused) {
        QFrame::keyPressEvent(event);
        return;
    }

    switch (event->key()) {
    case Qt::Key_Left:
        if(!left&&!right){

            left=true;
            right=false;
            down=false;
            up=false;
        }
        break;
    case Qt::Key_Right:
        if(!right&&!left){

            left=false;
            right=true;
            down=false;
            up=false;
        }
        break;
    case Qt::Key_Down:
        if(!down&&!up){

            left=false;
            right=false;
            down=true;
            up=false;
        }
        break;
    case Qt::Key_Up:
        if(!up&&!down){

            left=false;
            right=false;
            down=false;
            up=true;
        }
        break;
    case Qt::Key_Space:
        pause();
        break;
    default:
        QFrame::keyPressEvent(event);
    }


}

void SnakeBoard:: paintEvent(QPaintEvent *event){
    QFrame::paintEvent(event);

    QPainter painter(this);
    QRect rect = contentsRect();
    //! [7]

    if (isPaused) {
        painter.drawText(rect, Qt::AlignCenter, tr("Pause"));
        return;
    }
    if (loose){
        painter.drawText(rect, Qt::AlignCenter, tr("Loose"));
        return;
    }
    if(!isStarted)
        return;
    int boardTop = rect.bottom() - Height*squareHeight();
    for(int i=0;i<Width*Height;i++){
        for (int z = 0; z < box; z++) {
            if(z==0){
                draw(painter, rect.left() + x[z] * squareWidth(),
                     boardTop + (Height - y[z] - 1) * squareHeight(),
                     rect.left() + *xApple * squareWidth(),boardTop + (Height - *yApple - 1) * squareHeight(),0xDAAA00);
            }else{
                draw(painter, rect.left() + x[z] * squareWidth(),
                     boardTop + (Height - y[z] - 1) * squareHeight(),
                     rect.left() + *xApple * squareWidth(),boardTop + (Height - *yApple - 1) * squareHeight(),0x00ff00);}
        }
        update();
    }}

void SnakeBoard::timerEvent(QTimerEvent *event){
    chekApple();
    runSnake();


}

void SnakeBoard::setApple(){
    xApple[0]= QRandomGenerator::global()->bounded(Width);
    yApple[0]=QRandomGenerator::global()->bounded(Height);
    apple=false;
}

void SnakeBoard::chekApple(){
    if(x[0]==xApple[0]&& y[0]==yApple[0]){
        box++;
        score++;
        emit scoreChanged(score);
        setApple();
    }
}

void SnakeBoard::runSnake(){
    for (int z = box; z > 0; z--) {
        x[z] = x[(z - 1)];
        y[z] = y[(z - 1)];
    }

    for (int z = box; z > 0; z--) {

        if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {
            loose = true;
            box=2;
        }
    }

    if(left){
        x[0]-=len;
        if(x[0]<0)
            x[0]=Width;
    }else if(right){
        x[0]+=len;
        if(x[0]>Width)
            x[0]=0;

    }else if(down){
        y[0]-=len;
        if(y[0]<0)
            y[0]=Height;

    }else if(up){
        y[0]+=len;
        if(y[0]>Height)
            y[0]=0;

    }


}

void SnakeBoard::draw(QPainter &painter, int dx, int dy, int xApple, int yApple,int n)
{
    //painter.setPen(color.lighter());
    painter.drawLine(dx, dy + squareHeight() - 1, dx, dy);
    painter.drawLine(dx, dy, dx + squareWidth() - 1, dy);
    painter.fillRect(xApple, yApple, squareWidth(), squareHeight(), 0xff0000);
    painter.fillRect(dx, dy, squareWidth(), squareHeight(),n );
}
