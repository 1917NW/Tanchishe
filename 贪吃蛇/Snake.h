#ifdef WIN32
#pragma execution_character_set("utf-8")
#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Snake.h"

class Snake : public QMainWindow
{
    Q_OBJECT

public:
    Snake(QWidget *parent = Q_NULLPTR);
    void paintEvent(QPaintEvent* parent = 0);
    void InitSnake();
    QRect CreateFood();
    void IsEat();
    void IsHit();
private slots:
    void Snake_update();//定义蛇动的函数
private:
    Ui::SnakeClass ui;
    void keyPressEvent(QKeyEvent* key);
    QTimer* timer;//定时器
    bool blsRun;//是否开始
    int nDirection;//蛇移动的方向
    QVector<QRect> vSnakeRect;//蛇
    QRect SnakeHead;//蛇头
    bool blsOver;
    QString sDisplay;
    QRect food;//食物
    int nScore;
    QString scoreLabel;//显示得分
    int speed;//移动速度
};
#endif