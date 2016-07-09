#include "stdafx.h"
#include "State.h"

State::State(vector<Pile> piles, bool turn) {
	//initialize piles using the sizes provided.
	for (size_t i = 0; i < piles.size(); i++) {
		piles.push_back(Pile(piles.at(i)));
	}
	this->turn = turn;
}

//defualt constructor
State::State() {
	for (int i = 0; i < 3; i++) {
		piles.push_back(Pile(0));
	}
	this->turn = 0;
}

void State::bestMove() {

}

vector<vector<int>> State::getMoves() {
	sortPiles(); //first sort the piles to eliminate duplicates

	vector<vector<int>> moves;
	Pile firstPile = this->getPiles().at(0);
	Pile secondPile = this->getPiles().at(1);
	Pile thirdPile = this->getPiles().at(2);

	//if two empty piles, no more moves are left
	if (firstPile.isEmpty() && secondPile.isEmpty()) {
		//do nothing, no moves left to add.
	
	//if only one pile is empty, only one move remains.
	} else if (firstPile.isEmpty()) {
		moves.push_back({ 1,2 }); //subtract index 1 from index 2, store in index 2.

	//else, three piles remain and there are 3 possible moves available
	} else {
		moves.push_back({ 0,1 }); //subtract index 0 from index 1, store in index 1.
		moves.push_back({ 0,2 }); //subtract index 0 from index 2, store in index 2.
		moves.push_back({ 1,2 }); //subtract index 1 from index 2, store in index 2.
	}
}

bool State::isWinner() {
	vector<vector<int>> moves = getMoves();

	//base case: if there are no more moves, the game is over.
	if (moves.empty()) {
		//if the game ends and it is the AI's turn, the game is a losing game.
		if (turn == 0) {
			return false;
		//if the game ends and it's the player's turn, the game is a winning game.
		} else {
			return true;
		}
	}

	//simulate each move recursively and determine if any lead to a winning state
	for (size_t i = 0; i < moves.size(); i++) {
		//check if solution is memoized
		if (find(memoStates.begin(), memoStates.end(), this) != memoStates.end()) {
			return isVictory;
		}

		
		

		//if solution is not memoized, recursively solve it:
		State newState = this->executeMove(moves.at(i));
		isVictory = newState.isWinner();
		//memoize the state
		memoStates.push_back(newState);
	}

	return isVictory;
}

State State::executeMove(vector<int> move) {
	//pile zero is never modified, therefore copy it directly.
	vector<Pile> newPiles = { piles.at(0) , Pile(0) , Pile(0) };

	//determine which pile is being modified. modify it and copy the other values
	if (move.at(1) == 1) {
		newPiles.at(1) = piles.at(1) - piles.at(move.at(0));
	} else {
		newPiles.at(2) = piles.at(2) - piles.at(move.at(0));
	}
	sortPiles();
	//construct the new state and return it
	State newState = State(newPiles, !turn);

}

vector<Pile> State::getPiles() {
	return piles;
}

void State::setPiles(vector<Pile> piles) {
	this->piles = piles;
}

void State::sortPiles() {
	vector<Pile> newPiles;
	int min = INT_MAX;
	for (size_t i = 0; i < piles.size(); i++) {
		//find the minimum value
		for (size_t i = 0; i < piles.size(); i++) {
			if (piles.at(i) < min) {
				min = piles.at(i).getSize();
			}
		}
		newPiles.push_back(min);
	}
	piles = newPiles;
}

bool operator==(const State& rhs, const State& lhs) {
	if (rhs.piles == lhs.piles && lhs.turn == rhs.turn) {
		return true;
	}
	return false;
}