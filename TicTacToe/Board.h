#pragma once
#include <vector>

// Board values
const int EMPTY_VAL = 0;  // Must be zero
const int X_VAL = 1;
const int O_VAL = (-1) * X_VAL;  // Must be opposite of X_VAL


struct coordinate
{
	int row, col;
};

class Board
{

public:
	// Constructor
	Board(int size);

	int getSize() const { return m_size; }
	int getValue(const coordinate &c) const { return m_board[c.row][c.col]; }

	// Returns true if place was empty, false if place was occupied or value is not valid
	bool setValue(const coordinate &c, int value);

	// Returns X_VAL if X has won, O_VAL if O has won, TIE_VAL if tie OR game is not over.
	int checkVictory() const;

	// Returns true if game is over (someone won, or there was a tie)
	bool IsGameOver() const;

	// Returns true if coordinate is empty
	bool isEmpty(const coordinate &c) const 
	{ 
		return ((getValue(c) == EMPTY_VAL) ? true : false); 
	}

	// Returns true if board is full
	bool isBoardFull() const
	{
		return (((m_size*m_size) == m_numOfEntries) ? true : false);
	}

	// Clear the board
	void clear();

private:
	// Member variables-------------------
	int m_size; // size of board
	int m_status; // status of board (is there a winner etc..) updates in setValue()
	int m_numOfEntries; // number of signs (X, O) in board

	std::vector< std::vector<int> > m_board;

	// Member functions-------------------

	// Calculates the status of the board
	void calcStatus();

	void optimized_calcStatus(coordinate latest);
};

