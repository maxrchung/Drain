#pragma once

#include "Vector2.hpp"
#include "Sprite.hpp"
#include "Time.hpp"

class Raindrop {
public:
	Raindrop(float size, Sprite *sprite, Vector2 initial_2d_position, Vector2 final_2d_position, Time start, Time end);

	Vector2 initial_2d_position;
	Vector2 final_2d_position;
	Time start;
	Time end;
	float speed;
	float size;

	Sprite *sprite;

private:
	float min_speed;
	float max_speed;
	float min_size;
	//float max_speed;
};