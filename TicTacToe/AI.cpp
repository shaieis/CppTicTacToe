#include "AI.h"

// Public functions ==================================================================
MoveValue AI::minimax(int player, Board &board, int size)
{
	if (board.IsGameOver())
		return{ -1, -1, board.checkVictory() };

	MoveValue curr = { -1,-1, (-1)*player }; // Initialize to worst possible score and look for a better one.

	// Game not over
	for (int r = 0; r < size; ++r)
	{
		for (int c = 0; c < size; ++c)
		{
			if (board.setValue({ r,c }, player)) // setValue returns true if spot is empty
			{
				//Found empty spot. Recourse minimax to thar spot with other player
				int temp = minimax((-1)*player, board, size).value;

				board.setValue({ r,c }, EMPTY_VAL);

				if (temp == player) // Found best possible score. No need to look further.
					return{ r,c,player };

				if (player*temp >= player*curr.value)
					curr = { r,c,temp };
			}
		}
	}
	return curr;
}

// Private functions =================================================================
coordinate AI::chooseNextMove(int player, Board & board, int size)
{
	MoveValue c = minimax(player, board, size);
	return { c.row, c.col };
}



