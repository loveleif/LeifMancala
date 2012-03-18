/*
 * AutoNamePlayer.h
 *
 *  Created on: Mar 17, 2012
 *      Author: toffe
 */

#ifndef AUTONAMEPLAYER_H_
#define AUTONAMEPLAYER_H_
#define NAMES_SIZE 15

#include "Player.h"
#include <string>
#include <vector>
class AutoNamePlayer: public Player {
	typedef Player super;

	const static char* names[NAMES_SIZE];
	static unsigned int instanceCount;

	const char* whatsMyName();
public:
	AutoNamePlayer();
	virtual ~AutoNamePlayer();

	virtual Player::Move getNextMove() = 0;
};

#endif /* AUTONAMEPLAYER_H_ */
