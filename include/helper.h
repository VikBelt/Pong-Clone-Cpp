/* 
Created by Vikram Belthue 6.18.2020
I am making this file to add some cleanliness to the main file
*/

#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

void deleteGame(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* scoreData){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(scoreData);
	TTF_Quit();
	SDL_Quit();
}


