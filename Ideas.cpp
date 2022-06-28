#include "Ideas.h"
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

Ideas::Ideas() {
	this->read();
}

vector<string> Ideas::getIdea(string str, char delimiter) {
	stringstream ss(str);
	string token;
	vector<string>tokens;
	while (getline(ss, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}

void Ideas::read() {
	ifstream f("ideas.txt");
	string line;
	while (getline(f, line)) {
		vector<string>tokens = this->getIdea(line, ',');
		Idea i{ tokens[0], tokens[1], tokens[2], stoi(tokens[3]) };
		this->ideas.push_back(i);
	}
}

void Ideas::addIdea(Idea i) {
	this->ideas.push_back(i);
}

int Ideas::removeIdea(Idea i) {
	for (int k = 0; k < this->ideas.size(); k++) {
		Idea idea = ideas[k];
		if (idea.getDescription() == i.getDescription() && idea.getCreator() == i.getCreator() && idea.getAct() == i.getAct()) {
			this->ideas.erase(this->ideas.begin() + k);
			return 1;
		}
	}
	return 0;
}

void Ideas::updateIdea(Idea oldIdea, Idea newIdea) {
	for (int k = 0; k < this->ideas.size(); k++) {
		Idea idea = ideas[k];
		if (idea.getCreator() == oldIdea.getCreator() && idea.getAct() == oldIdea.getAct()) {
			ideas[k] = newIdea;
		}
	}
}

vector<Idea> Ideas::getIdeasSortedByAct() {
	vector<Idea> sortedIdeas = this->ideas;
	sort(sortedIdeas.begin(), sortedIdeas.end(), [](Idea A, Idea B) {return A.getAct() < B.getAct(); });
	return sortedIdeas;
}