/*
 * ComputerPlayer.cpp
 *
 *  Created on: Mar 17, 2012
 *      Author: Kristofer Leifland
 */

#include "ComputerPlayer.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;

unsigned int ComputerPlayer::instanceCount = 0;

const char* ComputerPlayer::names[] =
	{"HAL 9000", "Deep Thought", "Marvin", "MU-TH-R",
	 "Bender Bending Rodríguez", "GLaDOS", "Ash", "Bishop", "Project 2501",
	 "C-3PO", "R2-D2", "K-9", "Dr. Know", "Skynet", "T-1000"};

ComputerPlayer::ComputerPlayer() : super(whatsMyName()) {
	++instanceCount;
}

/*
 *  Returns this instances' name. The order of the available names are randomized
 *  at first instantiation and then new instantiations gets names according to
 *  the randomized order.
 */
const char* ComputerPlayer::whatsMyName() {
	if (instanceCount == 0) {
		// Shuffle names
		for (int i = 0; i < NAMES_SIZE; ++i)
			swap(names[i], names[rand() % (NAMES_SIZE - i) + i]);
	}
	return names[(instanceCount) % NAMES_SIZE];
}

ComputerPlayer::~ComputerPlayer() {
	// TODO Auto-generated destructor stub
}

