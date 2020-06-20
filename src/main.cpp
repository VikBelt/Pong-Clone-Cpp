/*
Created by Vikram Belthur 6.18.2020
Classes for the creation of the Game
*/

#define SDL_MAIN_HANDLED

#include <iostream>
#include <chrono>
#include <SDL.h>
#include <SDL_ttf.h>
#include "helper.h"
#include "game_objects.h"

using namespace Pong;

int main() {
	//SDL Setup
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_Window* window = SDL_CreateWindow("Vikram's PONG - C++ CLONE",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,GAME_WIDTH,GAME_HEIGHT,SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	//Init Font
	TTF_Font* scoreData = TTF_OpenFont("ostrich-regular.ttf", 60);
	// Create the player score text fields
	Score one_score(Vector(GAME_WIDTH / 4, 20), renderer, scoreData);
	Score two_score(Vector(3 * GAME_WIDTH / 4, 20), renderer, scoreData);

	//generate ball at the origin
	Vector ball_position{ (GAME_WIDTH / 2.0) - (BALL_WIDTH / 2.0),(GAME_HEIGHT / 2.0) - (BALL_WIDTH / 2.0) };
	Vector ball_speed{ BALL_SPEED,0.0};
	Ball game_ball{ ball_position, ball_speed};

	//generate the paddles on either side
	Vector paddle_one_position{ 50.0, (GAME_HEIGHT / 2.0) - (PADDLE_HEIGHT / 2.0) };
	Vector velocity_one{ 0,0 };
	Paddle paddle_one{ paddle_one_position,velocity_one };
	Vector paddle_two_position{GAME_WIDTH - 50.0, (GAME_HEIGHT / 2.0) - (PADDLE_HEIGHT / 2.0)};
	Vector velicity_two{ 0,0 };
	Paddle paddle_two{ paddle_two_position,velicity_two };

	//game loop - each frame
	bool running = true;
	bool keys[4] = {};
	double time = 0.0;

	while (running){
		auto start = std::chrono::high_resolution_clock::now();
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			//to quit the pgrm
			if (event.type == SDL_QUIT) {
				running = false;
			}

			//keys pressed
			else if (event.type == SDL_KEYDOWN) {

				if (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_b) {
					running = false;
				}
				//move the paddle up/down upon pressing w and s
				else if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP) {
					keys[paddleOneUp] = true;
				}
				else if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN) {
					keys[paddleOneDown] = true;
				}
			}

			//keysreleased
			else if (event.type == SDL_KEYUP) {
				
				if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP) {
					keys[paddleOneUp] = false;
				}
				else if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN) {
					keys[paddleOneDown] = false;
				}
			}
		}

		// Code to change Paddle One Position
		if (keys[paddleOneUp] == true) {
			paddle_one.velocity.y = -PADDLE_SPEED;
		}
		else if (keys[paddleOneDown] == true) {
			paddle_one.velocity.y = PADDLE_SPEED;
		}
		else {
			paddle_one.velocity.y = 0.0;
		}

		//Update motions
		paddle_one.Update(time);
		game_ball.Update(time);

		SDL_SetRenderDrawColor(renderer, 0, 0, 128, 0); //window background
		SDL_RenderClear(renderer);

		//create the game board
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //net color
		for (auto i = 0; i < GAME_HEIGHT; i++) {
			if (i % 5)	SDL_RenderDrawPoint(renderer, GAME_WIDTH / 2, i);
		}

		//showBoard
		game_ball.Show(renderer);
		paddle_one.Show(renderer);
		paddle_two.Show(renderer);
		one_score.Show();
		two_score.Show();
		SDL_RenderPresent(renderer);
		auto stop = std::chrono::high_resolution_clock::now();
		time = std::chrono::duration<double, std::chrono::milliseconds::period>(stop - start).count();
	}

	//Cleanup
	deleteGame(renderer, window, scoreData);
	return 0;
}
