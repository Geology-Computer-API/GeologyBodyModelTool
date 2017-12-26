#include "GWModelMainWindow.h"
#include <QApplication>
#include <QColorDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CGWModelMainWindow w;


    w.showMaximized();

//    QColorDialog dlg;
//    dlg.getColor();

    return a.exec();
}
