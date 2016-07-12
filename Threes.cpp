// Threes.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include "Game.h"
#include <vector>
#include <iostream>

int main(){
	int pileSizes[] = { 3, 2, 1 };
	Game game = Game(pileSizes);
	game.play();
	return 0;
}

