#include "stdafx.h"
#include "State.h"

State::State(vector<int> pileSizes) {
	//initialize piles using the sizes provided. any number of piles is supported
	for (int i = 0; i < pileSizes.size(); i++) {
		piles.push_back(Pile(pileSizes.at(i)));
	}
	findNextBestMove();
}

void State::findNextBestMove() {
	//check if the solution is memoized
	if (find(memoStates.begin(), memoStates.end(), *this) != memoStates.end()) {
		nextBestMove = this->nextBestMove;
	} else {
		//todo solve this state
		memoStates.push_back(*this);
	}
}

vector<Pile> State::getPiles() {
	return piles;
}

void State::setPiles(vector<Pile> piles) {
	this->piles = piles;
}

vector<int> State::getNextBestMove() {
	return nextBestMove;
}