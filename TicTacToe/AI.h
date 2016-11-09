#pragma once
#include "Board.h"

struct MoveValue
{
	int row, col, value;
};

class AI
{
public:
	static coordinate chooseNextMove(int player, Board &board, int size);

private:
	static MoveValue minimax(int player, Board &board, int size);
	
};

