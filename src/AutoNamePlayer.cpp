/*
 * AutoNamePlayer.cpp
 *
 *  Created on: Mar 17, 2012
 *      Author: toffe
 */

#include "AutoNamePlayer.h"
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;

unsigned int AutoNamePlayer::instanceCount = 0;

const char* AutoNamePlayer::names[] =
	{"HAL 9000", "Deep Thought", "Marvin", "MU-TH-R",
	 "Bender Bending Rodríguez", "GLaDOS", "Ash", "Bishop", "Project 2501",
	 "C-3PO", "R2-D2", "K-9", "Dr. Know", "Skynet", "T-1000"};

AutoNamePlayer::AutoNamePlayer() : super(whatsMyName()) {
	++instanceCount;
}

/*
 *  Returns this instances' name. The order of the available names are randomized
 *  at first instantiation and then new instantiations gets names according to
 *  the randomized order.
 */
const char* AutoNamePlayer::whatsMyName() {
	if (instanceCount == 0) {
		// Shuffle names
		srand(time(NULL));
		for (int i = 0; i < NAMES_SIZE; ++i)
			swap(names[i], names[rand() % (NAMES_SIZE - i) + i]);
	}
	return names[(instanceCount) % NAMES_SIZE];
}

AutoNamePlayer::~AutoNamePlayer() {
	// TODO Auto-generated destructor stub
}

