#include <iostream>
#include "game_objects.h"

//Class - Vector
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

//Class - Ball
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

//Class - Paddle
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

//Class - Score
Score::Score(Vector score_position, SDL_Renderer* renderer, TTF_Font* font_data) : rend{ renderer }, gfont{ font_data } 
{
	position = score_position;
	surf = TTF_RenderText_Solid(gfont, "0", { 0xFF, 0xFF, 0xFF, 0xFF });
	texture = SDL_CreateTextureFromSurface(renderer, surf);
	int width{};
	int height{};
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	score_box.x = (int)position.x;
	score_box.y = (int)position.y;
	score_box.w = width;
	score_box.h = height;
}

Score::~Score() {
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(texture);
}

void Score::Show() {
	SDL_RenderCopy(rend, texture, nullptr, &score_box);
}
