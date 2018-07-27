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
	const auto small = 15.0f;
	const auto lineSpacing = small * 3.0f;
	// Lyric 1
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
	// Credits
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
	// Poem 1
	place("chained and bound",						Vector2(0,	lineSpacing *	1.5f),		Time("01:12:376").ms, Time("01:21:433").ms, small);
	place("in a corner of empty space",				Vector2(0,	lineSpacing *	0.5f),		Time("01:12:376").ms, Time("01:21:433").ms, small);
	place("you whispered against the wall",			Vector2(0,	-lineSpacing *	0.5f),		Time("01:12:376").ms, Time("01:21:433").ms, small);
	place("pleas, pleas of help",					Vector2(0,	-lineSpacing *	1.5f),		Time("01:12:376").ms, Time("01:21:433").ms, small);

	place("a torrent of blurs outside",				Vector2(0,	lineSpacing *	1.5f),		Time("01:21:433").ms, Time("01:30:489").ms, small);
	place("the whole world passed by",				Vector2(0,	lineSpacing *	0.5f),		Time("01:21:433").ms, Time("01:30:489").ms, small);
	place("as you cried",							Vector2(0,	-lineSpacing *	0.5f),		Time("01:21:433").ms, Time("01:30:489").ms, small);
	place("cried and cried",						Vector2(0,	-lineSpacing *	1.5f),		Time("01:21:433").ms, Time("01:30:489").ms, small);

	place("drowning",								Vector2(0,	lineSpacing *	2.0f),		Time("01:30:489").ms, Time("01:39:546").ms, small);
	place("dangling in the abyss",					Vector2(0,	lineSpacing *	1.0f),		Time("01:30:489").ms, Time("01:39:546").ms, small);
	place("your fingers outstretched to nothing",	Vector2(0,	lineSpacing *	0.0f),		Time("01:30:489").ms, Time("01:39:546").ms, small);
	place("searching, for anything",				Vector2(0,	-lineSpacing *	1.0f),		Time("01:30:489").ms, Time("01:39:546").ms, small);
	place("anyone out there",						Vector2(0,	-lineSpacing *	2.0f),		Time("01:30:489").ms, Time("01:39:546").ms, small);

	place("i reached out",							Vector2(0,	lineSpacing *	1.5f),		Time("01:39:546").ms, Time("01:44:074").ms, small);
	place("and we touched.",						Vector2(0,	lineSpacing *	0.5f),		Time("01:39:546").ms, Time("01:44:074").ms, small);
	place("for a delicate second",					Vector2(0,	-lineSpacing *	0.5f),		Time("01:39:546").ms, Time("01:44:074").ms, small);
	place("forming a connection",					Vector2(0,	-lineSpacing *	1.5f),		Time("01:39:546").ms, Time("01:44:074").ms, small);

	place("trust in me",							Vector2(0,	lineSpacing *	1.5f),		Time("01:44:074").ms, Time("01:48:602").ms, small);
	place("follow me",								Vector2(0,	lineSpacing *	0.5f),		Time("01:44:074").ms, Time("01:48:602").ms, small);
	place("and i'll lead you to peace",				Vector2(0,	-lineSpacing *	0.5f),		Time("01:44:074").ms, Time("01:48:602").ms, small);
	place("i promised",								Vector2(0,	-lineSpacing *	1.5f),		Time("01:44:074").ms, Time("01:48:602").ms, small);

	place("so began our nights",					Vector2(0,	lineSpacing *	1.5f),		Time("01:48:602").ms, Time("01:53:131").ms, small);
	place("of running away",						Vector2(0,	lineSpacing *	0.5f),		Time("01:48:602").ms, Time("01:53:131").ms, small);
	place("trips of respite",						Vector2(0,	-lineSpacing *	0.5f),		Time("01:48:602").ms, Time("01:53:131").ms, small);
	place("far away",								Vector2(0,	-lineSpacing *	1.5f),		Time("01:48:602").ms, Time("01:53:131").ms, small);

	place("through city streets",					Vector2(0,	lineSpacing *	1.5f),		Time("01:53:131").ms, Time("01:57:659").ms, small);
	place("and rainy nights",						Vector2(0,	lineSpacing *	0.5f),		Time("01:53:131").ms, Time("01:57:659").ms, small);
	place("we splashed and danced",					Vector2(0,	-lineSpacing *	0.5f),		Time("01:53:131").ms, Time("01:57:659").ms, small);
	place("atop puddles",							Vector2(0,	-lineSpacing *	1.5f),		Time("01:53:131").ms, Time("01:57:659").ms, small);
	// Lyric 2
	draw("pushing aside", Vector2::Zero, Time("01:58:791").ms, Time("02:00:489").ms, fontSize);
	draw("my pain", Vector2::Zero, Time("02:01:338").ms, Time("02:05:584").ms, fontSize);
	draw("exchanged body heat", Vector2::Zero, Time("02:06:338").ms, Time("02:08:414").ms, fontSize);
	draw("again and again", Vector2::Zero, Time("02:09:475").ms, Time("02:14:640").ms, fontSize);
	draw("suffocating", Vector2::Zero, Time("02:16:904").ms, Time("02:18:744").ms, fontSize);
	draw("puff of smoke", Vector2::Zero, Time("02:19:452").ms, Time("02:21:150").ms, fontSize);
	draw("and i saw the world", Vector2::Zero, Time("02:24:263").ms, Time("02:27:659").ms, fontSize);
	draw("turn red", Vector2::Zero, Time("02:28:791").ms, Time("02:33:885").ms, fontSize);
	// Poem 2
	place("your voice",								Vector2(0,	lineSpacing *	1.0f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("pierced the falling rain",				Vector2(0,	lineSpacing *	0.0f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("singing, screaming in song",				Vector2(0,	-lineSpacing *	1.0f),		Time("00:00:000").ms, Time("00:00:000").ms, small);

	place("out, from every depth",					Vector2(0,	lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("came feeling",							Vector2(0,	lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("feelings of sincerity",					Vector2(0,	-lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("of everything",							Vector2(0,	-lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);

	place("for a few moments then",					Vector2(0,	lineSpacing *	1.0f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("we forgot the sad world",				Vector2(0,	lineSpacing *	0.0f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("crying in its sweet dream",				Vector2(0,	-lineSpacing *	1.0f),		Time("00:00:000").ms, Time("00:00:000").ms, small);

	place("you and i",								Vector2(0,	lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("laughed",								Vector2(0,	lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("stumbled through alleyways",				Vector2(0,	-lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("exploring every nook",					Vector2(0,	-lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);

	place("clasping tightly",						Vector2(0,	lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("i dragged us along",						Vector2(0,	lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("in a frenzied daze",						Vector2(0,	-lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("night after night",						Vector2(0,	-lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);

	place("a signal",								Vector2(0,	lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("shining high in the sky",				Vector2(0,	lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("to return back",							Vector2(0,	-lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("to daily life",							Vector2(0,	-lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);

	place("lost in the morning fog",				Vector2(0,	lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("we parted ways",							Vector2(0,	lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("separated by our",						Vector2(0,	-lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("different worlds",						Vector2(0,	-lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);

	place("in hiding we bid our time",				Vector2(0,	lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("waiting for the sun to set",				Vector2(0,	lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("for the next opportunity",				Vector2(0,	-lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("to sneak out in the rain",				Vector2(0,	-lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);

	place("night by night",							Vector2(0,	lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("we met each other",						Vector2(0,	lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("night by night",							Vector2(0,	-lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("we escaped",								Vector2(0,	-lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);

	place("counting the moons",						Vector2(0,	lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("from crescent to full",					Vector2(0,	lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("every adventure",						Vector2(0,	-lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("one to remember",						Vector2(0,	-lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);

	place("through the seasons",					Vector2(0,	lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("time passed",							Vector2(0,	lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("the sun rose sooner",					Vector2(0,	-lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("and our time, shorter",					Vector2(0,	-lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);

	place("runs became walks",						Vector2(0,	lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("laughs became smiles",					Vector2(0,	lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("now we took shelter",					Vector2(0,	-lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("from the pouring nights",							Vector2(0,	-lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);

	place("a toll, a price to pay",					Vector2(0,	lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("with your mind and body",				Vector2(0,	lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("a cost and affordance",					Vector2(0,	-lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("for each trip",							Vector2(0,	-lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);

	place("with exhaustion",						Vector2(0,	lineSpacing *	1.0f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("we barely met the night’s end",			Vector2(0,	lineSpacing *	0.0f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("to catch the day’s start",				Vector2(0,	-lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);

	place("but one night,",							Vector2(0,	lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("we failed to make it back",				Vector2(0,	lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("lost in the maze",						Vector2(0,	-lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("of winding streets",						Vector2(0,	-lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);

	place("as the day broke",						Vector2(0,	lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("ghosts and demons",						Vector2(0,	lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("evil of all kind",						Vector2(0,	-lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("spawned from the shadows",				Vector2(0,	-lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);

	place("every dark corner",						Vector2(0,	lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("hid encroaching fears",					Vector2(0,	lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("so we ran, ran away",					Vector2(0,	-lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("through twisting paths",					Vector2(0,	-lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);

	place("around corners and bends",				Vector2(0,	lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("a storm of frantic movements",			Vector2(0,	-lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);

	place("with a misstep",							Vector2(0,	lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("you tumbled to the floor",				Vector2(0,	lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("and a swarm of shadows",					Vector2(0,	-lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("swallowed you whole",					Vector2(0,	-lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);

	place("a panic, struggle",						Vector2(0,	lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("pulling you up",							Vector2(0,	lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("but we broke apart",						Vector2(0,	-lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("lost touch",								Vector2(0,	-lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);

	place("a final scream",							Vector2(0,	lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("left your lips",							Vector2(0,	lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("before the void took you",				Vector2(0,	-lineSpacing *	0.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	place("and i ran, ran away",					Vector2(0,	-lineSpacing *	1.5f),		Time("00:00:000").ms, Time("00:00:000").ms, small);
	// Lyric 3
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
	// Poem 3
	place("it wasn't until evening",				Vector2(0,	lineSpacing *	1.0f),		Time("05:57:659").ms, Time("05:59:923").ms, small);
	place("that i returned",						Vector2(0,	lineSpacing *	0.0f),		Time("05:57:659").ms, Time("05:59:923").ms, small);
	place("back to the city",						Vector2(0,	-lineSpacing *	1.0f),		Time("05:57:659").ms, Time("05:59:923").ms, small);

	place("where your body laid",					Vector2(0,	lineSpacing *	1.0f),		Time("05:59:923").ms, Time("06:03:319").ms, small);
	place("was a jagged shard",						Vector2(0,	lineSpacing *	0.0f),		Time("05:59:923").ms, Time("06:03:319").ms, small);
	place("a fraction of your soul",				Vector2(0,	-lineSpacing *	1.0f),		Time("05:59:923").ms, Time("06:03:319").ms, small);

	place("a memory, of bliss",						Vector2(0,	lineSpacing *	1.0f),		Time("06:03:319").ms, Time("06:06:716").ms, small);
	place("that you so chased",						Vector2(0,	lineSpacing *	0.0f),		Time("06:03:319").ms, Time("06:06:716").ms, small);
	place("and longed for",							Vector2(0,	-lineSpacing *	1.0f),		Time("06:03:319").ms, Time("06:06:716").ms, small);

	place("looking up",								Vector2(0,	lineSpacing *	1.0f),		Time("06:06:716").ms, Time("06:10:112").ms, small);
	place("clouds gathered",					Vector2(0,	lineSpacing *	0.0f),		Time("06:06:716").ms, Time("06:10:112").ms, small);
	place("and covered the sky",					Vector2(0,	-lineSpacing *	1.0f),		Time("06:06:716").ms, Time("06:10:112").ms, small);

	place("the first drops came",					Vector2(0,	lineSpacing *	1.0f),		Time("06:10:112").ms, Time("06:13:508").ms, small);
	place("dotted the landscape",					Vector2(0,	lineSpacing *	0.0f),		Time("06:10:112").ms, Time("06:13:508").ms, small);
	place("turned the world to haze",				Vector2(0,	-lineSpacing *	1.0f),		Time("06:10:112").ms, Time("06:13:508").ms, small);

	place("more and more",							Vector2(0,	lineSpacing *	1.5f),		Time("06:13:508").ms, Time("06:18:036").ms, small);
	place("fragments of you appeared",				Vector2(0,	lineSpacing *	0.5f),		Time("06:13:508").ms, Time("06:18:036").ms, small);
	place("twinkling and sparkling",				Vector2(0,	-lineSpacing *	0.5f),		Time("06:13:508").ms, Time("06:18:036").ms, small);
	place("in the wet glow",						Vector2(0,	-lineSpacing *	1.5f),		Time("06:13:508").ms, Time("06:18:036").ms, small);

	place("i reached, for all the pieces",			Vector2(0,	lineSpacing *	1.0f),		Time("06:18:036").ms, Time("06:23:697").ms, small);
	place("pooled them to my cut hands",				Vector2(0,	lineSpacing *	0.0f),		Time("06:18:036").ms, Time("06:23:697").ms, small);
	place("but there were far too many",			Vector2(0,	-lineSpacing *	1.0f),		Time("06:18:036").ms, Time("06:23:697").ms, small);

	place("was it worth it",						Vector2(0,	lineSpacing *	1.0f),		Time("06:23:697").ms, Time("06:27:093").ms, small);
	place("was it right",							Vector2(0,	lineSpacing *	0.0f),		Time("06:23:697").ms, Time("06:27:093").ms, small);
	place("was it good",							Vector2(0,	-lineSpacing *	1.0f),		Time("06:23:697").ms, Time("06:27:093").ms, small);

	place("i kissed the sharp fragments",			Vector2(0,	lineSpacing *	0.5f),		Time("06:27:093").ms, Time("06:31:055").ms, small);
	place("then consume them all",					Vector2(0,	-lineSpacing *	0.5f),		Time("06:27:093").ms, Time("06:31:055").ms, small);
	// Lyric 4
	draw("when the wall broke down", Vector2::Zero, Time("06:31:055").ms, Time("06:32:329").ms, fontSize);
	draw("you were there", Vector2::Zero, Time("06:32:895").ms, Time("06:33:885").ms, fontSize);
	draw("but i was on my own", Vector2::Zero, Time("06:34:735").ms, Time("06:35:725").ms, fontSize);
}
