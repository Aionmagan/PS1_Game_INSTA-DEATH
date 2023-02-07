/*  Created on: Jan 2, 2023
 *      Author: Noel Rojas Oliveras
 *
 *  Code has been source'd from the NY-Demos folder.
 *  Credits to the all the Authors involved
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */

/*should have just implemented this in full asm
 * but man was i lazy for this project, so inline it is XD
 */

#include "CAMERA.H"

short posx = 0;
short posy = 0;

void camera_follow(short* x, short* y)
{
/*	the inline asm essentially does this
 * i was just bored and wanted to do some asm
 * then the performances boost was actually needed
 * 	posx = *x - 160;
 *	posy = *y - 120;
 *
 *	if (posx <=  -11){posx =  -11;}
 *	if (posx >=   50){posx =   50;}
 *	if (posy <=  -20){posy =  -20;}
 *	if (posy >=  120){posy =  120;}
 *
 *	*x = *x - posx;
 *	*y = *y - posy;
*/
	asm volatile
	(
		"addi $0, $0, 0    \n\t" //$zero
		"addi $4, %4, -160 \n\t"
		"addi $5, %5, -120 \n\t"
		"slti $2, $4, -11  \n\t"
		"beq  $2, $0, .L1  \n\t"
		"addi $4, $0, -11  \n\t"
		".L1:              \n\t"
		"slti $2, $4, 50   \n\t"
		"bne  $2, $0, .L2  \n\t"
		"addi $4, $0, 50   \n\t"
		".L2:              \n\t"
		"slti $2, $5, -20  \n\t"
		"beq  $2, $0, .L3  \n\t"
		"addi $5, $0, -20  \n\t"
		".L3:              \n\t"
		"slti $2, $5, 120  \n\t"
		"bne  $2, $0, .L4  \n\t"
		"addi $5, $0, 120  \n\t"
		".L4:              \n\t"
		"move %2, $4	   \n\t"
		"move %3, $5	   \n\t"
		"sub %0, %4, $4    \n\t"
		"sub %1, %5, $5    \n\t"
		: "=r" (*x), "=r" (*y), "=r" (posx), "=r"(posy)
		: "r" (*x), "r" (*y)
		: "$0", "$1", "$2", "$4", "$5"
	);
}

void camera_screen(short* screenx, short* screeny, short* worldx, short* worldy)
{
	/*screenx = *worldx - posx;
	 *screeny = *worldy - posy;
	 */

	asm volatile
	(
			"sub %0, %2, %3 \n\t"
			"sub %1, %4, %5 \n\t"
			:"=r" (*screenx), "=r" (*screeny)
			:"r" (*worldx), "r"(posx), "r"(*worldy), "r"(posy)
	);
}

short cam_x()
{
	return posx;
}

short cam_y()
{
	return posy;
}
