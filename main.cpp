#include "Screenwriting.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Ideas ideas;
    Writers writers;
    Service serv{ ideas, writers };

    Screenwriting w{ serv };

    return a.exec();
}
