/*
 * StandardBoard.h
 * Provides game logic for the standard LeifMancala game.
 *
 *  Created on: Mar 16, 2012
 *      Author: Kristofer Leifland
 */

#ifndef STANDARDBOARD_H_
#define STANDARDBOARD_H_

#include "Pit.h"
#include "players/Player.h"
#include "Board.h"

class StandardBoard: public Board {
	vector<Pit*> pits;
	const int pitsPerPlayer;
	const vector<Player*> players;
	int whosTurnIndex;
	bool gameOver;
	static const char BLANK_PIT[];

	friend std::ostream &operator<<(std::ostream &out, const StandardBoard &board);

	/*
	 * Sets the specified pit index to the next pit index.
	 */
	int& incrPitIndex(int& pitIndex) const;

	/*
	 * Sets the specified pit index to the previous pit index.
	 */
	int& decrPitIndex(int& pitIndex) const;

	/*
	 * Sets the specified pit index a given number of steps away. steps can be
	 * negative.
	 */
	int& addPitIndex(int& pitIndex, int steps) const;

	/*
	 * Returns the store of the specified player.
	 */
	Pit& getStore(const Player& player) const;

	/*
	 * Sows all the seed from the specified pit index. Sowing will move around the
	 * board and put one seed per pit until the sowing pit is depleted.
	 *
	 * pitIndex - index of pit to sow from
	 * returns - pit index of the last pit to get sown
	 */
	int sow(int fromPit);

	/*
	 * Captures the seed in the specified pit index to the store of capturingPlayer.
	 */
	void capture(int lastPit, const Player& capturingPlayer);

	/*
	 * Next turn.
	 */
	void nextTurn(int lastSownIndex);

	/*
	 * Will go through the board to check if game is over. The game is over when
	 * at least one player has no seed in any of his or her houses.
	 */
	bool checkGameOver();

	/*
	 * Sets the specified string to a representation of a two player board.
	 */
	string& toString2Players(string &out) const;

	/*
	 * Sets the specified string to a representation of some pits.
	 *
	 * out - output
	 * fromIdx - pit index of the first pit
	 * n - number of pits to include (can be negative)
	 */
	string& pitsToString(string &out, unsigned int fromIdx, int n) const;

	/*
	 * Sets the specified string to a relative pit index column heading
	 */
	string& indexBar(string &out, unsigned int indent) const;

	/*
	 * ostream for logging.
	 */
	ostream &log();

	/*
	 * Ends the game.
	 */
	void endGame();


public:
	static const int MIN_PLAYERS;
	static const int MIN_PITS_PER_PLAYER;
	static const int MIN_SEEDS_PER_HOUSE;

	/*
	 * Constructs a StandardBoard. pitsPerPlayer has to be >= MIN_PITS_PER_PLAYER
	 * seedsPerHouse has to be >= MIN_SEEDS_PER_HOUSE.
	 */
	StandardBoard(const vector<Player*> &players, int pitsPerPlayer, int seedsPerHouse);
	virtual ~StandardBoard();

	/*
	 * Methods inherited from Board, see Board.h for comments.
	 */
	void move(Player::Move& move);
	int countStoreValue(const Player& player) const;
	int countHouseValue(const Player& player) const;
	bool isGameOver() const;
	Player& whosTurn() const;
	bool isMyTurn(const Player& player) const;
	vector<int>& getPossibleMoves(vector<int>& possibleMoves) const;
	string& toString(string& out) const;
	int toAbsPitIdx(int relPitIdx) const;
	int toRelPitIdx(int absPitIdx) const;
	void printScoreBoard() const;

	/*
	 * Used for sorting players depending on score.
	 */
	bool operator() (const Player* p1, const Player* p2) const;
};

#endif /* STANDARDBOARD_H_ */
