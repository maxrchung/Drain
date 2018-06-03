#include "CharacterConfig.hpp"
CharacterConfig::CharacterConfig(const float scale,
								 const int start,
								 const int end,
								 const int drawSpeed,
								 const Color& foreground,
								 const Color& background)
	: scale{ scale }, start{ start }, end{ end }, drawSpeed{ drawSpeed }, foreground{ foreground }, background{ background } {}