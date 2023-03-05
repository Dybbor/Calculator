#include <QtWidgets/QApplication>
#include "MainApplication.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalculatorGUI widget;
    widget.show();
    return a.exec();
}
