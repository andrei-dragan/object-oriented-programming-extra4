#include "Screenwriting.h"

Screenwriting::Screenwriting(Service& _serv, QWidget *parent)
    : serv{ _serv }, QMainWindow(parent)
{

    // init the model
    WriterModel* model = new WriterModel{ this->serv };
    this->model = model; 
    for (auto writer : this->serv.getWriters()) {
        WriterWindow* w = new WriterWindow{ writer.getName(), this->serv, model };
        w->setWindowTitle(QString::fromStdString(writer.getName()));
        w->show();
    }

    ui.setupUi(this);
}
