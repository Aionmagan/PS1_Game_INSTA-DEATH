/*  Created on: Jan 1, 2023
 *      Author: Noel Rojas Oliveras
 *
 *  Code has been source'd from the NY-Demos folder.
 *  Credits to the all the Authors involved
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */

#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <libps.h>
#include "Framework/FW.H"

void enemy_follow(obj_t* enemy, vec2_t* pos);
void enemy_update(obj_t* enemy);
void enemy_reset(obj_t* enemy);
void enemy_colcheck(obj_t* enemy, int amount);

#endif /*__ENEMY_H__*/
