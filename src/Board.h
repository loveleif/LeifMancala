/*
 * Board.h
 *
 *  Created on: Mar 16, 2012
 *      Author: toffe
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include "players/Player.h"


class Board {
	friend std::ostream &operator<<(std::ostream &out, const Board &board);
public:
	Board();
	virtual ~Board();

	virtual std::string toString() const = 0;
	virtual void move(Player::Move &move) = 0;
	virtual int countPoints(const Player &player) const = 0;
	virtual bool isGameOver() const = 0;
	virtual Player *whosTurn() const = 0;
	virtual bool isMyTurn(const Player &player) const = 0;
	virtual vector<int> getPossibleMoves() const = 0;

};

#endif /* BOARD_H_ */

