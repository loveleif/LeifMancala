/*
 * LeifMancala.cpp
 *
 *  Created on: Mar 16, 2012
 *      Author: Kristofer Leifland
 */

#include "StandardBoard.h"
#include "players/HumanPlayer.h"
#include "players/RandomPlayer.h"
#include "players/Player.h"
#include "Util.h"
#include <string>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <iostream>

void playGame(Board& board);
void newStandardGame();
void newQuickGame(int computerPlayers);
void help();

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
			newStandardGame();
			break;
		case 2:
			help();
			break;
		case 3:
			newQuickGame(1);
			break;
		case 4:
			newQuickGame(2);
			break;
		default:
			choose = true;
			cout << "Incorrect choice. Please try again.\n";
			break;
		}
	}
}

void newQuickGame(int computerPlayers) {
	string playerName;
	vector<Player*> players;
	playerName = "Puny Human";
	players.push_back(new HumanPlayer(playerName));
	for (int i = 0; i < computerPlayers; ++i)
		players.push_back(new RandomPlayer());

	int pitsPerPlayer = 6;
	int seedsPerHouse = 7;

	Board* board = new StandardBoard(players, pitsPerPlayer, seedsPerHouse);
	playGame(*board);
	delete board;
}

void newStandardGame() {
	cout << "Add a human player by entering it's name and pressing <Enter>."
			" Enter a blank line to stop.\n\n";
	bool readHumanPlayers = true;
	string playerName ("0");
	vector<Player*> players;
	int i = 0;
	while (readHumanPlayers) {
		cout << "Human player " << ++i << ": ";
		Util::readUserString(playerName);
		if (playerName.empty())
			readHumanPlayers = false;
		else
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
	int pitsPerPlayer = max(Util::readUserInt(), StandardBoard::MIN_PITS_PER_PLAYER);

	cout << "\n\n"
		 << "How many seeds would you like in each pit: ";
	int seedsPerHouse = max(Util::readUserInt(), StandardBoard::MIN_SEEDS_PER_HOUSE);

	cout << pitsPerPlayer << endl << seedsPerHouse << endl;
	for (unsigned int i = 0; i < players.size(); ++i)
		cout << i << " " << players[i]->getName() << endl;
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
	board.printScoreBoard();
}

int main() {
	srand(time(NULL));
	//newStandardGame();
	mainMenu();
}

void help() {

}


