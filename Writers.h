#pragma once
#include "Writer.h"
#include <vector>

class Writers {
private:
	std::vector<Writer>writers;
public:
	Writers();
	void read();
	void write();
	std::vector<std::string> getWriter(std::string str, char delimiter);
	std::vector<Writer>getWriters() { return this->writers; }
};