#include "Text.hpp"
#include <exception>
const RandomRange Text::poemScale = RandomRange(900, 1500, 100);
void Text::draw(const std::string& lyric,
				 const Vector2& center,
				 const int startTime,
				 const int endTime) {
	const auto characters = createCharacters(lyric);
	const auto totalWidth = calculateWidth(characters, lyricScale);
	auto left = Vector2(center.x - (totalWidth / 2.0f), center.y);
	for (const auto& character : characters) {
		const auto characterWidth = character.calculateWidth(lyricScale);
		const auto center = character.calculateCenter(lyricScale);
		const auto position = Vector2(left.x + center, left.y);
		character.draw(position, startTime, endTime, lyricScale);
		left.x += characterWidth + (tracking * lyricScale);
	}
}
void Text::place(const std::string& lyric,
				const Vector2& center,
				const int startTime,
				const int endTime) {
	const auto scale = poemScale.calculate();
	const auto centerSpaced = center * 4.0f * scale;
	const auto characters = createCharacters(lyric);
	const auto totalWidth = calculateWidth(characters, scale);
	auto left = Vector2(centerSpaced.x - (totalWidth / 2.0f), centerSpaced.y);
	for (const auto& character : characters) {
		const auto characterWidth = character.calculateWidth(scale);
		const auto center = character.calculateCenter(scale);
		const auto position = Vector2(left.x + center, left.y);
		character.place(position, startTime, endTime, scale);
		left.x += characterWidth + (tracking * scale);
	}
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
float Text::getPoemScale(const float scale) {
	return scale + poemScale.calculate();
}
void Text::render() {
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
	place("song:", Vector2(0, 0.5f), Time("01:03:319").ms, Time("01:05:584").ms);
	place("drain", Vector2(0, -0.5f), Time("01:03:602").ms, Time("01:05:584").ms);
	place("artist:", Vector2(0, 0.5f), Time("01:05:584").ms, Time("01:07:848").ms);
	place("electrocutica", Vector2(0, -0.5f), Time("01:05:867").ms, Time("01:07:848").ms);
	place("mapper:", Vector2(0, 0.5f), Time("01:07:848").ms, Time("01:10:112").ms);
	place("fartownik", Vector2(0, -0.5f), Time("01:08:131").ms, Time("01:10:112").ms);
	place("storyboarders:", Vector2(0, 2.5f), Time("01:10:112").ms, Time("01:11:244").ms);
	place("szvx", Vector2(0, 1.5f), Time("01:10:301").ms, Time("01:11:433").ms);
	place("niseboi", Vector2(0, 0.5f), Time("01:10:489").ms, Time("01:11:621").ms);
	place("xenocidel", Vector2(0, -0.5f), Time("01:10:678").ms, Time("01:11:810").ms);
	place("naranja sagged", Vector2(0, -1.5f), Time("01:10:867").ms, Time("01:11:999").ms);
	place("dicingdice", Vector2(0, -2.5f), Time("01:11:055").ms, Time("01:12:187").ms);
	// Poem 1
	place("chained and bound",						Vector2(0, 1.5f),		Time("01:12:376").ms, Time("01:21:433").ms);
	place("in a corner of empty space",				Vector2(0, 0.5f),		Time("01:12:376").ms, Time("01:21:433").ms);
	place("you whispered against the wall",			Vector2(0, -0.5f),		Time("01:12:376").ms, Time("01:21:433").ms);
	place("pleas, pleas of help",					Vector2(0, -1.5f),		Time("01:12:376").ms, Time("01:21:433").ms);

	place("a torrent of blurs outside",				Vector2(0, 1.5f),		Time("01:21:433").ms, Time("01:30:489").ms);
	place("the whole world passed by",				Vector2(0, 0.5f),		Time("01:21:433").ms, Time("01:30:489").ms);
	place("as you cried",							Vector2(0, -0.5f),		Time("01:21:433").ms, Time("01:30:489").ms);
	place("cried and cried",						Vector2(0, -1.5f),		Time("01:21:433").ms, Time("01:30:489").ms);

	place("drowning",								Vector2(0, 2.0f),		Time("01:30:489").ms, Time("01:39:546").ms);
	place("dangling in the abyss",					Vector2(0, 1.0f),		Time("01:30:489").ms, Time("01:39:546").ms);
	place("your fingers outstretched",				Vector2(0, 0.0f),		Time("01:30:489").ms, Time("01:39:546").ms);
	place("searching, for anything",				Vector2(0, -1.0f),		Time("01:30:489").ms, Time("01:39:546").ms);
	place("anyone out there",						Vector2(0, -2.0f),		Time("01:30:489").ms, Time("01:39:546").ms);

	place("i reached out",							Vector2(0, 1.5f),		Time("01:39:546").ms, Time("01:44:074").ms);
	place("and we touched.",						Vector2(0, 0.5f),		Time("01:39:546").ms, Time("01:44:074").ms);
	place("for a second",							Vector2(0, -0.5f),		Time("01:39:546").ms, Time("01:44:074").ms);
	place("forming a bond",							Vector2(0, -1.5f),		Time("01:39:546").ms, Time("01:44:074").ms);

	place("trust in me",							Vector2(0, 1.5f),		Time("01:44:074").ms, Time("01:48:602").ms);
	place("follow me",								Vector2(0, 0.5f),		Time("01:44:074").ms, Time("01:48:602").ms);
	place("and i'll lead you to peace",				Vector2(0, -0.5f),		Time("01:44:074").ms, Time("01:48:602").ms);
	place("i promised",								Vector2(0, -1.5f),		Time("01:44:074").ms, Time("01:48:602").ms);

	place("so began our nights",					Vector2(0, 1.5f),		Time("01:48:602").ms, Time("01:53:131").ms);
	place("of running away",						Vector2(0, 0.5f),		Time("01:48:602").ms, Time("01:53:131").ms);
	place("trips of respite",						Vector2(0, -0.5f),		Time("01:48:602").ms, Time("01:53:131").ms);
	place("far away",								Vector2(0, -1.5f),		Time("01:48:602").ms, Time("01:53:131").ms);

	place("through city streets",					Vector2(0, 1.5f),		Time("01:53:131").ms, Time("01:57:659").ms);
	place("and rainy nights",						Vector2(0, 0.5f),		Time("01:53:131").ms, Time("01:57:659").ms);
	place("we splashed and danced",					Vector2(0, -0.5f),		Time("01:53:131").ms, Time("01:57:659").ms);
	place("atop puddles",							Vector2(0, -1.5f),		Time("01:53:131").ms, Time("01:57:659").ms);
	// Lyric 2
	draw("pushing aside", Vector2::Zero, Time("01:58:791").ms, Time("02:00:489").ms);
	draw("my pain", Vector2::Zero, Time("02:01:338").ms, Time("02:05:584").ms);
	draw("exchanged body heat", Vector2::Zero, Time("02:06:338").ms, Time("02:08:414").ms);
	draw("again and again", Vector2::Zero, Time("02:09:475").ms, Time("02:14:640").ms);
	draw("suffocating", Vector2::Zero, Time("02:16:904").ms, Time("02:18:744").ms);
	draw("puff of smoke", Vector2::Zero, Time("02:19:452").ms, Time("02:21:150").ms);
	draw("and i saw the world", Vector2::Zero, Time("02:24:263").ms, Time("02:27:659").ms);
	draw("turn red", Vector2::Zero, Time("02:28:791").ms, Time("02:33:885").ms);
	// Poem 2
	place("your voice",								Vector2(0, 1.0f),		Time("02:33:885").ms, Time("02:38:414").ms);
	place("pierced the falling rain",				Vector2(0, 0.0f),		Time("02:33:885").ms, Time("02:38:414").ms);
	place("singing, screaming in song",				Vector2(0, -1.0f),		Time("02:33:885").ms, Time("02:38:414").ms);

	place("for a few moments then",					Vector2(0, 1.0f),		Time("02:38:414").ms, Time("02:42:949").ms);
	place("we forgot the sad world",				Vector2(0, 0.0f),		Time("02:38:414").ms, Time("02:42:949").ms);
	place("crying in its sweet dream",				Vector2(0, -1.0f),		Time("02:38:414").ms, Time("02:42:949").ms);

	place("you and i",								Vector2(0, 1.5f),		Time("02:42:949").ms, Time("02:47:470").ms);
	place("laughed",								Vector2(0, 0.5f),		Time("02:42:949").ms, Time("02:47:470").ms);
	place("stumbled through alleyways",				Vector2(0, -0.5f),		Time("02:42:949").ms, Time("02:47:470").ms);
	place("exploring every nook",					Vector2(0, -1.5f),		Time("02:42:949").ms, Time("02:47:470").ms);

	place("clasping tightly",						Vector2(0, 1.5f),		Time("02:47:470").ms, Time("02:51:999").ms);
	place("i dragged us along",						Vector2(0, 0.5f),		Time("02:47:470").ms, Time("02:51:999").ms);
	place("in a frenzied daze",						Vector2(0, -0.5f),		Time("02:47:470").ms, Time("02:51:999").ms);
	place("night after night",						Vector2(0, -1.5f),		Time("02:47:470").ms, Time("02:51:999").ms);

	place("a signal",								Vector2(0, 1.5f),		Time("02:51:999").ms, Time("02:56:527").ms);
	place("shining high in the sky",				Vector2(0, 0.5f),		Time("02:51:999").ms, Time("02:56:527").ms);
	place("to return back",							Vector2(0, -0.5f),		Time("02:51:999").ms, Time("02:56:527").ms);
	place("to daily life",							Vector2(0, -1.5f),		Time("02:51:999").ms, Time("02:56:527").ms);

	place("lost in the morning fog",				Vector2(0, 1.5f),		Time("02:56:527").ms, Time("03:01:055").ms);
	place("we parted ways",							Vector2(0, 0.5f),		Time("02:56:527").ms, Time("03:01:055").ms);
	place("separated by our",						Vector2(0, -0.5f),		Time("02:56:527").ms, Time("03:01:055").ms);
	place("different worlds",						Vector2(0, -1.5f),		Time("02:56:527").ms, Time("03:01:055").ms);

	place("in hiding we bid our time",				Vector2(0, 1.0f),		Time("03:01:055").ms, Time("03:05:584").ms);
	place("waiting for the next opportunity",		Vector2(0, 0.0f),		Time("03:01:055").ms, Time("03:05:584").ms);
	place("to sneak out in the rain",				Vector2(0, -1.0f),		Time("03:01:055").ms, Time("03:05:584").ms);

	place("night by night",							Vector2(0, 1.5f),		Time("03:05:584").ms, Time("03:10:112").ms);
	place("we met each other",						Vector2(0, 0.5f),		Time("03:05:584").ms, Time("03:10:112").ms);
	place("night by night",							Vector2(0, -0.5f),		Time("03:05:584").ms, Time("03:10:112").ms);
	place("we escaped",								Vector2(0, -1.5f),		Time("03:05:584").ms, Time("03:10:112").ms);

	place("counting the moons",						Vector2(0, 1.5f),		Time("03:10:112").ms, Time("03:14:640").ms);
	place("from crescent to full",					Vector2(0, 0.5f),		Time("03:10:112").ms, Time("03:14:640").ms);
	place("every adventure",						Vector2(0, -0.5f),		Time("03:10:112").ms, Time("03:14:640").ms);
	place("one to remember",						Vector2(0, -1.5f),		Time("03:10:112").ms, Time("03:14:640").ms);

	place("through the seasons",					Vector2(0, 1.5f),		Time("03:14:640").ms, Time("03:19:168").ms);
	place("time passed",							Vector2(0, 0.5f),		Time("03:14:640").ms, Time("03:19:168").ms);
	place("the sun rose sooner",					Vector2(0, -0.5f),		Time("03:14:640").ms, Time("03:19:168").ms);
	place("and our time, shorter",					Vector2(0, -1.5f),		Time("03:14:640").ms, Time("03:19:168").ms);

	place("runs became walks",						Vector2(0, 1.5f),		Time("03:19:168").ms, Time("03:23:697").ms);
	place("laughs became smiles",					Vector2(0, 0.5f),		Time("03:19:168").ms, Time("03:23:697").ms);
	place("now we took shelter",					Vector2(0, -0.5f),		Time("03:19:168").ms, Time("03:23:697").ms);
	place("from the pouring nights",				Vector2(0, -1.5f),		Time("03:19:168").ms, Time("03:23:697").ms);

	place("a toll, a price to pay",					Vector2(0, 1.5f),		Time("03:23:697").ms, Time("03:28:225").ms);
	place("with your mind and body",				Vector2(0, 0.5f),		Time("03:23:697").ms, Time("03:28:225").ms);
	place("a cost and affordance",					Vector2(0, -0.5f),		Time("03:23:697").ms, Time("03:28:225").ms);
	place("for each trip",							Vector2(0, -1.5f),		Time("03:23:697").ms, Time("03:28:225").ms);

	place("with exhaustion",						Vector2(0, 1.0f),		Time("03:28:225").ms, Time("03:32:753").ms);
	place("we barely met the night's end",			Vector2(0, 0.0f),		Time("03:28:225").ms, Time("03:32:753").ms);
	place("to catch the day's start",				Vector2(0, -1.0f),		Time("03:28:225").ms, Time("03:32:753").ms);

	place("but one night,",							Vector2(0, 1.5f),		Time("03:32:753").ms, Time("03:37:282").ms);
	place("we failed to make it back",				Vector2(0, 0.5f),		Time("03:32:753").ms, Time("03:37:282").ms);
	place("lost in the maze",						Vector2(0, -0.5f),		Time("03:32:753").ms, Time("03:37:282").ms);
	place("of winding streets",						Vector2(0, -1.5f),		Time("03:32:753").ms, Time("03:37:282").ms);

	place("as the day broke",						Vector2(0, 1.5f),		Time("03:37:282").ms, Time("03:41:810").ms);
	place("ghosts and demons",						Vector2(0, 0.5f),		Time("03:37:282").ms, Time("03:41:810").ms);
	place("evil of all kind",						Vector2(0, -0.5f),		Time("03:37:282").ms, Time("03:41:810").ms);
	place("spawned from the shadows",				Vector2(0, -1.5f),		Time("03:37:282").ms, Time("03:41:810").ms);

	place("every dark corner",						Vector2(0, 1.5f),		Time("03:41:810").ms, Time("03:46:338").ms);
	place("hid encroaching fears",					Vector2(0, 0.5f),		Time("03:41:810").ms, Time("03:46:338").ms);
	place("so we ran, ran away",					Vector2(0, -0.5f),		Time("03:41:810").ms, Time("03:46:338").ms);
	place("through twisting paths",					Vector2(0, -1.5f),		Time("03:41:810").ms, Time("03:46:338").ms);

	place("around corners and bends",				Vector2(0, 0.5f),		Time("03:46:338").ms, Time("03:48:602").ms);
	place("a storm of frantic movements",			Vector2(0, -0.5f),		Time("03:46:338").ms, Time("03:48:602").ms);

	place("with a misstep",							Vector2(0, 1.5f),		Time("03:48:602").ms, Time("03:53:131").ms);
	place("you tumbled to the floor",				Vector2(0, 0.5f),		Time("03:48:602").ms, Time("03:53:131").ms);
	place("and a swarm of shadows",					Vector2(0, -0.5f),		Time("03:48:602").ms, Time("03:53:131").ms);
	place("swallowed you whole",					Vector2(0, -1.5f),		Time("03:48:602").ms, Time("03:53:131").ms);

	place("a panic, struggle",						Vector2(0, 1.5f),		Time("03:53:131").ms, Time("03:57:659").ms);
	place("pulling you up",							Vector2(0, 0.5f),		Time("03:53:131").ms, Time("03:57:659").ms);
	place("but we broke apart",						Vector2(0, -0.5f),		Time("03:53:131").ms, Time("03:57:659").ms);
	place("and lost touch",							Vector2(0, -1.5f),		Time("03:53:131").ms, Time("03:57:659").ms);

	place("a final scream",							Vector2(0, 1.5f),		Time("03:57:659").ms, Time("04:04:168").ms);
	place("left your lips",							Vector2(0, 0.5f),		Time("03:57:659").ms, Time("04:04:168").ms);
	place("before the void took you",				Vector2(0, -0.5f),		Time("03:57:659").ms, Time("04:04:168").ms);
	place("and i ran, ran away",					Vector2(0, -1.5f),		Time("03:57:659").ms, Time("04:04:168").ms);
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
	place("it wasn't until evening",				Vector2(0, 1.0f),		Time("05:57:659").ms, Time("05:59:923").ms);
	place("that i returned",						Vector2(0, 0.0f),		Time("05:57:659").ms, Time("05:59:923").ms);
	place("back to the city",						Vector2(0, -1.0f),		Time("05:57:659").ms, Time("05:59:923").ms);

	place("where your body laid",					Vector2(0, 1.0f),		Time("05:59:923").ms, Time("06:03:319").ms);
	place("was a jagged shard",						Vector2(0, 0.0f),		Time("05:59:923").ms, Time("06:03:319").ms);
	place("a fraction of your soul",				Vector2(0, -1.0f),		Time("05:59:923").ms, Time("06:03:319").ms);

	place("a memory, of bliss",						Vector2(0, 1.0f),		Time("06:03:319").ms, Time("06:06:716").ms);
	place("that you so chased",						Vector2(0, 0.0f),		Time("06:03:319").ms, Time("06:06:716").ms);
	place("and longed for",							Vector2(0, -1.0f),		Time("06:03:319").ms, Time("06:06:716").ms);

	place("looking up",								Vector2(0, 1.0f),		Time("06:06:716").ms, Time("06:10:112").ms);
	place("clouds gathered",						Vector2(0, 0.0f),		Time("06:06:716").ms, Time("06:10:112").ms);
	place("and covered the sky",					Vector2(0, -1.0f),		Time("06:06:716").ms, Time("06:10:112").ms);

	place("the first drops came",					Vector2(0, 1.0f),		Time("06:10:112").ms, Time("06:13:508").ms);
	place("dotted the landscape",					Vector2(0, 0.0f),		Time("06:10:112").ms, Time("06:13:508").ms);
	place("turned the world to haze",				Vector2(0, -1.0f),		Time("06:10:112").ms, Time("06:13:508").ms);

	place("more and more",							Vector2(0, 1.5f),		Time("06:13:508").ms, Time("06:18:036").ms);
	place("fragments of you appeared",				Vector2(0, 0.5f),		Time("06:13:508").ms, Time("06:18:036").ms);
	place("twinkling and sparkling",				Vector2(0, -0.5f),		Time("06:13:508").ms, Time("06:18:036").ms);
	place("in the wet glow",						Vector2(0, -1.5f),		Time("06:13:508").ms, Time("06:18:036").ms);

	place("i reached, for all the pieces",			Vector2(0, 1.0f),		Time("06:18:036").ms, Time("06:23:697").ms);
	place("pooled them to my cut hands",			Vector2(0, 0.0f),		Time("06:18:036").ms, Time("06:23:697").ms);
	place("but there were far too many",			Vector2(0, -1.0f),		Time("06:18:036").ms, Time("06:23:697").ms);

	place("was it worth it",						Vector2(0, 1.0f),		Time("06:23:697").ms, Time("06:27:093").ms);
	place("was it right",							Vector2(0, 0.0f),		Time("06:23:697").ms, Time("06:27:093").ms);
	place("was it good",							Vector2(0, -1.0f),		Time("06:23:697").ms, Time("06:27:093").ms);

	place("i kissed the sharp fragments",			Vector2(0, 0.5f),		Time("06:27:093").ms, Time("06:31:055").ms);
	place("then consume them all",					Vector2(0, -0.5f),		Time("06:27:093").ms, Time("06:31:055").ms);
	// Lyric 4
	draw("when the wall broke down", Vector2::Zero, Time("06:31:055").ms, Time("06:32:329").ms);
	draw("you were there", Vector2::Zero, Time("06:32:895").ms, Time("06:33:885").ms);
	draw("but i was on my own", Vector2::Zero, Time("06:34:735").ms, Time("06:35:725").ms);
}
