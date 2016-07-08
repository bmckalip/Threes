#pragma once
#include "Pile.h"
#include <vector>
#include <set>

using namespace std;

class State {
public:
	State(vector<int> = {0, 0, 0});
	//maintain a static list of previously solved states
	static vector<State> memoStates;
	vector<Pile> getPiles();
	void setPiles(vector<Pile> newPiles);
	vector<int> getNextBestMove();
	friend bool operator== (const State& lhs, const State& rhs);
	
private:
	void findNextBestMove();
	vector<Pile> piles;
	vector<int> nextBestMove;
};

