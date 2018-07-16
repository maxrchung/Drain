#include "Vector3.hpp"

#include <cmath>

Walker::Walker(std::vector<Sprite *> sprites, std:;vector<Vector2> location)
	:sprites(sprites) {
	//convert each 2D location into a 3d location in real space
	for(int i = 0; i < location.size(); ++i) {
		this->location[i] = convertThreeD(location[i]);
	}
}

~Walker::Walker() {
}


/*
 * distance: forward distance walked, can be positive or negative?
 * startTime/endTime: specificy the distance walked
 */
void Walker::walk(float distance, Time startTime, tiome endTime) {

	return;
}

/*
 * angle vectors are for the azimuth and altitude respectively
 * these are absolute positioning in degrees
 */
/*
void Walker::rotate(Vector2 startAngle, Vector2 endAngle, Time startTime, Time endTime) {
	//check that the altitude angles are within range
	if((fabs(startAngle.y) > 90) || (fabs(endAngle.y) > 90))
		return;

	//modulo the angle so we don't have to deal with that later
	startAngle.x = fmod(startAngle.x, 360);
	endAngle.x = fmod(startAngle.x, 360);

	for(int i = 0; i < sprites.size(); ++i) {
		Vector2 startPosition;
		Vector2 endPosition;
		sprites[i]->move(startTime.ms, endTime.ms, startPosition, endPosition);
	}

	return;
}
*/	

bool Walker::checkAzimuth(Vector3 coordinates, float size) {
	bool out = 0;

	float leftAngle = this->angle.x + this->fov/2;
	if( (leftAngle > 360) || (leftAngle < 0) ) {
		leftAngle += 360;
		leftAngle = fmod(leftAngle, 360);
	}

	float rightAngle = this->angle.x - this->fov/2;
	if( (rightAngle > 360) || (rightAngle < 0) ) {
		rightAngle += 360;
		rightAngle = fmod(rightAngle, 360);
	}

	float coordinateAngle = atan2((position.y - coordinates.y), (position.x - coordinates.x)) * (180/M_PI);

	if( (coordinateAngle <= leftAngle) && (coordinateAngle >= rightAngle) ) {
		out = 1;
	} else if( coordinateAngle >= leftAngle) {
		//check if the particle will partly be on screen
	} else if( coordinateAngle >= rightAngle) {
	}

	return out;
}

/*
 * check check the z direction
 */
bool Walker::checkAltitude(Vector3 coordinates, float size) {

}

/*
 * checks that the object is within screen
 */
bool Walker::checkInScreen(Vector3 coordinates, float size) {
	return (checkAzimuth(coordinates, size) && checkAltitude(coordinates, size));
}


/*
 * convert 2d coordinates and a size into 3d coordinates
 */
Vector3 Walker::convertThreeD(Vector2 coordinates, float size) {
	Vector3 out;

	out.z = 0;
	
	return out;
}

/*
 * convert 3d coordinates into 2d coordinates and a size
 * the size is a pointer that can be read from the calling function 
 */
Vector2 Walker:: convertTwoD(Vector3 coordinates, float *size) {
	Vector2 out;

	out.x = coordinates.x / coordinates.z;
	out.y = coordiantes.y / coordinates.z;
	
	*size = 0;

	return out;
}
