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
	void checkForWinner();
	pair<int, int> validateInput(pair<int, int>);
	bool IsInBounds(int value, int low, int high);

	State currentState;
	bool turn;
	int winner;
};

