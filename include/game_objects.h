/*
Created by Vikram Belthur 6.18.2020
Classes for the creation of the Game
*/

#pragma once
#include <iostream>
#include <string>
#include <SDL_ttf.h>
#include <SDL.h>

namespace Pong {

	//game dimmensions
	constexpr auto GAME_WIDTH = 1600;
	constexpr auto GAME_HEIGHT = 900;
	constexpr auto BALL_WIDTH = 20;
	constexpr auto BALL_HEIGHT = 20;
	constexpr auto BALL_SPEED = 1.0;
	constexpr auto PADDLE_WIDTH = 15;
	constexpr auto PADDLE_HEIGHT = 85;
	constexpr auto PADDLE_SPEED = 1.0;

	//Vector Class
	class Vector {
	public:
		//variables for vector
		double x;
		double y;
		Vector(double, double);
		//operator overloads
		Vector operator* (double scale);
		Vector operator+ (Vector source);
		Vector& operator+= (const Vector& source);
	};

	//Ball Class
	class Ball {
	public:
		//Ball fields
		Vector position{ 0,0 };
		Vector velocity{ 0,0 };
		SDL_Rect ball{};
		//methods
		Ball(Vector,Vector);
		void Update(double);
		void Show(SDL_Renderer*);
	};

	enum class Collider {
		None = 0,
		Bottom,
		Middle,
		Top,
	};

	enum class WallCollider {
		None = 0,
		Top,
		Bottom,
		Left,
		Right
	 };
	
	//Paddle Class
	class Paddle {
	public:
		//Paddle fields
		Vector position{ 0,0 };
		Vector velocity{ 0,0 };
		SDL_Rect paddle{};
		//methods
		Paddle(Vector, Vector);
		void Update(double);
		void Show(SDL_Renderer*);
	};

	class Score {
	public:
		//Score Fields
		Vector position{ 0,0 };
		SDL_Surface* surf{ nullptr };
		SDL_Texture* texture{ nullptr };
		SDL_Renderer* rend{ nullptr };
		TTF_Font* gfont{ nullptr };
		SDL_Rect score_box{};
		//methods
		Score(Vector, SDL_Renderer*, TTF_Font*);
		void Show();
		void SetScore(int score);
		~Score();
	};

} //namespace Pong
