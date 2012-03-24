/*
 * HumanPlayer.cpp
 *
 *  Created on: Mar 16, 2012
 *      Author: toffe
 */

#include "HumanPlayer.h"
#include "../Board.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include "../Util.h"

HumanPlayer::HumanPlayer(string &name) : super(name) {
	// TODO Auto-generated constructor stub
}

HumanPlayer::~HumanPlayer() {
	// TODO Auto-generated destructor stub
}

Player::Move HumanPlayer::getNextMove(const Board& board) {
	vector<int> possibleMoves;
	board.getPossibleMoves(possibleMoves);

	bool getInput = true;
	int pitIndex;
	while (getInput) {
		cout << getName() << ", make your move: ";
		pitIndex = board.toAbsPitIdx(Util::readUserInt());

		vector<int>::iterator iter;
		iter = find(possibleMoves.begin(), possibleMoves.end(), pitIndex);

		if (iter == possibleMoves.end())
			cout << "Impossible move, please try again." << endl;
		else
			getInput = false;
	}
	return Player::Move(*this, pitIndex);
}
