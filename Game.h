#include "State.h"
#include <vector>
#pragma once

using namespace std;

class Game {
public:
	Game(int[]); //constructor
	int play();

private:
	//object functions
	void			printState();
	void			playerTurn();
	void			AITurn();
	void			checkForWinner();
	pair<int, int>	validateInput(pair<int, int>);
	bool			IsInBounds(int value, int low, int high);
	void			rigGame();

	//object variables
	State	currentState;
	int		winner;
	
	//static member variables
	const static pair<int, int> INVALID_MOVE;
	const static bool			ID_AI;
	const static bool			ID_PLAYER;
};

