#include "cube3D.h"
#include <math.h>
#include <stdio.h>

/*
	to dray the scene we use vertical line
	line_h is the leght of the line that give the illusion of the distance
	line offset is just a padding of the line to have them 
	at the center of the screen
	to avoid fisheye effect (that happen because different lenft of the ray)  we need to moltiply the distance of the ray with the cosine of the distance of the player angle and the ray angle
*/
void scene3d(double dist, int ray, double angle, t_player *player )
{
	double line_h;
	double line_offset;

	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	dist = dist * cos(angle);
	line_h = (8 * 8 * 320) / dist;
	if (line_h > 320)
		line_h = 320;
	line_offset = 160 - line_h / 2;
	
	draw3d(player, ray*8+530, line_offset, ray*8+530, line_h+line_offset);

}