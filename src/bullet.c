/*  Created on: Jan 11, 2023
 *      Author: Noel Rojas Oliveras
 *
 *  Code has been source'd from the NY-Demos folder.
 *  Credits to the all the Authors involved
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */

#include "bullet.h"

void bullet_init(bullet_t* shot)
{
	shot->alive = 0;
	shot->box.attribute = 0;
	shot->box.h = 4;
	shot->box.w = 4;
	shot->box.x = 0;
	shot->box.y = 0;
	shot->box.r = 128;
	shot->box.g = 128;
	shot->box.b = 0;
	shot->dir.x = 0;
	shot->dir.y = 0;
}

void bullet_update(bullet_t* shot)
{
	shot->world.x += shot->dir.x*12;
	shot->world.y += shot->dir.y*12;

	if (shot->box.x <   0 ||
		shot->box.x > 355 ||
		shot->box.y <   0 ||
		shot->box.y > 340){shot->alive = 0;}
}

void bullet_shoot(bullet_t*shot, vec2_t *pos)
{
	short dirx, diry;
	short ox, oy; //offset
	if      (pad_button(PADTRIANGLE)){dirx =  0; diry = -1; ox = 2; oy = 18;}
	else if (pad_button(PADCROSS)   ){dirx =  0; diry =  1; ox = 2; oy = -6;}
	else if (pad_button(PADSQUARE)	){dirx = -1; diry =  0; ox = 14; oy = 6;}
	else if (pad_button(PADCIRCLE)	){dirx =  1; diry =  0; ox =-12; oy = 6;}
	else    {return;}

	shot->dir.x   = dirx;
	shot->dir.y   = diry;
	shot->world.x = pos->x-ox;
	shot->world.y = pos->y-oy;
	shot->alive  = 1;
}
