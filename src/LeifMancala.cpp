/*
 * LeifMancala.cpp
 *
 *  Created on: Mar 16, 2012
 *      Author: toffe
 */
#include "StandardBoard.h"
#include "players/HumanPlayer.h"
#include "players/ComputerPlayer.h"
#include "players/Player.h"
#include <string>
#include <vector>
#include <iostream>
int main() {
	cout << "Start:\n";
	string name1 ("Player 1");
	string name2 ("Player 2");
	string name3 ("Player 3");
	HumanPlayer *p1 = new HumanPlayer (name1);
	HumanPlayer *p2 = new HumanPlayer (name2);
	HumanPlayer *p3 = new HumanPlayer (name3);
	/*
	ComputerPlayer *c1 = new ComputerPlayer ();
	ComputerPlayer *c2 = new ComputerPlayer ();
	ComputerPlayer *c3 = new ComputerPlayer ();
	ComputerPlayer *c4 = new ComputerPlayer ();
	ComputerPlayer *c5 = new ComputerPlayer ();
	ComputerPlayer *c6 = new ComputerPlayer ();
	ComputerPlayer *c7 = new ComputerPlayer ();
	ComputerPlayer *c8 = new ComputerPlayer ();
	ComputerPlayer *c9 = new ComputerPlayer ();
	ComputerPlayer *c10 = new ComputerPlayer ();
	ComputerPlayer *c11 = new ComputerPlayer ();
	ComputerPlayer *c12 = new ComputerPlayer ();
	ComputerPlayer *c13 = new ComputerPlayer ();
	ComputerPlayer *c14 = new ComputerPlayer ();
	ComputerPlayer *c15 = new ComputerPlayer ();

	cout << c1->getName() << endl;
	cout << c2->getName() << endl;
	cout << c3->getName() << endl;
	cout << c4->getName() << endl;
	cout << c5->getName() << endl;
	cout << c6->getName() << endl;
	cout << c7->getName() << endl;
	cout << c8->getName() << endl;
	cout << c9->getName() << endl;
	cout << c10->getName() << endl;
	cout << c11->getName() << endl;
	cout << c12->getName() << endl;
	cout << c13->getName() << endl;
	cout << c14->getName() << endl;
	cout << c15->getName() << endl;*/
	vector<Player*> players;
	players.push_back(p1);
	players.push_back(p2);
	players.push_back(p3);

	Pit pit1 (*p1, true);
	Pit pit2 (*p2, false);
	//cout << pit1 << endl;
	//cout << pit2 << endl;
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
	//cout << pit1 << endl;

	Board *board = new StandardBoard(players, 7, 5);
	cout << *board << endl;
	return 0;
}
