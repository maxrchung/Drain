#include "Lyric.hpp"
#include <exception>
Lyric::Lyric(const std::string& lyric, const Vector2& center, const CharacterConfig& config) {
	const auto characters = createCharacters(lyric);
	draw(characters, center, config);
}
float Lyric::calculateWidth(const std::vector<Character>& characters, float scale) const {
	auto width = 0.0f;
	for (const auto& character : characters) {
		width += character.calculateWidth() * scale;
	}
	const auto totalKerning = (characters.size() - 1) * kerning * scale;
	width += totalKerning;
	return width;
}
std::vector<Character> Lyric::createCharacters(const std::string& lyric) const {
	std::vector<Character> characters;
	for (const auto& letter : lyric) {
		characters.push_back(Character(letter));
	}
	return characters;
}
void Lyric::draw(const std::vector<Character>& characters, const Vector2& center, const CharacterConfig& config) const {
	const auto lyricWidth = calculateWidth(characters, config.scale);
	auto left = Vector2(center.x - (lyricWidth / 2.0f), center.y);
	for (const auto& character : characters) {
		const auto position = Vector2(left.x + (character.calculateWidth() / 2.0f), left.y);
		character.draw(position, config);
		left.x += (character.calculateWidth() * config.scale) + (kerning * config.scale);
	}
}