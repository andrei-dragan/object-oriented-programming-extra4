#include "WriterModel.h"

using namespace std;

WriterModel::WriterModel(Service& _serv) : serv{ _serv } {};

int WriterModel::rowCount(const QModelIndex& parent) const {
	return this->serv.getIdeas().size();
}

int WriterModel::columnCount(const QModelIndex& parent) const {
	return 4;
}

QVariant WriterModel::data(const QModelIndex& index, int role) const {
	int row = index.row();
	int column = index.column();

	vector<Idea>ideas = this->serv.getIdeasSortedByAct();

	if (row >= ideas.size()) {
		return QVariant{};
	}

	if (role == Qt::DisplayRole) {
		if (column == 0) {
			return QVariant{ QString::fromStdString(ideas[row].getDescription()) };
		}
		else if (column == 1) {
			return QVariant{ QString::fromStdString(ideas[row].getStatus()) };
		}
		else if (column == 2) {
			return QVariant{ QString::fromStdString(ideas[row].getCreator()) };
		}
		else if (column == 3) {
			return QVariant{ QString::fromStdString(to_string(ideas[row].getAct())) };
		}
	}

	return QVariant{};
}

void WriterModel::addIdea(string description, string name, int act) {
	Idea i{ description, "proposed", name, act };

	int rows = this->serv.getIdeas().size();

	this->beginInsertRows(QModelIndex{}, rows, rows);
	this->serv.addIdea(i);
	this->endInsertRows();
}

void WriterModel::acceptIdea(std::string description, std::string name, int act) {
	Idea newIdea{ description, "accepted", name, act };
	Idea oldIdea{ description, "proposed", name, act };
	this->serv.updateIdea(oldIdea, newIdea);
	emit dataChanged(QModelIndex{}, QModelIndex{});
}

void WriterModel::updateDescriptionIdea(Idea idea, string newDescription) {
	if (newDescription == "") {
		return;
	}
	Idea newIdea{ newDescription, idea.getStatus(), idea.getCreator(), idea.getAct()};
	Idea oldIdea{ idea.getDescription(), idea.getStatus(), idea.getCreator(), idea.getAct()};
	this->serv.updateIdea(oldIdea, newIdea);
	emit dataChanged(QModelIndex{}, QModelIndex{});
}

Qt::ItemFlags WriterModel::flags(const QModelIndex& index) const {
	return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}	