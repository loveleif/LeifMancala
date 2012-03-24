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

	virtual void move(Player::Move &move) = 0;

	/*
	 * Sums seed value of seed that are in the specified players store(s).
	 */
	virtual int countStoreValue(const Player &player) const = 0;

	/*
	 * Sums seed value of seed that are in the specified players houses.
	 */
	virtual int countHouseValue(const Player &player) const = 0;

	virtual bool isGameOver() const = 0;

	virtual Player& whosTurn() const = 0;

	virtual bool isMyTurn(const Player &player) const = 0;

	/*
	 * Returns a vector with the pit indices that can be moved by the current
	 * player.
	 */
	virtual vector<int>& getPossibleMoves(vector<int>& possibleMoves) const = 0;

	/*
	 * Converts relative pit index to absolute. Relative pit indices
	 * are what the user see.
	 */
	virtual int toAbsPitIdx(int relPitIdx) const = 0;

	/*
	 * Converts absolute pit index to relative pit index. Relative pit indices
	 * are what the user see.
	 */
	virtual int toRelPitIdx(int absPitIdx) const = 0;

	virtual void printScoreBoard() const = 0;

	/*
	 * Saves string representation of the board in the specified string. Returns
	 * reference to the string.
	 */
	virtual string& toString(string& out) const = 0;
};

#endif /* BOARD_H_ */

