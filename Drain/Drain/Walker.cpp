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

	//move those boys
	moveSprites(distance, startTime, endTime);
  
	return;
}


void Walker::moveSprites(float distance, Time startTime, Time endTime) {

	int total_time = endTime.ms - startTime.ms;

	std::string spriteImage = getPath(Path::Circle);

	const float sizeX = Vector2::ScreenSize.x/2;
	const float sizeY = Vector2::ScreenSize.y/2;
	for(int i = 0; i < (int) distance; ++i) {
		int int_start_time = startTime.ms + i * w_rand(-1000, 1000);
		if(int_start_time < startTime.ms)
			int_start_time = startTime.ms;
		
		int int_end_time = int_start_time + w_rand(1000, total_time);

		if(int_end_time > endTime.ms)
			int_end_time = endTime.ms;

		float start_scale = min_scale;
		float end_scale = max_scale;

		Vector2 start_coord = Vector2(w_rand(-sizeX, sizeX),
					       w_rand(-sizeY, sizeY));

		Vector2 end_coord = findProjection(Vector2::Zero, start_coord);

		Sprite *sprite = Storyboard::CreateSprite(spriteImage, start_coord);


		sprite->Move(int_start_time, int_end_time, start_coord, end_coord);
		sprite->Scale(int_start_time, int_end_time, start_scale, end_scale);
	}

	/*
	int a = 0;
	int b = 0;
	int c = 0;

	const int elapsed_time = endTime.ms - startTime.ms;
		
	for(auto & drop: this->raindrops) {
		int int_start_time = startTime.ms;
		int int_end_time = endTime.ms;

		Vector3 start_coord_3d = drop.position;
		Vector2 start_coord_2d = drop.sprite->position;

		//only walk in the z direction
		Vector3 end_coord_3d = start_coord_3d;
		end_coord_3d.z -= distance;


		Vector3 temp = Vector3::Zero;
		Vector2 end_coord_2d = Vector2::Zero;

		bool end = 0;
		if(end_coord_3d.z < 0) {
			//determine the exit coordinates of the drop
			end_coord_3d.z = 1;
			temp = threeToTwo(end_coord_3d, drop.size);

			end_coord_2d = findProjection(start_coord_2d, end_coord_2d);
			end = 1;
			++c;	
		} else {
			temp = threeToTwo(end_coord_3d, drop.size);
			end_coord_2d = Vector2::Vector2(temp.x, temp.y);
			end = checkInScreen(end_coord_3d, drop.size);
		}
		float initial_distance = (end_coord_2d - start_coord_2d).Magnitude();

		float start_scale = drop.sprite->scale;
		float end_scale = temp.z + start_scale;

		bool start = checkInScreen(start_coord_3d, drop.size);


		//const values
		const float const_start_scale = start_scale;
		const float const_end_scale = end_scale;
		const float const_scale_diff = const_end_scale - const_start_scale;

		const float const_x_start_pos = start_coord_2d.x;
		const float const_x_end_pos = end_coord_2d.x;

		if(!start) {
			start_coord_2d = findAppearPoint(start_coord_3d, end_coord_3d, drop.size);
			start_scale = min_scale;
			int_start_time = (min_scale - const_start_scale) / const_scale_diff * elapsed_time + int_start_time;
			++a;
		}

		if(!end) {
			end_coord_2d = findCollision(start_coord_2d, end_coord_2d);
			float x_diff = end_coord_2d.x - start_coord_2d.x;
			float scale_diff = end_scale - start_scale;
			float pos_ratio = x_diff / (const_x_end_pos - start_coord_2d.x);

			//std::cout << pos_ratio << "|" << scale_diff << "|" << x_diff << "\n";
			end_scale = pos_ratio * scale_diff + start_scale;
			int_end_time = pos_ratio * (int_end_time - int_start_time) + int_start_time;
			++b;
		}
		std::cout << "debug: " << start << " " << end << " " << int_start_time << "|" << int_end_time << "|" << start_coord_2d << "|" << end_coord_2d << "|" << start_scale << "|" << end_scale << "\n";

		drop.sprite->Move(int_start_time, int_end_time, start_coord_2d, end_coord_2d);
		drop.sprite->Scale(int_start_time, int_end_time, start_scale, end_scale);
	}
	std::cout << a << " " << b << " " << c << "\n";
	*/
}

/*
 * checks that the object is within screen
 */
bool Walker::checkInScreen(Vector3 coordinates, float size) {
	bool out = 1;

	if(coordinates.z < 0)
		out = 0;

	//if scale is too small
	if( out && (((this->sizeScale * size) / (coordinates.z * this->sprite_size)) < min_scale) ) {
		out = 0;
	}

	Vector3 coordinate = threeToTwo(coordinates, size);

	//if xcoord is out of bounds
	if( out && std::abs(coordinate.x) > (Vector2::ScreenSize.x / 2) ) {
		float edge = std::abs(coordinate.x) - (size * this->sprite_size / 2);
		if( edge > (Vector2::ScreenSize.x / 2) ) {
			out = 0;
			std::cout << "x out of range\n";
		}
	}

	//if ycoord is out of bounds
	if(out && (std::abs(coordinate.y) > (Vector2::ScreenSize.y / 2)) ) {
		float edge = std::abs(coordinate.y) - (size * this->sprite_size / 2);
		if( edge > (Vector2::ScreenSize.y / 2) ) {
			out = 0;
			std::cout << "y out of range\n";
		}
	}

	return out;
}


/*
 * convert 2d coordinates and a size into 3d coordinates
 * take sprite coordinates
 * assume location of camera being 0 0 0
 */
Vector3 Walker::twoToThree(Sprite *sprite, float size) {
	Vector3 out;

	out.z = (size * this->sizeScale) / sprite->scale;

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
	out.z = (size * this->sizeScale) / coordinates.z;

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

	//determine which border of the screen has a collision
	Vector2 mid = Vector2::ScreenSize;

	if(slopeV.y < 0)
		mid.y = -Vector2::ScreenSize.y;

	if(slopeV.x < 0)
		mid.x = -Vector2::ScreenSize.x;


	float slope = slopeV.y / slopeV.x;

	switch((!!slopeV.y) | (!!slopeV.x << 1)) {
	case 0: //same point
		return a;

	case 1: //horizontal line
	case 2: //vertical line
		out = b;
		break;

	case 3:
		out.y = a.y - (slope * (a.x - mid.x));
		out.x = a.x - ((a.y - mid.y) / slope);
		break;
	}

	if(std::abs(out.y) > Vector2::ScreenSize.y)
		out.y = mid.y;

	if(std::abs(out.x) > Vector2::ScreenSize.x)
		out.x = mid.x;

	return out;
}

Vector2 Walker::findProjection(Vector2 a, Vector2 b) {
	Vector2 out = Vector2::Zero;

	Vector2 slopeV = b - a;
	Vector2 mid = Vector2::ScreenSize/2;

	float slope = slopeV.y / slopeV.x;

	if(slopeV.y < 0)
		mid.y = -Vector2::ScreenSize.y/2;

	if(slopeV.x < 0)
		mid.x = -Vector2::ScreenSize.x/2;

	switch((!!slopeV.y) | (!!slopeV.x << 1)) {
	case 0:
		break;
		
	case 1:
		out.x = mid.x;
		break;

	case 2:
		out.y = mid.y;
		break;
		
	case 3:
		/*
		out.y = a.y - (slope * (mid.x - a.x));
		out.x - a.x - ((mid.y - a.y) / slope);
		*/
		out.y = slope * mid.x + a.y;
		out.x = (mid.y - a.y) / slope;
		if(std::abs(out.y) > Vector2::ScreenSize.y/2)
			out.y = mid.y;

		if(std::abs(out.x) > Vector2::ScreenSize.x/2)
			out.x = mid.x;

		break;
	}
	return out;
}


/*
 * find the point at which the raindrop becomes visible
 */
Vector2 Walker::findAppearPoint(Vector3 a, Vector3 b, float size) {
	Vector2 out = Vector2::Zero;

	Vector3 out_3d = Vector3::Zero;
	out_3d.z = (size * this->sizeScale) / this->min_scale;

	Vector3 diff = b - a;

	float x_ratio = (diff.x / diff.z);
	float y_ratio = (diff.y / diff.z);

	out_3d.x = x_ratio * (out_3d.z - a.z) + a.x;
	out_3d.y = y_ratio * (out_3d.z - a.z) + a.y;

	out_3d = threeToTwo(out_3d, size);

	out.x = out_3d.x;
	out.y = out_3d.y;

	return out;
}


void Walker::addSprites(float distance, Time startTime, Time endTime) {
	//speed in distance/second
	distance = abs(distance);
	float speed = 1000 * distance / (endTime.ms - startTime.ms);

	const float sizeX = Vector2::ScreenSize.x/2;
	const float sizeY = Vector2::ScreenSize.y/2;

	//constant to multiply speed by, affects density
	const uint8_t multiplier = 1;

	//max value for loop
	uint64_t iteratorMax = speed * multiplier;

	//path to image
	std::string spriteImage = getPath(Path::Circle);

	//maximum distance to draw a raindrop
	float drawDistance = this->max_distance + distance * 2;

	for(uint64_t i = 0; i < iteratorMax; ++i) {
		raindrop drop;
		drop.size = w_rand(minSize, maxSize);

		Vector2 position_two = Vector2(w_rand(-sizeX, sizeX),
					       w_rand(-sizeY, sizeY));



		Sprite *sprite = Storyboard::CreateSprite(spriteImage, position_two);
		sprite->scale = w_rand(min_scale/2, min_scale);


		Vector3 position_three = twoToThree(sprite, drop.size);

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
