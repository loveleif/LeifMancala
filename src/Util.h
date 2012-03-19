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
};

#endif /* UTIL_H_ */
