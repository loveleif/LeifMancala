/*
 * Pit.h
 *
 *  Created on: Mar 16, 2012
 *      Author: toffe
 */

#ifndef PIT_H_
#define PIT_H_

#include "Seed.h"
#include "Player.h"
#include <stack>

using namespace std;

class Pit {
	bool mIsStore;
	Player *owner;
	stack<Seed> seeds;

public:
	Pit(Player &owner, bool isStore);
	virtual ~Pit();

	void add(Seed seed);
	Seed pop();
	bool isEmpty();
	bool isStore();
	Player *getOwner();
};

#endif /* PIT_H_ */
