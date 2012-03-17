/*
 * StandardBoard.h
 *
 *  Created on: Mar 16, 2012
 *      Author: toffe
 */

#ifndef STANDARDBOARD_H_
#define STANDARDBOARD_H_

#include <vector>
#include "Pit.h"
#include "Player.h"
#include "Board.h"

class StandardBoard: public Board {
	vector<Pit*> pits;
	const int pitsPerPlayer;
	const vector<Player*> players;
	int whosTurnIndex;

	int &incrPitIndex(int &pitIndex) const;
	int &decrPitIndex(int &pitIndex) const;
	int &addPitIndex(int &pitIndex, int steps) const;
	Pit *getStore(const Player &player) const;
	int sow(int fromPit);
	void capture(int lastPit, const Player &capturingPlayer);
	void nextTurn(int lastSownIndex);

public:
	StandardBoard(const vector<Player*> &players, int pitsPerPlayer, int seedsPerHouse);
	virtual ~StandardBoard();

	void move(Player::Move &move);
	int countPoints(const Player &player) const;
	bool isGameOver() const;
	Player *whosTurn() const;
};

#endif /* STANDARDBOARD_H_ */
