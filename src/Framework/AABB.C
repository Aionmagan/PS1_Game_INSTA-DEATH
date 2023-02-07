/*
 * AABB.c
 *
 *  Created on: Jan 6, 2023
 *      Author: Noel Rojas Oliveras
 */
#include "AABB.H"

int aabb(GsBOXF* a, GsBOXF* b)
{
	return (a->x < b->x + b->w &&
		    a->x + a->w > b->x &&
		    a->y < b->y + b->h &&
		    a->y + a->h > b->y);
}
