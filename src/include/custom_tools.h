#ifndef _CUSTOM_TOOLS_H
#define _CUSTOM_TOOLS_H


extern void VDP_drawInt(u16 valeur,u8 zeros,s16 x, s16 y);

extern void VDP_drawIntEx_BG_A_CPU_PRIO(u16 valeur,u8 zeros,s16 x, s16 y, u8 pal);

extern void VDP_drawIntEx_BG_A_CPU(u16 valeur,u8 zeros,s16 x, s16 y, u8 pal);

extern void VDP_drawIntEx_BG_A_QUEUE(u16 valeur,u8 zeros,s16 x, s16 y, u8 pal);

extern void VDP_drawIntEx_BG_A_DMA(u16 valeur,u8 zeros,s16 x, s16 y, u8 pal);

extern void VDP_drawIntEx_BG_B_CPU_PRIO(u16 valeur , u8 zeros , s16 x, s16 y , u8 pal);

extern void VDP_drawIntEx_BG_B_CPU(u16 valeur , u8 zeros , s16 x, s16 y , u8 pal);








#endif // _MAIN