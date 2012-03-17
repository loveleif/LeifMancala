/*
 * Pit.cpp
 *
 *  Created on: Mar 16, 2012
 *      Author: toffe
 */

#include "Pit.h"
#include <cassert>

Pit::Pit(const Player &owner, bool isStore) : mIsStore(isStore), owner(&owner) {
}

Pit::~Pit() {
}

void Pit::add(Seed seed) {
	seeds.push_back(seed);
}

Seed Pit::pop() {
	assert(!isEmpty());
	Seed out = seeds[seeds.size() - 1];
	seeds.pop_back();
	return out;
}

bool Pit::isEmpty() const {
	return seeds.empty();
}

bool Pit::isStore() const {
	return mIsStore;
}

const Player *Pit::getOwner() const {
	return owner;
}

void Pit::popAndPush(Pit &pushPit) {
	pushPit.add(pop());
}

void Pit::popAndPushAll(Pit &pushPit) {
	while (!isEmpty())
		popAndPush(pushPit);
}

int Pit::getValue() const {
	int value = 0;
	vector<Seed>::const_iterator iter;
	for (iter = seeds.begin(); iter != seeds.end(); ++iter)
		value += iter->getValue();
	return value;
}

int Pit::getSeedCount() const {
	return seeds.size();
}
