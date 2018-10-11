#pragma once

#include "Sprite.hpp"
#include "SpriteCollection.hpp"
#include "Time.hpp"
#include "Vector2.hpp"
#include "Walker.hpp"

#include <vector>

class Rain_walker : public Walker {
public:
	Rain_walker(const std::vector<SpriteCollection> &sprites);
};
