/*
 * OBJECT.H
 *
 *  Created on: Jan 13, 2023
 *      Author: Noel Rojas Oliveras
 */

#ifndef __FRAMEWORK_OBJECT_H__
#define __FRAMEWORK_OBJECT_H__

#include <libps.h>

typedef struct
{
	short x;
	short y;
}vec2_t;

typedef struct
{
	GsSPRITE sprite;
	GsBOXF collider; //used for collition (and debug render)
	u_short anim_counter;
	u_short anim_row;
	u_short anim_frame;
	short life;
	vec2_t dir;
	vec2_t world; //world position
}obj_t;

typedef struct
{
	GsSPRITE sprite;
	vec2_t world;
}sobj_t;//static object, used for levels

void object_init(obj_t* obj, u_long* imgaddr, u_short h, u_short w,
				 short x, short y, short u, short v, u_short ch, u_short cw);

void sobject_init(sobj_t* obj, u_long* imgaddr, u_short h,
		          u_short w, short x, short y);

//animations are read by colum, each row is a new animation sequence
void object_anim(obj_t* obj, u_short frame_limit,
				u_short slowness, u_short vertical_offset, short can_animate);

#endif /* FRAMEWORK_OBJECT_H_ */
