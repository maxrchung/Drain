#include "Character.hpp"
#include "a.hpp"
#include <exception>
std::unique_ptr<Character> Character::get(const char character) {
	switch (character) {
		case 'a':
			return std::make_unique<a>();
		default:
			throw new std::exception("Unsupported lyric character: " + character);
	}
}