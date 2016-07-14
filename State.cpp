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
	isVictory = isWinner();
	bestMove();
}

//defualt constructor
State::State() {
	this->piles[0] = Pile(0);
	this->piles[1] = Pile(0);
	this->piles[2] = Pile(0);
	this->turn = 0;
}

void State::bestMove() {
	vector<pair<int, int >> moves = getMoves();

	for (size_t i = 0; i < moves.size(); i++) {
		pair<int, int> move = moves.at(i);
		if (executeMove(move).isWinner()) {
			optimalMove = move;
			return;
		}
	}

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
		//if it's the AI's turn, it lost and vice versa.
		return turn;
	}

	vector<pair<int, int>> winningMoves;
	//simulate each move recursively and determine if any lead to a winning state
	for (size_t i = 0; i < moves.size(); i++) {
		State newState = this->executeMove(moves.at(i));

		//check if state is memoized
		if (find(memoStates.begin(), memoStates.end(), newState) != memoStates.end()) {
			return newState.isVictory;
		}

		//if this state is not memoized, recursively check if it's a winning move.
		if (newState.isWinner()) {
			winningMoves.push_back(moves.at(i));
		}

		//memoize the state
		memoStates.push_back(newState);
	}

	//determine if state is a victor based on winningMoves vector
	if (!winningMoves.empty()) {
		return true;
	}else {
		return false;
	}
}

State State::executeMove(pair<int, int> move) {
	if (move == make_pair(0, 0)) { 
		return *this; 
	}

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
	return State(newPiles, !turn);
	//return newState;

}

bool State::getTurn() {
	return turn;
}

pair<int, int> State::getBestMove() {
	bestMove();
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
//very sloppy selection sort:
void State::sortPiles() {
	/*
	we wrote our program to handle input in ascending order before we realized it was supposed to be done
	in decending order, so our program handles it in ascending order on the backend, and when it's time
	to print strates and handle user input, it is printed backwards and converted when necessary.
	*/

	int min, minIndex, temp;
	for (size_t i = 0; i < 3; i++) {
		min = INT_MAX;
		//find the minimum value of the sub array
		for (size_t j = i; j < 3; j++) {
			if (piles[j] < min) {
				minIndex = j;
				min = piles[j].getSize();
			}
		}
		//swap the value at the front with the minimum value.
		temp = piles[minIndex].getSize();
		piles[minIndex] = piles[i];
		piles[i] = Pile(temp);
	}
}

bool State::operator==(const State& other) const {
	for (int i = 0; i < 3; i++) {
		if (this->piles[i] != other.piles[i]) {
			return false;
		}
	}
	if (this->turn != other.turn) {
		return false;
	}
	return true;
}