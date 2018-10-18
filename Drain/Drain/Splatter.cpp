#include "Path.hpp"
#include "Splatter.hpp"
#include "Storyboard.hpp"
#include "Swatch.hpp"
#include <ctime>

std::default_random_engine Splatter::GENERATOR = std::default_random_engine(time(0));
std::exponential_distribution<double> Splatter::EXPONENTIAL = std::exponential_distribution<double>(3.5);    // mean of the exp distribution = 1 / 3.5
std::uniform_real_distribution<double> Splatter::UNIFORM_ANGLE = std::uniform_real_distribution<double>(0, 359); // uniform distribution between 0 and 359 (degrees)

// standalone, defined by centerPos Vector2
Splatter::Splatter(const Time& startTime, const Time& endTime, const float size, const int numDrops, const int satelliteSpawnTime, const Vector2 centerPos, const bool fadeOut)
	: fadeOut{ fadeOut },
	startTime{ startTime },
	endTime{ endTime },
	centerPos{ centerPos },
	sizeFactor{ size },
	numDrops{ numDrops },
	satelliteSpawnTime{ satelliteSpawnTime },
	totalDur{ endTime.ms - startTime.ms } {}

// position defined by existing AirBubble
Splatter::Splatter(const Time& startTime, const Time& endTime, const float size, const int numDrops, const int satelliteSpawnTime, Bubble* const bubble, const bool fadeOut)   // replace with AirBubble
	: Splatter(startTime, endTime, size, numDrops, satelliteSpawnTime, bubble->sprites.position, fadeOut) { // replace 0,0 with bubble->loc
	bubble->Fade(startTime.ms, startTime.ms + BUBBLE_FADE_IN_TIME);
}

SpriteCollection Splatter::buildSpriteCollection() {
	auto locations = std::vector<Vector2>();
	auto scales = std::vector<float>();
	const auto centerPos = sprites[0]->position;
	const auto centerScale = sprites[0]->scale;
	locations.push_back(Vector2::Zero);
	scales.push_back(centerScale);

	for (int i = 1; i < sprites.size(); ++i) {
		locations.push_back(sprites[i]->position - centerPos);
		scales.push_back(sprites[i]->scale);
	}

	const auto collection = SpriteCollection(sprites, locations, scales);
	return collection;
}

// returns and draws a single circle at pos after offset ms
void Splatter::draw(Vector2 pos, int offset, float size, float growDur, float growFromSize, Easing easing) {
	auto s = Storyboard::CreateSprite(getPath(Path::Circle), pos);

	if (growDur != 0) {
		if (startTime.ms + offset + growDur < endTime.ms)
			s->Scale(startTime.ms + offset, startTime.ms + offset + growDur, size * growFromSize, size, easing);
		else
			s->Scale(startTime.ms + offset, endTime.ms, size * growFromSize, size, easing);
	}
	else
		s->Scale(startTime.ms + offset, startTime.ms + offset, size, size); // scale to proper size instantaneously

	Swatch::colorFgToFgSprites({ s }, startTime.ms + offset, endTime.ms); // color will determine Sprite lifetime

	// Only fade out if flag was set in constructor
	if (fadeOut) {
		Swatch::colorFgToBgSprites({ s }, endTime.ms, endTime.ms + SPLATTER_FADE_OUT_TIME);
	}
	sprites.push_back(s);
}

SpriteCollection Splatter::make(const Time& startTime, const Time& endTime, const int spawnTime, Bubble* const bubble, const bool fadeOut) {
	const auto size = bubble->sprites.overallScale;
	const auto collection = Splatter(startTime, endTime, size, 300, spawnTime, bubble, fadeOut).make();
	return collection;
}

// returns number of sprites drawn, going for something like this: http://gifimage.net/splatter-gif-10/
SpriteCollection Splatter::make() {
	// main droplet will grow from 80% to 100% of its size over 1/2 of its lifespan
	draw(centerPos, 0, sizeFactor, totalDur * 0.5, 0.8, Easing::EasingOut);
	for (int i = 1; i < numDrops; i++) {
		// offset 'easing' is an exponential exp
		auto expRandomPoint = EXPONENTIAL(GENERATOR);
		while (expRandomPoint > 1.0) {  // in the off chance that RNG returns more than 1, roll again
			expRandomPoint = EXPONENTIAL(GENERATOR);
		}

		auto offset = expRandomPoint * satelliteSpawnTime; // satellite droplets will spawn in for 2 seconds
		offset -= 200;  // shift left 200ms
		if (offset < 0) {
			offset = 0; // so we can have some satellites spawn instantly
		}

		// use polar coordinates and don't have stupid weird ways to calculate stuff
		auto angle = UNIFORM_ANGLE(GENERATOR);
		// Divide by 2.0f to get radius instead of diameter
		// 0.8f because the center circle starts from 0.8 size then goes to 1.0
		auto dist = (expRandomPoint + sizeFactor / 2.0f * 0.8f) * SPRITE_SIZE;   // dist away from centerPoint the satellite will be drawn
		auto pos = centerPos + Vector2(dist * cosf(angle * DEG_TO_RAD), dist * sinf(angle * DEG_TO_RAD));
		// size decreases as distance increases
		auto size = sizeFactor / dist / MAX_SATELLITE_SIZE_FACTOR;
		if (size > MAX_SATELLITE_SIZE_FACTOR * sizeFactor) {     // limit size of satellites to 1/4 of that of the centerPoint
			size = MAX_SATELLITE_SIZE_FACTOR * sizeFactor;
		}
		// distance between divided by 100 to take into account 100px radius image, allow some overlap
		if (size < MIN_SATELLITE_SIZE || pos.DistanceBetween(centerPos) / SPRITE_SIZE < (sizeFactor / 2 + size / 2) * MAX_SATELLITE_SIZE_FACTOR) {
			continue;   // calculated satellite droplet is miniscule or is completely engulfed by the centerPoint
		}

		// reuse offset for duration of fading in of satellite drops
		draw(pos, static_cast<int>(offset), size);
	}

	const auto collection = buildSpriteCollection();
	return collection;
}

SpriteCollection Splatter::makeWalkerSplatter(const Time& startTime, const Vector2& centerPos, const float scale) {
	const auto collection = Splatter(startTime, startTime, scale, 300, 0, centerPos, false).make();
	return collection;
}

void Splatter::renderBackground() {
	const auto splatterTime = Time("02:55:036");
	const auto endTime = Time("03:04:168");
	auto splatters = std::vector<SpriteCollection>();

	for (int i = 0; i < 15; ++i) {
		Vector2 position;
		while ((position.x > -150 && position.x < 120) &&
			(position.y > -190 && position.y < 90)) {
			position = Vector2(RandomRange::calculate(-427, 427), RandomRange::calculate(-240, 240));
		}
		const auto size = RandomRange::calculate(5, 10, 10);
		Splatter(splatterTime, endTime, size, 400, endTime.ms - splatterTime.ms, position).make();
	}
}

void Splatter::renderFirstGradualPop(std::vector<Bubble*>& bubbles) {
	const auto splatterTimes = std::vector<Time>({
		Time("02:33:885"),
		Time("02:38:414"),
		Time("02:42:942"),
		Time("02:47:470"),
		Time("02:52:140"),
		Time("02:56:527"),
		Time("03:01:055"),
		Time("03:05:584")
												 });
	int splattersPerTime = bubbles.size() / splatterTimes.size();
	int remainder = bubbles.size() % splatterTimes.size();

	for (const auto& splatterTime : splatterTimes) {
		for (int j = 0; j < splattersPerTime; ++j) {
			const auto endTime = splatterTime.ms + SPLATTER_ALIVE_TIME;
			make(splatterTime.ms, endTime, SPLATTER_ALIVE_TIME, bubbles.back());
			bubbles.pop_back();
		}
		if (remainder-- > 0) {
			const auto endTime = splatterTime.ms + SPLATTER_ALIVE_TIME;
			make(splatterTime.ms, endTime, SPLATTER_ALIVE_TIME, bubbles.back());
			bubbles.pop_back();
		}
	}
}

std::vector<SpriteCollection> Splatter::renderSecondAllPop(std::vector<Bubble*>& bubbles) {
	const auto splatterTime = Time("03:18:036");
	const auto endTime = Time("03:19:168");
	auto splatters = std::vector<SpriteCollection>();

	for (const auto bubble : bubbles) {
		splatters.push_back(make(splatterTime, endTime, endTime.ms - splatterTime.ms, bubble, false));
	}

	return splatters;
}