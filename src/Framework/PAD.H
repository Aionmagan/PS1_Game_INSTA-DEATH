/*  Created on: Jan 1, 2023
 *      Author: Noel Rojas Oliveras
 *
 *  Code has been source'd from the NY-Demos folder.
 *  Credits to the all the Authors involved
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */

#ifndef __FRAMEWORK_PAD_H__
#define __FRAMEWORK_PAD_H__

#define PADUP     	 (1<<12)
#define PADDOWN   	 (1<<14)
#define PADLEFT   	 (1<<15)
#define PADRIGHT  	 (1<<13)
#define PADTRIANGLE  (1<<4)
#define PADCROSS     (1<<6)
#define PADSQUARE    (1<<7)
#define PADCIRCLE    (1<<5)
#define PADSTART  	 (1<<11)
#define PADSELECT    (1<<8)

void pad_init();
int pad_button(int flag);

#endif /* FRAMEWORK_PAD_H_ */
