/*
 * RandomPlayer.h
 *
 *  Created on: Mar 18, 2012
 *      Author: toffe
 */

#ifndef RANDOMPLAYER_H_
#define RANDOMPLAYER_H_

#include "ComputerPlayer.h"

class RandomPlayer: public ComputerPlayer {
public:
	RandomPlayer();
	virtual ~RandomPlayer();

	Player::Move getNextMove();
};

#endif /* RANDOMPLAYER_H_ */
