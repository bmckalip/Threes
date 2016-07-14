#include "Pile.h"
#include <vector>
#pragma once

using namespace std;

class State {
public:
	//constructors
	State(Pile piles[], bool);
	State();

	//getters
	pair<int, int>	getBestMove();
	Pile*			getPiles();
	bool			getTurn();

	//misc
	State			executeMove(pair<int, int>);
	bool			operator==(const State& other) const;
	bool			isVictory;

private:
	//utility functions
	void					sortPiles();
	bool					isWinner();
	vector <pair<int, int>>	getMoves();
	void					bestMove();

	//object variables
	Pile					piles[3];
	bool					turn;
	pair<int, int>			optimalMove;

	//static member variables
	static vector<State>	memoStates; //list of previously 'solved' states

};

