/*
 * Board.cpp
 *
 *  Created on: Mar 16, 2012
 *      Author: Kristofer Leifland
 */

#include "Board.h"
#include <iostream>
Board::Board() { }

Board::~Board() { }

std::ostream &operator<<(std::ostream &out, const Board &board) {
	string strBoard;
	return out << board.toString(strBoard);
}
