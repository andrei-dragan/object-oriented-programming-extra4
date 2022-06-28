#pragma once
#include "Ideas.h"
#include "Writers.h"

class Service {
private:
	Ideas ideas;
	Writers writers;
public:
	Service(Ideas _ideas, Writers _writers) : ideas{ _ideas }, writers{ _writers } {};
	std::vector<Writer>getWriters() { return this->writers.getWriters(); }
	std::vector<Idea>getIdeas() { return this->ideas.getIdeas(); }
	std::vector<Idea>getIdeasSortedByAct() { return this->ideas.getIdeasSortedByAct(); }
	void addIdea(Idea i) { this->ideas.addIdea(i); }
	void updateIdea(Idea oldIdea, Idea newIdea) { this->ideas.updateIdea(oldIdea, newIdea); }
};