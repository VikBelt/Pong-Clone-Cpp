#pragma once
#include <iostream>
#include <SDL_ttf.h>
#include <SDL.h>

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
constexpr auto BALL_WIDTH = 20;
constexpr auto BALL_HEIGHT = 20;

class Ball {
public:
	//Ball fields
	Vector position{ 0,0 };
	SDL_Rect ball{};
	//methods
	Ball(Vector);
	void Show(SDL_Renderer*);
};

//Paddle Class
constexpr auto PADDLE_WIDTH = 5;
constexpr auto PADDLE_HEIGHT = 70;

class Paddle {
public:
	//Paddle fields
	Vector position{ 0,0 };
	SDL_Rect paddle{};
	//methods
	Paddle(Vector);
	void Show(SDL_Renderer*);
};

class Score {
public:
	//Score Fields
	Vector position{ 0,0 };
	SDL_Surface* surf{nullptr};
	SDL_Texture* texture{nullptr};
	SDL_Renderer* rend{nullptr};
	TTF_Font* gfont{nullptr};
	SDL_Rect score_box{};
	//methods
	Score(Vector,SDL_Renderer*, TTF_Font*);
	void Show();
	~Score();
};
