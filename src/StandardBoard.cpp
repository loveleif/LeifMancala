/*
 * StandardBoard.cpp
 *
 *  Created on: Mar 16, 2012
 *      Author: Kristofer Leifland
 */

#include "StandardBoard.h"
#include "Util.h"
#include <cassert>
#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

const char StandardBoard::BLANK_PIT[] = "        ";
const int StandardBoard::MIN_PLAYERS = 2;
const int StandardBoard::MIN_PITS_PER_PLAYER = 3;
const int StandardBoard::MIN_SEEDS_PER_HOUSE = 1;

StandardBoard::StandardBoard(const vector<Player*> &players, int pitsPerPlayer, int seedsPerHouse)
				: pitsPerPlayer(pitsPerPlayer), players(players), whosTurnIndex(0), gameOver(false) {
	assert(pitsPerPlayer >= MIN_PITS_PER_PLAYER);
	assert(seedsPerHouse >= MIN_SEEDS_PER_HOUSE);

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
}

void StandardBoard::move(Player::Move &move) {
	assert(!isGameOver());
	assert(&move.getPlayer() == &(pits[move.getPitIndex()]->getOwner()));
	assert(!pits[move.getPitIndex()]->isEmpty());
	assert(&move.getPlayer() == &whosTurn());

	log() << "[MOVE]: " << move.getPlayer().getName() << " moves on pit " << toRelPitIdx(move.getPitIndex()) << endl;

	int lastSownIndex = sow(move.getPitIndex());

	if (pits[lastSownIndex]->getSeedCount() == 1)
		capture(lastSownIndex, move.getPlayer());

	nextTurn(lastSownIndex);
}

int StandardBoard::sow(int pitIndex) {
	Pit *fromPit = pits[pitIndex];
	while (!fromPit->isEmpty())
		fromPit->popAndPush(*pits[incrPitIndex(pitIndex)]);
	return pitIndex;
}

void StandardBoard::capture(int pitIndex, const Player& capturingPlayer) {
	// Captured pit is store
	if (pits[pitIndex]->isStore())
		return;

	Pit *captureStore = &getStore(capturingPlayer);
	int relPitIdx = toRelPitIdx(pitIndex);

	if (&pits[pitIndex]->getOwner() != &capturingPlayer) {
		// Captured pit does not belong to capturing player
		pits[pitIndex]->popAndPushAll(*captureStore);
		log() << "[CAPTURE]: " << capturingPlayer << " captures " << pits[pitIndex]->getOwner() << "'s pit " << relPitIdx << endl;
		return;
	}

	// Captured pit belongs to capturing player
	for (unsigned int i = 0; i < pits.size(); ++i) {
		if (toRelPitIdx(i) == relPitIdx)
			pits[i]->popAndPushAll(*captureStore);
	}
	log() << "[CAPTURE]: " << capturingPlayer << " captures all pits on column " << toRelPitIdx(pitIndex) << endl;
}

void StandardBoard::printScoreBoard() const {
	cout << "SCOREBOARD\n"
		 << "==========\n\n";
	vector<Player*> scoreboardPlayers (players);
	sort(scoreboardPlayers.begin(), scoreboardPlayers.end(), *this);

	vector<Player*>::iterator iterPl;
	for (iterPl = scoreboardPlayers.begin(); iterPl != scoreboardPlayers.end(); ++iterPl) {
		cout << (**iterPl).getName() << ": " << getStore(**iterPl).getValue() << endl;
	}
}

void StandardBoard::nextTurn(int lastSownIndex) {
	if(checkGameOver())
		return;

	if (&*pits[lastSownIndex] != &getStore(whosTurn())) {
		whosTurnIndex = (whosTurnIndex + 1) % players.size();
		log() << "[TURN]: " << whosTurn() << " get another turn." << endl;
	} else {
		log() << "[TURN]: " << whosTurn() << "'s turn." << endl;
	}
}

void StandardBoard::endGame() {
	vector<Pit*>::iterator iter;

	// All remaining Seed will be moved to the current owners store
	for (iter = pits.begin(); iter != pits.end(); ++iter) {
		if (!(**iter).isStore()) {
			(**iter).popAndPushAll(getStore((**iter).getOwner()));
		}
	}
	log() << "------- Game Over! -------\n";
	gameOver = true;
}

bool StandardBoard::operator() (const Player* p1, const Player* p2) const {
	return getStore(*p1).getValue() > getStore(*p2).getValue();
}

bool StandardBoard::checkGameOver() {
	vector<Player*>::const_iterator iter;

	for (iter = players.begin(); iter != players.end(); ++iter) {
		if (countHouseValue(**iter) == 0) {
			endGame();
			return isGameOver();
		}
	}
	return isGameOver();
}

int StandardBoard::countStoreValue(const Player& player) const {
	return getStore(player).getValue();
}

int StandardBoard::countHouseValue(const Player& player) const {
	vector<Pit*>::const_iterator iter;
	bool okToReturn = false;
	int houseValue = 0;
	for (iter = pits.begin(); iter != pits.end(); ++iter) {
		if (&(**iter).getOwner() == &player && !(**iter).isStore()) {
			houseValue += (**iter).getValue();
			okToReturn = true;
		} else if (okToReturn) {
			return houseValue;
		}
	}
	throw logic_error("Didn't find Player.");
}

int& StandardBoard::incrPitIndex(int &pitIndex) const {
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
		if (&(pit->getOwner()) == &player)
			return *pit;
		pitIndex += pitsPerPlayer;
	}
	throw logic_error("Didn't find store.");
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

string& StandardBoard::indexBar(string& out, unsigned int indent) const {
	stringstream sstm;
	sstm << string(indent, ' ');
	for (int i = 0; i < pitsPerPlayer - 1; ++i)
		sstm << "   " << i+1 << "  ";
	sstm << "\n";
	sstm << string(indent, ' ');
	for (int i = 0; i < pitsPerPlayer - 1; ++i)
		sstm << "-------";
	sstm << "\n" << endl;
	out = sstm.str();
	return out;
}

string& StandardBoard::toString2Players(string& out) const {
	std::stringstream sstm;
	string houses, tmp;

	sstm << indexBar(tmp, 8);

	// Player 1 houses
	pitsToString(houses, 0, pitsPerPlayer - 1);
	sstm << BLANK_PIT << "--->\n";
	sstm << BLANK_PIT << houses << BLANK_PIT;

	// Player 1 name
	bool playerZeroTurn = isMyTurn(*players[0]);
	sstm << (playerZeroTurn ? "  ->" : "    ")
		 << players[0]->getName()
		 << (playerZeroTurn ? "<-  " : "    ")
		 << "\n";

	// Player 1+2 stores
	sstm << *pits[pitsPerPlayer - 1] << string (houses.size(), ' ') << *pits[2 * pitsPerPlayer - 1] << endl;

	// Player 2 houses
	pitsToString(houses, pits.size() - 2, -(pitsPerPlayer - 1));
	sstm << BLANK_PIT << houses << BLANK_PIT;


	// Player 2 name
	sstm << (!playerZeroTurn ? "  ->" : "    ")
		 << players[1]->getName()
		 << (!playerZeroTurn ? "<-  " : "    ")
		 << "\n";

	sstm << string (8 + houses.size() - 4, ' ') << "<---" << "\n";

	out = sstm.str();
	return out;
}

string& StandardBoard::toString(string& out) const {
	if (players.size() == 2)
		return toString2Players(out);

	stringstream sstm;
	string houses, tmp;

	sstm << indexBar(tmp, 0);

	bool reverse = false, playerTurn;
	int startIdx = 0, n;
	for (unsigned int playerIdx = 0; playerIdx < players.size(); ++playerIdx) {
		reverse = (playerIdx % 2) != 0;
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
		playerTurn = isMyTurn(*players[playerIdx]);
		sstm << (playerTurn ? "  ->" : "    ")
			 << players[playerIdx]->getName()
			 << (playerTurn ? "<-  " : "    ")
			 << "\n";

		if (!reverse) {
			sstm << string(houses.size() - 8, ' ');
		}
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
 *  is not empty. The supplied vector will be
 */
vector<int>& StandardBoard::getPossibleMoves(vector<int>& possibleMoves) const {
	int playerPitStart = whosTurnIndex * pitsPerPlayer;
	int playerPitEnd = playerPitStart + pitsPerPlayer;
	for (int pitIdx = playerPitStart; pitIdx < playerPitEnd; ++pitIdx)
		if (!pits[pitIdx]->isEmpty() && !pits[pitIdx]->isStore())
			possibleMoves.push_back(pitIdx);
	return possibleMoves;
}

int StandardBoard::toAbsPitIdx(int relPitIdx) const {
	if (relPitIdx < 1 || relPitIdx >= pitsPerPlayer)
		return -10000; // Returns useless pitindex

	bool reverse = (whosTurnIndex % 2) != 0;
	if (!reverse)
		return relPitIdx + whosTurnIndex * pitsPerPlayer - 1;
	else
		return -relPitIdx - 1 + pitsPerPlayer * (1 + whosTurnIndex);
}

int StandardBoard::toRelPitIdx(int absPitIdx) const {
	int turnIndex = absPitIdx / pitsPerPlayer;
	bool reverse = (turnIndex % 2) != 0;
	if (!reverse)
		return absPitIdx - turnIndex * pitsPerPlayer + 1;
	else
		return - absPitIdx + (turnIndex + 1) * pitsPerPlayer - 1;
}

ostream &StandardBoard::log() {
	return cout;
}

