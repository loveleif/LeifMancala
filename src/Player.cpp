/*
 * Player.cpp
 *
 *  Created on: Mar 16, 2012
 *      Author: toffe
 */

#include "Player.h"

Player::Player(const string &name) : name(name) {
}

Player::~Player() { }

const string &Player::getName() {
	return name;
}
