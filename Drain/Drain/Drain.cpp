#include "Lyric.hpp"
#include "Path.hpp"
#include "Storyboard.hpp"
#include <iostream>
int main() {
	const auto config = CharacterConfig(100.0f, 0, 10000, 2000, Color(255), Color(0));
	Lyric("a", config);

	// Gets rid of beatmap background
	Storyboard::CreateSprite("36592_serial_experiments_lain.jpg", Vector2::Zero, Layer::Background);
	//auto const background = Storyboard::CreateSprite(getPath(Path::Pixel), Vector2::Zero, Layer::Background);
	//background->Scale(0, 300000, )
	// Put storyboard osb path inside of StoryboardInputPath.txt
	// e.g. X:\osu!\Songs\774573 ELECTROCUTICA feat Luschka - Drain -Re_Act Mix-\ELECTROCUTICA feat. Luschka - Drain -ReAct Mix- (fartownik).osb
	auto storyboardInputPath = std::ifstream("StoryboardInputPath.txt");
	std::string path;
	std::getline(storyboardInputPath, path);
	Storyboard::Write(path);
	return 0;
}