#include "DevelopIdeaWindow.h"
#include <QMessageBox>
#include <fstream>

using namespace std;

DevelopIdeaWindow::DevelopIdeaWindow(Idea _idea, WriterModel* _model, Service& _serv, QWidget *parent)
	: idea{ _idea }, model {_model}, serv{ _serv }, QWidget(parent)
{
	ui.setupUi(this);
	this->ui.textEditDescription->insertPlainText(QString::fromStdString(this->idea.getDescription()));
	connect(this->ui.pushButtonSave, &QPushButton::clicked, this, &DevelopIdeaWindow::saveIdea);
}

DevelopIdeaWindow::~DevelopIdeaWindow()
{
}

void DevelopIdeaWindow::saveIdea() {
	string description = this->ui.textEditDescription->toPlainText().toStdString();
	if (description == "") {
		QMessageBox* error = new QMessageBox{};
		error->setText("The description should not be empty! Try again!");
		error->show();
		this->ui.textEditDescription->clear();
		return;
	}

	string fileName = this->idea.getCreator() + to_string(this->idea.getAct()) + ".txt";
	ofstream g(fileName);
	g << description;
	this->close();
}