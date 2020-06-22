/* 
Created by Vikram Belthur 6.18.2020
I am making this file to add some cleanliness to the main file
*/

#pragma once
#include "game_objects.h"

namespace Pong {

	auto p1_score = 0;
	auto p2_score = 0;
	auto scale = 0.0;
	//Keys to Move Paddle
	enum gameKeys {
		paddleOneUp = 0,
		paddleOneDown,
		paddleTwoUp,
		paddleTwoDown
	};

	void GameCpu(Ball& game_ball, Paddle& paddle_two) {

		if (game_ball.position.y >= paddle_two.position.y) {
			paddle_two.velocity.y = 0.75 * PADDLE_SPEED;
		}
		else if (game_ball.position.y < paddle_two.position.y) {
			paddle_two.velocity.y = -0.75 * PADDLE_SPEED;
		}
		else {
			paddle_two.velocity.y = 0;
		}
	}
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
	
	//Check wall collision
	WallCollider wallCollision(Ball& ball) {
		//ball dimmensions
		double ball_top = ball.position.y;
		double ball_bottom = ball.position.y + BALL_HEIGHT;
		double ball_left = ball.position.x;
		double ball_right = ball.position.x + BALL_WIDTH;
		if (ball_left < 0.0) { return WallCollider::Left; }
		else if (ball_right > GAME_WIDTH) { return WallCollider::Right; }
		else if (ball_top < 0.0) { return WallCollider::Top; }
		else if (ball_bottom > GAME_HEIGHT) {return WallCollider::Bottom;}
		else { return WallCollider::None; }
	}

	
	//change ball velocity upon comparison
	void CollisionVelocity(Ball& game_ball, Paddle& paddle_one, Paddle& paddle_two) {
		if (ballCollision(game_ball, paddle_one) != Collider::None || ballCollision(game_ball, paddle_two) != Collider::None)
		{
			scale += 0.075;
			//check collision types
			if (ballCollision(game_ball, paddle_one) == Collider::Top || ballCollision(game_ball, paddle_two) == Collider::Top)
			{
				game_ball.velocity.x = -(game_ball.velocity.x + scale);
				game_ball.velocity.y = -0.75 * (game_ball.velocity.x+scale);
			}

			if (ballCollision(game_ball, paddle_one) == Collider::Middle || ballCollision(game_ball, paddle_two) == Collider::Middle)
			{
				game_ball.velocity.x = -(game_ball.velocity.x + scale);
			}

			if (ballCollision(game_ball, paddle_one) == Collider::Bottom || ballCollision(game_ball, paddle_two) == Collider::Bottom)
			{
				game_ball.velocity.x = -(game_ball.velocity.x + scale) ;
				game_ball.velocity.y = 0.75 *(game_ball.velocity.x+scale);
			}
		}
	}

	//effects of the Wall Collision
	void WallEffect(Ball& game_ball, Score& one_score, Score& two_score){
		if (wallCollision(game_ball) != WallCollider::None)
		{
			if (wallCollision(game_ball) == WallCollider::Left) {
				p2_score++;
				game_ball.position.y = GAME_HEIGHT / 2;
				game_ball.position.x = GAME_WIDTH / 2;
				two_score.SetScore(p2_score);
				scale = 0;
				game_ball.velocity.x = -1.0;
				game_ball.velocity.y = 0.0;
			}
			if (wallCollision(game_ball) == WallCollider::Right) {
				p1_score++;
				game_ball.position.y = GAME_HEIGHT / 2;
				game_ball.position.x = GAME_WIDTH / 2;
				one_score.SetScore(p1_score);
				scale = 0;
				game_ball.velocity.x = -1.0;
				game_ball.velocity.y = 0.0;
			}
			if (wallCollision(game_ball) == WallCollider::Top || wallCollision(game_ball) == WallCollider::Bottom)
			{
				game_ball.velocity.y = -game_ball.velocity.y;
			}
		}
	}

	//draw the net
	void DrawNet(SDL_Renderer* renderer) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 128, 0); //window background
		SDL_RenderClear(renderer);

		//create the game board
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //net color
		for (auto i = 0; i < GAME_HEIGHT; i++) {
			if (i % 5)	SDL_RenderDrawPoint(renderer, GAME_WIDTH / 2, i);
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
