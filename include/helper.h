/* 
Created by Vikram Belthur 6.18.2020
I am making this file to add some cleanliness to the main file
*/

#pragma once
#include "game_objects.h"

namespace Pong {
	
	//Keys to Move Paddle
	enum gameKeys {
		paddleOneUp = 0,
		paddleOneDown,
		paddleTwoUp,
		paddleTwoDown
	};

	//deleteGame
	void deleteGame(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* scoreData) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		TTF_CloseFont(scoreData);
		TTF_Quit();
		SDL_Quit();
	}

} //namespace Pong



