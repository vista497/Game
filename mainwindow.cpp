#include "mainwindow.h"
#include <QPushButton>
#include "tetris.h"
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    //Кнопки приложений
    tetrisButton=new QPushButton("&Tetris");
    tetrisButton->setFocusPolicy(Qt::NoFocus);
    snakeButton=new QPushButton("&Snake");
    snakeButton->setFocusPolicy(Qt::NoFocus);

    //Коннект
    connect(tetrisButton, SIGNAL(clicked()),
           this, SLOT(tetrisShow()));
    connect(snakeButton, SIGNAL(clicked()),
           this, SLOT(snakeShow()));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(tetrisButton, 0,0);
    layout->addWidget(snakeButton, 1,0);

    setLayout(layout);
    setWindowTitle(tr("Project421"));
    resize(250, 500);

}

MainWindow::~MainWindow()
{
}

void MainWindow::tetrisShow(){
    tetris.show();
}

void MainWindow::snakeShow(){
    snake.show();
}

