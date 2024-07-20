#include "activitywindow2.h"
#include "mainwindow2.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow2 w;
//    ActivityWindow2 w(""); // передать имя файла без расширения
    w.show();
    return a.exec();
}
