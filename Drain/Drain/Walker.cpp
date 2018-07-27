#include "Storyboard.hpp"
#include "Path.hpp"

#include "Walker.hpp"

#include <cmath>

Walker::Walker(std::vector<Sprite *> sprites) {
	//convert each 2d location into a 3d location in real space

	for(int i = 0; i < sprites.size(); ++i) {
		raindrop drop;
		drop.sprite = sprites[i];
		drop.size = w_rand(this->minSize, this->maxSize);
		drop.position = twoToThree(sprites[i], drop.size);
		this->raindrops.push_back(drop);
	}
}


/*
 * distance: forward distance walked, can be positive or negative?
 * startTime/endTime: specificy how long walked
 */
void Walker::walk(float distance, Time startTime, Time endTime) {
	//for every sprite
	Vector3 temp = Vector3::Zero;

	//in addition to the sprites from the initial rain generator
	//add more sprites
	addSprites(distance, startTime, endTime);

	for(auto & drop: this->raindrops) {
		Vector3 start_coord = drop.position;
		
		Vector2 start_coord_2d = drop.sprite->position;

		//only walk in the z direction
		Vector3 end_coord = start_coord;
		end_coord.z -= distance;

		Vector3 temp = threeToTwo(end_coord, drop.size);
		Vector2 end_coord_2d = Vector2::Vector2(temp.x, temp.y);

		Vector2 t = end_coord_2d - start_coord_2d;
		float initial_distance = t.Magnitude();
		float distance_ratio = 0;

		float start_scale = drop.sprite->scale;
		float end_scale = temp.z;

		uint8_t start = checkInScreen(start_coord, drop.size);
		uint8_t end = (checkInScreen(end_coord, drop.size)) << 1;

		uint8_t s = start | end;
		switch(s) {
		case 0: //never in sight
		case 3: //starts and ends in sight
			//don't need to do anything for either
			break;

		case 1: //starts in sight, ends not in sight
			end_coord_2d = findCollision(start_coord_2d, end_coord_2d);
			t = end_coord_2d - start_coord_2d;
			distance_ratio = (t.Magnitude()) / initial_distance;
			end_scale = distance_ratio * (end_scale - start_scale) + start_scale;
			endTime.ms = startTime.ms + (endTime.ms - startTime.ms) * distance_ratio;
			break;

		case 2: //start not in sight, end in sight
			start_coord_2d = findDistance(start_coord, end_coord, drop.size);
			t = end_coord_2d - start_coord_2d;
			distance_ratio =  1 - ((t.Magnitude()) / initial_distance);
			start_scale = min_scale;
			startTime.ms += distance_ratio * (endTime.ms - startTime.ms);
			break;

		default:
			std::cout << "Error in Walker::walk\n";
			break;
		}

		if(s) {
			drop.sprite->Move(startTime.ms, endTime.ms, start_coord_2d, end_coord_2d);
			drop.sprite->Scale(startTime.ms, endTime.ms, start_scale, end_scale);
		}
	}

	return;
}


/*
 * checks that the object is within screen
 */
bool Walker::checkInScreen(Vector3 coordinates, float size) {
	bool out = 1;

	//size of sprite in pixels
	float spriteSize = 100;

	if(coordinates.z < 1)
		out = 0;

	if( (size / (coordinates.z * this->sprite_size) < min_scale) )
		out = 0;

	Vector3 coordinate = threeToTwo(coordinates, size);

	if( out && fabs(coordinate.x) > (Vector2::ScreenSize.x / 2) ) {
		float edge = fabs(coordinate.x) - (size * spriteSize / 2);
		if( edge > (Vector2::ScreenSize.x / 2) )
			out = 0;
	}

	//if out is already determined to be 0, don't do extra work
	if(out && (fabs(coordinate.y) > (Vector2::ScreenSize.y / 2)) ) {
		float edge = fabs(coordinate.y) - (size * spriteSize / 2);
		if( edge > (Vector2::ScreenSize.y / 2) )
			out = 0;
	}

	return out;
}


/*
 * convert 2d coordinates and a size into 3d coordinates
 * take sprite coordinates
 */
Vector3 Walker::twoToThree(Sprite *sprite, float size) {
	Vector3 out;

	out.z = size / (this->sprite_size * sprite->scale);

	out.x = sprite->position.x * out.z;
	out.y = sprite->position.y * out.z;					      

	return out;
}

/*
 * convert 3d coordinates into 2d coordinates and a size
 * the Vector3 will have x and y as usual, but the z 
 * member will be the scale
 * probably not a good idea but uhh
 */
Vector3 Walker::threeToTwo(Vector3 coordinates, float size) {
	Vector3 out;

	out.x = coordinates.x / coordinates.z;
	out.y = coordinates.y / coordinates.z;

	//scale of the image
	out.z = size / (coordinates.z * this->sprite_size);

	return out;
}


/*
 * assuming that b is out of the screen
 * finds the point at which the line between 
 * a and b hits the edge of the screen
 */
Vector2 Walker::findCollision(Vector2 a, Vector2 b) {
	Vector2 out = Vector2::Zero;

	Vector2 slopeV = b - a;
	float slope = (b.y - a.y) / (b.x - a.x);

	Vector2 mid = Vector2::ScreenSize;

	if(slopeV.y > 0)
		mid.y = -Vector2::ScreenSize.y;

	if(slopeV.x > 0)
		mid.x = -Vector2::ScreenSize.x;


	out.y = a.y - slope * (a.x - mid.x);
	out.x = a.x - ((a.y - mid.y) / slope);

	if(abs(out.y) > Vector2::ScreenSize.y)
		out.y = mid.y;

	if(abs(out.x) > Vector2::ScreenSize.x)
		out.x = mid.x;

	return out;
}


Vector2 Walker::findDistance(Vector3 a, Vector3 b, float size) {
	Vector2 out = Vector2::Zero;

	Vector3 out_3d = Vector3::Zero;
	out_3d.z = size / (this->sprite_size * this->min_scale);

	Vector3 begin = threeToTwo(a, size);
	Vector3 end = threeToTwo(b, size);

	Vector3 diff = end - begin;

	float ratio = (out_3d.z - end.z) / diff.z;

	out_3d.x = b.x - ratio * diff.x;
	out_3d.y = b.y - ratio * diff.y;

	out_3d = threeToTwo(out_3d, size);

	out.x = out_3d.x;
	out.y = out_3d.y;

	return out;
}


void Walker::addSprites(float distance, Time startTime, Time endTime) {
	float speed = distance / (endTime.ms - startTime.ms);

	const float sizeX = Vector2::ScreenSize.x;
	const float sizeY = Vector2::ScreenSize.y;

	//some constant to multiply the speed by
	const uint8_t multiplier = 255;

	//max value for loop
	uint64_t iteratorMax = speed * multiplier;

	//path to image
	std::string spriteImage = getPath(Path::Circle);

	//maximum distance to draw a raindrop
	float drawDistance = this->max_distance + distance * 2;

	for(uint64_t i = 0; i < iteratorMax; ++i) {
		Vector3 position_three = Vector3(w_rand(-sizeX, sizeX),
						 w_rand(-sizeY, sizeY),
						 w_rand(1, drawDistance));
		raindrop drop;
		drop.size = w_rand(minSize, maxSize);
		Vector3 position_two = threeToTwo(position_three, drop.size);

		Sprite *sprite = Storyboard::CreateSprite(spriteImage, Vector2(position_two.x, position_two.y));
		sprite->scale = position_two.z;


		drop.sprite = sprite;
		drop.position = position_three;

		this->raindrops.push_back(drop);
	}

	return;
}


float Walker::w_rand(float min, float max) {
	float out = (float)rand() / RAND_MAX;
	out *= (max - min);
	out += min;

	return out;
}
