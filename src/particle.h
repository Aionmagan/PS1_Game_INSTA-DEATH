/*  Created on: Jan 1, 2023
 *      Author: Noel Rojas Oliveras
 *
 *  Code has been source'd from the NY-Demos folder.
 *  Credits to the all the Authors involved
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */


#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Framework/FW.H"

#define GROUP_PRT 3
#define PRT_AMOUNT 15

#define EMY_PRT 0
#define PYR_PRT 1
#define HLT_PRT 2

#define BLOOD_COL 0
#define HEAL_COL 1

typedef struct
{
	GsBOXF particle;
	u_int life;
	u_int vely;
	u_int velx;
	vec2_t dir;
	vec2_t world;
}particle_t;

void particle_init(particle_t* p, int colorflag);
void particle_start(particle_t* p, vec2_t* pos);
void particle_update(particle_t* p);

#endif /*__PARTICLE_H__*/
