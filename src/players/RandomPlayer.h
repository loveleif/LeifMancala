/*
 * RandomPlayer.h
 * Random player picks moves on random.
 *
 *  Created on: Mar 18, 2012
 *      Author: Kristofer Leifland
 */

#ifndef RANDOMPLAYER_H_
#define RANDOMPLAYER_H_

#include "ComputerPlayer.h"

class RandomPlayer: public ComputerPlayer {
public:
	RandomPlayer();
	virtual ~RandomPlayer();

	Player::Move getNextMove(const Board &board);
};

#endif /* RANDOMPLAYER_H_ */
