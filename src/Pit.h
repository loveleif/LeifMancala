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
#include <vector>

using namespace std;

class Pit {
	const bool mIsStore;
	const Player *owner;
	vector<Seed> seeds;

public:
	Pit(const Player &owner, bool isStore);
	virtual ~Pit();

	void add(Seed seed);
	Seed pop();
	void popAndPush(Pit &pushPit);
	void popAndPushAll(Pit &pushPit);
	bool isEmpty() const;
	bool isStore() const;
	const Player *getOwner() const;
	int getValue() const;
	int getSeedCount() const;
};

#endif /* PIT_H_ */
