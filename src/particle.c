/*  Created on: Jan 1, 2023
 *      Author: Noel Rojas Oliveras
 *
 *  Code has been source'd from the NY-Demos folder.
 *  Credits to the all the Authors involved
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */

#include <libps.h>
#include <stdlib.h>
#include "particle.h"

short i;

void particle_init(particle_t* p, int colorflag)
{
	for(i = 0; i < PRT_AMOUNT; ++i)
	{
		p[i].particle.attribute = 0;
		p[i].particle.w = 2;
		p[i].particle.h = 2;
		p[i].particle.x = 0;
		p[i].particle.y = 0;

		switch(colorflag)
		{
		case BLOOD_COL:
			p[i].particle.r = 128;
			p[i].particle.g = 0;
			break;
		case HEAL_COL:
			p[i].particle.g = 128;
			p[i].particle.r = 0;
			break;
		default:break;
		}

		p[i].particle.b =0;

		p[i].life = 0;
		p[i].dir.x = 0;
		p[i].dir.y = 0;
	}
}

void particle_start(particle_t* p, vec2_t* pos)
{
	for(i = 0; i < PRT_AMOUNT; ++i)
	{
		p[i].particle.attribute = 0;
		p[i].life = (rand()%13)+5;
		p[i].dir.x = (rand()%3) -1;
		p[i].dir.y = (rand()%3) -1;
		p[i].velx = (rand()%3)+1;
		p[i].vely = (rand()%3)+1;
		p[i].world.x = pos->x;
		p[i].world.y = pos->y;

		if((p[i].dir.x + p[i].dir.y) == 0)
			p[i].dir.x++;
	}
}


void particle_update(particle_t* p)
{
	for(i = 0; i < PRT_AMOUNT; ++i)
	{
		if (p[i].life > 0)
		{
			p[i].world.x += p[i].dir.x * p[i].velx;
			p[i].world.y += p[i].dir.y * p[i].vely;
			p[i].life--;
		}else
			p[i].particle.attribute |= (1<<31);
	}
}
