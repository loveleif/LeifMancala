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
	stack<Seed> seeds;
	const Player &owner;

public:
	Pit(const Player &owner, bool isStore);
	virtual ~Pit();

	void add(Seed seed);
	Seed pop();
	bool isEmpty();
	bool isStore();
};

#endif /* PIT_H_ */
