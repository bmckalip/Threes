#include "State.h"
#include <vector>
#pragma once

using namespace std;

class Game {
public:
	Game(int[]);
	int play();
	void printState();
private:
	void playerTurn();
	void AITurn();
//	bool executeMove(int*);
//	bool isValid(int* move);

	State currentState;
	bool turn;
	int winner;
};

