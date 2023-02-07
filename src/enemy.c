/*  Created on: Jan 1, 2023
 *      Author: Noel Rojas Oliveras
 *
 *  Code has been source'd from the NY-Demos folder.
 *  Credits to the all the Authors involved
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */

#include "enemy.h"

void enemy_follow(obj_t* enemy, vec2_t* pos)
{
	if 		(pos->y > enemy->world.y){enemy->dir.y =  1; enemy->anim_row = 2;}
	else if (pos->y < enemy->world.y){enemy->dir.y = -1; enemy->anim_row = 1;}
	else    					{enemy->dir.y =  0;}

	if      (pos->x > enemy->world.x)
	{
		enemy->dir.x =  1; enemy->anim_row = 0;
		enemy->sprite.scalex = ONE;
	}
	else if (pos->x < enemy->world.x)
	{
		enemy->dir.x = -1; enemy->anim_row = 0;
		enemy->sprite.scalex = -ONE;
	}
	else {enemy->dir.x =  0;}

	/* didn't worked ;( | too slow and clunky
	u_long l;
	enemy->dirx = *x - enemy->sprite.x;
	enemy->diry = *y - enemy->sprite.y;

	l = enemy->dirx*enemy->dirx +
			  enemy->diry*enemy->diry;
	l = ISqrt(l);

	enemy->dirx/=l;
	enemy->diry/=l;*/
}

void enemy_update(obj_t* enemy)
{
	enemy->world.x += enemy->dir.x;
	enemy->world.y += enemy->dir.y;

	enemy->collider.x = enemy->sprite.x-8;
	enemy->collider.y = enemy->sprite.y-10;

	object_anim(enemy, 2, 10, 96, 1);

}

void enemy_reset(obj_t* enemy)
{
	short side;
	short x, y;
	side = rand()%4;

	switch(side)
	{
	case 0: //left side
		x = -10;
		y = rand()%360;
		break;
	case 1: //top side
		x = rand()%360;
		y = -10;
		break;
	case 2: //right side
		x = 360;
		y = rand()%360;
		break;
	case 3: //bottom side
		x = rand()%360;
		y = 360;
		break;
	}

	enemy->life = 3;
	enemy->world.x = x;
	enemy->world.y = y;
}

void enemy_colcheck(obj_t* enemy, int amount)
{
	/*this is stupid expensive and should be done another
	 * way but i'm too lazy to do it and the ps1 is a beast
	 *
	 * this is a very bad implementation of collission push back
	 * (which should not be done this way ever) but meh
	 */
	int i, j;
	short x, y;

	for(i = 0; i < amount; ++i)
	{
		for(j = 0; j < amount; ++j)
		{
			if (i == j)continue;
			if (aabb(&enemy[i].collider, &enemy[j].collider))
			{
				enemy[i].collider.r = 128;
				enemy[i].collider.g = 0;

				x = (enemy[j].collider.x - enemy[i].collider.x) > 0 ? 1:-1;
				y = (enemy[j].collider.y - enemy[i].collider.y) > 0 ? 1:-1;

				if 		(x > 1) x = 1;
				else if (x < -1) x = -1;
				if 		(y > 1) x = 1;
				else if (y < -1) x = -1;

				enemy[i].world.x -=x;
				enemy[i].world.y -=y;
				break;
			}else
			{
				enemy[i].collider.r = 0;
				enemy[i].collider.g = 128;
			}
		}
	}
}

