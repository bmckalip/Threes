#pragma once
#include "State.h"
#include <vector>

using namespace std;

class Game {
public:
	Game(vector<int>);
	int play();
private:
	void Game::sortPiles(Pile& unsorted);
	void playerTurn();
	void AITurn();
	int getMin();
	bool executeMove(vector<int>);
	bool isValid(vector<int> move);

	State currentState;
	bool turn;
	int winner;
};

