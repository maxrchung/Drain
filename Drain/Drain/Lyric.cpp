#include "Lyric.hpp"
#include <exception>
Lyric::Lyric(const std::string& lyric,
			 const Vector2& center,
			 const int start,
			 const int end,
			 const int drawSpeed,
			 const Color& foreground,
			 const Color& background,
			 const float scale) {
	const auto characters = createCharacters(lyric);
	const auto lyricWidth = calculateWidth(characters, scale);
	auto left = Vector2(center.x - (lyricWidth / 2.0f), center.y);
	for (const auto& character : characters) {
		const auto characterWidth = character.calculateWidth(scale);
		const auto position = Vector2(left.x + (characterWidth / 2.0f), left.y);
		character.draw(position, start, end, drawSpeed, foreground, background, scale);
		left.x += (characterWidth * scale) + (kerning * scale);
	}
}
float Lyric::calculateWidth(const std::vector<Character>& characters, const float scale) const {
	auto width = 0.0f;
	for (const auto& character : characters) {
		width += character.calculateWidth(scale) * scale;
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