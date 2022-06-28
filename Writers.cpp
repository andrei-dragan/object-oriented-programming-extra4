#include "Writers.h"
#include <fstream>
#include <sstream>

using namespace std;

Writers::Writers() {
	this->read();
}

vector<string> Writers::getWriter(string str, char delimiter) {
	stringstream ss(str);
	vector<string>tokens;
	string token;
	while (getline(ss, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}

void Writers::read() {
	ifstream f("writers.txt");
	string line;
	while (getline(f, line)) {
		vector<string>tokens = this->getWriter(line, ',');
		Writer w{ tokens[0], tokens[1] };
		this->writers.push_back(w);
	}
}