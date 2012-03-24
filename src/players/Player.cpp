/*
 * Player.cpp
 *
 *  Created on: Mar 16, 2012
 *      Author: Kristofer Leifland
 */

#include "Player.h"
#include <iostream>
#include <iomanip>

Player::Player(const string &name) : name(name) {
}

Player::~Player() { }

const string &Player::getName() const {
	return name;
}

std::ostream &operator<<(std::ostream &out, const Player &player) {
	return out << player.getName();
}
