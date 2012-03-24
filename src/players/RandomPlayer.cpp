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

Player::Move& RandomPlayer::getNextMove(Player::Move& input, const Board &board) {
	vector<int> possibleMoves;
	board.getPossibleMoves(possibleMoves);
	int picked = Util::pickRandom(possibleMoves);

	input = Player::Move (*this, picked);
	return input;
}
