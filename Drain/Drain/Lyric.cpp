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
void Lyric::place(const std::string& lyric,
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
		character.place(position, startTime, endTime, scale);
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
	const auto small = 18.0f;
	const auto lineSpacing = small * 3.0f;
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
	place("song:", Vector2(0, lineSpacing * 0.5f), Time("01:03:319").ms, Time("01:05:584").ms, small);
	place("drain", Vector2(0, -lineSpacing * 0.5f), Time("01:03:602").ms, Time("01:05:584").ms, small);
	place("artist:", Vector2(0, lineSpacing * 0.5f), Time("01:05:584").ms, Time("01:07:848").ms, small);
	place("electrocutica", Vector2(0, -lineSpacing * 0.5f), Time("01:05:867").ms, Time("01:07:848").ms, small);
	place("mapper:", Vector2(0, lineSpacing * 0.5f), Time("01:07:848").ms, Time("01:10:112").ms, small);
	place("fartownik", Vector2(0, -lineSpacing * 0.5f), Time("01:08:131").ms, Time("01:10:112").ms, small);
	place("storyboarders:", Vector2(0, lineSpacing * 2.5f), Time("01:10:112").ms, Time("01:11:244").ms, small);
	place("szvx", Vector2(0, lineSpacing * 1.5f), Time("01:10:301").ms, Time("01:11:433").ms, small);
	place("niseboi", Vector2(0, lineSpacing * 0.5f), Time("01:10:489").ms, Time("01:11:621").ms, small);
	place("xenocidel", Vector2(0, -lineSpacing * 0.5f), Time("01:10:678").ms, Time("01:11:810").ms, small);
	place("naranja sagged", Vector2(0, -lineSpacing * 1.5f), Time("01:10:867").ms, Time("01:11:999").ms, small);
	place("dicingdice", Vector2(0, -lineSpacing * 2.5f), Time("01:11:055").ms, Time("01:12:187").ms, small);
	draw("push it aside", Vector2::Zero, Time("01:58:791").ms, Time("02:00:489").ms, fontSize);
	draw("my pain", Vector2::Zero, Time("02:01:338").ms, Time("02:05:584").ms, fontSize);
	draw("exchanged body heat", Vector2::Zero, Time("02:06:338").ms, Time("02:08:414").ms, fontSize);
	draw("again and again", Vector2::Zero, Time("02:09:475").ms, Time("02:14:640").ms, fontSize);
	draw("suffocating", Vector2::Zero, Time("02:16:904").ms, Time("02:18:744").ms, fontSize);
	draw("puff of smoke", Vector2::Zero, Time("02:19:452").ms, Time("02:21:150").ms, fontSize);
	draw("and i saw the world", Vector2::Zero, Time("02:24:263").ms, Time("02:27:659").ms, fontSize);
	draw("turn red", Vector2::Zero, Time("02:28:791").ms, Time("02:33:885").ms, fontSize);
	draw("dripping", Vector2::Zero, Time("04:04:168").ms, Time("04:04:805").ms, fontSize);
	draw("trickling", Vector2::Zero, Time("04:06:433").ms, Time("04:07:211").ms, fontSize);
	draw("dribbling", Vector2::Zero, Time("04:08:697").ms, Time("04:09:475").ms, fontSize);
	draw("a little more", Vector2::Zero, Time("04:12:942").ms, Time("04:14:640").ms, fontSize);
	draw("give me some more", Vector2::Zero, Time("04:17:470").ms, Time("04:19:168").ms, fontSize);
	draw("dripping", Vector2::Zero, Time("04:22:282").ms, Time("04:23:060").ms, fontSize);
	draw("trickling", Vector2::Zero, Time("04:24:546").ms, Time("04:25:324").ms, fontSize);
	draw("dribbling", Vector2::Zero, Time("04:26:739").ms, Time("04:27:588").ms, fontSize);
	draw("into my core", Vector2::Zero, Time("04:31:055").ms, Time("04:36:574").ms, fontSize);
	draw("i don't know", Vector2::Zero, Time("04:44:074").ms, Time("04:46:338").ms, fontSize);
	draw("when i lost", Vector2::Zero, Time("04:46:904").ms, Time("04:48:815").ms, fontSize);
	draw("my key", Vector2::Zero, Time("04:49:239").ms, Time("04:55:749").ms, fontSize);
	draw("take a vow", Vector2::Zero, Time("04:56:527").ms, Time("04:59:923").ms, fontSize);
	draw("and just", Vector2::Zero, Time("05:00:560").ms, Time("05:01:763").ms, fontSize);
	draw("kill me", Vector2::Zero, Time("05:02:187").ms, Time("05:08:838").ms, fontSize);
	draw("i don't know", Vector2::Zero, Time("05:20:301").ms, Time("05:22:565").ms, fontSize);
	draw("when i lost", Vector2::Zero, Time("05:23:131").ms, Time("05:24:970").ms, fontSize);
	draw("my key", Vector2::Zero, Time("05:25:395").ms, Time("05:31:621").ms, fontSize);
	draw("take a vow", Vector2::Zero, Time("05:32:753").ms, Time("05:36:150").ms, fontSize);
	draw("and just", Vector2::Zero, Time("05:36:857").ms, Time("05:37:989").ms, fontSize);
	draw("kill me", Vector2::Zero, Time("05:38:414").ms, Time("05:49:735").ms, fontSize);
	draw("when the wall broke down", Vector2::Zero, Time("06:31:055").ms, Time("06:32:329").ms, fontSize);
	draw("you were there", Vector2::Zero, Time("06:32:895").ms, Time("06:33:461").ms, fontSize);
	draw("but i was on my own", Vector2::Zero, Time("06:34:735").ms, Time("06:35:725").ms, fontSize);
}