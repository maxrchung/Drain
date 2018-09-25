#include "Text.hpp"
#include <algorithm>
#include <exception>
#include <limits>
const RandomRange Text::poemScale = RandomRange(8, 12);
const RandomRange Text::poemSpacing = RandomRange(10, 26);
void Text::draw(const std::string& lyric,
				const Vector2& center,
				const int startTime,
				const int endTime) {
	const auto characters = createCharacters(lyric);
	const auto totalWidth = calculateWidth(characters, lyricScale);
	auto left = Vector2(center.x - (totalWidth / 2.0f), center.y);
	for (const auto& character : characters) {
		const auto characterWidth = character.calculateWidth(lyricScale);
		const auto center = character.calculateLeftToCenter(lyricScale);
		const auto position = Vector2(left.x + center, left.y);
		character.draw(position, startTime, endTime, lyricScale);
		left.x += characterWidth + (tracking * lyricScale);
	}
}
void Text::place(const std::vector<std::string>& stanza,
				 const int startTime,
				 const int endTime) {
	std::vector<std::vector<Character>> lines;
	std::for_each(stanza.begin(), stanza.end(), [&](const auto& line) {
		lines.push_back(createCharacters(line));
	});
	std::vector<int> scales(lines.size());
	std::vector<int> spacers(lines.size() - 1);
	for (auto i = 0; i < lines.size(); ++i) {
		scales[i] = poemScale.calculate();
		if (i != lines.size() - 1) {
			spacers[i] = poemSpacing.calculate();
		}
	}
	auto totalHeight = 0;
	for (auto i = 0; i < lines.size() - 1; ++i) {
		const auto& line = lines[i];
		const auto scale = scales[i];
		totalHeight += calculateHeight(line, scale);
		if (i != lines.size() - 1) {
			const auto spacer = spacers[i];
			totalHeight += spacer;
		}
	}
	auto top = totalHeight / 2.0f;
	for (auto i = 0; i < lines.size(); ++i) {
		const auto& line = lines[i];
		const auto scale = scales[i];
		const auto center = Vector2(0, top - calculateTopToCenter(line, scale));
		const auto totalWidth = calculateWidth(line, scale);
		auto left = Vector2(-totalWidth / 2.0f, center.y);
		for (const auto& character : line) {
			const auto characterWidth = character.calculateWidth(scale);
			const auto position = Vector2(left.x + character.calculateLeftToCenter(scale), left.y);
			character.place(position, startTime, endTime, scale);
			left.x += characterWidth + (tracking * scale);
		}
		if (i != lines.size() - 1) {
			top -= calculateHeight(line, scale);
			top -= spacers[i];
		}
	}
}
float Text::calculateTopToCenter(const std::vector<Character>& characters, const float scale) {
	auto max = std::numeric_limits<float>::min();
	for (const auto& character : characters) {
		const auto center = character.calculateTopToCenter(scale);
		if (center > max) {
			max = center;
		}
	}
	return max;
}
float Text::calculateHeight(const std::vector<Character>& characters, const float scale) {
	auto bottom = std::numeric_limits<float>::max();
	auto top = std::numeric_limits<float>::min();
	for (const auto& character : characters) {
		const auto& strokes = character.getStrokes();
		if (strokes.empty()) {
			continue;
		}
		for (const auto& stroke : strokes) {
			const auto startY = stroke->getStartPosition().y * scale;
			if (startY < bottom) {
				bottom = startY;
			}
			if (startY > top) {
				top = startY;
			}
			const auto endY = stroke->getEndPosition().y * scale;
			if (endY < bottom) {
				bottom = endY;
			}
			if (endY > top) {
				top = endY;
			}
		}
	}
	const auto height = top - bottom + Stroke::thickness * scale;
	return height;
}
float Text::calculateWidth(const std::vector<Character>& characters, const float scale) {
	auto width = 0.0f;
	for (const auto& character : characters) {
		width += character.calculateWidth(scale);
	}
	const auto totalTracking = (characters.size() - 1) * tracking * scale;
	const auto totalWidth = width + totalTracking;
	return totalWidth;
}
std::vector<Character> Text::createCharacters(const std::string& lyric) {
	std::vector<Character> characters;
	for (const auto& letter : lyric) {
		characters.push_back(Character(letter));
	}
	return characters;
}
void Text::render() {
	// Uncomment for banner use only
	//draw("drain", Vector2::Zero, Time("00:03:000").ms, Time("00:03:000").ms + Timing::whole * 4);

	std::cout << "Rendering Text..." << std::endl;

	// Lyric 1
	draw("suffocating", Vector2::Zero, Time("00:05:584").ms, Time("00:06:999").ms);
	draw("puff of smoke", Vector2::Zero, Time("00:08:131").ms, Time("00:09:475").ms);
	draw("i took your breath in", Vector2::Zero, Time("00:14:357").ms, Time("00:16:055").ms);
	draw("and you spoke", Vector2::Zero, Time("00:17:187").ms, Time("00:18:602").ms);
	draw("and i saw the world", Vector2::Zero, Time("00:21:999").ms, Time("00:25:678").ms);
	draw("turn white", Vector2::Zero, Time("00:26:527").ms, Time("00:35:159").ms);
	draw("are you still calling me", Vector2::Zero, Time("00:36:716").ms, Time("00:38:697").ms);
	draw("i melt", Vector2::Zero, Time("00:40:395").ms, Time("00:49:168").ms);
	draw("into", Vector2::Zero, Time("00:49:452").ms, Time("00:50:867").ms);
	draw("your voice", Vector2::Zero, Time("00:51:716").ms, Time("00:52:565").ms);
	// Credits
	place({
		"song:",
		"drain"
		  }, Time("01:03:319").ms, Time("01:05:584").ms);
	place({
		"artist:",
		"electrocutica"
		  }, Time("01:05:584").ms, Time("01:07:848").ms);
	place({
		"mapper:",
		"fartownik"
		  }, Time("01:07:848").ms, Time("01:10:112").ms);
	place({
		"storyboarders:",
		"szvx",
		"niseboi",
		"xenocidel",
		"naranja sagged",
		"dicingdice"
		  }, Time("01:10:112").ms, Time("01:12:187").ms);
	// Poem 1
	place({
		"chained and bound",
		"in a corner of empty space",
		"you whispered against the wall",
		"pleas, pleas of help",
		  }, Time("01:12:376").ms, Time("01:21:433").ms);
	place({
		"a torrent of blurs outside",
		"the whole world passed by",
		"as you cried",
		"cried and cried",
		  }, Time("01:21:433").ms, Time("01:30:489").ms);
	place({
		"drowning",
		"dangling in the abyss",
		"your fingers outstretched",
		"searching, for anything",
		"anyone out there",
		  }, Time("01:30:489").ms, Time("01:39:546").ms);
	place({
		"i reached out",
		"and we touched.",
		"for a second",
		"forming a bond",
		  }, Time("01:39:546").ms, Time("01:44:074").ms);
	place({
		"trust in me",
		"follow me",
		"and you'll find peace,",
		"i promised",
		  }, Time("01:44:074").ms, Time("01:48:602").ms);
	place({
		"so began our nights",
		"of running away",
		"trips of respite",
		"far away",
		  }, Time("01:48:602").ms, Time("01:53:131").ms);
	place({
		"through city streets",
		"and rainy nights",
		"we splashed and danced",
		"atop puddles",
		  }, Time("01:53:131").ms, Time("01:57:659").ms);
	// Lyric 2
	draw("pushing aside", Vector2::Zero, Time("01:58:791").ms, Time("02:00:489").ms);
	draw("my pain", Vector2::Zero, Time("02:01:338").ms, Time("02:05:584").ms);
	draw("exchanged body heat", Vector2::Zero, Time("02:06:338").ms, Time("02:08:414").ms);
	draw("again and again", Vector2::Zero, Time("02:09:475").ms, Time("02:14:640").ms);
	draw("suffocating", Vector2::Zero, Time("02:16:904").ms, Time("02:18:744").ms);
	draw("puff of smoke", Vector2::Zero, Time("02:19:452").ms, Time("02:21:150").ms);
	draw("and i saw the world", Vector2::Zero, Time("02:24:263").ms, Time("02:27:659").ms);
	draw("turn red", Vector2::Zero, Time("02:28:791").ms, Time("02:32:753").ms);
	// Poem 2
	place({
		"your voice pierced the rain",
		"singing, screaming in song"
		  }, Time("02:33:885").ms, Time("02:38:414").ms);
	place({
		"for a few moments then",
		"we forgot the sad world",
		"crying in its sweet dream",
		  }, Time("02:38:414").ms, Time("02:42:949").ms);
	place({
		"you and i laughed",
		"stumbled through alleyways",
		"exploring every nook"
		  }, Time("02:42:949").ms, Time("02:47:470").ms);
	place({
		"clasping tightly",
		"i dragged us along",
		"in a frenzied daze",
		"night after night",
		  }, Time("02:47:470").ms, Time("02:51:999").ms);
	place({
		"until a light",
		"cusping the sky",
		"signaled a return",
		"to daily life",
		  }, Time("02:51:999").ms, Time("02:56:527").ms);
	place({
		"lost in the morning fog",
		"we parted ways",
		"separated by",
		"our different worlds",
		  }, Time("02:56:527").ms, Time("03:01:055").ms);
	place({
		"in hiding we bid our time",
		"waiting for the next chance",
		"to sneak out in the rain",
		  }, Time("03:01:055").ms, Time("03:05:584").ms);
	place({
		"night by night",
		"we met each other",
		"night by night",
		"we escaped",
		  }, Time("03:05:584").ms, Time("03:10:112").ms);
	place({
		"counting the moons",
		"from crescent to full",
		"every adventure",
		"one to remember",
		  }, Time("03:10:112").ms, Time("03:14:640").ms);
	place({
		"through the seasons",
		"time passed",
		"the sun rose sooner",
		"and our time, shorter",
		  }, Time("03:14:640").ms, Time("03:19:168").ms);
	place({
		"runs became walks",
		"laughs became smiles",
		"now we took shelter",
		"from the pouring nights",
		  }, Time("03:19:168").ms, Time("03:23:697").ms);
	place({
		"a toll, a price to pay",
		"with your mind and body",
		"a cost and affordance",
		"for each trip",
		  }, Time("03:23:697").ms, Time("03:28:225").ms);
	place({
		"with exhaustion",
		"we barely met the night's end",
		"to catch the day's start",
		  }, Time("03:28:225").ms, Time("03:32:753").ms);
	place({
		"but one night",
		"we failed to make it back",
		"lost in the maze",
		"of winding streets",
		  }, Time("03:32:753").ms, Time("03:37:282").ms);
	place({
		"as the day broke",
		"ghosts and demons",
		"evil of all kind",
		"spawned from the shadows",
		  }, Time("03:37:282").ms, Time("03:41:810").ms);
	place({
		"every dark corner",
		"hid encroaching fears",
		"forcing us to run away",
		"down frantic paths",
		  }, Time("03:41:810").ms, Time("03:46:338").ms);
	place({
		"around corners and bends",
		"a storm of movements",
		  }, Time("03:46:338").ms, Time("03:48:602").ms);
	place({
		"with a misstep",
		"you tumbled to the floor",
		"and a swarm of shadows",
		"swallowed you whole",
		  }, Time("03:48:602").ms, Time("03:53:131").ms);
	place({
		"a panic, a struggle",
		"pulling you up",
		"but we broke apart",
		"and lost touch",
		  }, Time("03:53:131").ms, Time("03:57:659").ms);
	place({
		"a final scream",
		"left your lips",
		"before the void took you",
		"and i ran, ran away",
		  }, Time("03:57:659").ms, Time("04:04:168").ms);
	// Lyric 3
	draw("dripping", Vector2::Zero, Time("04:04:168").ms, Time("04:05:805").ms);
	draw("trickling", Vector2::Zero, Time("04:06:433").ms, Time("04:07:211").ms);
	draw("dribbling", Vector2::Zero, Time("04:08:697").ms, Time("04:09:475").ms);
	draw("a little more", Vector2::Zero, Time("04:12:942").ms, Time("04:14:640").ms);
	draw("give me some more", Vector2::Zero, Time("04:17:470").ms, Time("04:19:168").ms);
	draw("dripping", Vector2::Zero, Time("04:22:282").ms, Time("04:23:060").ms);
	draw("trickling", Vector2::Zero, Time("04:24:546").ms, Time("04:25:324").ms);
	draw("dribbling", Vector2::Zero, Time("04:26:739").ms, Time("04:27:588").ms);
	draw("into my core", Vector2::Zero, Time("04:31:055").ms, Time("04:36:574").ms);
	draw("i don't know", Vector2::Zero, Time("04:44:074").ms, Time("04:46:338").ms);
	draw("when i lost", Vector2::Zero, Time("04:46:904").ms, Time("04:48:815").ms);
	draw("my key", Vector2::Zero, Time("04:49:239").ms, Time("04:55:749").ms);
	draw("take a vow", Vector2::Zero, Time("04:56:527").ms, Time("04:59:923").ms);
	draw("and just", Vector2::Zero, Time("05:00:560").ms, Time("05:01:763").ms);
	draw("kill me", Vector2::Zero, Time("05:02:187").ms, Time("05:08:838").ms);
	draw("i don't know", Vector2::Zero, Time("05:20:301").ms, Time("05:22:565").ms);
	draw("when i lost", Vector2::Zero, Time("05:23:131").ms, Time("05:24:970").ms);
	draw("my key", Vector2::Zero, Time("05:25:395").ms, Time("05:31:621").ms);
	draw("take a vow", Vector2::Zero, Time("05:32:753").ms, Time("05:36:150").ms);
	draw("and just", Vector2::Zero, Time("05:36:857").ms, Time("05:37:989").ms);
	draw("kill me", Vector2::Zero, Time("05:38:414").ms, Time("05:49:735").ms);
	// Poem 3
	place({
		"it wasn't until evening",
		"that i returned to the city",
		"where your body laid",
		"was a shard of your soul",
		  }, Time("05:57:659").ms, Time("06:02:187").ms);
	place({
		"a memory, of feeling",
		"of thought and prayer",
		"a moment of bliss",
		"that you captured",
		  }, Time("06:02:187").ms, Time("06:06:716").ms);
	place({
		"above",
		"clouds gathered in the sky",
		"the first drops",
		"dotted the landscape",
		  }, Time("06:06:716").ms, Time("06:11:244").ms);
	place({
		"more and more",
		"fragments of you appeared",
		"twinkling and sparkling",
		"in the wet glow",
		  }, Time("06:11:244").ms, Time("06:15:772").ms);
	place({
		"i reached out",
		"for all the sharp pieces",
		"pooled them to my cut hands",
		  }, Time("06:15:772").ms, Time("06:20:301").ms);
	place({
		"was it right",
		"was it good",
		"was it worth it",
		  }, Time("06:20:301").ms, Time("06:24:829").ms);
	place({
		"i kissed the fragments",
		"then consume them all",
		  }, Time("06:24:829").ms, Time("06:31:055").ms);
	// Lyric 4
	draw("when the wall broke down", Vector2::Zero, Time("06:31:055").ms, Time("06:32:329").ms);
	draw("you were there", Vector2::Zero, Time("06:32:895").ms, Time("06:33:885").ms);
	draw("but i was on my own", Vector2::Zero, Time("06:34:735").ms, Time("06:35:725").ms);
}
