#ifndef _VARIABLES_H
#define _VARIABLES_H



#include "structures.h"




//-----------------------------------------------------------------------------//
//                                                                             //
//                                 GAME CONSTANTS                              //
//                                                                             //
//-----------------------------------------------------------------------------// 

#define FAILED                  0
#define SUCCESS                 1




//-----------------------------------------------------------------------------//
//                                                                             //
//                                   GAME SCENE                                //
//                                                                             //
//-----------------------------------------------------------------------------// 

#define SEQUENCE_LOGO           0
#define SEQUENCE_TITLE          1
#define SEQUENCE_INTERMEDE      2
#define SEQUENCE_GAME           3




//-----------------------------------------------------------------------------//
//                                                                             //
//                                     PLAYER                                  //
//                                                                             //
//-----------------------------------------------------------------------------// 

#define STATE_IDLE              0
#define STATE_WALK              1
#define STATE_CROUCH            2
#define STATE_PUNCH             3
#define STATE_KICK              4
#define STATE_PUNCH_CROUCH      5
#define STATE_KICK_CROUCH       6


#define AXIS_RIGHT              0
#define AXIS_LEFT               1








//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                  GENERAL VARIABLES                                   //
//                                                                                      //
//--------------------------------------------------------------------------------------//

extern char text_output[5];
extern u16 palette_64[64];


extern u8 G_COUNTER_LOGO;
extern u8 G_COUNTER_TITLE;




extern u8 G_SEQUENCE;
extern u8 G_LEVEL;
extern bool G_SEQUENCE_LOADED;
extern u16 G_LEVEL_LIMIT;


extern u16 G_ADR_VRAM_BG_B;
extern u16 G_ADR_VRAM_BG_A;
extern u16 G_ADR_VRAM_HUB;


extern s16 G_POS_X_CAMERA;




extern Map *map_BG_B;
extern Map *map_BG_A;




extern struct_PLAYER_ player;
extern bool player_AXIS;
extern bool G_REPEAT;
extern u8 G_INDEX_ANIM_PUNCH;



extern s16 scrollTable_BG_B[23];
extern s16 scrollTable_BG_A[23];








//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                       SPRITES                                        //
//                                                                                      //
//--------------------------------------------------------------------------------------//

extern Sprite *sprite_PLAYER;













#endif // _VARIABLES_H