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
    void Snake_update();//�����߶��ĺ���
private:
    Ui::SnakeClass ui;
    void keyPressEvent(QKeyEvent* key);
    QTimer* timer;//��ʱ��
    bool blsRun;//�Ƿ�ʼ
    int nDirection;//���ƶ��ķ���
    QVector<QRect> vSnakeRect;//��
    QRect SnakeHead;//��ͷ
    bool blsOver;
    QString sDisplay;
    QRect food;//ʳ��
    int nScore;
    QString scoreLabel;//��ʾ�÷�
    int speed;//�ƶ��ٶ�
};
#endif