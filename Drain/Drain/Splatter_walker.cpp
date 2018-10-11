#include "Splatter.hpp"
#include "Splatter_walker.hpp"
#include "Swatch.hpp"
#include "Vector2.hpp"


Splatter_walker::Splatter_walker(std::vector<SpriteCollection> sprites)
	: Walker::Walker(sprites) {}

/*
void moveCurrent(float distance, Time startTime, Time endTime) {
}
*/

// void Splatter_walker::moveSprites(float distance, Time startTime, Time endTime, float density) {
// 	int total_time = endTime.ms - startTime.ms;
// 	float speed = distance / total_time;

// 	const float sizeX = Vector2::ScreenSize.x/2 * 0.4;
// 	const float sizeY = Vector2::ScreenSize.y/2 * 0.4;

// 	int count = speed * density;
// 	for(int i = 0; i < count; ++i) {
// 		int int_start_time = startTime.ms + i * w_rand(0, 100);
// 		int int_end_time = int_start_time + w_rand(1000, total_time);

// 		if(int_end_time > endTime.ms)
// 			int_end_time = endTime.ms - w_rand(0, 2000);

// 		if(int_start_time > endTime.ms) {
// 			int_start_time = endTime.ms - 1000;
// 			int_end_time = endTime.ms;
// 			break;
// 		}


// 		float start_scale = min_scale;
// 		float end_scale = max_scale * w_rand(1, 5);

// 		Vector2 start_coord = Vector2(w_rand(-sizeX, sizeX),
// 					      w_rand(-sizeY, sizeY));

// 		Vector2 end_coord = findProjection(Vector2::Zero, start_coord);
// 		SpriteCollection sprite = create(startTime, {0, 0}, start_scale);

// 		sprite.MoveAndScale(int_start_time, int_end_time, start_coord, end_coord, start_scale, end_scale);
// 		Swatch::colorFgToFgSprites(sprite.sprites, int_start_time, int_end_time);
// 	}
// }


SpriteCollection create(const Time& startTime, const Vector2& centerPos, const float scale) {
	return Splatter::makeWalkerSplatter(startTime, centerPos, scale);
}
