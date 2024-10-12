#include <genesis.h>




#include "structures.h"








//**************************************************************************************//
//                                                                                      //
//                                  GENERAL VARIABLES                                   //
//                                                                                      //
//**************************************************************************************//

char text_output[5];

u16 palette_64[64];


u8 G_SEQUENCE;

bool G_SEQUENCE_LOADED;

u16 G_POINTS;

u16 G_COUNTER;

bool G_PAUSE;

u16 G_HI_SCORE;


//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                        LOGO                                          //
//                                                                                      //
//--------------------------------------------------------------------------------------//

u16 G_COUNTER_LOGO;


//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                        TITLE                                         //
//                                                                                      //
//--------------------------------------------------------------------------------------//

u16 G_COUNTER_TITLE;

bool G_OPTIONS;

bool G_COLORS_OPTION;


//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                      INTERMEDE                                       //
//                                                                                      //
//--------------------------------------------------------------------------------------//

u16 G_ADR_VRAM_TEXT;

u16 G_COUNTER_INTERMEDE;

u8 G_INDEX_MADONNA;

u8 G_LINE_INDEX;

u8 G_LETTER_INDEX;

u8 G_TEXT_MAX_LINES;


//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                        LEVEL                                         //
//                                                                                      //
//--------------------------------------------------------------------------------------//

u8 G_LEVEL;

u16 G_LEVEL_LIMIT;

u16 G_ADR_VRAM_BG_B;

u16 G_ADR_VRAM_BG_A;

u16 G_ADR_VRAM_HUB;

u16 G_ADR_VRAM_LIFE_PLAYER;

u16 G_ADR_VRAM_LIFE_BOSS;

s16 G_POS_X_CAMERA;

u8 G_GROUND_POSITION;




u8 G_PHASE_LEVEL;

u8 G_NUMBER_ENEMY;

//bool G_SPECIAL_ENEMY_SPAWNED;

bool G_SPAWN_AUTHORIZED;




u8 G_INDEX_LIFE_PLAYER;

u8 G_STEP_LIFE_PLAYER;

u8 G_INDEX_LIFE_BOSS;




Map *map_BG_B;
Map *map_BG_A;




struct_PLAYER_ player;
bool player_AXIS;
bool G_REPEAT;
u8 G_INDEX_ANIM_PUNCH;




s16 scrollTable_BG_B[23];
s16 scrollTable_BG_A[23];



struct_ENEMY_ LIST_ENEMIES[4];

u16 G_SPAWN_COUNTER;
u8 G_SPAWN_INDEX;
u8 G_SPAWN_MAX_INDEX;









//**************************************************************************************//
//                                                                                      //
//                                       SPRITES                                        //
//                                                                                      //
//**************************************************************************************//

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                        TITLE                                         //
//                                                                                      //
//--------------------------------------------------------------------------------------//

Sprite *sprite_ARROW;


//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                      INTERMEDE                                       //
//                                                                                      //
//--------------------------------------------------------------------------------------//

Sprite *sprite_MADONNA;
Sprite *sprite_BOX;
Sprite *sprite_CHAIN;




//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                        LEVEL                                         //
//                                                                                      //
//--------------------------------------------------------------------------------------//

Sprite *sprite_PAUSE;

Sprite *sprite_PLAYER;

Sprite *sprite_STAGE;






