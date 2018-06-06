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
	auto width = 0.0f;
	for (const auto& stroke : strokes) {

	}
	return width;
}
void Character::draw(const Vector2& position, const CharacterConfig& config) const {

}