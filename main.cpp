#include "mainwindow.h"
#include <QApplication>
#include <QString>

using namespace std;
#pragma execution_character_set("utf-8")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QString winname=QString (QObject::tr("连连看"));
    w.setWindowTitle(winname);
    w.show();
    return a.exec();
}
