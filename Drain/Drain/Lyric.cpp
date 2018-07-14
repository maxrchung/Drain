#include "Lyric.hpp"
#include <exception>
void Lyric::draw(const std::string& lyric,
				 const Vector2& center,
				 const int startTime,
				 const int endTime,
				 const float scale) {
	const auto characters = createCharacters(lyric);
	const auto totalWidth = calculateWidth(characters, scale);
	auto left = Vector2(center.x - (totalWidth / 2.0f), center.y);
	for (const auto& character : characters) {
		const auto characterWidth = character.calculateWidth(scale);
		const auto center = character.calculateCenter(scale);
		const auto position = Vector2(left.x + center, left.y);
		character.draw(position, startTime, endTime, scale);
		left.x += characterWidth + (tracking * scale);
	}
}
float Lyric::calculateWidth(const std::vector<Character>& characters, const float scale) {
	auto width = 0.0f;
	for (const auto& character : characters) {
		width += character.calculateWidth(scale);
	}
	const auto totalTracking = (characters.size() - 1) * tracking * scale;
	const auto totalWidth = width + totalTracking;
	return totalWidth;
}
std::vector<Character> Lyric::createCharacters(const std::string& lyric) {
	std::vector<Character> characters;
	for (const auto& letter : lyric) {
		characters.push_back(Character(letter));
	}
	return characters;
}
void Lyric::render() {
	const auto fontSize = 25.0f;
	draw("suffocating", Vector2::Zero, Time("00:05:584").ms, Time("00:06:999").ms, fontSize);
	draw("puff of smoke", Vector2::Zero, Time("00:08:131").ms, Time("00:09:475").ms, fontSize);
	draw("i took your breath in", Vector2::Zero, Time("00:14:357").ms, Time("00:16:055").ms, fontSize);
	draw("and you spoke", Vector2::Zero, Time("00:17:187").ms, Time("00:18:602").ms, fontSize);
	draw("and i saw the world", Vector2::Zero, Time("00:21:999").ms, Time("00:25:678").ms, fontSize);
	draw("turn white", Vector2::Zero, Time("00:26:527").ms, Time("00:35:159").ms, fontSize);
	draw("are you still calling me", Vector2::Zero, Time("00:36:716").ms, Time("00:38:697").ms, fontSize);
	draw("i melt", Vector2::Zero, Time("00:40:395").ms, Time("00:49:168").ms, fontSize);
	draw("into", Vector2::Zero, Time("00:49:452").ms, Time("00:50:867").ms, fontSize);
	draw("your voice", Vector2::Zero, Time("00:51:716").ms, Time("00:52:565").ms, fontSize);

	//I melt into your voice
	//
	//Pushing aside my pain
	//Exchanged body heat
	//Again and again
	//Suffocating
	//Puff of smoke
	//And I saw the world turn red
	//
	//Dripping, trickling, dribbling
	//A little more
	//Give me some more
	//
	//Dripping, trickling, dribbling
	//Into my core
	//
	//I don’t know when I lost my key
	//Take a vow
	//And just kill me
	//
	//When the wall broke down,
	//You were there; but I was on my own.
}