﻿#include "GWModelMainWindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    CGWModelMainWindow w;
    w.showMaximized();

    return a.exec();
}
