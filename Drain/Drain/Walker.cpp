#include "RandomRange.hpp"
#include "Storyboard.hpp"
#include "Path.hpp"

#include "Walker.hpp"

#include <cmath>

Walker::Walker(std::vector<Sprite *> sprites) {
	//convert each 2D location into a 3d location in real space
	for(int i = 0; i < sprites.size(); ++i) {
		raindrop drop;
		drop.sprite = sprites[i];
		drop.position = twoToThree(sprites[i]);
		drop.size = RandomRange::calculate(this->minSize, this->maxSize);

		raindrops.push_back(drop);
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
		Vector3 startCoord = drop.position;
		Vector3 temp = threeToTwo(startCoord);

		Vector2 startTwoD = Vector2(temp.x, temp.y);
		
		//only walk in the z direction
		Vector3 endCoord = startCoord;
		endCoord.z -= distance;

		temp = threeToTwo(endCoord);
		Vector2 endTwoD = Vector2::Vector2(temp.x, temp.y);


		float startScale = drop.sprite->scale * drop.size;
		float endScale = startScale * temp.z;

		uint8_t start = checkInScreen(startCoord, endScale);
		uint8_t end = (checkInScreen(endCoord, endScale)) << 1;

		uint8_t s = start | end;
		switch(s) {
		case 0: //never in sight
		case 3: //starts and ends in sight
			//don't need to do anything for either
			break;
		case 1: //starts in sight, ends not in sight

			break;
		case 2: //start not in sight, end in sight
			break;
		default:
			std::cout << "Error in Walker::walk\n";
			break;
		}

		if(s) {
			drop.sprite->Move(startTime.ms, endTime.ms, startTwoD, endTwoD);
			drop.sprite->Scale(startTime.ms, endTime.ms, startScale, endScale);
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

	if((coordinates.z < 1) || (coordinates.z > max_distance))
		out = 0;

	Vector3 coordinate = threeToTwo(coordinates);

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
Vector3 Walker::twoToThree(Sprite *sprite) {
	Vector3 out;

	float size = sprite->scale;
	Vector2 coordinates = sprite->position;

	out.z = (max_distance * size) / sqrt( (coordinates.x * coordinates.x) + (coordinates.y * coordinates.y ) );

	out.x = coordinates.x * out.z;
	out.y = coordinates.y * out.z;					      

	return out;
}

/*
 * convert 3d coordinates into 2d coordinates and a size
 * the Vector3 will have x and y as usual, but the z 
 * member will be the size
 * probably not a good idea but uhh
 */
Vector3 Walker:: threeToTwo(Vector3 coordinates) {
	Vector3 out;

	out.x = coordinates.x / coordinates.z;
	out.y = coordinates.y / coordinates.z;
	
	float r = coordinates.Magnitude();

	out.z = (r/max_distance);

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
		Vector3 position_three = Vector3(RandomRange::calculate(-sizeX, sizeX),
						 RandomRange::calculate(-sizeY, sizeY),
						 RandomRange::calculate(1, drawDistance));

		Vector3 position_two = threeToTwo(position_three);

		Sprite *sprite = Storyboard::CreateSprite(spriteImage, Vector2(position_two.x, position_two.y));
		sprite->scale = position_two.z;

		raindrop drop;
		drop.sprite = sprite;
		drop.position = position_three;
		drop.size = RandomRange::calculate(minSize, maxSize);
		raindrops.push_back(drop);
	}

	return;
}
