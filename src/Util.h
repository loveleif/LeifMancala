/*
 * Util.h
 *
 *  Created on: Mar 18, 2012
 *      Author: Kristofer Leifland
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>

namespace Util {

	template <class T>
	T pickRandom(std::vector<T> &vec) {
		return vec[rand() % vec.size()];
	}

	/*
	 * Returns c modulus m.
	 * From: http://stackoverflow.com/questions/1082917/mod-of-negative-number-is-melting-my-brain
	 */
	int mod(int x, int m);

	int readUserInt();
	std::string& readUserString(std::string& input, const char* message);
	std::string& readUserString(std::string& input);
};

#endif /* UTIL_H_ */
