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
#include <stdexcept>
#include <string>
#include <sstream>
using namespace std;
StandardBoard::StandardBoard(const vector<Player*> &players, int pitsPerPlayer, int seedsPerHouse)
				: pitsPerPlayer(pitsPerPlayer), players(players), whosTurnIndex(0), gameOver(false) {
	// Each player needs at least one house and one store
	assert(pitsPerPlayer >= 2);

	// Create Pits and Seeds
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
	// vector<Pit*> pits - pits will get out of scope and destructed automatically
	// the vector destructor will destruct all the containing Pits.
	//
	// vector<Player*> players - will get out of scope and destructed automatically
	// the vector destructor will destruct all the containing Players.


	// TODO Auto-generated destructor stub
}

void StandardBoard::move(Player::Move &move) {
	assert(!isGameOver());
	assert(&(move.player) == &*(pits[move.pitIndex]->getOwner()));
	assert(!pits[move.pitIndex]->isEmpty());

	int lastSownIndex = sow(move.pitIndex);
	if (pits[lastSownIndex]->getSeedCount() == 1)
		capture(lastSownIndex, move.player);

	nextTurn(lastSownIndex);
}

void StandardBoard::nextTurn(int lastSownIndex) {
	if(checkGameOver())
		return;

	if (&*(pits[lastSownIndex]) == &*(getStore(*whosTurn())))
		whosTurnIndex = (whosTurnIndex + 1) % players.size();
}

bool StandardBoard::checkGameOver() {
	vector<Pit*>::iterator iter;

	for (iter = pits.begin(); iter != pits.end(); ++iter)
		if (!(*iter)->isStore() && (*iter)->getSeedCount() > 0)
			return false;
	return gameOver = true;
}

int &StandardBoard::incrPitIndex(int &pitIndex) const {
	return addPitIndex(pitIndex, 1);
}

int &StandardBoard::decrPitIndex(int &pitIndex) const {
	return addPitIndex(pitIndex, -1);
}

int &StandardBoard::addPitIndex(int &pitIndex, int steps) const {
	return pitIndex = (pitIndex + steps) % pits.size();
}

Pit *StandardBoard::getStore(const Player &player) const {
	Pit *pit;
	unsigned int pitIndex = pitsPerPlayer - 1;
	while (pitIndex <= players.size() * pitsPerPlayer) {
		pit = pits[pitIndex];
		assert(pit->isStore()); // Just to be on the safe side
		if (&*(pit->getOwner()) == &player)
			return pit;
	}
	throw logic_error("Didn't fins store.");
}

/*
 * Sows all the seed from the specified pit index. Sowing will move around the
 * board and put one seed per pit until the sowing pit is depleted.
 *
 * pitIndex - index of pit to sow from
 * returns - pit index of the last pit to get sown
 */
int StandardBoard::sow(int pitIndex) {
	Pit *fromPit = pits[pitIndex];
	while (!fromPit->isEmpty())
		pits[incrPitIndex(pitIndex)]->add(fromPit->pop());
	return pitIndex;
}

void StandardBoard::capture(int pitIndex, const Player &capturingPlayer) {
	// Captured pit is store
	if (pits[pitIndex]->isStore())
		return;

	Pit *captureStore = getStore(capturingPlayer);

	// Captured pit does not belong to capturing player
	if (&*(pits[pitIndex]->getOwner()) != &capturingPlayer) {
		pits[pitIndex]->popAndPushAll(*captureStore);
		return;
	}

	//Captured pit belongs to capturing player
	int stepsToStore = 0;
	while (!pits[decrPitIndex(pitIndex)]->isStore())
		++stepsToStore;
	addPitIndex(pitIndex, -stepsToStore);

	// Seed transaction
	pits[pitIndex]->popAndPushAll(*captureStore);
}

int StandardBoard::countPoints(const Player &player) const {
	return getStore(player)->getValue();
}

bool StandardBoard::isGameOver() const {
	return gameOver;
}

Player *StandardBoard::whosTurn() const {
	return players[whosTurnIndex];
}

string StandardBoard::toString() const {
	std::stringstream sstm;

	bool reverse = false;
	int pitIdx = 0;
	for (unsigned int playerIdx = 0; playerIdx < players.size(); ++playerIdx) {

		reverse = playerIdx % 2;

		for (int i = 0; i < pitsPerPlayer; ++i) {
			sstm << *pits[pitIdx];
			if (reverse)
				--pitIdx;
			else
				++pitIdx;

		}
		sstm << " <--- " << players[playerIdx]->getName() << endl;
		pitIdx += pitsPerPlayer + (reverse ? 1 : -1);

	}
	return sstm.str();
}


