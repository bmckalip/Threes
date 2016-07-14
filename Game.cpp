#include "stdafx.h"
#include "Game.h"
#include <iostream>

//define invalidMove as the errorCode to return upon encoutering an invalid move.
const pair<int, int> Game::INVALID_MOVE = make_pair(-1, -1);

//define the ai and player turn id's.
const bool Game::ID_AI = 0;
const bool Game::ID_PLAYER = 1;

//class constructor
Game::Game(int pileSizes[]) {
	//construct an array of piles based on the recieved size input.
	Pile piles[] = { Pile(pileSizes[0]), Pile(pileSizes[1]), Pile(pileSizes[2]) };
	currentState = State(piles, ID_AI);
	//declare that there is no current winner
	winner = -1;
	rigGame();
}

void Game::rigGame() {
	//determine if the AI will win with the current state.
	if (!currentState.isVictory) {
		//if not, copy the piles and make the player go first. set this as the current state.
		currentState = State(currentState.getPiles(), !currentState.getTurn());
		cout << "You go first!" << endl << endl;
	} else {
		//if so, go first.
		cout << "I'll go first!" << endl << endl;
	}
}

int Game::play() {
	cout << "Game starting, the piles are as follows:" << endl;
	printState();
	
	//take turns until a winner is found.
	while (winner == -1) {
		if (currentState.getTurn() == ID_AI) {
			AITurn();
		} else {
			playerTurn();
		}
		//after each turn, check for a winner and print the new statew of the board.
		checkForWinner();
		printState();
	}
	return winner;
}

void Game::AITurn() {
	//get the best move available to the AI
	pair<int, int> move = currentState.getBestMove();
	cout << "The computer is executing move: " << move.first + 1 << ", " << move.second + 1 << endl << endl;
	//execute the move
	currentState = currentState.executeMove(move);
}

void Game::playerTurn() {
	pair<int, int> move;
	cout << "Enter two indices you wish to subtract seperated by a space: ";
	cin >> move.first >> move.second;
	move = validateInput(move);

	//continue to prompt user for a valid move until one is recieved.
	while(move == INVALID_MOVE) {
		cout << "invalid move, please try again: ";
		cin >> move.first >> move.second;
		move = validateInput(move);
	}

	//move is valid, execute it.
	currentState = currentState.executeMove(move);
}

pair<int, int> Game::validateInput(pair<int, int> move) {

	//check if move refers to valid indexes
	if (!IsInBounds(move.first, 1, 3)) { return INVALID_MOVE; }
	if (!IsInBounds(move.second, 1, 3)) { return INVALID_MOVE; }

	//check if piles to subtract are the same. if so, this is invalid.
	if (move.first == move.second) { return INVALID_MOVE; }

	//order the move correctly: (pile containing value to subtract, pile to subtract from.)
	if (move.first > move.second) {
		int temp = move.first;
		move.first = move.second;
		move.second = temp;
	}

	//index-ify the move in preperation of execution.
	move.first--;
	move.second--;

	//check if either pile is empty. if so, invalid move.
	if (currentState.getPiles()[move.first].isEmpty() ||
		currentState.getPiles()[move.second].isEmpty()) {
		return INVALID_MOVE;
	}
	return move;
}

bool Game::IsInBounds(int value, int low, int high) {
	return !(value < low) && (value <= high);
}

void Game::checkForWinner() {
	//if there are two empty piles, the game is over.
	if (currentState.getPiles()[0] == 0 && currentState.getPiles()[1] == 0) {
		//whoever's turn it is when there are two empty piles is the loser.
		winner = !currentState.getTurn();
	}
}

void Game::printState() {
	/*
	we wrote our program to handle input in ascending order before we realized it was supposed to be done
	in decending order, so our program handles it in ascending order on the backend, and when it's time
	to print strates and handle user input, it is printed backwards and converted when necessary.
	*/
	cout << "Pile indexes: ";
	for (size_t i = 3; i > 0; i--) {
		cout << i << " \t";
	}

	cout << endl << "Pile Values:  ";
	for (size_t i = 3; i > 0; i--) {
		cout << currentState.getPiles()[i - 1].getSize() << " \t";
	}
	cout << endl << endl;
}



