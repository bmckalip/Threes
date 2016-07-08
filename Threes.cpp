// Threes.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include "Game.h"
#include <vector>

int main(){
	vector<int> pileSizes = {3, 5, 10};
	Game game = Game(pileSizes);
	game.play();
	return 0;
}

