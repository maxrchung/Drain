#include "LineStroke.hpp"
#include "Path.hpp"
#include "Storyboard.hpp"
LineStroke::LineStroke(const Vector2& start, const Vector2& end) 
	: Stroke{ start, end } {
}
float LineStroke::calculateLength() const {
	const auto length = (end - start).Magnitude();
	return length;
}
void LineStroke::createSprites(const Vector2& position, const float scale) {
	line = Storyboard::CreateSprite(getPath(Path::Square), position + start * scale, Layer::Background, Origin::CentreLeft);
	startPoint = Storyboard::CreateSprite(getPath(Path::Circle), position + start * scale, Layer::Background);
	endPoint = Storyboard::CreateSprite(getPath(Path::Circle), position + end * scale, Layer::Background);
}
void LineStroke::draw(const Vector2& position,
					  const int strokeStart,
					  const int strokeEnd,
					  const int drawSpeed,
					  const Color& foreground,
					  const Color& background,
					  const float scale) {

}