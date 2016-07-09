#pragma once
#include "Pile.h"
#include <vector>
#include <set>

using namespace std;

class State {
public:
	//constructor
							State(vector<Pile>, bool);
							State();

	//getters
	vector<Pile>			getPiles();
	bool					getTurn();
	vector<int>				getBestMove();
	vector <vector<int>>	getMoves();
	bool					isWinner();

	//setters
	void					setPiles(vector<Pile> newPiles);
	State					executeMove(vector<int>);
	friend bool				operator==(const State& rhs, const State& lhs);
private:
	//utility functions
	void					bestMove();
	void					sortPiles();

	//object variables
	vector<Pile>			piles;
	bool					turn; // 0 means it's the AI's turn and 1 means its the player's turn
	vector<int>				optimalMove;
	bool					isVictory;

	//static member variables
	static vector<State>	memoStates;

};

