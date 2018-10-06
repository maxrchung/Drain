#include "Text.hpp"
#include <algorithm>
#include <exception>
#include <limits>
const RandomRange Text::poemScale = RandomRange(8, 12);
const RandomRange Text::poemSpacing = RandomRange(10, 26);
void Text::draw(const std::string& lyric,
				const std::string& pStartTime,
				const std::string& pEndTime,
				const Vector2& center) {
	const auto startTime = Time(pStartTime).ms;
	const auto endTime = Time(pEndTime).ms;
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
				 const std::string& pStartTime,
				 const std::string& pEndTime) {
	const auto startTime = Time(pStartTime).ms;
	const auto endTime = Time(pEndTime).ms;
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
	//const auto bannerEndTime = Time(3000 + Timing::whole * 4).format;
	//draw("drain", "00:03:000", bannerEndTime;

	std::cout << "Rendering Text..." << std::endl;

	// Lyric 1
	draw("suffocating", "00:05:584", "00:06:999");
	draw("puff of smoke", "00:08:131", "00:09:475");
	draw("i took your breath in", "00:14:357", "00:16:055");
	draw("and you spoke", "00:17:187", "00:18:602");
	draw("and i saw the world", "00:21:999", "00:25:678");
	draw("turn white", "00:26:527", "00:35:159");
	draw("are you still calling me", "00:36:716", "00:38:697");
	draw("i melt", "00:40:395", "00:49:168");
	draw("into", "00:49:452", "00:50:867");
	draw("your voice", "00:51:716", "00:52:565");
	// Credits
	place({
		"song:",
		"drain"
		  }, "01:03:319", "01:05:584");
	place({
		"artist:",
		"electrocutica"
		  }, "01:05:584", "01:07:848");
	place({
		"mapper:",
		"fartownik"
		  }, "01:07:848", "01:10:112");
	place({
		"storyboarders:",
		"s2vx",
		"naranja sagged",
		"niseboi",
		"xenocidel",
		"dicingdice"
		  }, "01:10:112", "01:12:187");
	// Poem 1
	place({
		"chained and bound",
		"in a corner of empty space",
		"you whispered against the wall",
		"pleas, pleas of help",
		  }, "01:12:376", "01:21:433");
	place({
		"a torrent of blurs outside",
		"the whole world passed by",
		"as you cried",
		"cried and cried",
		  }, "01:21:433", "01:30:489");
	place({
		"drowning",
		"dangling in the abyss",
		"your fingers outstretched",
		"searching, for anything",
		"anyone out there",
		  }, "01:30:489", "01:39:546");
	place({
		"i reached",
		"and we touched.",
		"for a second",
		"forming a bond",
		  }, "01:39:546", "01:44:074");
	place({
		"trust in me",
		"follow me",
		"and you'll find peace,",
		"i promised",
		  }, "01:44:074", "01:48:602");
	place({
		"so began our nights",
		"of running away",
		"trips of respite",
		"far away",
		  }, "01:48:602", "01:53:131");
	place({
		"through city streets",
		"and rainy nights",
		"we splashed and danced",
		"atop puddles",
		  }, "01:53:131", "01:57:659");
	// Lyric 2
	draw("pushing aside", "01:58:791", "02:00:489");
	draw("my pain", "02:01:338", "02:05:584");
	draw("exchanged body heat", "02:06:338", "02:08:414");
	draw("again and again", "02:09:475", "02:14:640");
	draw("suffocating", "02:16:904", "02:18:744");
	draw("puff of smoke", "02:19:452", "02:21:150");
	draw("and i saw the world", "02:24:263", "02:27:659");
	draw("turn red", "02:28:791", "02:32:753");
	// Poem 2
	place({
		"your voice pierced the rain",
		"singing, screaming in song"
		  }, "02:33:885", "02:38:414");
	place({
		"for a few moments then",
		"we forgot the sad world",
		"crying in its sweet dream",
		  }, "02:38:414", "02:42:949");
	place({
		"you and i laughed",
		"stumbled through alleyways",
		"exploring every nook"
		  }, "02:42:949", "02:47:470");
	place({
		"clasping tightly",
		"i dragged us along",
		"in a frenzied daze",
		"night after night",
		  }, "02:47:470", "02:51:999");
	place({
		"until a light",
		"cusping the sky",
		"signaled us back",
		"to daily life",
		  }, "02:51:999", "02:56:527");
	place({
		"lost in the morning fog",
		"we parted ways",
		"separated by different worlds",
		  }, "02:56:527", "03:01:055");
	place({
		"in hiding we bid our time",
		"waiting for the next chance",
		"to drench in the rain",
		  }, "03:01:055", "03:05:584");
	place({
		"night by night",
		"we met each other",
		"night by night",
		"we escaped",
		  }, "03:05:584", "03:10:112");
	place({
		"counting the moons",
		"from crescent to full",
		"every adventure",
		"one to remember",
		  }, "03:10:112", "03:14:640");
	place({
		"through the seasons",
		"time passed",
		"the sun rose sooner",
		"and our time, shorter",
		  }, "03:14:640", "03:19:168");
	place({
		"runs became walks",
		"laughs became smiles",
		"now we took shelter",
		"from the pouring nights",
		  }, "03:19:168", "03:23:697");
	place({
		"a toll, a price to pay",
		"with your mind and body",
		"a cost and affordance",
		"for each trip",
		  }, "03:23:697", "03:28:225");
	place({
		"with exhaustion",
		"we barely met the night's end",
		"to catch the day's start",
		  }, "03:28:225", "03:32:753");
	place({
		"until one night",
		"we failed to return",
		"lost in the maze",
		"of winding streets",
		  }, "03:32:753", "03:37:282");
	place({
		"as day broke",
		"ghosts and demons",
		"evil of all kind",
		"spawned from the shadows",
		  }, "03:37:282", "03:41:810");
	place({
		"every dark corner",
		"hid encroaching fears",
		"pushing us to escape",
		"down frantic paths",
		  }, "03:41:810", "03:46:338");
	place({
		"around corners and bends",
		"a storm of movements",
		  }, "03:46:338", "03:48:602");
	place({
		"with a misstep",
		"you tumbled to the floor",
		"where a swarm of shadows",
		"swallowed you whole",
		  }, "03:48:602", "03:53:131");
	place({
		"a panic, struggle",
		"pulling you up",
		"but we broke apart",
		"lost touch",
		  }, "03:53:131", "03:57:659");
	place({
		"a final scream",
		"left your lips",
		"before the void took you",
		"and i ran, ran away",
		  }, "03:57:659", "04:04:168");
	// Lyric 3
	draw("dripping", "04:04:168", "04:05:805");
	draw("trickling", "04:06:433", "04:07:211");
	draw("dribbling", "04:08:697", "04:09:475");
	draw("a little more", "04:12:942", "04:14:640");
	draw("give me some more", "04:17:470", "04:19:168");
	draw("dripping", "04:22:282", "04:23:060");
	draw("trickling", "04:24:546", "04:25:324");
	draw("dribbling", "04:26:739", "04:27:588");
	draw("into my core", "04:31:055", "04:36:574");
	draw("i don't know", "04:44:074", "04:46:338");
	draw("when i lost", "04:46:904", "04:48:815");
	draw("my key", "04:49:239", "04:55:749");
	draw("take a vow", "04:56:527", "04:59:923");
	draw("and just", "05:00:560", "05:01:763");
	draw("kill me", "05:02:187", "05:08:838");
	draw("i don't know", "05:20:301", "05:22:565");
	draw("when i lost", "05:23:131", "05:24:970");
	draw("my key", "05:25:395", "05:31:621");
	draw("take a vow", "05:32:753", "05:36:150");
	draw("and just", "05:36:857", "05:37:989");
	draw("kill me", "05:38:414", "05:49:735");
	// Poem 3
	place({
		"it wasn't until evening",
		"that i returned to the city",
		"where your body laid",
		"was a shard of your soul",
		  }, "05:57:659", "06:02:187");
	place({
		"a memory, of feeling",
		"of thought and prayer",
		"a moment of bliss",
		"that you captured",
		  }, "06:02:187", "06:06:716");
	place({
		"clouds gathered above",
		"the first drops",
		"sprinkling the sky",
		"dotted the landscape",
		  }, "06:06:716", "06:11:244");
	place({
		"more and more",
		"fragments of you appeared",
		"twinkling and sparkling",
		"in the wet glow",
		  }, "06:11:244", "06:15:772");
	place({
		"i reached",
		"for all the sharp pieces",
		"pooled them to my cut hands",
		  }, "06:15:772", "06:20:301");
	place({
		"was it right",
		"was it good",
		"was it worth it",
		  }, "06:20:301", "06:24:829");
	place({
		"i kissed the fragments",
		"then consume them all",
		  }, "06:24:829", "06:31:055");
	// Lyric 4
	draw("when the wall broke down", "06:31:055", "06:32:329");
	draw("you were there", "06:32:895", "06:33:885");
	draw("but i was on my own", "06:34:735", "06:35:725");
}
