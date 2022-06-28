#pragma once
#include <string>

class Idea {
private:
	std::string description, status, creator;
	int act;
public:
	Idea(std::string _description, std::string _status, std::string _creator, int _act) : description{ _description }, status{ _status }, creator{ _creator }, act{ _act } {};
	std::string getDescription() { return this->description; }
	std::string getStatus() { return this->status; }
	std::string getCreator() { return this->creator; }
	int getAct() { return this->act; }
};