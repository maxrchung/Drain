#include "Raindrop.hpp"

Raindrop::Raindrop(float size, SpriteCollection droplet, Vector2 initial_2d_position, Vector2 final_2d_position, Time start, Time end)
	:size(size), droplet(droplet), initial_2d_position(initial_2d_position), final_2d_position(final_2d_position), start(start), end(end){
	//speed = (final_2d_position - initial_2d_position )/ (end.ms - start.ms);
}

