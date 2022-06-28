#include "WriterWindow.h"
#include "DevelopIdeaWindow.h"
#include <QMessageBox>
#include <fstream>

using namespace std;

WriterWindow::WriterWindow(string _name, Service& _serv, WriterModel* _model, QWidget* parent)
	: name{_name}, serv {_serv}, model{ _model }, QWidget(parent) {

	ui.setupUi(this);
	this->ui.tableViewIdeas->setModel(this->model);
	this->ui.tableViewIdeas->resizeColumnsToContents();

	// set selection behavior
	this->ui.tableViewIdeas->setSelectionBehavior(QAbstractItemView::SelectRows);
	this->ui.tableViewIdeas->setSelectionMode(QAbstractItemView::SingleSelection);

	connect(this->ui.pushButtonAddIdea, &QPushButton::clicked, this, &WriterWindow::addIdea);

	// for the "Develop Idea" button
	this->checkAccepted();
	connect(this->model, &QAbstractTableModel::dataChanged, this, &WriterWindow::checkAccepted);
	connect(this->ui.pushButtonDevelopIdea, &QPushButton::clicked, this, &WriterWindow::developIdeas);

	// check if we need the "Accept Idea" button
	vector<Writer> writers = this->serv.getWriters();
	string expertise;
	for (auto writer : writers) {
		if (writer.getName() == this->name) {
			expertise = writer.getExpertise();
		}
	}
	if (expertise != "Senior") {
		this->ui.pushButtonAcceptIdea->hide();
	}
	else {
		connect(this->ui.pushButtonAcceptIdea, &QPushButton::clicked, this, &WriterWindow::acceptIdea);
	}

	// for "Save Plot"
	connect(this->ui.pushButtonSavePlot, &QPushButton::clicked, this, &WriterWindow::savePlot);
}

WriterWindow::~WriterWindow()
{
}

void WriterWindow::addIdea() {
	string description = this->ui.lineEditDescription->text().toStdString();
	int act = -1; 
	try {
		act = stoi(this->ui.lineEditAct->text().toStdString());
	}
	catch (exception& e) {
		QMessageBox* error = new QMessageBox{};
		error->setText("The act should be an integer number! Try again!");
		error->show();
		this->ui.lineEditAct->clear();
		return;
	}

	if (act <= 0 || act >= 4) {
		QMessageBox* error = new QMessageBox{};
		error->setText("The act should be an integer number between 1 and 3! Try again!");
		error->show();
		this->ui.lineEditAct->clear();
		return;
	}

	if (description == "") {
		QMessageBox* error = new QMessageBox{};
		error->setText("The description should not be empty! Try again!");
		error->show();
		this->ui.lineEditDescription->clear();
		return;
	}

	// we try to add
	this->model->addIdea(description, this->name, act);
	this->ui.lineEditDescription->clear();
	this->ui.lineEditAct->clear();
}

void WriterWindow::acceptIdea() {
	QModelIndexList row = this->ui.tableViewIdeas->selectionModel()->selectedIndexes();
	QModelIndex* indexes = row.data();

	int rowToDelete = indexes[0].row();
	string description = indexes[0].data().toString().toStdString();
	string expertise = indexes[1].data().toString().toStdString();
	string name = indexes[2].data().toString().toStdString();
	int act = stoi(indexes[3].data().toString().toStdString());

	if (expertise == "proposed") {
		this->model->acceptIdea(description, name, act);
	}
}

void WriterWindow::checkAccepted() {
	this->ui.pushButtonDevelopIdea->hide();
	for (auto idea : this->serv.getIdeas()) {
		if (idea.getCreator() == this->name && idea.getStatus() == "accepted") {
			this->ui.pushButtonDevelopIdea->show();
			return;
		}
	}
}

void WriterWindow::developIdeas() {
	for (auto idea : this->serv.getIdeas()) {
		if (idea.getCreator() == this->name && idea.getStatus() == "accepted") {
			DevelopIdeaWindow* w = new DevelopIdeaWindow{ idea, this->model, this->serv };
			w->show();
		}
	}
}

void WriterWindow::savePlot() {
	ofstream g("plot.txt");
	for (int act = 1; act <= 3; act++) {
		g << "Act" + to_string(act) + ":" << '\n';
		for (auto idea : this->serv.getIdeas()) {
			if (idea.getAct() == act && idea.getStatus() == "accepted") {
				g << idea.getDescription() + " (" + idea.getCreator() + ")" << '\n';
			}
		}
	}
}