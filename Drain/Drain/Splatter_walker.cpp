#include "Splatter.hpp"
#include "Splatter_walker.hpp"
#include "Swatch.hpp"
#include "Vector2.hpp"


Splatter_walker::Splatter_walker(const std::vector<SpriteCollection> &sprites)
	: Walker(sprites) {
}

SpriteCollection create(const Time& startTime, const Vector2& centerPos, const float scale) {
	return Splatter::makeWalkerSplatter(startTime, centerPos, scale);
}
