/*
 * HumanPlayer.cpp
 *
 *  Created on: Mar 16, 2012
 *      Author: Kristofer Leifland
 */

#include "HumanPlayer.h"
#include "../Board.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include "../Util.h"

HumanPlayer::HumanPlayer(string &name) : super(name), firstMove(true) {
}

HumanPlayer::~HumanPlayer() {
	// TODO Auto-generated destructor stub
}

Player::Move HumanPlayer::getNextMove(const Board& board) {
	vector<int> possibleMoves;
	vector<int>::iterator iter;
	board.getPossibleMoves(possibleMoves);

	bool getInput = true;
	int pitIndex;
	while (getInput) {
		cout << getName();
		if (!firstMove) {
			cout << ", make your move: ";
		} else {
			// A little help on the way for newbies
			cout << ", make your move (possible moves are";
			for (iter = possibleMoves.begin(); iter != possibleMoves.end(); ++iter)
				cout << " " <<  board.toRelPitIdx(*iter);
			cout << "):";
			firstMove = false;
		}
		pitIndex = board.toAbsPitIdx(Util::readUserInt());

		iter = find(possibleMoves.begin(), possibleMoves.end(), pitIndex);

		if (iter == possibleMoves.end())
			cout << "Impossible move, please try again." << endl;
		else
			getInput = false;
	}

	return Player::Move(*this, pitIndex);
}
