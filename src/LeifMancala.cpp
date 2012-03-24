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
#include "Util.h"
#include <string>
#include <vector>
#include <iostream>
#include <time.h>
#include <cstdlib>

void playGame(Board& board);

int readInt() {
   string strInput;
   getline(cin, strInput);
   int input = atoi(strInput.c_str());
   return input;
}

void mainMenu() {
	cout << "Welcome to LeifMancala!\n"
		 << "=======================\n\n"
		 << "Menu:\n"
		 << "1. New game\n"
		 << "2. Help\n"
		 << "\nQuick Start:\n"
		 << "3. One human against one computer player\n"
		 << "4. One human against two computer players\n\n";

	int choice;
	bool choose = true;
	while (choose) {
		cout << "Make your choice: ";

		choice = Util::readUserInt();
		choose = false;
		switch (choice) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			choose = true;
			cout << "Incorrect choice. Please try again.\n";
			break;
		}
	}
}



void newStandardGame() {
	cout << "Add a human player by entering it's name and pressing <Enter>."
			" Enter a blank line to stop.\n\n";

	string playerName = "0";
	vector<Player*> players;
	int i = 0;
	while (!playerName.empty()) {
		cout << "Human player " << ++i << ": ";
		Util::readUserString(playerName);
		players.push_back(new HumanPlayer(playerName));
	}

	cout << "\n\n"
		 << "How many computer players would you like in your game: ";
	int numOfCompPlayers = Util::readUserInt();
	if (numOfCompPlayers + (int) players.size() < StandardBoard::MIN_PLAYERS) {
		cout << "You need at least " << StandardBoard::MIN_PLAYERS << " players. Computer players will automatically be added for you.\n";
		numOfCompPlayers = StandardBoard::MIN_PLAYERS -  players.size();
	}
	for (int i = 0; i < numOfCompPlayers; ++i)
		players.push_back(new RandomPlayer());

	cout << "\n\n"
		 << "How many pits would you like per player, including the store (min " << StandardBoard::MIN_PITS_PER_PLAYER << "): ";
	int pitsPerPlayer = min(Util::readUserInt(), StandardBoard::MIN_PITS_PER_PLAYER);

	cout << "\n\n"
		 << "How many seeds would you like in each pit: ";
	int seedsPerHouse = min(Util::readUserInt(), StandardBoard::MIN_SEEDS_PER_HOUSE);

	Board* board = new StandardBoard(players, pitsPerPlayer, seedsPerHouse);
	playGame(*board);
	delete board;
}

void playGame(Board& board) {
	while(!board.isGameOver()) {
		cout << board;
		Player::Move move = board.whosTurn().getNextMove(board);
		board.move(move);
	}
}

int main() {
	srand(time(NULL));

	newStandardGame();
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
			//board->move(*board->whosTurn().getNextMove(*board));
		}
	}
	cout << "Game Over!" << endl;

	delete board;
	delete move;
	return 0;
}


