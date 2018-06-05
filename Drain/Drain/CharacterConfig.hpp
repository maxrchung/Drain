#pragma once
#include "Color.hpp"
class CharacterConfig {
public:
	explicit CharacterConfig(const float scale,
							 const int start,
							 const int end,
							 const int drawSpeed,
							 const Color& foreground,
							 const Color& background);
	const float scale;
	const int start;
	const int end;
	const int drawSpeed;
	const Color foreground;
	const Color background;
};