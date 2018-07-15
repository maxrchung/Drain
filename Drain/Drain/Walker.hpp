#pragma once

#include "Vector3.hpp"

#include <cmath>

Walker::Walker() {
}

~Walker::Walker() {
}

void Walker::walk(Vector2 startPosition, Vector2 endPosition, Time startTime, tiome endTime) {
	return;
}

/*
 * angle vectors are for the azimuth and altitude respectively
 * these are absolute positioning in degrees
 */
void Walker::rotate(Vector2 startAngle, Vector2 endAngle, Time startTime, Time endTime) {
	//check that the altitude angles are within range
	if((fabs(startAngle.y) > 90) || (fabs(endAngle.y) > 90))
		return;

	//modulo the angle so we don't have to deal with that later
	startAngle.x = fmod(startAngle.x, 360);
	endAngle.x = fmod(startAngle.x, 360);



	return;
}
	
