#pragma once
#include "Character.hpp"
#include "Color.hpp"
#include "Time.hpp"
#include "Vector2.hpp"
#include <memory>
#include <string>
#include <vector>
// To use Lyric, call the static function draw() and enter all the parameters
// I decided to use a static method over constructor because this doesn't need to return an object
class Lyric {
public:
	static void draw(const std::string& lyric,
					 const Vector2& center,
					 const int startTime,
					 const int endTime,
					 const Color& background,
					 const Color& foreground,
					 const float scale);
private:
	// Space between characters represented as a factor of scale
	static constexpr float kerning = 0.25f;
	static float calculateWidth(const std::vector<Character>& characters, const float scale);
	static std::vector<Character> createCharacters(const std::string& lyric);
};