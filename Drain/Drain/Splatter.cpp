#include "Path.hpp"
#include "Splatter.hpp"
#include "Storyboard.hpp"
#include "Swatch.hpp"
#include <ctime>

std::default_random_engine Splatter::generator = std::default_random_engine(time(0));
std::exponential_distribution<double> Splatter::exp = std::exponential_distribution<double>(3.5);    // mean of the exp distribution = 1 / 3.5
std::gamma_distribution<double> Splatter::gamma = std::gamma_distribution<double>(2, 2);
std::normal_distribution<double> Splatter::normal = std::normal_distribution<double>(4.5, 4.1); // mean, std dev
std::normal_distribution<double> Splatter::normal2 = std::normal_distribution<double>(4.5, 4.2); // mean, std dev
std::uniform_real_distribution<double> Splatter::uniform = std::uniform_real_distribution<double>(-1, 1); // uniform distribution between -1 and 1
std::uniform_real_distribution<double> Splatter::uniformAngle = std::uniform_real_distribution<double>(0, 359); // uniform distribution between 0 and 359 (degrees)

// standalone, defined by centerPos Vector2
Splatter::Splatter(const Time& startTime, const Time& endTime,
    const float size, const int numDrops, const int type, const int satelliteSpawnTime, const Vector2 centerPos)
    : startTime{ startTime }, endTime{ endTime },
    sizeFactor{ size }, numDrops{ numDrops }, type{ type },
    satelliteSpawnTime{ satelliteSpawnTime }, centerPos { centerPos }
{
    totalDur = endTime.ms - startTime.ms;
}

// position defined by existing AirBubble
Splatter::Splatter(const Time& startTime, const Time& endTime,
    const float size, const int numDrops, const int type, const int satelliteSpawnTime, Bubble* const bubble)   // replace with AirBubble
    : Splatter(startTime, endTime, size, numDrops, type, satelliteSpawnTime, bubble->sprites.position)   // replace 0,0 with bubble->loc
{
	bubble->Fade(startTime.ms, startTime.ms + bubbleFadeTime);
}

// returns and draws a single circle at pos after offset ms
Sprite * Splatter::draw(Vector2 pos, int offset, float size,
    float fadeInDur, float fadeFrom, float fadeTo, float growDur, float growFromSize, Easing easing)
{
    auto s = Storyboard::CreateSprite(getPath(Path::Circle), pos);
    if (growDur != 0) {
        if (startTime.ms + offset + growDur < endTime.ms)
            s->Scale(startTime.ms + offset, startTime.ms + offset + growDur, size * growFromSize, size, easing);
        else
            s->Scale(startTime.ms + offset, endTime.ms, size * growFromSize, size, easing);
    }
    else
        s->Scale(startTime.ms + offset, startTime.ms + offset, size, size); // scale to proper size instantaneously
    if (fadeInDur != 0){
        if (startTime.ms + offset + fadeInDur < endTime.ms)
            s->Fade(startTime.ms + offset, startTime.ms + offset + fadeInDur, fadeFrom, fadeTo, easing);
        else
            s->Fade(startTime.ms + offset, endTime.ms, fadeFrom, fadeTo, easing);
    }
    Swatch::colorFgToFgSprites({ s }, startTime.ms + offset, endTime.ms); // color will determine Sprite lifetime
    sprites.push_back(s);
    return s;
}

// returns number of sprites drawn, going for something like this: http://gifimage.net/splatter-gif-10/
int Splatter::make() {
    // main droplet will grow from 80% to 100% of its size over 1/2 of its lifespan
    auto centerPoint = draw(centerPos, 0, sizeFactor, 0, 0, 1, totalDur * 0.5, 0.8, Easing::EasingOut);
    int ans = 1;
    for (int i = 1; i < numDrops; i++) {
        // offset 'easing' is an exponential exp
        auto expRandomPoint = exp(generator);
        auto gammaRP = gamma(generator);
        auto normalRP = normal(generator);
        auto normalRP2 = normal2(generator);
        auto neg3 = (uniform(generator) > 0) ? 1 : -1;
        while (expRandomPoint > 1.0) {  // in the off chance that RNG returns more than 1, roll again
            expRandomPoint = exp(generator);
        }
        auto offset = expRandomPoint * satelliteSpawnTime; // satellite droplets will spawn in for 2 seconds
        offset -= 200;  // shift left 200ms
        if (offset < 0) {
            offset = 0; // so we can have some satellites spawn instantly
        }
        // distance from centerPos increases as offset increases
        // some randomness for the satellite droplet positions
        auto neg = uniform(generator);
        auto neg2 = uniform(generator);
        Vector2 pos;
        float size;     // size decreases as distance increases
        switch (type) {
        case 1:
            pos = centerPos + Vector2(neg * normalRP, neg2 * normalRP2) * expRandomPoint * neg3 / sizeFactor / sizeFactor;
            size = sizeFactor / (centerPos.DistanceBetween(pos)-sizeFactor) * 2;
            break;
        case 2:
            // todo: ideally would like to also scale based on expRP so closer satellites appear first
            pos = centerPos + Vector2(neg * normalRP, neg2 * normalRP2) * gammaRP * neg3 * 10;
            // todo: size is dropping off too fast with distance
            size = sizeFactor / (SPRITE_SIZE * (centerPos.DistanceBetween(pos) / 50 - sizeFactor));
            break;
        case 3:
            // use polar coordinates and don't have stupid weird ways to calculate stuff
            auto angle = uniformAngle(generator);
            auto dist = expRandomPoint * SPRITE_SIZE;   // dist away from centerPoint the satellite will be drawn
            pos = centerPos + Vector2(dist * cosf(angle * DEG_TO_RAD), dist * sinf(angle * DEG_TO_RAD));
            size = sizeFactor / dist / MAX_SATELLITE_SIZE_FACTOR;
            break;
        }
        if (size > MAX_SATELLITE_SIZE_FACTOR * sizeFactor) {     // limit size of satellites to 1/4 of that of the centerPoint
            size = MAX_SATELLITE_SIZE_FACTOR * sizeFactor;
        }
        // distance between divided by 100 to take into account 100px radius image, allow some overlap
        if (size < MIN_SATELLITE_SIZE || pos.DistanceBetween(centerPos) / SPRITE_SIZE < (sizeFactor / 2 + size / 2) * MAX_SATELLITE_SIZE_FACTOR){
            continue;   // calculated satellite droplet is miniscule or is completely engulfed by the centerPoint
        }
        if (expRandomPoint > 0.7)   // cap expRandomPoint so we can have it fade to a max of opacity 1
            expRandomPoint = 0.7;   // reuse expRandomPoint for randomizing opacity of satellite drops
        // reuse offset for duration of fading in of satellite drops
        draw(pos, static_cast<int>(offset), size, offset, expRandomPoint + 0.2, expRandomPoint + 0.3);
        ans++;
    }
    std::cout << ans << std::endl;
    return ans;
}

void Splatter::render() {
    std::cout << "Rendering Splatter..." << std::endl;
    // sprite size is 100px radius circle, sizeFactor scales this size, so 0.2 = 20px radius
    // numDrops is an upper bound
    Splatter(Time("04:00:000"), Time("04:05:000"), 0.5, 1000, 2, 2000, Vector2(50, 50)).make();
    Splatter(Time("04:01:000"), Time("04:05:000"), 0.3, 300, 1, 2000, Vector2(-10, -100)).make();
    Splatter(Time("04:02:000"), Time("04:05:000"), 0.2, 300, 1, 2000, Vector2(-130, 0)).make();
}

void Splatter::make(const Time& startTime,
					const Time& endTime,
					Bubble* const bubble) {
	const auto size = bubble->sprites.total_scale.x;
	Splatter(startTime, endTime, 0.5f, 400, 3, 500, bubble).make();
}

void Splatter::renderFirstGradualPop(std::vector<Bubble*>& bubbles) {
	const auto startTime = Time("02:33:885").ms;
	const auto endTime = Time("03:10:112").ms;
	const auto totalTime = endTime - startTime;
	const auto timePerBubble = static_cast<float>(totalTime) / bubbles.size();

	for (int i = 0; i < bubbles.size(); ++i) {
		const auto splatterStartTime = startTime + i * timePerBubble;
		const auto splatterEndTime = splatterStartTime + timePerBubble;
		make(splatterStartTime, endTime, bubbles[i]);
	}
}

void Splatter::renderSecondAllPop(std::vector<Bubble*>& bubbles) {

}