/*
 * RandomPlayer.cpp
 *
 *  Created on: Mar 18, 2012
 *      Author: Kristofer Leifland
 */

#include "RandomPlayer.h"
#include "../Util.h"
#include "../Board.h"

RandomPlayer::RandomPlayer() {
	// TODO Auto-generated constructor stub

}

RandomPlayer::~RandomPlayer() {
	// TODO Auto-generated destructor stub
}

Player::Move *RandomPlayer::getNextMove(const Board &board) {
	vector<int> possibleMoves = board.getPossibleMoves();
	int picked = Util::pickRandom(possibleMoves);
	return new Player::Move (*this, picked);
}
