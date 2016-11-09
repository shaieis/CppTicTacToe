#include "Board.h"

// Ctor ==============================================================================
Board::Board(int size)
{
	m_size = size;
	m_board.resize(size, std::vector<int>(size, EMPTY_VAL));
	
	m_numOfEntries = 0;

}


// Public functions ==================================================================
bool Board::setValue(const coordinate &c, int value)
{

	if (value == EMPTY_VAL) 
	{
		if (m_board[c.row][c.col] != EMPTY_VAL) // If place is already empty do nothing
		{
			m_board[c.row][c.col] = value;
			--m_numOfEntries;
			calcStatus(); 
		}
		return true;
	}

	// Check if value is valid
	if (value != X_VAL && value != O_VAL)
		return false;

	if (m_board[c.row][c.col] == EMPTY_VAL)
	{
		m_board[c.row][c.col] = value;
		++m_numOfEntries;
		optimized_calcStatus(c);
		
		return true;
	}
	
	// Place is not empty
	return false;
}

int Board::checkVictory() const
{
	return m_status;
}

bool Board::IsGameOver() const
{
	return( (checkVictory() != EMPTY_VAL) || isBoardFull() );
	
}

void Board::clear()
{
	// Empty board
	for (int r = 0; r < m_size; ++r)
		for (int c = 0; c < m_size; ++c)
			m_board[r][c] = EMPTY_VAL;

	m_numOfEntries = 0;

	// Change board status
	m_status = EMPTY_VAL;

}


// Private functions =================================================================
void Board::calcStatus()
{
	int temp;
	bool foundVictory;

	// Check rows
	for (int i = 0; i < m_size; ++i)
	{
		foundVictory = true;
		temp = m_board[i][0];
		if (temp == EMPTY_VAL)
			continue;

		for (int j = 1; j < m_size; ++j)
		{
			if (temp != m_board[i][j])
			{
				foundVictory = false;
				break;
			}
		}

		if (foundVictory) 
		{
			m_status = temp;
			return; // Found a winner
		}
			
	}

	// Check colums
	for (int j = 0; j < m_size; ++j)
	{
		foundVictory = true;
		temp = m_board[0][j];
		if (temp == EMPTY_VAL)
			continue;

		for (int i = 1; i < m_size; ++i)
		{
			if (temp != m_board[i][j])
			{
				foundVictory = false;
				break;
			}
		}
		if (foundVictory)
		{
			m_status = temp; // Found a winner
			return;
		}
	}

	// Check first diagonal
	temp = m_board[0][0];

	if (temp != EMPTY_VAL)
	{
		foundVictory = true;
		for (int i = 0; i < m_size; ++i)
		{
			if (temp != m_board[i][i])
			{
				foundVictory = false;
				break;
			}
		}
		if (foundVictory)
		{
			m_status = temp;
			return; // Found a winner
		}
	}
	
	// Check second diagonal
	temp = m_board[0][m_size - 1];

	if (temp != EMPTY_VAL)
	{
		foundVictory = true;
		for (int i = 0; i < m_size; ++i)
		{
			if (temp != m_board[i][m_size - i - 1])
			{
				foundVictory = false;
				break;
			}
		}
		if (foundVictory)
		{
			m_status = temp;
			return; // Found a winner
		}
	}

	// No winners
	m_status = EMPTY_VAL; 
}

void Board::optimized_calcStatus(coordinate latest)
{
	// This algorithm is based on the fact that after each move, 
	// a change in status can only appear in same row, col, or diagonal as the move

	int latestVal = m_board[latest.row][latest.col];
	bool foundVictory;

	// Check in row latest.row
	foundVictory = true;
	for (int c = 0; c < m_size; ++c)
		if (latestVal != m_board[latest.row][c])
		{
			foundVictory = false;
			break;
		}

	if (foundVictory)
	{
		m_status = latestVal;
		return;
	}

	// Check in row latest.col
	foundVictory = true;
	for (int r = 0; r < m_size; ++r)
		if (latestVal != m_board[r][latest.col])
		{
			foundVictory = false;
			break;
		}

	if (foundVictory)
	{
		m_status = latestVal;
		return;
	}

	// Check if latest is on first diagonal.

	if (latest.col == latest.row)
	{
		foundVictory = true;
		for (int i = 0; i < m_size; ++i)
			if (latestVal != m_board[i][i])
			{
				foundVictory = false;
				break;
			}
		if (foundVictory)
		{
			m_status = latestVal;
			return;
		}
	}

	// Check if latest is on second diagonal.
	if (latest.row + latest.col + 1 == m_size)
	{
		foundVictory = true;
		for (int i = 0; i < m_size; ++i)
			if (latestVal != m_board[i][m_size - i - 1])
			{
				foundVictory = false;
				break;
			}
		if (foundVictory)
		{
			m_status = latestVal;
			return;
		}
	}
}


