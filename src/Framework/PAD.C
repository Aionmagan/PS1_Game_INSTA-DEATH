/*  Created on: Jan 1, 2023
 *      Author: Noel Rojas Oliveras
 *
 *  Code has been source'd from the NY-Demos folder.
 *  Credits to the all the uthors involved
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */

#include "PAD.H"
#include <libps.h>

volatile u_char* buff[2];
short p;

void pad_init()
{
	GetPadBuf(&buff[0], &buff[1]);
}

int pad_button(int flag)
{
	return (flag & (~(*(buff[0]+3) | *(buff[0]+2) << 8)));
}


