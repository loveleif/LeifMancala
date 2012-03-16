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

	int &incrPitIndex(int &pitIndex);
	int &decrPitIndex(int &pitIndex);
	int &addPitIndex(int &pitIndex, int steps);
	Pit *getStore(Player &player);
	int sow(int fromPit);
	void capture(int lastPit, Player &capturingPlayer);

public:
	StandardBoard(const vector<Player*> &players, int pitsPerPlayer, int seedsPerHouse);
	virtual ~StandardBoard();

	void move(Player::Move &move);
	int countPoints(const Player &player);
	bool isGameOver();
};

#endif /* STANDARDBOARD_H_ */
