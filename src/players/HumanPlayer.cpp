/*
 * HumanPlayer.cpp
 *
 *  Created on: Mar 16, 2012
 *      Author: toffe
 */

#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(string &name) : super(name) {
	// TODO Auto-generated constructor stub
}

HumanPlayer::~HumanPlayer() {
	// TODO Auto-generated destructor stub
}

Player::Move *HumanPlayer::getNextMove(const Board &board) {
	// TODO Auto-generated method stub
	return new Player::Move (*this, 0);
}
