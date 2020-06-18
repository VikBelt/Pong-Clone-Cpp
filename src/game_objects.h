#pragma once
#include <iostream>
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
