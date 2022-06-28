#pragma once
#include <QAbstractTableModel>
#include "Service.h"

class WriterModel : public QAbstractTableModel {
private:
	Service& serv;

public:
	WriterModel(Service& _serv);
	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	int columnCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	Qt::ItemFlags flags(const QModelIndex& index) const;
	
	void addIdea(std::string description, std::string name, int act);
	void acceptIdea(std::string description, std::string name, int act);
	void updateDescriptionIdea(Idea idea, std::string newDescription);
};	