/*
 * ComputerPlayer.h
 *
 *  Created on: Mar 17, 2012
 *      Author: toffe
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

	virtual Player::Move getNextMove() = 0;
};

#endif /* COMPUTERPLAYER_H_ */
