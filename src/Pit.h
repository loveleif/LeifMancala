/*
 * Pit.h
 * Class representing a mancala pit.
 *
 *  Created on: Mar 16, 2012
 *      Author: Kristofer Leifland
 */

#ifndef PIT_H_
#define PIT_H_

#include "Seed.h"
#include "players/Player.h"
#include <vector>

using namespace std;

class Pit {
	const bool mIsStore;
	const Player *owner;
	vector<Seed> seeds;

	friend std::ostream &operator<<(std::ostream &out, const Pit &pit);

public:
	Pit(const Player &owner, bool isStore);
	virtual ~Pit();

	/*
	 * Add seed to this pit.
	 */
	void add(Seed seed);

	/*
	 * Removes the last added seed from the pit and returns (a copy of) it.
	 */
	Seed pop();

	/*
	 * Pops and add the popped seed to the specified pit.
	 */
	void popAndPush(Pit &pushPit);

	/*
	 * Pops all seed in this pit and moves it to the specified pit.
	 */
	void popAndPushAll(Pit &pushPit);

	/*
	 * Returns true if there's no seed in this pit.
	 */
	bool isEmpty() const;

	/*
	 * Returns true if this is a store.
	 */
	bool isStore() const;

	/*
	 * Returns the owner of this pit.
	 */
	const Player& getOwner() const;

	/*
	 * Returns the value of the seed in this pit.
	 */
	int getValue() const;

	/*
	 * Return the number of seed in this pit.
	 */
	int getSeedCount() const;

	/*
	 * Returns string representation of the pit.
	 */
	std::string toString() const;
};

#endif /* PIT_H_ */
