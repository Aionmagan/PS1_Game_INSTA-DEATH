/*  Created on: Jan 11, 2023
 *      Author: Noel Rojas Oliveras
 *
 *  Code has been source'd from the NY-Demos folder.
 *  Credits to the all the Authors involved
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */

#ifndef __BULLET_H__
#define __BULLET_H__

//#include <libps.h>
#include "Framework/FW.H"

typedef struct
{
	GsBOXF box;
	short alive;
	vec2_t dir;
	vec2_t world;
}bullet_t;

void bullet_init(bullet_t* shot);
void bullet_update(bullet_t* shot);
void bullet_shoot(bullet_t*shot, vec2_t *pos);

#endif /*__BULLET_H__*/
