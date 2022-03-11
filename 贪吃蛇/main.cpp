
#pragma execution_character_set("utf-8")
#include "Snake.h"
#include <QtWidgets/QApplication>
#include<qpainter.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Snake w;
    w.show();
    return a.exec();
}
