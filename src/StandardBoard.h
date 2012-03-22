/*
 * StandardBoard.h
 *
 *  Created on: Mar 16, 2012
 *      Author: toffe
 */

#ifndef STANDARDBOARD_H_
#define STANDARDBOARD_H_

#include "Pit.h"
#include "players/Player.h"
#include "Board.h"
#include <vector>
#include <string>


class StandardBoard: public Board {
	vector<Pit*> pits;
	const int pitsPerPlayer;
	const vector<Player*> players;
	int whosTurnIndex;
	bool gameOver;
	static const char BLANK_PIT[];

	friend std::ostream &operator<<(std::ostream &out, const StandardBoard &board);

	int &incrPitIndex(int &pitIndex) const;
	int &decrPitIndex(int &pitIndex) const;
	int &addPitIndex(int &pitIndex, int steps) const;
	Pit *getStore(const Player &player) const;
	int sow(int fromPit);
	void capture(int lastPit, const Player &capturingPlayer);
	void nextTurn(int lastSownIndex);
	bool checkGameOver();
	string toString2Players() const;
	string pitsToString(unsigned int fromIdx, int n) const;
	string indexBar() const;
	ostream &log();

public:
	StandardBoard(const vector<Player*> &players, int pitsPerPlayer, int seedsPerHouse);
	virtual ~StandardBoard();

	void move(Player::Move &move);
	int countPoints(const Player &player) const;
	bool isGameOver() const;
	Player *whosTurn() const;
	bool isMyTurn(const Player &player) const;
	vector<int> getPossibleMoves() const;
	std::string toString() const;
	int toAbsPitIdx(int relPitIdx) const;
	int toRelPitIdx(int absPitIdx) const;
};

#endif /* STANDARDBOARD_H_ */
