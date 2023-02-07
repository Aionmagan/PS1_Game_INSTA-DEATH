/*
 * RENDER.C
 *
 *  Created on: Jan 13, 2023
 *      Author: Noel Rojas Oliveras
 */


#include "RENDER.H"

#define OT_LEN 9

GsOT g_OT[2];
GsOT_TAG g_tag[2][1<<OT_LEN];

PACKET g_packet[2][24*100];
short context;

/*------------------------
 *  rendering fucntions
 *------------------------
 */
void render_init()
{
	SetVideoMode(MODE_NTSC);
	GsInitGraph(SW, SH, 4, 0, 0);
	GsDefDispBuff(0, 0, 0, SH);

	GsDISPENV.screen.w = SW;
	GsDISPENV.screen.h = SH;

	g_OT[0].length = OT_LEN;
	g_OT[0].org = g_tag[0];
	g_OT[1].length = OT_LEN;
	g_OT[1].org = g_tag[1];

	GsClearOt(0, 0, &g_OT[0]);
	GsClearOt(0, 0, &g_OT[1]);

	ResetGraph(0);
	context = GsGetActiveBuff();
}

void render_start()
{
	GsSetWorkBase((PACKET*)g_packet[context]);
	GsClearOt(0, 0, &g_OT[context]);
}

void render_end()
{
	DrawSync(0);
	up_time = VSync(-1)+10;
	GsSwapDispBuff();
	GsSortClear(0, 0, 0, &g_OT[context]);
	GsDrawOt(&g_OT[context]);
	context ^= 1;
}

/*-------------------------------------
 *  specific rendering fucntions calls
 *-------------------------------------
 */
void render_particle(GsBOXF* box)
{
	GsSortBoxFill(box, &g_OT[context], 0);
}

void render_sprite(GsSPRITE* sprite, short layer)
{
	GsSortSprite(sprite, &g_OT[context], layer);
}
