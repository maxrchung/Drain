#include "Lyric.hpp"
#include <exception>
Lyric::Lyric(const std::string& lyric, const CharacterConfig& config, const Vector2& center) {
	const auto characters = getCharacters(lyric);
	draw(characters, config, center);
}
std::vector<std::unique_ptr<Character>> Lyric::getCharacters(const std::string& lyric) const {
	std::vector<std::unique_ptr<Character>> characters;
	for (const auto& letter : lyric) {
		characters.push_back(Character::get(letter));
	}
	return characters;
}
float Lyric::calculateSize(const std::vector<std::unique_ptr<Character>>& characters, float scale) const {
	float size = 0.0f;
	for (const auto& character : characters) {
		size += character->getWidth() * scale;
	}
	const auto totalKerning = (characters.size() - 1) * kerning * scale;
	size += totalKerning;
	return size;
}
void Lyric::draw(const std::vector<std::unique_ptr<Character>>& characters, const CharacterConfig& config, const Vector2& center) const {
	const auto lyricWidth = calculateSize(characters, config.scale);
	auto left = Vector2(center.x - (lyricWidth / 2.0f), center.y);
	for (const auto& character : characters) {
		const auto position = Vector2(left.x + (character->getWidth() / 2.0f), left.y);
		character->draw(position, config);
		left.x += (character->getWidth() * config.scale) + (kerning * config.scale);
	}
}
