#pragma once
#include "Color.hpp"
struct CharacterConfig {
	explicit CharacterConfig(const int start,
							 const int end,
							 const int drawSpeed,
							 const Color& foreground,
							 const Color& background,
							 const float scale);
	const int start;
	const int end;
	const int drawSpeed;
	const Color foreground;
	const Color background;
	const float scale;
};