#pragma once
#include "Character.hpp"
#include "Color.hpp"
#include "Time.hpp"
#include "Vector2.hpp"
#include <memory>
#include <string>
#include <vector>
class Lyric {
public:
	explicit Lyric(const std::string& lyric, 
				   const Vector2& center, 
				   const int startTime,
				   const int endTime,
				   const int drawSpeed,
				   const Color& foreground,
				   const Color& background,
				   const float scale);
private:
	// Space between characters represented as a factor of scale
	static constexpr float kerning = 0.25f;
	static float calculateWidth(const std::vector<Character>& characters, const float scale);
	static std::vector<Character> createCharacters(const std::string& lyric);
	static void render(const std::vector<Character>& characters,
					   const float lyricWidth,
					   const Vector2& center,
					   const int startTime,
					   const int endTime,
					   const int drawSpeed,
					   const Color& foreground,
					   const Color& background,
					   const float scale);
};