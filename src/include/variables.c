#include <genesis.h>




#include "structures.h"








//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                  GENERAL VARIABLES                                   //
//                                                                                      //
//--------------------------------------------------------------------------------------//

char text_output[5];
u16 palette_64[64];


u16 G_COUNTER_LOGO;
u16 G_COUNTER_TITLE;
u16 G_COUNTER_INTERMEDE;




u8 G_SEQUENCE;
u8 G_LEVEL;
bool G_SEQUENCE_LOADED;
u16 G_LEVEL_LIMIT;


u8 G_INDEX_MADONNA;
u8 G_LINE_INDEX;
u8 G_LETTER_INDEX;

u8 G_TEXT_MAX_LINES;


u16 G_ADR_VRAM_BG_B;
u16 G_ADR_VRAM_BG_A;
u16 G_ADR_VRAM_HUB;
u16 G_ADR_VRAM_TEXT;


s16 G_POS_X_CAMERA;




Map *map_BG_B;
Map *map_BG_A;




struct_PLAYER_ player;
bool player_AXIS;
bool G_REPEAT;
u8 G_INDEX_ANIM_PUNCH;




s16 scrollTable_BG_B[23];
s16 scrollTable_BG_A[23];



struct_ENEMY_ LIST_ENEMIES[4];









//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                       SPRITES                                        //
//                                                                                      //
//--------------------------------------------------------------------------------------//

Sprite *sprite_MADONNA;
Sprite *sprite_BOX;
Sprite *sprite_CHAIN;


Sprite *sprite_PLAYER;








