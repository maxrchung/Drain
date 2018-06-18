#pragma once

#include "Vector2.hpp"
#include "Sprite.hpp"
#include "SpriteCollection.hpp"
#include "Time.hpp"

class Raindrop {
public:
	Raindrop(float size, SpriteCollection droplet, Vector2 initial_2d_position, Vector2 final_2d_position, Time start, Time end);

	Vector2 initial_2d_position;
	Vector2 final_2d_position;
	Time start;
	Time end;
	float speed;
	float size;

	SpriteCollection droplet;
private:
	float min_speed;
	float max_speed;

	float min_size;
	float max_size;
};