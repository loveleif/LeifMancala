/*
 * Board.h
 *
 *  Created on: Mar 16, 2012
 *      Author: toffe
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "Player.h"


class Board {
public:
	Board();
	virtual ~Board();

	virtual void move(Player::Move &move) = 0;
	virtual int countPoints(const Player &player) const = 0;
	virtual bool isGameOver() const = 0;
};

#endif /* BOARD_H_ */

