/*
 * Pit.cpp
 *
 *  Created on: Mar 16, 2012
 *      Author: toffe
 */

#include "Pit.h"

Pit::Pit(Player &owner, bool isStore) : mIsStore(isStore), owner(&owner) {
}

Pit::~Pit() {
}

void Pit::add(Seed seed) {
	seeds.push(seed);
}

Seed Pit::pop() {
	Seed out = seeds.top();
	seeds.pop();
	return out;
}

bool Pit::isEmpty() {
	return seeds.empty();
}

bool Pit::isStore() {
	return mIsStore;
}

Player *Pit::getOwner() {
	return owner;
}
