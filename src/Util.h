/*
 * Util.h
 * Utility functions.
 *
 *  Created on: Mar 18, 2012
 *      Author: Kristofer Leifland
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <cstdlib>
#include <vector>
#include <string>

namespace Util {

	/*
	 * Returns random element from the provided vector.
	 */
	template <class T>
	T pickRandom(std::vector<T> &vec) {
		return vec[rand() % vec.size()];
	}

	/*
	 * Returns c modulus m.
	 * From http://stackoverflow.com/questions/1082917/mod-of-negative-number-is-melting-my-brain
	 */
	int mod(int x, int m);

	/*
	 * Reads an integer from the user and returns it.
	 */
	int readUserInt();

	/*
	 * Reads a string from the user and stores it in the specified string. Also
	 * returns reference to the read string.
	 */
	std::string& readUserString(std::string& input);
};

#endif /* UTIL_H_ */
