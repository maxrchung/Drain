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
	explicit Lyric(const std::string& lyric, const Vector2& center, const CharacterConfig& config);
private:
	float calculateWidth(const std::vector<Character>& characters, float scale) const;
	std::vector<Character> createCharacters(const std::string& lyric) const;
	void draw(const std::vector<Character>& characters, const Vector2& center, const CharacterConfig& config) const;
	// Space between characters represented as a factor of scale
	static constexpr float kerning = 0.25f;
};