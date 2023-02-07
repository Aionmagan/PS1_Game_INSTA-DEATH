/*
 * OBJECT.C
 *
 *  Created on: Jan 13, 2023
 *      Author: NetYaroze
 */

#include "OBJECT.H"
#include "RENDER.H" //SW / SH

void object_init(obj_t* obj, u_long* imgaddr, u_short h, u_short w,
				 short x, short y, short u, short v, u_short ch, u_short cw)
{
	GsIMAGE img;
	RECT rect = {0};
	u_long* tim = imgaddr; tim++;

	GsGetTimInfo(tim, &img);
	setRECT(&rect, img.px, img.py, img.pw, img.ph);
	LoadImage(&rect, img.pixel);

	setRECT(&rect, img.cx, img.cy, img.cw, img.ch);
	LoadImage(&rect, img.clut);

	obj->sprite.attribute |= (1<<30);
	obj->sprite.attribute |= (1<<29);
	obj->sprite.attribute |= (1<<24);
	obj->sprite.w = w;//img.pw*4;
	obj->sprite.h = h;//img.ph;
	obj->sprite.tpage = GetTPage(1, 0, img.px, img.py);

	obj->sprite.x = x;
	obj->sprite.y = y;
	obj->sprite.u = u;
	obj->sprite.v = v;

	obj->sprite.r =
			obj->sprite.b =
			obj->sprite.g = 80;

	obj->sprite.cx = img.cx; obj->sprite.cy = img.cy;
	obj->sprite.mx = obj->sprite.w>>1;
	obj->sprite.my = obj->sprite.h>>1;

	obj->sprite.scalex = obj->sprite.scaley = ONE;
	obj->sprite.rotate = 0;

	obj->world.x = x;
	obj->world.y = y;

	obj->collider.attribute = 0;
	obj->collider.h = ch;
	obj->collider.w = cw;
	obj->collider.g = 128;
	obj->collider.r = obj->collider.b = 0;
}

void sobject_init(sobj_t* obj, u_long* imgaddr, u_short h,
				  u_short w, short x, short y)
{
	GsIMAGE img;
	RECT rect = {0};
	u_long* tim = imgaddr; tim++;

	GsGetTimInfo(tim, &img);
	setRECT(&rect, img.px, img.py, img.pw, img.ph);
	LoadImage(&rect, img.pixel);

	setRECT(&rect, img.cx, img.cy, img.cw, img.ch);
	LoadImage(&rect, img.clut);

	obj->sprite.attribute = 0;
	obj->sprite.attribute |= (1<<24);
	obj->sprite.w = w;//img.pw*4;
	obj->sprite.h = h;//img.ph;
	obj->sprite.tpage = GetTPage(0, 0, img.px, img.py);

	obj->sprite.x = x;
	obj->sprite.y = y;
	obj->sprite.u = 0;
	obj->sprite.v = 0;

	obj->sprite.r =
			obj->sprite.b =
			obj->sprite.g = 80;

	obj->sprite.cx = img.cx; obj->sprite.cy = img.cy;
	obj->sprite.mx = obj->sprite.w>>1;
	obj->sprite.my = obj->sprite.h>>1;

	obj->sprite.scalex = ONE+2048;
	obj->sprite.scaley = ONE+2048;
	obj->sprite.rotate = 0;

	obj->world.x = x;
	obj->world.y = x;
}

void object_anim(obj_t* obj, u_short frame_limit,
				u_short slowness, u_short vertical_offset, short can_animate)
{
	if (can_animate)
	{
		if (obj->anim_counter < up_time)
		{
			obj->anim_frame++;
			if(obj->anim_frame > frame_limit) obj->anim_frame = 0;
			obj->sprite.u = obj->anim_frame * obj->sprite.w;
			obj->anim_counter = up_time + slowness;
		}
	}
	obj->sprite.v = (obj->anim_row*obj->sprite.w)+vertical_offset;
}
