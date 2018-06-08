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
				   const int start,
				   const int end,
				   const int drawSpeed,
				   const Color& foreground,
				   const Color& background,
				   const float scale);
private:
	// Space between characters represented as a factor of scale
	static constexpr float kerning = 0.25f;
	float calculateWidth(const std::vector<Character>& characters, const float scale) const;
	std::vector<Character> createCharacters(const std::string& lyric) const;
};