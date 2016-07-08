#include "stdafx.h"
#include "Game.h"
#include <limits>
#include <iostream>

Game::Game(vector<int> pileSizes) {
	currentState = State(pileSizes);
	turn = 0;
	winner = NULL;
	isWinner = false;
}

int Game::play() {
	while (winner == NULL) {
		if (turn == 0) {
			playerTurn();
		} else {
			AITurn();
		}
	}
	return winner;
}

void Game::playerTurn() {
	cout << "Pile indexes: ";
	for (size_t i = 0; i < currentState.getPiles().size(); i++) {
		cout << i << ",\t";
	}
	cout << endl;
	cout << "Pile Values: ";
	for (size_t i = 0; i < currentState.getPiles().size(); i++) {
		cout << currentState.getPiles().at(i).getSize() << ",\t";
	}
	cout << endl;

	vector<int> move;
	cout << "Enter two indexes you wish to subtract seperated by a space: (eg. 0 2)" << endl;
	cin >> move.at(0) >> move.at(1);
	if (executeMove(move)) {
		turn = !turn;
	}
}

void Game::AITurn() {
	vector<int> move = currentState.getNextBestMove();
	if (executeMove(move)) {
		turn = !turn;
	}
}

bool Game::executeMove(vector<int> move) {
	if (!isValid(move)) return false;

	vector<Pile> piles = currentState.getPiles();
	Pile firstPile = piles.at(move.at(0));
	Pile secondPile = piles.at(move.at(1));

	if (firstPile < secondPile) {
		piles.at(move.at(0)) = secondPile - firstPile;
	} else {
		piles.at(move.at(0)) = firstPile - secondPile;
	}

	currentState.setPiles(piles);
	return true;
}

bool Game::isValid(vector<int> move) {
	for (size_t i = 0; i < move.size(); i++) {
		if (size_t(move.at(i)) > currentState.getPiles().size()) return false;
	}
	return true;
}