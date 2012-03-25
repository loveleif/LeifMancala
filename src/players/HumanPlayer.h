/*
 * HumanPlayer.h
 * Player that uses textual user input to generate moves in getNextMove().
 *
 *  Created on: Mar 16, 2012
 *      Author: Kristofer Leifland
 */

#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

#include "Player.h"

class HumanPlayer: public Player {
	bool firstMove;

	typedef Player super;
public:
	HumanPlayer(string &name);
	virtual ~HumanPlayer();

	Player::Move getNextMove(const Board &board);
};

#endif /* HUMANPLAYER_H_ */
