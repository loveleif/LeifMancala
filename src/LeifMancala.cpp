/*
 * LeifMancala.cpp
 *
 *  Created on: Mar 16, 2012
 *      Author: toffe
 */
#include "StandardBoard.h"
#include "HumanPlayer.h"
#include "Player.h"
#include <string>
#include <vector>
#include <iostream>
int main() {
	string name1 ("Player 1");
	string name2 ("Player 2");
	HumanPlayer *p1 = new HumanPlayer (name1);
	HumanPlayer *p2 = new HumanPlayer (name2);
	vector<Player*> players;
	players.push_back(p1);
	players.push_back(p2);

	Pit pit1 (*p1, true);
	Pit pit2 (*p2, false);
	cout << pit1 << endl;
	cout << pit2 << endl;
	pit1.add(Seed());
	pit1.add(Seed());
	pit1.add(Seed());
	pit1.add(Seed());
	pit1.add(Seed());
	pit1.add(Seed());
	pit1.add(Seed());
	pit1.add(Seed());
	pit1.add(Seed());
	pit1.add(Seed());
	pit1.add(Seed());
	pit1.add(Seed());
	pit1.add(Seed());
	cout << pit1 << endl;
	//Board *board = new StandardBoard(players, 7, 5);
	return 0;
}
