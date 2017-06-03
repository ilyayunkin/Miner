#include <QApplication>
#include <SapperWidget.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SapperWidget w;
    w.show();

    return a.exec();
}
