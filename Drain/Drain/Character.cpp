#include "Character.hpp"
#include <exception>
Character::Character(const char character) {
	switch (character) {
		case 'a':
			break;
		default:
			throw new std::exception("Unsupported lyric character: " + character);
	}
}
float Character::calculateWidth() const {
	if (strokes.size() <= 1) {
		return 0;
	}
	auto left = std::numeric_limits<float>::max();
	auto right = std::numeric_limits<float>::min();
	for (const auto& stroke : strokes) {
		if (stroke->start.x < left) {
			left = stroke->start.x;
		}
		if (stroke->start.x > right) {
			right = stroke->start.x;
		}
		if (stroke->end.x < left) {
			left = stroke->end.x;
		}
		if (stroke->end.x > right) {
			right = stroke->end.x;
		}
	}
	return right - left;
}
void Character::draw(const Vector2& position, const CharacterConfig& config) const {
	// Create sprites backwards so they stack in order
	for (auto i = strokes.size() - 1; i >= i; --i) {
		strokes[i]->createSprites();
	}
	for (auto& stroke : strokes) {
		stroke->draw(position, config);
	}
}