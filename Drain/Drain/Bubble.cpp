#include "Bubble.hpp"
#include "Path.hpp"
#include "Storyboard.hpp"

#include <vector>

Bubble::Bubble()
	: sprites(create_sprites()) {
}


void Bubble::Move(int startTime, int endTime, Vector2 startPos, Vector2 endPos, Easing easing = Easing::Linear) {
	this->sprites.Move(startTime, endTime, startPos, endPos, easing);
	return;
}


void Bubble::MoveX(int startTime, int endTime, float startX, float endX, Easing easing = Easing::Linear) {
	this->sprites.MoveX(startTime, endTime, startX, endX, easing);
	return;
}


void Bubble::MoveY(int startTime, int endTime, float startY, float endY, Easing easing = Easing::Linear) {
	this->sprites.MoveX(startTime, endTime, startY, endY, easing);
	return;
}


void Bubble::Scale(int startTime, int endTime, float startScale, float endScale, Easing easing = Easing::Linear, int precision = 3) {
	this->sprites.Scale(startTime, endTime, startScale, endScale, easing, precision);
	return;
}


void Bubble::MoveAndScale(int startTime, int endTime, Vector2 startPos,Vector2 endPos,float startScale, float endScale, Easing easing = Easing::Linear, int precision = 3) {
	this->sprites.MoveAndScale(startTime, endTime, startPos, endPos, startScale, endScale, easing, precision);
	return;
}


SpriteCollection Bubble::create_sprites() {
	int highlight_count = w_rand(this->min_highlight, this->max_highlight);

	std::vector<Sprite *> sprite_vector;
	std::vector<Vector2> location;
	sprite_vector.push_back(Storyboard::CreateSprite(getPath(Path::Circle)));
	
	for(int i = 0; i < highlight_count - 1; ++i) {
		Vector2 offset = Vector2::Zero;
		offset.x = (this->sprite_size / 2) * w_rand(-1, 1);
		offset.y = (this->sprite_size / 2) * w_rand(-1, 1);
		sprite_vector.push_back(Storyboard::CreateSprite(getPath(Path::Circle), offset));
		location.push_back(offset);
	}

	return SpriteCollection(sprite_vector, location);
}


float Bubble::w_rand(float min, float max) {
	float out = (float)rand() / RAND_MAX;
	out *= (max - min);
	out += min;

	return out;	       
}
