#include "Storyboard.hpp"
#include "Path.hpp"

#include "Walker.hpp"

#include <cmath>

Walker::Walker(std::vector<Sprite *> sprites)
	: sprites{sprites} {
}


/*
 * distance: forward distance walked, can be positive or negative?
 * startTime/endTime: specificy how long walked
 */
void Walker::walk(float distance, Time startTime, Time endTime) {
	//for every sprite
	Vector3 temp = Vector3::Zero;

	//move the boys from rainGenerator
	moveCurrent(distance, startTime, endTime);

	//move those boys
	moveSprites(distance, startTime, endTime);
  
	return;
}


void Walker::moveCurrent(float distance, Time startTime, Time endTime) {
	int int_start_time = startTime.ms;
	int total_time = endTime.ms - startTime.ms;

	for(auto & drop : sprites) {
		if(inScreen(drop->position)) {
			Vector2 start_coord = drop->position;
			Vector2 end_coord = findProjection(Vector2::Zero, start_coord);

			float ratio_traveled = (end_coord - start_coord).Magnitude() / (end_coord.Magnitude());

			float start_scale = drop->scale;
			float end_scale = start_scale * (1 + ratio_traveled);
		
			int int_end_time = int_start_time + w_rand(1000, total_time);
			if(int_end_time > endTime.ms)
				int_end_time = endTime.ms;

			drop->Move(int_start_time, int_end_time, start_coord, end_coord);
			drop->Scale(int_start_time, int_end_time, start_scale, end_scale);
		}

	}
}

void Walker::moveSprites(float distance, Time startTime, Time endTime) {

	int total_time = endTime.ms - startTime.ms;

	std::string spriteImage = getPath(Path::Circle);

	const float sizeX = Vector2::ScreenSize.x/2 * 0.4;
	const float sizeY = Vector2::ScreenSize.y/2 * 0.4;
	int count = distance * (total_time/1000);

	for(int i = 0; i < count; ++i) {
		int int_start_time = startTime.ms + i * w_rand(0, 1000);
		if(int_start_time < startTime.ms)
			int_start_time = startTime.ms;
		
		int int_end_time = int_start_time + w_rand(1000, total_time);
		if(int_end_time > endTime.ms)
			int_end_time = endTime.ms - w_rand(0, 2000);

		float start_scale = min_scale;
		float end_scale = max_scale * w_rand(1, 5);

		Vector2 start_coord = Vector2(w_rand(-sizeX, sizeX),
					       w_rand(-sizeY, sizeY));

		Vector2 end_coord = findProjection(Vector2::Zero, start_coord);

		Sprite *sprite = Storyboard::CreateSprite(spriteImage, start_coord);


		sprite->Move(int_start_time, int_end_time, start_coord, end_coord);
		sprite->Scale(int_start_time, int_end_time, start_scale, end_scale);
	}
}

/*
 * checks that the object is within screen
 */
bool Walker::inScreen(Vector2 a) {
	bool out = 1;

	if(std::abs(a.x) > Vector2::ScreenSize.x/2)
		out = 0;

	if(out && (std::abs(a.y) > Vector2::ScreenSize.y/2))
		out = 0;

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

Vector2 Walker::findProjection(Vector2 a, Vector2 b) {
	Vector2 out = Vector2::Zero;

	Vector2 slopeV = b - a;
	Vector2 mid = Vector2::ScreenSize/2;

	float slope = slopeV.y / slopeV.x;

	float size_offset = this->sprite_size * this->max_scale * 5;

	if(slopeV.y < 0) {
		mid.y = -Vector2::ScreenSize.y/2 - size_offset;
	} else {
		mid.y += size_offset;
	}

	if(slopeV.x < 0) {
		mid.x = -Vector2::ScreenSize.x/2 - size_offset;
	} else {
		mid.y += size_offset;
	}

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


float Walker::w_rand(float min, float max) {
	float out = (float)rand() / RAND_MAX;
	out *= (max - min);
	out += min;

	return out;
}
