#pragma once
#include "Idea.h"
#include <vector>

class Ideas {
private:
	std::vector<Idea>ideas;
public:
	Ideas();
	void read();
	std::vector<std::string> getIdea(std::string str, char delimiter);
	std::vector<Idea> getIdeas() { return this->ideas; }
	std::vector<Idea> getIdeasSortedByAct();
	void addIdea(Idea i);
	void updateIdea(Idea oldIdea, Idea newIdea);
	int removeIdea(Idea i);
};