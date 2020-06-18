#include <iostream>
#include "game_objects.h"

//Vector Class
Vector::Vector(double xpos = 0.0, double ypos = 0.0) : x{ xpos }, y{ ypos } {
	//Empty Body
}

Vector Vector::operator*(double scale) {
	return Vector(x * scale, y * scale);
}

Vector Vector::operator+(Vector source) {
	return Vector(x + source.x, y + source.y);
}

Vector& Vector::operator+=(const Vector& source) {
	x = x + source.x;
	y = y + source.y;
	return *this;
}

//Ball Class
Ball::Ball(Vector s_position) {
	//want to define the Ball rectangle
	position = s_position;
	ball.x = (int)position.x;
	ball.y = (int)position.y;
	ball.w = BALL_WIDTH;
	ball.h = BALL_HEIGHT;
}

void Ball::Show(SDL_Renderer* rend) {
	//want to display the rectangle from the constructor
	ball.x = (int)position.x;
	ball.y = (int)position.y;
	SDL_RenderFillRect(rend, &ball);
}

//Paddle Class
Paddle::Paddle(Vector s_position) {
	//want to define the Ball rectangle
	position = s_position;
	paddle.x = (int)position.x;
	paddle.y = (int)position.y;
	paddle.w = PADDLE_WIDTH;
	paddle.h = PADDLE_HEIGHT;
}

void Paddle::Show(SDL_Renderer* rend) {
	//want to display the rectangle from the constructor
	paddle.x = (int)position.x;
	paddle.y = (int)position.y;
	SDL_RenderFillRect(rend, &paddle);
}
