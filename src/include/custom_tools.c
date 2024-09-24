#include <genesis.h>


#include "variables.h"


void VDP_drawInt(u16 valeur,u8 zeros,s16 x, s16 y)
{
	intToStr(valeur,text_output,zeros); //MIN -500.000.000 - MAX 500.000.000
	VDP_drawTextBG(BG_B,text_output,x,y);
}




void VDP_drawIntEx_BG_A_CPU_PRIO(u16 valeur , u8 zeros , s16 x, s16 y , u8 pal)
{
	intToStr(valeur,text_output,zeros); //MIN -500.000.000 - MAX 500.000.000
	VDP_drawTextEx(BG_A,text_output,TILE_ATTR(pal, TRUE, FALSE, FALSE),x,y,CPU);
}


void VDP_drawIntEx_BG_A_CPU(u16 valeur , u8 zeros , s16 x, s16 y , u8 pal)
{
	intToStr(valeur,text_output,zeros); //MIN -500.000.000 - MAX 500.000.000
	VDP_drawTextEx(BG_A,text_output,TILE_ATTR(pal, FALSE, FALSE, FALSE),x,y,CPU);
}


void VDP_drawIntEx_BG_A_QUEUE(u16 valeur , u8 zeros , s16 x, s16 y , u8 pal)
{
	intToStr(valeur,text_output,zeros); //MIN -500.000.000 - MAX 500.000.000
	VDP_drawTextEx(BG_A,text_output,TILE_ATTR(pal, TRUE, FALSE, FALSE),x,y,DMA_QUEUE);
}


void VDP_drawIntEx_BG_A_DMA(u16 valeur , u8 zeros , s16 x, s16 y , u8 pal)
{
	intToStr(valeur,text_output,zeros); //MIN -500.000.000 - MAX 500.000.000
	VDP_drawTextEx(BG_A,text_output,TILE_ATTR(pal, FALSE, FALSE, FALSE),x,y,DMA);
}




void VDP_drawIntEx_BG_B_CPU_PRIO(u16 valeur , u8 zeros , s16 x, s16 y , u8 pal)
{
	intToStr(valeur,text_output,zeros); //MIN -500.000.000 - MAX 500.000.000
	VDP_drawTextEx(BG_B,text_output,TILE_ATTR(pal, TRUE, FALSE, FALSE),x,y,CPU);
}


void VDP_drawIntEx_BG_B_CPU(u16 valeur , u8 zeros , s16 x, s16 y , u8 pal)
{
	intToStr(valeur,text_output,zeros); //MIN -500.000.000 - MAX 500.000.000
	VDP_drawTextEx(BG_B,text_output,TILE_ATTR(pal, FALSE, FALSE, FALSE),x,y,CPU);
}










