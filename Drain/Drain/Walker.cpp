#include "Walker.hpp"

#include <cmath>

Walker::Walker(std::vector<Sprite *> sprites, std::vector<Vector2> location, std::vector<float> size)
	:sprites(sprites) {
	//convert each 2D location into a 3d location in real space
	for(int i = 0; i < location.size(); ++i) {
		this->location[i] = convertThreeD(location[i], size[i]);
	}
}


/*
 * distance: forward distance walked, can be positive or negative?
 * startTime/endTime: specificy the distance walked
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
		endCoord.z += distance;

		temp = convertTwoD(endCoord);
		Vector2 endTwoD = Vector2::Vector2(temp.x, temp.y);
		float endScale = startScale * temp.z;


		bool check = checkInScreen(endCoord, endScale);
		if( check ) {
			sprites[i]->Move(startTime.ms, endTime.ms, startTwoD, endTwoD);
		} else {

		}
	}

	return;
}


/*
 * checks that the object is within screen
 */
bool Walker::checkInScreen(Vector3 coordinates, float size) {
	bool out = 1;
	float spriteSize = 100;

	Vector3 coordinates = convertTwoD(coordinates, size);

	if( fabs(coordinates.x) > (Vector2::ScreenSize.x / 2) ) {
		float edge = fabs(coordinates.x) - (size * spriteSize / 2);
		if( edge > (Vector::ScreenSize.x / 2) ) {
			out = 0;
		} 
	}

	//if out is already determined to be 0, don't do extra work
	if(out && (fabs(coordinates.y) > (Vector2::ScreenSize.y / 2)) ) {
		float edge = fabs(coordinates.y) - (size * spriteSize / 2);
		if( edge > (Vector::ScreenSize.y / 2) ) {
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
	Vector2 out;

	out.x = coordinates.x / coordinates.z;
	out.y = coordinates.y / coordinates.z;
	
	float r = coordinates.magnitude();

	out.z = (r/max_distance);

	return out;
}
