#pragma once
#include "Character.hpp"
#include "Color.hpp"
#include "Time.hpp"
#include "Vector2.hpp"
#include <memory>
#include <string>
#include <vector>
// I decided to use a static render method over constructor because this doesn't need to return an object
class Text {
public:
	static void render();
private:
	static void draw(const std::string& lyric,
					 const Vector2& center,
					 const int startTime,
					 const int endTime);
	static void place(const std::vector<std::string>& stanza,
					  const int startTime,
					  const int endTime);
	static const RandomRange poemScale;
	static const RandomRange poemSpacing;
	static constexpr float lyricScale = 22.0f;
	// Space between characters represented as a factor of scale
	static constexpr float tracking = 0.26f;
	static float calculateTopToCenter(const std::vector<Character>& characters, const float scale);
	static float calculateHeight(const std::vector<Character>& characters, const float scale);
	static float calculateWidth(const std::vector<Character>& characters, const float scale);
	static std::vector<Character> createCharacters(const std::string& lyric);
};