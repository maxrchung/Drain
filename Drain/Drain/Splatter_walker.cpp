#include "Splatter.hpp"
#include "Splatter_walker.hpp"
#include "Swatch.hpp"
#include "Vector2.hpp"



/*
void moveCurrent(float distance, Time startTime, Time endTime) {
}
*/

void Splatter_walker::moveSprites(float distance, Time startTime, Time endTime, float density) {
	int total_time = endTime.ms - startTime.ms;
	float speed = distance / total_time;

	const float sizeX = Vector2::ScreenSize.x/2 * 0.4;
	const float sizeY = Vector2::ScreenSize.y/2 * 0.4;

	int count = speed * density;
	for(int i = 0; i < count; ++i) {
		int int_start_time = startTime.ms + i * w_rand(0, 100);
		int int_end_time = int_start_time + w_rand(1000, total_time);

		if(int_end_time > endTime.ms)
			int_end_time = endTime.ms - w_rand(0, 2000);

		if(int_start_time > endTime.ms) {
			int_start_time = endTime.ms - 1000;
			int_end_time = endTime.ms;
			break;
		}


		float start_scale = min_scale;
		float end_scale = max_scale * w_rand(1, 5);

		Vector2 start_coord = Vector2(w_rand(-sizeX, sizeX),
					      w_rand(-sizeY, sizeY));

		Vector2 end_coord = findProjection(Vector2::Zero, start_coord);
		SpriteCollection sprite = Splatter::makeWalkerSplatter(startTime, {0, 0}, start_scale);

		sprite.MoveAndScale(int_start_time, int_end_time, start_coord, end_coord, start_scale, end_scale);
		Swatch::colorFgToFgSprites(sprite.sprites, int_start_time, int_end_time);
	}
}

Vector2 Splatter_walker::findProjection(Vector2 a, Vector2 b) {
        Vector2 out = Vector2::Zero;

	Vector2 slopeV = b - a;
	float slope = slopeV.y / slopeV.x;
	float size_offset = this->sprite_size * this->max_scale * 5;

	Vector2 mid;
	if(slopeV.y < 0) {
		mid.y = -Vector2::ScreenSize.y/2 - size_offset;
	} else {
		mid.y = Vector2::ScreenSize.y/2 + size_offset;
	}

	if(slopeV.x < 0) {
		mid.x = -Vector2::ScreenSize.x/2 - size_offset;
	} else {
		mid.x = Vector2::ScreenSize.x/2 + size_offset;
	}

	switch((!!slopeV.y) | (!!slopeV.x << 1)) {
	case 0:
		break;

	case 1:
		out.x = mid.x;
		break;

	case 2:
		out.y = mid.y;
		break;

	case 3:
		out.y = slope * mid.x + a.y;
		out.x = (mid.y - a.y) / slope;
		if(std::abs(out.y) > Vector2::ScreenSize.y/2)
			out.y = mid.y;

		if(std::abs(out.x) > Vector2::ScreenSize.x/2)
			out.x = mid.x;

		break;
	}

	return out;
	
}

float Splatter_walker::w_rand(float min, float max) {
	float out = (float)rand() / RAND_MAX;
	out *= (max - min);
	out += min;

	return out;
}

