#include "Pile.h"
#include <vector>
#pragma once

//using namespace std;

class State {
public:
	//constructor
							State(Pile piles[], bool);
							State();

	//getters
	Pile*					getPiles();
	bool					getTurn();
	pair<int, int>			getBestMove();
	vector <pair<int,int>>	getMoves();
	bool					isWinner();

	//setters
	void					setPiles(Pile* newPiles);
	State					executeMove(pair<int, int>);
	//friend bool			operator==(const State& rhs, const State& lhs);
	bool					operator==(const State& other) const;

private:
	//utility functions
	void					bestMove();
	void					sortPiles();

	//object variables
	Pile					piles[3];
	bool					turn; // 0 means it's the AI's turn and 1 means its the player's turn
	pair<int, int>			optimalMove;
	bool					isVictory;

	//static member variables
	static vector<State>	memoStates;

};

