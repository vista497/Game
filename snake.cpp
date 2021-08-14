#include "snake.h"
#include "snakeboard.h"
#include <QCoreApplication>
#include <QGridLayout>
#include <QLabel>
#include <QLCDNumber>
#include <QPushButton>
#include <QResizeEvent>


SnakeGame::SnakeGame(QWidget *parent)
    : QWidget(parent), board(new SnakeBoard)
{

    //board= new SnakeBoard;
    startButton = new QPushButton(tr("&Start"));
    startButton->setFocusPolicy(Qt::NoFocus);
    quitButton = new QPushButton(tr("&Quit"));
    quitButton->setFocusPolicy(Qt::NoFocus);
    scoreLcd = new QLCDNumber(5);
    scoreLcd->setSegmentStyle(QLCDNumber::Filled);

    connect(startButton, &QPushButton::clicked, board, &SnakeBoard::start);
    connect(quitButton, &QPushButton::clicked, qApp, &QCoreApplication::quit);

    connect(board, &SnakeBoard::scoreChanged,
            scoreLcd, qOverload<int>(&QLCDNumber::display));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(startButton, 0,3);
    layout->addWidget(quitButton, 1,3);
    layout->addWidget(board, 0, 1, 10, 2);
    layout->addWidget(scoreLcd, 3,3);
    setLayout(layout);

    setWindowTitle(tr("Snake"));
}

void SnakeGame::resizeEvent(QResizeEvent* e)
{
    int h = e->size().height();
    int w = e->size().width();
    h=w;
    resize(w, h);

}
