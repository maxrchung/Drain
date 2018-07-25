#include "Walker.hpp"

#include <cmath>

Walker::Walker(std::vector<Sprite *> sprites)
	:sprites(sprites) {
	//convert each 2D location into a 3d location in real space
	for(int i = 0; i < sprites.size(); ++i) {
		location.push_back(convertThreeD(sprites[i]->position, sprites[i]->scale));
	}
}


/*
 * distance: forward distance walked, can be positive or negative?
 * startTime/endTime: specificy how long walked
 */
void Walker::walk(float distance, Time startTime, Time endTime) {
	//for every sprite
	Vector3 temp = Vector3::Zero;
	for(int i = 0; i < location.size(); ++i) {
		Vector3 startCoord = location[i];
		Vector3 temp = convertTwoD(startCoord);

		Vector2 startTwoD = Vector2::Vector2(temp.x, temp.y);
		float startScale = temp.z;

		//only walk in the z direction
		Vector3 endCoord = startCoord;
		endCoord.z -= distance;

		temp = convertTwoD(endCoord);
		Vector2 endTwoD = Vector2::Vector2(temp.x, temp.y);
		float endScale = startScale * temp.z;


		bool check = checkInScreen(endCoord, endScale);
		if( !check ) {
			endTwoD = findCollision(startTwoD, endTwoD);
		}

		startTwoD = sprites[i]->position;
		sprites[i]->Move(startTime.ms, endTime.ms, startTwoD, endTwoD);
		sprites[i]->Scale(startTime.ms, endTime.ms, startScale, endScale);
	}

	return;
}


/*
 * checks that the object is within screen
 */
bool Walker::checkInScreen(Vector3 coordinates, float size) {
	bool out = 1;
	float spriteSize = 100;

	if(coordinates.z < 1) {
		out = 0;
	}

	Vector3 coordinate = convertTwoD(coordinates);

	if( out && fabs(coordinate.x) > (Vector2::ScreenSize.x / 2) ) {
		float edge = fabs(coordinate.x) - (size * spriteSize / 2);
		if( edge > (Vector2::ScreenSize.x / 2) ) {
			out = 0;
		} 
	}

	//if out is already determined to be 0, don't do extra work
	if(out && (fabs(coordinate.y) > (Vector2::ScreenSize.y / 2)) ) {
		float edge = fabs(coordinate.y) - (size * spriteSize / 2);
		if( edge > (Vector2::ScreenSize.y / 2) ) {
			out = 0;
		}
	}

	return out;
}


/*
 * convert 2d coordinates and a size into 3d coordinates
 */
Vector3 Walker::convertThreeD(Vector2 coordinates, float size) {
	Vector3 out;

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
Vector3 Walker:: convertTwoD(Vector3 coordinates) {
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

	Vector2 mid = Vector2::Midpoint;

	if(slopeV.y > 0)
		mid.y = -Vector2::Midpoint.y;

	if(slopeV.x > 0)
		mid.x = -Vector2::Midpoint.x;


	out.y = a.y - slope * (a.x - mid.x);
	out.x = a.x - ((a.y - mid.y) / slope);

	if(abs(out.y) > Vector2::Midpoint.y)
		out.y = mid.y;

	if(abs(out.x) > Vector2::Midpoint.x)
		out.x = mid.x;

	return out;
}
