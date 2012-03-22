/*
 * LeifMancala.cpp
 *
 *  Created on: Mar 16, 2012
 *      Author: toffe
 */
#include "StandardBoard.h"
#include "players/HumanPlayer.h"
#include "players/RandomPlayer.h"
#include "players/Player.h"
#include <string>
#include <vector>
#include <iostream>
#include <time.h>
#include <cstdlib>

int readInt() {
   string strInput;
   getline(cin, strInput);
   int input = atoi(strInput.c_str());
   return input;
}

int main() {
	srand(time(NULL));


	string name ("Human");
	string name2 ("Human 2");
	string name3 ("Mr man");
	Player *p1 = new HumanPlayer (name);
	//Player *p2 = new RandomPlayer ();
	Player *p2 = new RandomPlayer;
	Player *p3 = new RandomPlayer;
	vector<Player*> players;
	players.push_back(p1);
	players.push_back(p2);
	players.push_back(p3);

	int pi;
	Player::Move *move;
	Board *board = new StandardBoard(players, 7, 5);
	while (!board->isGameOver()) {
		cout << *board << "\n\n";

		if (board->isMyTurn(*p1)) {
			//pi = readInt();
			cout << "Make move: ";
			cin >> pi;
			move = new Player::Move(*p1, board->toAbsPitIdx(pi));
			board->move(*move);
		} else {
			board->move(*board->whosTurn().getNextMove(*board));
		}
	}
	cout << "Game Over!" << endl;

	delete board;
	delete move;
	return 0;
}


