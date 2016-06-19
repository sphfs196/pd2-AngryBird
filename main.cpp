#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("angry bird~");
    w.setWindowIcon(QIcon(":/image/ice.png"));
    w.show();

    return a.exec();
}
