/*
 * StandardBoard.cpp
 *
 *  Created on: Mar 16, 2012
 *      Author: toffe
 */

#include "StandardBoard.h"
#include "Player.h"
#include <vector>
#include <cassert>
using namespace std;
StandardBoard::StandardBoard(const vector<Player*> &players, int pitsPerPlayer, int seedsPerHouse) {
	// Each player needs at least one house and one store
	assert(pitsPerPlayer >= 2);

	Pit *house;
	vector<Player*>::const_iterator iter;
	for (iter = players.begin(); iter != players.end(); ++iter) {
		for (int iPit = 0; iPit < pitsPerPlayer - 1; ++iPit) {
			house = new Pit(**iter, false); // Create house
			for (int iSeed = 0; iSeed < seedsPerHouse; ++iSeed)
				house->add(Seed()); // Add Seed to House
			pits.push_back(house); // Add House to Board
		}
		pits.push_back(new Pit(**iter, true)); // Add store
	}
}

StandardBoard::~StandardBoard() {
	// TODO Auto-generated destructor stub
}

void StandardBoard::move(Player::Move &move) {
	// TODO Auto-generated method stub
}

int StandardBoard::countPoints(const Player &player) {
	// TODO Auto-generated method stub
	return 0;
}

bool StandardBoard::isGameOver() {
	// TODO Auto-generated method stub
	return false;
}
