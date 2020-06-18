#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL.h>
#include "game_objects.h";

constexpr auto GAME_WIDTH = 1280;
constexpr auto GAME_HEIGHT = 720;

int main() {
	//SDL Setup
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window{ nullptr };

	window = SDL_CreateWindow(
		"Vikram's PONG - C++ CLONE",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		GAME_WIDTH,
		GAME_HEIGHT,
		SDL_WINDOW_RESIZABLE
	);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	//generate ball at the origin
	Vector ball_position{ (GAME_WIDTH / 2.0) - (BALL_WIDTH / 2.0),(GAME_HEIGHT / 2.0) - (BALL_WIDTH / 2.0) };
	Ball game_ball{ ball_position };

	//generate the paddles on either side
	Vector paddle_one_position{ 50.0, (GAME_HEIGHT / 2.0) - (PADDLE_HEIGHT / 2.0) };
	Paddle paddle_one{ paddle_one_position };
	Vector paddle_two_position{GAME_WIDTH - 50.0, (GAME_HEIGHT / 2.0) - (PADDLE_HEIGHT / 2.0)};
	Paddle paddle_two {paddle_two_position};

	//game loop
	SDL_Event event;
	bool running = true;
	while (running) {
		while (SDL_PollEvent(&event)) {
			//to quit the pgrm
			if (event.type == SDL_QUIT) {
				running = false;
			}
			//end the program when escape is pressed
			else if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					running = false;
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 128, 0); //window background
		SDL_RenderClear(renderer);

		//create the net
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //net color
		for (auto i = 0; i < GAME_HEIGHT; i++) {
			if (i % 5)	SDL_RenderDrawPoint(renderer, GAME_WIDTH / 2, i);
		}

		//show ball & paddles
		game_ball.Show(renderer);
		paddle_one.Show(renderer);
		paddle_two.Show(renderer);
		SDL_RenderPresent(renderer);
	}

	//Cleanup
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
