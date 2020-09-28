#include "Framedesk.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Framedesk w;
    w.show();
    return a.exec();
}
