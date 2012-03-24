/*
 * Util.cpp
 *
 *  Created on: Mar 18, 2012
 *      Author: toffe
 */

#include "Util.h"
#include <iostream>
using namespace std;
int Util::mod(int x, int m) {
	    int r = x%m;
	    return r<0 ? r+m : r;
}

int Util::readUserInt() {
	int choice;
	while (!(cin >> choice)) {
		cin.clear();
		cin.ignore();
		cout << "\nIncorrect entry. Try again: ";
	}
	return choice;
}

string& Util::readUserString(string& input, const char* message) {
	cout << message;
	return readUserString(input);
}

string& Util::readUserString(string& input) {
	getline(cin, input);
	return input;
}
