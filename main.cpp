#include "mainwindow.h"

#include <QApplication>
#include <QIcon>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("C:/proyectos de qt/Tasky1/"));
    MainWindow w;
    w.show();
    return a.exec();


}
