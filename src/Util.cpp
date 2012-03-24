/*
 * Util.cpp
 *
 *  Created on: Mar 18, 2012
 *      Author: Kristofer Leifland
 */

#include "Util.h"
#include <sstream>
#include <iostream>
using namespace std;

int Util::mod(int x, int m) {
	    int r = x%m;
	    return r<0 ? r+m : r;
}

int Util::readUserInt() {
	string input;
	std::istringstream i(readUserString(input));
	int number;
	char c;
	while (!(i >> number) || i.get(c)) {
		cout << "Failed to read integer. Please try again: ";
		i.str(readUserString(input));
	}
	return number;
}


string& Util::readUserString(string& input) {
	getline(cin, input);
	return input;
}
