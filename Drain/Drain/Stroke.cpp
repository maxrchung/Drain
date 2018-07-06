#include "Stroke.hpp"
#include "Swatch.hpp"
const RandomRange Stroke::pointScale = RandomRange(110, 150, Stroke::imageSize);
void Stroke::colorBgSprites(const std::vector<Sprite*>& sprites, const int startDraw, const int endDraw) {
	for (auto const sprite : sprites) {
		sprite->Color(startDraw, endDraw, Swatch::offwhite, Swatch::offwhite);
	}
}
void Stroke::colorFgSprites(const std::vector<Sprite*>& sprites, const int startDraw, const int endDraw) {
	for (auto const sprite : sprites) {
		sprite->Color(startDraw, endDraw, Swatch::offwhite, Swatch::water);
	}
}
void Stroke::fadeSprites(const std::vector<Sprite*>& sprites, const int startDrain, const int endDrain) {
	for (auto const sprite : sprites) {
		sprite->Color(startDrain, endDrain, Swatch::water, Swatch::offwhite);
	}
}
void Stroke::hideSprites(const std::vector<Sprite*>& sprites, const int endDraw) {
	for (auto const sprite : sprites) {
		sprite->Fade(endDraw, endDraw, 1.0f, 0.0f);
	}
}
void Stroke::rotateSprites(const std::vector<Sprite*>& sprites, const int startDraw, const float rotation) {
	for (auto const sprite : sprites) {
		sprite->Rotate(startDraw, startDraw, rotation, rotation);
	}
}
void Stroke::scaleInner(const std::vector<Sprite*>& sprites, const int startDraw, const Vector2& startPosition, const Vector2& center, const float scale) {
	for (auto const sprite : sprites) {
		const auto outerScale = (startPosition - center).Magnitude() * scale / imageSize - (thickness * 0.5f * scale) / imageSize;
		sprite->Scale(startDraw, startDraw, outerScale, outerScale);
	}
}
void Stroke::scaleOuter(const std::vector<Sprite*>& sprites, const int startDraw, const Vector2& startPosition, const Vector2& center, const float scale) {
	for (auto const sprite : sprites) {
		const auto outerScale = (startPosition - center).Magnitude() * scale / imageSize + (thickness * 0.5f * scale) / imageSize;
		sprite->Scale(startDraw, startDraw, outerScale, outerScale);
	}
}
void Stroke::scalePoints(const std::vector<Sprite*>& points, const int startDraw, const float scale) {
	const auto thicknessScale = thickness * scale / imageSize * pointScale.calculate();
	for (auto const point : points) {
		point->Scale(startDraw, startDraw, thicknessScale, thicknessScale);
	}
}