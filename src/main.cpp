#include <QApplication>
#include <SapperWidget.h>

#include "Sapper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Sapper s(8, 10);
    SapperWidget w(s);
    w.show();

    return a.exec();
}
