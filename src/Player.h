/*
 * Player.h
 *
 *  Created on: Mar 16, 2012
 *      Author: toffe
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>

using namespace std;

class Player {
	const string name;

public:
	class Move {
	public:
		const Player &player;
		const int pitIndex;

		Move(const Player &player, int pitIndex) : player(player), pitIndex(pitIndex) { }
	};

	Player(const string &name);
	virtual ~Player();

	virtual Player::Move getNextMove() = 0;
};

#endif /* PLAYER_H_ */
