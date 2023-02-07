/*
 * RENDER.H
 *
 *  Created on: Jan 13, 2023
 *      Author: NetYaroze
 */

#ifndef __FRAMEWORK_RENDER_H_
#define __FRAMEWORK_RENDER_H_

#include <libps.h>

#define SW 320
#define SH 240

u_long up_time;

void render_init();
void render_start();
void render_end();

void render_particle(GsBOXF* box);
void render_sprite(GsSPRITE* sprite, short layer);

#endif /* FRAMEWORK_RENDER_H_ */
