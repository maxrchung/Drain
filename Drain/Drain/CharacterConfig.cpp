#include "CharacterConfig.hpp"
CharacterConfig::CharacterConfig(const int start,
								 const int end,
								 const int drawSpeed,
								 const Color& foreground,
								 const Color& background,
								 const float scale)
	: start{ start }, end{ end }, drawSpeed{ drawSpeed }, foreground{ foreground }, background{ background }, scale{ scale } {}