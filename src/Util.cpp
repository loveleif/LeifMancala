/*
 * Util.cpp
 *
 *  Created on: Mar 18, 2012
 *      Author: toffe
 */

#include "Util.h"


int Util::mod(int x, int m) {
	    int r = x%m;
	    return r<0 ? r+m : r;
}
