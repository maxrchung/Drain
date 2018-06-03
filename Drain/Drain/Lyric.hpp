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
	explicit Lyric(const std::string& lyric, const CharacterConfig& config, const Vector2& center = Vector2::Zero);
private:
	std::vector<std::unique_ptr<Character>> getCharacters(const std::string& lyric) const;
	float calculateSize(const std::vector<std::unique_ptr<Character>>& characters, float scale) const;
	void draw(const std::vector<std::unique_ptr<Character>>& characters, const CharacterConfig& config, const Vector2& center) const;
	// Space between characters represented as a factor of scale
	static constexpr float kerning = 0.25f;
};