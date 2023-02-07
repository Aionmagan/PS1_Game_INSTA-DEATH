/*  Created on: Jan 2, 2023
 *      Author: Noel Rojas Oliveras
 *
 *  Code has been source'd from the NY-Demos folder.
 *  Credits to the all the Authors involved
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */

#ifndef __FRAMEWORK_CAMERA_H__
#define __FRAMEWORK_CAMERA_H__

void camera_screen(short* screenx, short* screeny, short* worldx, short* worldy);
void camera_follow(short* x, short* y);
short cam_x();
short cam_y();

#endif /* FRAMEWORK_CAMERA_H_ */
