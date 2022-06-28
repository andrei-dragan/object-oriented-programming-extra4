#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Screenwriting.h"
#include "Service.h"
#include "WriterWindow.h"

class Screenwriting : public QMainWindow
{
    Q_OBJECT

public:
    Screenwriting(Service& _serv, QWidget *parent = Q_NULLPTR);

private:
    WriterModel* model;
    Service& serv;
    Ui::ScreenwritingClass ui;
};
