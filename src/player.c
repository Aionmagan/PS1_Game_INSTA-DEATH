/*  Created on: Jan 2, 2023
 *      Author: Noel Rojas Oliveras
 *
 *  Code has been source'd from the NY-Demos folder.
 *  Credits to the all the Authors involved
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */

#include "player.h"

short can_anim = 0;

void player_update(obj_t* player)
{
	if      (pad_button(PADUP)   ){can_anim = 1; player->world.y-=3;}
	else if (pad_button(PADDOWN) ){can_anim = 1; player->world.y+=3;}
	else if (pad_button(PADLEFT) ){can_anim = 1; player->world.x-=3;}
	else if (pad_button(PADRIGHT)){can_anim = 1; player->world.x+=3;}
	else                          {can_anim = 0;}

	if      (pad_button(PADTRIANGLE)){player->anim_row = 1;}
	else if (pad_button(PADCROSS)   ){player->anim_row = 2;}
	else if (pad_button(PADSQUARE))
	{
		player->anim_row = 0;
		player->sprite.scalex = -ONE;

	}else if (pad_button(PADCIRCLE))
	{
		player->anim_row = 0;
		player->sprite.scalex = ONE;
	}

	object_anim(player, 2, 10, 0, can_anim);

	if (player->world.x <   0){player->world.x =   1;}
	if (player->world.x > 354){player->world.x = 355;}
	if (player->world.y <   0){player->world.y =   1;}
	if (player->world.y > 339){player->world.y = 340;}

	player->collider.x = player->sprite.x-8;
	player->collider.y = player->sprite.y-10;

	player->sprite.x = player->world.x;
	player->sprite.y = player->world.y;
}


