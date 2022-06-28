#pragma once

#include <QWidget>
#include "ui_DevelopIdeaWindow.h"
#include "Service.h"
#include "WriterModel.h"

class DevelopIdeaWindow : public QWidget
{
	Q_OBJECT

public:
	DevelopIdeaWindow(Idea _idea, WriterModel* _model, Service& _serv, QWidget *parent = Q_NULLPTR);
	~DevelopIdeaWindow();

private:
	Idea idea;
	WriterModel* model;
	Service& serv;
	Ui::DevelopIdeaWindow ui;

public:
	void saveIdea();
};
