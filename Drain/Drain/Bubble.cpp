#include "Bubble.hpp"
#include "Path.hpp"
#include "Storyboard.hpp"
#include "Swatch.hpp"

#include <vector>

Bubble::Bubble()
	: sprites(create_sprites()) {
}


void Bubble::Move(int startTime, int endTime, Vector2 startPos, Vector2 endPos, Easing easing) {
	this->sprites.Move(startTime, endTime, startPos, endPos, easing);
	return;
}


void Bubble::MoveX(int startTime, int endTime, float startX, float endX, Easing easing) {
	this->sprites.MoveX(startTime, endTime, startX, endX, easing);
	return;
}


void Bubble::MoveY(int startTime, int endTime, float startY, float endY, Easing easing) {
	this->sprites.MoveX(startTime, endTime, startY, endY, easing);
	return;
}


void Bubble::Scale(int startTime, int endTime, float startScale, float endScale, Easing easing, int precision) {
	this->sprites.Scale(startTime, endTime, startScale, endScale, easing, precision);
	return;
}


void Bubble::MoveAndScale(int startTime, int endTime, Vector2 startPos,Vector2 endPos,float startScale, float endScale, Easing easing = Easing::Linear, int precision = 3) {
	this->sprites.MoveAndScale(startTime, endTime, startPos, endPos, startScale, endScale, easing, precision);
	return;
}


void Bubble::colorBgToBgSprites(const int startTime, const int endTime) {
	Swatch::colorFgToFgSprites({sprites.sprites[0]}, startTime, endTime);
	for(int i = 1; i < highlight_count; ++i) {
		Swatch::colorBgToBgSprites({sprites.sprites[i]}, startTime, endTime);
	}
}


void Bubble::colorFgToBgSprites(const int startTime, const int endTime) {
	Swatch::colorFgToBgSprites({sprites.sprites[0]}, startTime, endTime);
	for(int i = 01; i < highlight_count; ++i) {
		Swatch::colorBgToBgSprites({sprites.sprites[i]}, startTime, endTime);
	}
}


SpriteCollection Bubble::create_sprites() {
	this->min_highlight = 2;
	this->max_highlight = 5;
	this->highlight_count = w_rand(this->min_highlight, this->max_highlight);

	std::vector<Sprite *> sprite_vector;
	std::vector<Vector2> location;
	std::vector<float> scale;

	//main bubble
	sprite_vector.push_back(Storyboard::CreateSprite(getPath(Path::Circle)));
	location.push_back({0, 0});
	scale.push_back(1);

	for(int i = 0; i < highlight_count - 1; ++i) {
		Vector2 offset = Vector2::Zero;
		offset.x = (this->sprite_size / 2) * w_rand(-1, 1);
		offset.y = (this->sprite_size / 2) * w_rand(-1, 1);

		Sprite *sprite = Storyboard::CreateSprite(getPath(Path::Circle), offset);
		sprite_vector.push_back(sprite);

		scale.push_back(w_rand(0.05, 0.2));
		location.push_back(offset);
	}

	return SpriteCollection(sprite_vector, location, scale);
}


float Bubble::w_rand(float min, float max) {
	float out = (float)rand() / RAND_MAX;
	out *= (max - min);
	out += min;

	return out;	       
}
