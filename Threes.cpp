#include "stdafx.h"
#include "Game.h"
#include <iostream>

int main(){
	//define the participant identities
	const bool AI = 0;
	const bool PLAYER = 1;

	//declare three piles
	int pileSizes[3];

	//prompt user to define the sizes of these piles
	cout << "enter the three desired pile sizes separated by spaces (eg: 2 1 5): ";
	cin >> pileSizes[0] >> pileSizes[1] >> pileSizes[2];

	//construct a game
	Game game = Game(pileSizes);
	//play the game and determine a winner
	int winner = game.play();
	
	//print the results
	if(winner == AI){
		cout << "you have no more moves, AI has won!";
	}else {
		//should never print:
		cout << "AI has no more moves, you has won!";
	}

	return 0;
}

