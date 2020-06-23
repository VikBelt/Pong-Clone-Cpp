
//Created by Vikram Belthur
//Code to Test the pong Game

#include "game_int.h"
#include "game.h"

int main() {
	//runs the pong-clone
	if (!StartMenu()) {
		return 1;
	}

	RunGame();
	return 0;
}
