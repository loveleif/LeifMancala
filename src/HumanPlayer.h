/*
 * HumanPlayer.h
 *
 *  Created on: Mar 16, 2012
 *      Author: toffe
 */

#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

#include "Player.h"

class HumanPlayer: public Player {
	typedef Player super;
public:
	HumanPlayer(string &name);
	virtual ~HumanPlayer();
};

#endif /* HUMANPLAYER_H_ */
