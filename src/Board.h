/*
 * Board.h
 * Base class for the game board. Board is responsible for all game logic.
 *
 *  Created on: Mar 16, 2012
 *      Author: Kristofer Leifland
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

	virtual string& toString(string& out) const = 0;
	virtual void move(Player::Move &move) = 0;
	virtual int countStoreValue(const Player &player) const = 0;
	virtual int countHouseValue(const Player &player) const = 0;
	virtual bool isGameOver() const = 0;
	virtual Player& whosTurn() const = 0;
	virtual bool isMyTurn(const Player &player) const = 0;
	virtual vector<int>& getPossibleMoves(vector<int>& possibleMoves) const = 0;
	virtual int toAbsPitIdx(int relPitIdx) const = 0;
	virtual int toRelPitIdx(int absPitIdx) const = 0;
	virtual void printScoreBoard() const = 0;
};

#endif /* BOARD_H_ */

