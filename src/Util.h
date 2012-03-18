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
#include <cstdlib>
namespace Util {

	template <class T>
	T pickRandom(std::vector<T> &vec) {
		return vec[rand() % vec.size()];
	}
};

#endif /* UTIL_H_ */
