/*
 * main.c
 *
 *  Created on: Dec 27, 2022
 *      Author: Noel Rojas Oliveras
 */

#include <libps.h>
#include <stdio.h>
#include <stdlib.h>
#include "DATA.H"

#include "Framework/FW.H"

#include "particle.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"

#define ENE_AMOUNT 10
#define SHOT_AMOUNT 10

int g_fcounter;
int g_fontID;

GsBOXF box;
bullet_t shots;
obj_t player1;
sobj_t lvl;
sobj_t is; //intro screen;

obj_t enemy[ENE_AMOUNT];
particle_t particles[PRT_AMOUNT];

u_long i;

void hardware_init()
{
	render_init();
	pad_init();
	FntLoad(960, 256);
	g_fontID = FntOpen(10, 10, 256, 200, 0, 250);
}

void intro_screen()
{
	short istimer = 0;
	short stoptimer = 0;
	short move = 0;

	sobject_init(&is, (u_long*)NY_TITLE_DATA, 256, 256, SW>>1, SH>>1);
	is.sprite.scalex = ONE>>1;
	is.sprite.scaley = ONE>>1;
	is.sprite.r = 0;
	is.sprite.g = 0;
	is.sprite.b = 0;

	while(1)
	{
		if(is.sprite.r > 80 && move == 0)
		{
			is.sprite.scalex = is.sprite.scaley = ONE+256;
			is.sprite.rotate = 0;

			if (stoptimer < up_time)
			{
				move = 1;
				is.sprite.scalex =
						is.sprite.scaley = ONE-2048;
			}
		}else
		{
			is.sprite.rotate += ONE;
			is.sprite.scalex = is.sprite.scaley += move > 0 ? -1 : 1;

			if (is.sprite.scalex <= 0)
				is.sprite.scalex = is.sprite.scaley = 0;

			stoptimer = up_time + 200;

			if (istimer < up_time)
			{
				is.sprite.r =
				is.sprite.g =
				is.sprite.b += move > 0 ? -3 : 3;

				istimer = up_time;
			}
		}

		if (move && is.sprite.r <= 0) break;

		render_start();
		render_sprite(&is.sprite, 0);
		render_end();
	}
}

void game_init()
{
	bullet_init(&shots);
	sobject_init(&lvl, (u_long*)LEVEL1_DATA, 256, 256, (SW>>1)+20, (SH>>1)+50);
	object_init(&player1, (u_long*)PLAYER_DATA,
				32, 32, SH>>1, SW>>1, 0, 32, 24, 12);

	for(i = 0; i < ENE_AMOUNT; ++i)
	{
		object_init(&enemy[i], (u_long*)ZOMBIE_DATA,
					32, 32, 0, 0, 0, 32, 24, 12);
		enemy_reset(&enemy[i]); //put in one of the corners
	}

	for(i = 0; i < PRT_AMOUNT; ++i)
		particle_init(&particles[i], BLOOD_COL);
}

int main()
{
	u_long ud = 0;
	u_long counter = 0;
	short dead = 0;
	short q = 1;
	hardware_init();
	intro_screen();
	game_init();

	while(q)
	{
		if (pad_button(PADSELECT)) q = 0;
		//update every real second
		if (ud < up_time)
		{
			ud = up_time + 1;

			particle_update(particles);
			player_update(&player1);

			if (shots.alive)
				bullet_update(&shots);
			else
				bullet_shoot(&shots, &player1.world);

			for(i = 0; i < ENE_AMOUNT; ++i)
			{
				enemy_follow(&enemy[i], &player1.world);
				enemy_update(&enemy[i]);
				enemy_colcheck(enemy, ENE_AMOUNT);

				if (shots.alive)
				{
					if (aabb(&shots.box, &enemy[i].collider))
					{
						shots.alive = 0;
						enemy[i].life--;
						if (enemy[i].life <= 0){enemy_reset(&enemy[i]); counter++;}
						particle_start(particles, &enemy[i].world);
					}
				}

				if (aabb(&player1.collider, &enemy[i].collider))
				{
					dead = 1;
				}

			}

			camera_follow(&player1.sprite.x, &player1.sprite.y);
			camera_screen(&lvl.sprite.x, &lvl.sprite.y, &lvl.world.x, &lvl.world.y);

			for(i = 0; i < ENE_AMOUNT; ++i)
				camera_screen(&enemy[i].sprite.x, &enemy[i].sprite.y,
							  &enemy[i].world.x  , &enemy[i].world.y   );

			for(i = 0; i < PRT_AMOUNT; ++i)
							camera_screen(&particles[i].particle.x, &particles[i].particle.y,
										  &particles[i].world.x  , &particles[i].world.y   );

			camera_screen(&shots.box.x, &shots.box.y,
						  &shots.world.x  , &shots.world.y);
		}

		while(dead)
		{
			if (pad_button(PADSTART))
			{
				dead = 0;
				player1.world.x = SW>>1;
				player1.world.y = SH>>1;
				counter = 0;
				for(i = 0; i < ENE_AMOUNT; ++i)
					enemy_reset(&enemy[i]);
			}
			FntPrint(g_fontID, "\n\n GAME OVER \n Press START to play again");
			FntFlush(g_fontID);

			GsSwapDispBuff();
		}

		render_start();

		FntPrint(g_fontID, "KILLS = %d", counter);
		FntFlush(g_fontID);

		for(i =0; i < PRT_AMOUNT; ++i)
			render_particle(&particles[i].particle);

		for(i = 0; i < ENE_AMOUNT; ++i)
		{
			render_sprite(&enemy[i].sprite, 0);
			//render_particle(&enemy[i].collider);
		}

		if (shots.alive)
			render_particle(&shots.box);

		render_sprite(&player1.sprite, 0);
		//render_particle(&player1.collider);
		render_sprite(&lvl.sprite, 1);

		render_end();
	}
	return 0;
}
