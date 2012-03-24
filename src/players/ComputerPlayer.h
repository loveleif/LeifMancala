/*
 * ComputerPlayer.h
 * Abstract class that handles automatic naming for it's sub classes.
 *
 *  Created on: Mar 17, 2012
 *      Author: Kristofer Leifland
 */

#ifndef COMPUTERPLAYER_H_
#define COMPUTERPLAYER_H_
#define NAMES_SIZE 15

#include "Player.h"
#include <string>
#include <vector>
class ComputerPlayer: public Player {
	typedef Player super;

	const static char* names[NAMES_SIZE];
	static unsigned int instanceCount;

	const char* whatsMyName();
public:
	ComputerPlayer();
	virtual ~ComputerPlayer();
};

#endif /* COMPUTERPLAYER_H_ */
