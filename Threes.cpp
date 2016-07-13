// Threes.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include "Game.h"
#include <vector>
#include <iostream>

int main(){
	int pileSizes[] = { 1, 1, 5 };
	Game game = Game(pileSizes);
	int winner = game.play();
	int pause;
	if(winner == 0){
		cout << "AI has won!";
	}else {
		cout << "player has won!";
	}
	cin >> pause;
	return 0;
}

