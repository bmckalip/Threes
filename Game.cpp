#include "stdafx.h"
#include "Game.h"
#include <limits>
#include <iostream>

Game::Game(int pileSizes[]) {
	turn = 1;
	Pile piles[] = { Pile(pileSizes[0]), Pile(pileSizes[1]), Pile(pileSizes[2]) };
	currentState = State(piles, turn);
	winner = -1;
}

int Game::play() {
	
	while (winner == -1) {
		printState();
		if (turn == 0) {
			AITurn();
		} else {
			playerTurn();
		}
	}
	return winner;
}

void Game::playerTurn() {
	pair<int, int> move;
	cout << "Enter two indexes you wish to subtract seperated by a space: (eg. 0 2): ";
	cin >> move.first >> move.second;
	
	currentState = currentState.executeMove(move);
	turn = currentState.getTurn();
}

void Game::AITurn() {
	pair<int, int> move = currentState.getBestMove();
	cout << "The computer is executing move: " << move.first << ", " << move.second << endl;
	currentState = currentState.executeMove(move);
	turn = currentState.getTurn();
}
/*
bool Game::executeMove(int* move) {
	if (!isValid(move)) return false;

	vector<Pile> piles = currentState.getPiles();
	Pile firstPile = piles.at(move[0]);
	Pile secondPile = piles.at(move[1]);

	if (firstPile < secondPile) {
		piles.at(move[0]) = secondPile - firstPile;
	} else {
		piles.at(move[0]) = firstPile - secondPile;
	}

	currentState.setPiles(piles);
	return true;
}
*/
/*
bool Game::isValid(int* move) {
	for (size_t i = 0; i < 2; i++) {
		if (size_t(move[i]) > currentState.getPiles().size()) return false;
	}
	return true;
}
*/

void Game::printState() {
	cout << "Pile indexes: ";
	for (size_t i = 0; i < 3; i++) {
		cout << i << ",\t";
	}
	cout << endl;
	cout << "Pile Values:  ";
	for (size_t i = 0; i < 3; i++) {
		cout << currentState.getPiles()[i].getSize() << ",\t";
	}
	cout << endl << endl;
}