#include "stdafx.h"
#include "State.h"

vector<State> State::memoStates;

State::State(Pile piles[], bool turn) {
	//initialize piles using the sizes provided.
	this->piles[0] = piles[0];
	this->piles[1] = piles[1];
	this->piles[2] = piles[2];
	this->turn = turn;
	sortPiles();
}

//defualt constructor
State::State() {
	this->piles[0] = Pile(0);
	this->piles[1] = Pile(0);
	this->piles[2] = Pile(0);
	this->turn = 0;
}

void State::bestMove() {
	optimalMove = make_pair(0, 0);
}

vector<pair<int, int>> State::getMoves() {
	//sortPiles(); //first sort the piles to eliminate duplicates

	vector<pair<int, int>> moves;
	Pile firstPile = this->getPiles()[0];
	Pile secondPile = this->getPiles()[1];
	Pile thirdPile = this->getPiles()[2];

	//if two empty piles, no more moves are left
	if (firstPile.isEmpty() && secondPile.isEmpty()) {
		//do nothing, no moves left to add.
	
	//if only one pile is empty, only one move remains.
	} else if (firstPile.isEmpty()) {
		moves.push_back(make_pair(1, 2)); //subtract index 1 from index 2, store in index 2.

	//else, three piles remain and there are 3 possible moves available
	} else {
		moves.push_back(make_pair(0, 1)); //subtract index 0 from index 1, store in index 1.
		moves.push_back(make_pair(0, 2)); //subtract index 0 from index 2, store in index 2.
		moves.push_back(make_pair(1, 2)); //subtract index 1 from index 2, store in index 2.
	}
	return moves;
}

bool State::isWinner() {
	vector<pair<int, int>> moves = getMoves();

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
		//need to figure out how to properly overload the ==operator for std find to work
		//if (find(memoStates.begin(), memoStates.end(), this) != memoStates.end()) {return isVictory;}
		
		//if solution is not memoized, recursively solve it:
		State newState = this->executeMove(moves.at(i));
		isVictory = newState.isWinner();
		//memoize the state
		memoStates.push_back(newState);
	}

	return isVictory;
}

State State::executeMove(pair<int, int> move) {
	//pile zero is never modified, therefore copy it directly.
	Pile newPiles[] = { piles[0] , Pile(0) , Pile(0) };

	//subtract the first choice from the second
	newPiles[move.second] = piles[move.second] - piles[move.first];

	//determine which pile is not being modified and copy it
	if (move.second == 1) {
		newPiles[2] = piles[2];
	} else {
		newPiles[1] = piles[1];
	}
	
	//construct the new state and return it
	bool newTurn = !turn;
	return State(newPiles, newTurn);
	//return newState;

}

bool State::getTurn() {
	return turn;
}

pair<int, int> State::getBestMove() {
	return optimalMove;
}

Pile* State::getPiles() {
	return piles;
}

void State::setPiles(Pile* piles) {
	this->piles[0] = piles[0];
	this->piles[1] = piles[1];
	this->piles[2] = piles[2];
}

void State::sortPiles() {
	int min = INT_MAX;
	for (size_t i = 0; i < 3; i++) {
		//find the minimum value
		for (size_t j = i; i < 3; i++) {
			if (piles[i] < min) {
				min = piles[i].getSize();
			}
		}
		piles[ i] = Pile(min);
	}
}
/*
bool operator==(const State& rhs, const State& lhs) {
	if (rhs.piles == lhs.piles && lhs.turn == rhs.turn) {
		return true;
	}
	return false;
}
*/
bool State::operator==(const State& other) const {
	if (this->piles == other.piles && this->turn == other.turn) {
		return true;
	}
	return false;
}