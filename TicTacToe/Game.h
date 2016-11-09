#pragma once

#include "Board.h"
#include "AI.h"

class Game
{
public:
	// Constructor
	Game(int size);
	// Destructor
	~Game() { delete board; }

	// Start a game
	void start();

	// Draw board on console
	void draw() const;

private:
	// Member variables-------------------
	Board *board;
	int m_size; // size of board

	// Member functions-------------------

	// Ask your for number of players
	void numOfPlayers();

	// Ask who plays first (Only in single player mode) 
	int whoStartsFirst() const;

	// Game modes:
	void singlePlayer();
	void multiPlayer();

	// Ask player to make a move
	void playerMove(int player) const;

	// Ask AI to make a move
	void AIMove(int player) const;

	// Restart game
	void restart();

	void printLabel() const;
	inline void drawLine() const;
	inline void drawSign(int value) const;

	
};

