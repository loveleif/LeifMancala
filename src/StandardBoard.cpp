/*
 * StandardBoard.cpp
 *
 *  Created on: Mar 16, 2012
 *      Author: toffe
 */

#include "StandardBoard.h"
#include "players/Player.h"
#include <vector>
#include <cassert>
#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>
#include "Util.h"
using namespace std;

const char StandardBoard::BLANK_PIT[] = "        ";

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
	assert(&move.getPlayer() == &*(pits[move.getPitIndex()]->getOwner()));
	assert(!pits[move.getPitIndex()]->isEmpty());

	log() << "Move: " << move.getPlayer().getName() << " on pit " << toRelPitIdx(move.getPitIndex()) << " (relative)" << endl;

	int lastSownIndex = sow(move.getPitIndex());
	if (pits[lastSownIndex]->getSeedCount() == 1)
		capture(lastSownIndex, move.getPlayer());

	nextTurn(lastSownIndex);
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

	Pit *captureStore = &getStore(capturingPlayer);

	if (&*pits[pitIndex]->getOwner() != &capturingPlayer) {
		// Captured pit does not belong to capturing player
		pits[pitIndex]->popAndPushAll(*captureStore);
		log() << "Capture: " << capturingPlayer << " on pit " << pitIndex << " (absolute)" << endl;
		return;
	}

	// Captured pit belongs to capturing player

	int tmpPitIdx = pitIndex;
	int stepsToLastStore = 1;
	while (!pits[decrPitIndex(tmpPitIdx)]->isStore())
		++stepsToLastStore;
	int stepstoNextStore = pitsPerPlayer - stepsToLastStore;

	// Seed transactions
	log() << "Capture: " << capturingPlayer << " on pits ";
	for (unsigned int i = 0; i < players.size(); ++i) {
		if (i % 2 == 0)
			addPitIndex(pitIndex, 2 * stepstoNextStore);
		else
			addPitIndex(pitIndex, 2 * stepsToLastStore);

		pits[pitIndex]->popAndPushAll(*captureStore);
		log() << pitIndex << " ";
	}
	log() << " (absolute)" << endl;
}

void StandardBoard::nextTurn(int lastSownIndex) {
	if(checkGameOver())
		return;

	if (&*pits[lastSownIndex] != &getStore(whosTurn()))
		whosTurnIndex = (whosTurnIndex + 1) % players.size();

	log() << whosTurn() << "'s turn." << endl;
}

bool StandardBoard::checkGameOver() {
	vector<Pit*>::iterator iter;

	for (iter = pits.begin(); iter != pits.end(); ++iter) {
		if (!(*iter)->isStore() && (*iter)->getSeedCount() > 0)
			return false;
	}
	return gameOver = true;
}

int &StandardBoard::incrPitIndex(int &pitIndex) const {
	return addPitIndex(pitIndex, 1);
}

int &StandardBoard::decrPitIndex(int &pitIndex) const {
	return addPitIndex(pitIndex, -1);
}

int &StandardBoard::addPitIndex(int &pitIndex, int steps) const {
	return pitIndex = Util::mod(pitIndex + steps, pits.size());
}

Pit& StandardBoard::getStore(const Player &player) const {
	Pit *pit;
	unsigned int pitIndex = pitsPerPlayer - 1;
	while (pitIndex < pits.size()) {
		pit = pits[pitIndex];
		assert(pit->isStore()); // Just to be on the safe side
		if (&*(pit->getOwner()) == &player)
			return *pit;
		pitIndex += pitsPerPlayer;
	}
	throw logic_error("Didn't find store.");
}

int StandardBoard::countPoints(const Player &player) const {
	return getStore(player).getValue();
}

bool StandardBoard::isGameOver() const {
	return gameOver;
}

Player& StandardBoard::whosTurn() const {
	return *players[whosTurnIndex];
}

string& StandardBoard::pitsToString(string& out, unsigned int fromIdx, int n) const {
	stringstream sstm;
	int pitStep = (n < 0) ? -1 : 1;
	n = abs(n);
	int pitIdx = fromIdx;
	for (int i = 0; i < n; ++i) {
		sstm << *pits[pitIdx];
		addPitIndex(pitIdx, pitStep);
	}

	out = sstm.str();
	return out;
}

string& StandardBoard::indexBar(string& out) const {
	stringstream sstm;
	for (int i = 0; i < pitsPerPlayer - 1; ++i)
		sstm << "   " << i+1 << "  ";
	sstm << "\n";
	sstm << "------------------------------------";
	sstm << "\n" << endl;
	out = sstm.str();
	return out;
}

string& StandardBoard::toString2Players(string& out) const {
	std::stringstream sstm;
	string houses, tmp;

	sstm << indexBar(tmp);

	// Player 1 houses
	pitsToString(houses, 0, pitsPerPlayer - 1);
	sstm << BLANK_PIT << "--->\n";
	sstm << BLANK_PIT << houses << BLANK_PIT << " " << players[0]->getName() << "\n";

	// Player 1+2 stores
	sstm << *pits[pitsPerPlayer - 1] << string (houses.size(), ' ') << *pits[2 * pitsPerPlayer - 1] << endl;

	// Player 2 houses
	pitsToString(houses, pits.size() - 2, -(pitsPerPlayer - 1));
	sstm << BLANK_PIT << houses << BLANK_PIT << players[1]->getName() << "\n";
	sstm << string (8 + houses.size() - 4, ' ') << "<---" << "\n";

	out = sstm.str();
	return out;
}

string& StandardBoard::toString(string& out) const {
	if (players.size() == 2)
		return toString2Players(out);

	stringstream sstm;
	string houses, tmp;

	sstm << indexBar(tmp);

	bool reverse = false, playerTurn;
	int startIdx = 0, n;
	for (unsigned int playerIdx = 0; playerIdx < players.size(); ++playerIdx) {
		reverse = playerIdx % 2;
		if (reverse)
			startIdx = (playerIdx + 1) * pitsPerPlayer - 2;
		else
			startIdx = playerIdx * pitsPerPlayer;

		n = (pitsPerPlayer - 1) * (reverse ? -1 : 1);
		pitsToString(houses, startIdx, n);

		if (reverse)
			sstm << string(houses.size() - 4, ' ');
		sstm << (reverse ? "<---" : "--->") << "\n"
			 << houses;

		// Player name
		playerTurn = this->isMyTurn(*players[playerIdx]);
		sstm << (playerTurn ? "  ->" : "    ")
			 << players[playerIdx]->getName()
			 << (playerTurn ? "<-  " : "    ")
			 << "\n";

		if (!reverse)
			sstm << string(houses.size() - 8, ' ');
		sstm << *pits[(playerIdx + 1) * pitsPerPlayer - 1] << "\n";

	}

	out = sstm.str();
	return out;
}

bool StandardBoard::isMyTurn(const Player &player) const {
	return &player == &whosTurn();
}

/*
 *  Adds pit indices that are "moveable" to the supplied vector. A pit is
 *  movable if it belongs to the current player in turn, is not a store and
 *  is not empty.
 */
vector<int>& StandardBoard::getPossibleMoves(vector<int>& possibleMoves) const {
	possibleMoves.clear();

	int playerPitStart = whosTurnIndex * pitsPerPlayer;
	int playerPitEnd = playerPitStart + pitsPerPlayer;
	for (int pitIdx = playerPitStart; pitIdx < playerPitEnd; ++pitIdx)
		if (!pits[pitIdx]->isEmpty() && !pits[pitIdx]->isStore())
			possibleMoves.push_back(pitIdx);
	return possibleMoves;
}

int StandardBoard::toAbsPitIdx(int relPitIdx) const {
	assert(relPitIdx < pitsPerPlayer);

	bool reverse = whosTurnIndex % 2;
	if (!reverse)
		return relPitIdx + whosTurnIndex * pitsPerPlayer - 1;
	else
		return -relPitIdx - 1 + pitsPerPlayer * (1 + whosTurnIndex);
}

int StandardBoard::toRelPitIdx(int absPitIdx) const {
	int turnIndex = absPitIdx / pitsPerPlayer;
	bool reverse = turnIndex % 2;
	if (!reverse)
		return absPitIdx - turnIndex * pitsPerPlayer + 1;
	else
		return - absPitIdx + (turnIndex + 1) * pitsPerPlayer - 1;
}

ostream &StandardBoard::log() {
	return cout;
}
