#pragma once

#define SDL_MAIN_HANDLED

#include <iostream>
#include <chrono>
#include <SDL.h>
#include <SDL_ttf.h>

namespace Pong
{
	constexpr int START_WIDTH{ 900 };
	constexpr int START_HEIGHT{ 800 };
	
	bool StartMenu()
	{
		bool proceed = true;
		SDL_Init(SDL_INIT_EVERYTHING);
		TTF_Init();
		SDL_Window* swindow = SDL_CreateWindow("START MENU", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, START_WIDTH, START_HEIGHT, SDL_WINDOW_RESIZABLE);
		SDL_Renderer* srenderer = SDL_CreateRenderer(swindow, -1, 0);

		//Welcome Text
		TTF_Font* font = TTF_OpenFont("ostrich-regular.ttf", 30);
		SDL_Color White = { 255,255,255 };
		SDL_Surface* surface = TTF_RenderText_Solid(font, "Welcome to HD Pong!", White);
		SDL_Texture* message = SDL_CreateTextureFromSurface(srenderer, surface);

		SDL_Rect textbox{};
		textbox.x = 0;
		textbox.y = 100;
		textbox.w = 900;
		textbox.h = 200;
	
		//Credits test
		SDL_Surface* credit_surf = TTF_RenderText_Solid(font, "Created with C++ by Vikram Belthur", White);
		SDL_Texture* credit = SDL_CreateTextureFromSurface(srenderer, credit_surf);

		SDL_Rect creditbox{};
		creditbox.x = 50;
		creditbox.y = 350;
		creditbox.w = 800;
		creditbox.h = 80;

		SDL_SetRenderDrawColor(srenderer, 0, 0, 128, 0); //window background
		SDL_RenderClear(srenderer);
		SDL_RenderPresent(srenderer);

		//Show Welcome Text
		SDL_RenderCopy(srenderer, message, nullptr, &textbox);
		SDL_RenderCopy(srenderer, credit, nullptr, &creditbox);
		SDL_RenderPresent(srenderer);

		bool running = true;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "What do you want to do?", "Press G to proceed to the HD-PONG, or Q to exit", swindow);
		while (running) {
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_KEYDOWN) {
					if (event.key.keysym.sym == SDLK_q) {
						proceed = false;
						running = false;
					}
					else if (event.key.keysym.sym == SDLK_g) {
						proceed = true;
						running = false;
					}
				}
				
			}
			
		}
		
		//cleanup
		SDL_DestroyRenderer(srenderer);
		SDL_DestroyTexture(message);
		SDL_FreeSurface(surface);
		SDL_FreeSurface(credit_surf);
		SDL_DestroyWindow(swindow);
		TTF_CloseFont(font);
		TTF_Quit();
		SDL_Quit();

		return proceed;
	}

} //namespace Pong
