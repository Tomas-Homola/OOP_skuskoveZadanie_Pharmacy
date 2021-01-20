#include "Pharmacy.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Pharmacy w;
    w.show();
    return a.exec();
}
