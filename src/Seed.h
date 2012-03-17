/*
 * Seed.h
 *
 *  Created on: Mar 16, 2012
 *      Author: Kristofer Leifland
 */

#ifndef SEED_H_
#define SEED_H_

class Seed {
	int value;
	const static int DEFAULT_VALUE = 1;
public:
	Seed(int value = DEFAULT_VALUE) {
		this->value = value;
	}

	virtual ~Seed() { }

	int getValue() const {
		return value;
	}
};

#endif /* SEED_H_ */
