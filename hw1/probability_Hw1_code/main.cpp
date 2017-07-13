#include <QApplication>
#include "widget.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    w.show();

    return a.exec();
}
