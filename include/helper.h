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

	//Ball-Paddle Collision Check with collision box SAT method
	Collider ballCollision(const Ball& ball, const Paddle& paddle) {
		//ball dimmensions
		double ball_top = ball.position.y;
		double ball_bottom = ball.position.y + BALL_HEIGHT;
		double ball_left = ball.position.x;
		double ball_right = ball.position.x + BALL_WIDTH;
		//paddle dimmensions
		double paddle_top = paddle.position.y;
		double paddle_bottom = paddle.position.y + PADDLE_HEIGHT;
		double paddle_left = paddle.position.x;
		double paddle_right = paddle.position.x + PADDLE_WIDTH;

		//check overlap cases
		if (ball_top >= paddle_bottom) {
			return Collider::None;
		}
		if (ball_bottom <= paddle_top) { 
			return Collider::None; 
		}
		if (ball_left >= paddle_right) { 
			return Collider::None; 
		}
		if (ball_right <= paddle_left) { 
			return Collider::None; 
		}

		//segments of ball
		double paddle_third = paddle_bottom - (2.0 * PADDLE_HEIGHT / 3.0);
		double paddle_middle = paddle_bottom - (PADDLE_HEIGHT / 3.0);
		if ( (ball_bottom > paddle_top) &&  (ball_bottom < paddle_third)) { return Collider::Top; }
		else if ((ball_bottom > paddle_third) && (ball_bottom < paddle_middle)) { return Collider::Middle; }
		else { return Collider::Bottom; }
	}

	//change ball velocity upon comparison
	void CollisionVelocity(Ball& game_ball, Paddle& paddle_one, Paddle& paddle_two) {
		if (ballCollision(game_ball, paddle_one) != Collider::None || ballCollision(game_ball, paddle_two) != Collider::None)
		{
			//check collision types
			if (ballCollision(game_ball, paddle_one) == Collider::Top || ballCollision(game_ball, paddle_two) == Collider::Top)
			{
				game_ball.velocity.x = -game_ball.velocity.x;
				game_ball.velocity.y = -0.75 * game_ball.velocity.x;
			}

			if (ballCollision(game_ball, paddle_one) == Collider::Middle || ballCollision(game_ball, paddle_two) == Collider::Middle)
			{
				game_ball.velocity.x = -game_ball.velocity.x;
			}

			if (ballCollision(game_ball, paddle_one) == Collider::Bottom || ballCollision(game_ball, paddle_two) == Collider::Bottom)
			{
				game_ball.velocity.x = -game_ball.velocity.x;
				game_ball.velocity.y = 0.75 * game_ball.velocity.x;
			}
		}
	}

	//deleteGame
	void DeleteGame(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* scoreData) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		TTF_CloseFont(scoreData);
		TTF_Quit();
		SDL_Quit();
	}

} //namespace Pong


