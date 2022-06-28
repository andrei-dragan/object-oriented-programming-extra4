#pragma once
#include <string>

class Writer {
private:
	std::string name;
	std::string expertise;
public:
	Writer(std::string _name, std::string _expertise) : name{ _name }, expertise{ _expertise } {};
	std::string getName() { return this->name; }
	std::string getExpertise() { return this->expertise; }
};