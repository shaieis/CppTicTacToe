#include "Game.h"
# include <iostream>

// Ctor ==============================================================================
Game::Game()
{}

// Public functions ==================================================================
void Game::start() 
{
	
	printLabel();
	//Ask for board size
	sizeOfBoard();
	//Ask for number of players
	numOfPlayers();
}

void Game::draw() const
{

	system("cls");

	// draw column numbers
	std::cout << "  ";
	for (int i = 1; i < m_size + 1; ++i)
	{
		std::cout << "  " << i << " ";
	}
	std::cout << std::endl;

	// draw table with row numbers
	for (int i = 0; i < m_size; ++i)
	{
		drawLine();
		std::cout << i + 1 << " | ";  // row number
		for (int j = 0; j < m_size; ++j)
		{
			drawSign(board->getValue({ i,j }));
			std::cout << " | ";
		}
		std::cout << std::endl;

	}
	drawLine();
}

// Private functions =================================================================

void Game::sizeOfBoard()
{
	int size;
	do {
		std::cout << "Please choose size of board between 3 and 9 ";
		std::cin >> size;
		std::cout << std::endl;
	} while ((size < 3) || (size > 9));

	m_size = size;
	board = new Board(size);
}
void Game::numOfPlayers() 
{

	char m_numOfPlayers;

	// Ask for number of players until user enters a valid answer
	do {
		std::cout << "Please choose: 1 - Single player (Against computer)  2 - Two Players ";
		std::cin >> m_numOfPlayers;
		std::cout << std::endl;
	} while (m_numOfPlayers != '1' && m_numOfPlayers != '2');


	if (m_numOfPlayers == '1')
		singlePlayer();
	else
		multiPlayer();
}

int Game::whoStartsFirst() const
{
	char input;
	do {

		std::cout << "Please choose your sign: X or O (X starts first) ";
		std::cin >> input;
		std::cout << std::endl;

	} while (input != 'X' && input != 'O');

	if (input == 'X')
		return X_VAL;
	else
		return O_VAL;
}

void Game::singlePlayer()
{
	char selection;
	int player;
	int currPlayer;
	int status;

	// Game loop
	do {
		// Ask who starts first, Player or AI
		player = whoStartsFirst();

		currPlayer = X_VAL; // X always starts first

		do {
			draw();

			if (currPlayer == player) // Choose who plays next: user or AI
				playerMove(currPlayer);
			else
				AIMove(currPlayer);

			currPlayer *= -1; // Select next player


		} while (!board->IsGameOver());

		// Game over
		draw();

		status = board->checkVictory();

		std::cout << std::endl;

		//Print result
		if (status == EMPTY_VAL)
			std::cout << "It's a tie!";
		else if (status == player)
			std::cout << "You WON!!";
		else if (status != player)
			std::cout << "You lost...";

		std::cout << std::endl << std::endl << "Type A to try again, anything else to exit: " ;
		
		std::cin >> selection;
		restart();
	} while (selection == 'A');
}

void Game::multiPlayer()
{
	char selection;
	int currPlayer;
	int status;

	// Game loop
	do {
		currPlayer = X_VAL; // X always starts fisrt
		do {
			draw();

			playerMove(currPlayer); // Ask player to make a move
		
			currPlayer *= -1; // Select next player

		} while (!board->IsGameOver());

		// Game over
		draw();

		status = board->checkVictory();
		std::cout << std::endl;

		//Print result
		if (status == EMPTY_VAL)
			std::cout << "It's a tie!";
		else if (status == X_VAL)
			std::cout << "player X Won";
		else if (status == O_VAL)
			std::cout << "Player O Won";

		std::cout << std::endl << std::endl << "Type A to try again, anything else to exit: ";

		std::cin >> selection;
		restart();
	} while (selection == 'A');
}

void Game::playerMove(int player) const
{
	//Print who's turn it is
	std::cout << "It's ";
	drawSign(player);
	std::cout << "'s turn. What is your next move:";
	
	int row, col;
	bool validValues;

	// Ask for coordinates for move and make sure they are valid. If not ask again
	do
	{
		validValues = true;
		std::cout << std::endl << "row: ";
		std::cin >> row;
		std::cout << "column: "; 
		std::cin >> col;
		if (col < 1 || col > m_size + 1 || row < 1 || row > m_size + 1)
		{
			validValues = false;
			std::cout << "No such spot, Please try again:";
		}
		else if (!(board->setValue({ row-1 ,col-1 }, player))) // setValue returns false if spot is taken
		{
			validValues = false;
			std::cout << "Spot is already taken, Please try again:";
		}

	} while (!validValues);

}

void Game::AIMove(int player) const
{
	board->setValue(AI::chooseNextMove(player, *board, m_size), player);
}

void Game::restart()
{
	board->clear();
}

void Game::printLabel() const
{
	system("cls");
	std::cout << "====== Tic Tac Toe ======" << std::endl << std::endl;
}

inline void Game::drawLine() const
	{
		std::cout << "  -";
		for (int i = 0; i < m_size * 4; ++i)
			std::cout << "-";
		std::cout << std::endl;
	}

inline void Game::drawSign(int value) const
	{
		switch (value)
		{
		case X_VAL:
			std::cout << "X";
			break;
		case O_VAL:
			std::cout << "O";
			break;
		case EMPTY_VAL:
			std::cout << " ";
			break;
		}
		
	}
	


