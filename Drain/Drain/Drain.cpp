#include "Bubble.hpp"
#include "BubbleGenerator.hpp"
#include "Drip.hpp"
#include "DripWalker.hpp"
#include "Math.hpp"
#include "Path.hpp"
#include "RainGenerator.hpp"
#include "RainWalker.hpp"
#include "Splatter.hpp"
#include "SplatterWalker.hpp"
#include "Storyboard.hpp"
#include "Swatch.hpp"
#include "Sketch.hpp"
#include "Text.hpp"
#include "Walker.hpp"
#include <ctime>
#include <cmath>
#include <iostream>

int main() {
	srand(time(NULL));
	Swatch::init();

	// Solid background
	if (1) {
		// Gets rid of beatmap background
		Storyboard::CreateSprite("36592_serial_experiments_lain.jpg", Vector2::Zero, Layer::Background);
		// Solid color background
		auto const background = Storyboard::CreateSprite(getPath(Path::Pixel), Vector2::Zero, Layer::Background);
		background->ScaleVector(0, 0, Vector2::ScreenSize, Vector2::ScreenSize, Easing::Linear, 0);
		Swatch::colorBgToBgSprites({ background }, 0, Timing::songEnd);
	}

	Text::render();
	//Sketch::render();

	// Rain
	if (1) {
		RainGenerator firstRain = RainGenerator::RainGenerator(Time("00:05:580"), Time("00:51:716"));
		RainGenerator gen = RainGenerator(Time("01:03:319"), Time("01:30:489"), true, 1.03f);
		std::vector<Sprite *> raindrops = gen.FreezeRain();
		std::vector<SpriteCollection> coll_raindrops;
		for (auto drop : raindrops) {
			coll_raindrops.push_back(drop);
		}
		auto const walker = new RainWalker(coll_raindrops);
		walker->walk(Time("01:30:489"), Time("01:57:659"), 10);
	}

	// Bubble generation
	// Moved right above background so that text and sketch can appear normally above them
	if (1) {
		BubbleGenerator bubGen = BubbleGenerator::BubbleGenerator();
		BubbleGenerator::renderMouthBubbles();
		auto splatBubbles = bubGen.GetSplatBubbles();
		Splatter::renderFirstGradualPop(splatBubbles);

		BubbleGenerator bubGen2 = BubbleGenerator::BubbleGenerator(true);
		auto splatBubbles2 = bubGen2.GetSplatBubbles();
		auto splatters = Splatter::renderSecondAllPop(splatBubbles2);
		Walker* walker = new SplatterWalker(splatters);
		// Commented hack so it's not a hack anymore: artifically add to endtime to account for spawning rate
		walker->walk(Time("03:19:168").ms, Time("04:06:716").ms, 1.0);
	}

	// Drip
	if (1) {
		// First drip section
		Drip::renderFirstFill();

		// Second drip section
		auto drips = Drip::renderSecondDrips();
		Walker* walker = new DripWalker(drips);
		walker->walk(Time("05:39:546").ms, Time("05:57:659").ms, 1.0);
	}

	// Rendering background image 
	if (1) {
		BubbleGenerator::BubbleGenerator();
		RainGenerator(Time("02:55:580"), Time("03:10:716"));
		//Text::renderBanner();
		Sketch::renderBackground();
		Splatter::renderBackground();
		Drip::renderBackground();
	}

	// Put storyboard osb path inside of StoryboardInputPath.txt
	// e.g. X:\osu!\Songs\774573 ELECTROCUTICA feat Luschka - Drain -Re_Act Mix-\ELECTROCUTICA feat. Luschka - Drain -ReAct Mix- (fartownik).osb
	auto storyboardInputPath = std::ifstream("StoryboardInputPath.txt");
	std::string path;
	std::getline(storyboardInputPath, path);
	Storyboard::Write(path);

	return 0;
}