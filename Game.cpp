#include "stdafx.h"
#include "Game.h"
#include <limits>
#include <iostream>

Game::Game(int pileSizes[]) {
	Pile piles[] = { Pile(pileSizes[0]), Pile(pileSizes[1]), Pile(pileSizes[2]) };
	currentState = State(piles, 0);
	winner = -1;
}

int Game::play() {
	//determine if the AI will win with the current state.
	if (!currentState.isVictory) {
		//if not, copy the piles and make the player go first. set this as the current state.
		currentState = State(currentState.getPiles(), !currentState.getTurn());
		cout << "You go first!" << endl << endl;
	}
	else {
		cout << "I'll go first!" << endl << endl;
	}
	cout << "Starting state:" << endl;
	printState();
	//while there is no winner, take turns.
	while (winner == -1) {
		if (currentState.getTurn() == 0) {
			AITurn();
		} else {
			playerTurn();
		}
		checkForWinner();
		printState();
	}
	return winner;
}

void Game::playerTurn() {
	pair<int, int> move;
	cout << "Enter two indexes you wish to subtract seperated by a space: ";
	cin >> move.first >> move.second;
	
	currentState = currentState.executeMove(validateInput(move));
	turn = currentState.getTurn();
}

void Game::AITurn() {
	pair<int, int> move = currentState.getBestMove();
	cout << "The computer is executing move: " << move.first + 1 << ", " << move.second + 1 << endl;
	currentState = currentState.executeMove(move);
	turn = currentState.getTurn();
}

pair<int, int> Game::validateInput(pair<int, int> move) {
	//check if move refers to valid indexes
	if (!IsInBounds(move.first, 1, 3)) { return make_pair(-1, -1); }
	
	if (!IsInBounds(move.second, 1, 3)) { return make_pair(-1, -1); }

	//index-ify the move
	move.first--;
	move.second--;

	//make sure input is ordered correctly
	if (move.first > move.second) {
		int temp = move.first;
		move.first = move.second;
		move.second = temp;
	}

	return move;
}


void Game::printState() {
	cout << "Pile indexes: ";
	for (size_t i = 3; i > 0; i--) {
		cout << i << " \t";
	}
	cout << endl;
	cout << "Pile Values:  ";
	for (size_t i = 3; i > 0; i--) {
		cout << currentState.getPiles()[i - 1].getSize() << " \t";
	}
	cout << endl << endl;
}

void Game::checkForWinner() {
	if (currentState.getPiles()[0] == 0 && currentState.getPiles()[1] == 0) {
		winner = !currentState.getTurn();
	}
}

bool Game::IsInBounds(int value, int low, int high) {
	return !(value < low) && (value <= high);
}

