#pragma once

#include <QWidget>
#include "ui_WriterWindow.h"
#include "WriterModel.h"

class WriterWindow : public QWidget
{
	Q_OBJECT

public:
	WriterWindow(std::string _name, Service& _serv, WriterModel* _model, QWidget *parent = Q_NULLPTR);
	~WriterWindow();

private:
	std::string name;
	Service& serv;
	WriterModel* model;
	Ui::WriterWindow ui;

public:
	void addIdea();
	void acceptIdea();
	void checkAccepted();
	void developIdeas();
	void savePlot();
};
