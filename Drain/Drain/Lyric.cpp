#include "Lyric.hpp"
#include <exception>
Lyric::Lyric(const std::string& lyric,
			 const Vector2& center,
			 const int startTime,
			 const int endTime,
			 const int drawSpeed,
			 const Color& foreground,
			 const Color& background,
			 const float scale) {
	const auto characters = createCharacters(lyric);
	const auto lyricWidth = calculateWidth(characters, scale);
	render(characters, lyricWidth, center, startTime, endTime, drawSpeed, foreground, background, scale);
}
float Lyric::calculateWidth(const std::vector<Character>& characters, const float scale) {
	auto width = 0.0f;
	for (const auto& character : characters) {
		width += character.calculateWidth(scale);
	}
	const auto totalKerning = (characters.size() - 1) * kerning * scale;
	width += totalKerning;
	return width;
}
std::vector<Character> Lyric::createCharacters(const std::string& lyric) {
	std::vector<Character> characters;
	for (const auto& letter : lyric) {
		characters.push_back(Character(letter));
	}
	return characters;
}
void Lyric::render(const std::vector<Character>& characters,
				   const float lyricWidth,
				   const Vector2& center,
				   const int startTime,
				   const int endTime,
				   const int drawSpeed,
				   const Color& foreground,
				   const Color& background,
				   const float scale) {
	auto left = Vector2(center.x - (lyricWidth / 2.0f), center.y);
	for (const auto& character : characters) {
		const auto characterWidth = character.calculateWidth(scale);
		const auto position = Vector2(left.x + (characterWidth / 2.0f), left.y);
		character.render(position, startTime, endTime, drawSpeed, foreground, background, scale);
		left.x += (characterWidth * scale) + (kerning * scale);
	}
}