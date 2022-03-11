
#include "Snake.h"
#include<qpainter.h>
#include<qtimer.h>
#include<QKeyEvent>
#include<QRandomGenerator>
Snake::Snake(QWidget* parent)
    : QMainWindow(parent), blsRun(false), speed(500)
{
    ui.setupUi(this);
    this->setGeometry(QRect(600, 300, 290, 310));
}

void Snake::paintEvent(QPaintEvent* parent)
{
    QPainter painter(this);
    if(blsRun==false)
        InitSnake();
    //画游戏背景
    //画外墙
    painter.setPen(Qt::black);
    painter.setBrush(Qt::gray);
    painter.drawRect(15, 15, 260, 260);

    //画内墙
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    painter.drawRect(20, 20, 250, 250);
    painter.drawPixmap(20, 20, 250, 250, QPixmap(":/Snake/img/bg.jpg"));
    //画小格子
    /*painter.setPen(Qt::blue);
    for (int i = 2; i <= 27; i++)
    {
        painter.drawLine(20, i * 10, 270, i * 10);
        painter.drawLine(i * 10, 20, i * 10, 270);
    }*/
    //显示游戏开始、结束
    QFont font1("Courier", 24);
    painter.setFont(font1);
    painter.setPen(Qt::red);
    painter.setBrush(Qt::red);
    painter.drawText(80, 150, sDisplay);

    //得分显示
    QFont font2("Courier", 15);
    painter.setFont(font2);
    painter.setPen(Qt::blue);
    painter.setBrush(Qt::blue);
    painter.drawText(140, 300, scoreLabel);
    painter.drawText(230, 300, QString::number(nScore));
    //画蛇
    painter.setPen(Qt::black);
    painter.setBrush(Qt::green);
   // painter.drawRect(food);
    painter.drawPixmap(food, QPixmap(":/Snake/img/Apple.png"));
    painter.drawRects(&vSnakeRect[0], vSnakeRect.size());
    if (blsOver)
        timer->stop();
}

void Snake::InitSnake()
{
    nDirection = 2;
    blsRun = true;
    blsOver = false;
    food = CreateFood();
    vSnakeRect.resize(5);
    nScore = 0;
    scoreLabel = "得分";
    sDisplay = "游戏开始";
    //利用一个for循环初始化vector
    for (int i = 0; i < vSnakeRect.size(); i++)
    {
        vSnakeRect[vSnakeRect.size() - 1 - i] = QRect(100, 70 + 10 * i, 10, 10);
    }
    SnakeHead = vSnakeRect.first();
    timer = new QTimer(this);
    timer->start(500);
    connect(timer, SIGNAL(timeout()), SLOT(Snake_update()));
}

void Snake::keyPressEvent(QKeyEvent* event) {
    QKeyEvent* key = (QKeyEvent*)event;
    switch (key->key()) {
    case Qt::Key_Up:nDirection = 1;
        break;
    case Qt::Key_Down:nDirection = 2;
        break;
    case Qt::Key_Left:nDirection = 3;
        break;
    case Qt::Key_Right:nDirection = 4;
        break;
    default:;
    }
}

void Snake::Snake_update() {
    sDisplay = "";
    SnakeHead = vSnakeRect.first();
    IsEat();
    IsHit();
    for (int j = 0; j < vSnakeRect.size() - 1; j++)
    {
        vSnakeRect[vSnakeRect.size() - 1 - j] = vSnakeRect[vSnakeRect.size() - 2-j];
    }
    switch (nDirection)
    {
    case 1:
        SnakeHead.setTop(SnakeHead.top() - 10);
        SnakeHead.setBottom(SnakeHead.bottom() - 10);
        break;
    case 2:
        SnakeHead.setTop(SnakeHead.top() + 10);
        SnakeHead.setBottom(SnakeHead.bottom() + 10);
        break;
    case 3:
        SnakeHead.setLeft(SnakeHead.left() - 10);
        SnakeHead.setRight(SnakeHead.right() - 10);
        break;
    case 4:
        SnakeHead.setLeft(SnakeHead.left() + 10);
        SnakeHead.setRight(SnakeHead.right() + 10);
        break;
    default:;
    }
    vSnakeRect[0] = SnakeHead;
    if (SnakeHead.left() < 20 || SnakeHead.right() > 270 || SnakeHead.top() < 20 || SnakeHead.bottom() > 270) {
        sDisplay = "游戏结束";
        blsOver = true;
    }
    update();//调用paintEvent
    
}

QRect Snake::CreateFood() {
    int x, y;
    x = QRandomGenerator::global()->bounded(0,1000)%25;
    y = QRandomGenerator::global()->bounded(0, 1000)%25;
    QRect rect(20 + x * 10, 20 + y * 10, 10, 10);//食物位置
    return rect;
}

void Snake::IsEat() {
    if (SnakeHead == food) {
        SnakeHead = food;
        vSnakeRect.push_back(vSnakeRect.last());
        food = CreateFood();
        nScore += 10;
        if (speed > 50) {
            speed = speed - 10;
            timer->stop();
            timer->start(speed);
        }
    }
}

void Snake::IsHit()
{
    for(int i=1;i<vSnakeRect.size();i++)
        if (SnakeHead == vSnakeRect[i])
        {
            sDisplay = "游戏结束";
            blsOver = true;
            update();
        }
}