#ifndef _VARIABLES_H
#define _VARIABLES_H



#include "structures.h"




//*****************************************************************************//
//                                                                             //
//                                 GAME CONSTANTS                              //
//                                                                             //
//*****************************************************************************// 

//-----------------------------------------------------------------------------//
//                                                                             //
//                                   GENERAL                                   //
//                                                                             //
//-----------------------------------------------------------------------------// 

#define FAILED                  0
#define SUCCESS                 1

#define VRAM_START_ADRESS       1 // 1 OR 16

#define AXIS_RIGHT              0
#define AXIS_LEFT               1




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

#define PLAYER_PUNCH_MARGIN     2
#define PLAYER_KICK_MARGIN      4




#define STATE_IDLE              0
#define STATE_WALK              1
#define STATE_CROUCH            2

#define STATE_PUNCH             3
#define STATE_KICK              4

#define STATE_PUNCH_CROUCH      5
#define STATE_KICK_CROUCH       6

#define STATE_JUMP_V            7
#define STATE_JUMP_H            8
#define STATE_JUMP_KICK         9
#define STATE_JUMP_KICK_BW      10

#define STATE_HIT_UP            11
#define STATE_HIT_DOWN          12

#define STATE_GRAB              14
#define STATE_DEAD              15




#define NO_JUMP_KICK            0
#define JUMP_KICK               1
#define JUMP_KICK_HIT           2

#define NO_JUMP_PUNCH           0
#define JUMP_PUNCH              1
#define JUMP_PUNCH_HIT          2


#define JUMP_HIGH_POINT         15

#define JUMP_KICK_COLL_START    11
#define JUMP_KICK_COLL_END      21

#define JUMP_PUNCH_COLL_START   11
#define JUMP_PUNCH_COLL_END     19




//-----------------------------------------------------------------------------//
//                                                                             //
//                                     TITLE                                   //
//                                                                             //
//-----------------------------------------------------------------------------// 

#define LEVEL_OPTION            0
#define COLORS_OPTION           1

#define MD_COLORS               0
#define PCE_COLORS              1


//-----------------------------------------------------------------------------//
//                                                                             //
//                                     LEVEL                                   //
//                                                                             //
//-----------------------------------------------------------------------------// 

#define LEVEL_ENTER             0
#define LEVEL_PLAY              1
#define LEVEL_END               2




//-----------------------------------------------------------------------------//
//                                                                             //
//                                    ENEMIES                                  //
//                                                                             //
//-----------------------------------------------------------------------------// 

#define DUDE                    0
#define PUNK                    1
#define KNIFE_MAN               2
#define CHAIN_MAN               3
#define GUN_MAN                 4
#define STICK_MAN               5


#define LEFT_SPAWN_POSITION     -56
#define RIGHT_SPAWN_POSITION    216


#define ENEMY_RIGHT_BOUND       20//27 (-7)
#define ENEMY_LEFT_BOUND        4//6 (-2)




//-----------------------------------------------------------------------------//
//                                                                             //
//                                ENEMIES STATE                                //
//                                                                             //
//-----------------------------------------------------------------------------//

#define ENEMY_WALK              1
#define ENEMY_GRAB              2
#define ENEMY_GRAB_2            3
#define ENEMY_THREAT_FW         4
#define ENEMY_THREAT_BW         5
#define ENEMY_ATTACK_UP         6
#define ENEMY_ATTACK_DOWN       7
#define ENEMY_HIT_UP_SLIDE      8
#define ENEMY_HIT_DOWN_SLIDE    9
#define ENEMY_HIT_UP            10
#define ENEMY_HIT_DOWN          11
#define ENEMY_DEAD              12
#define ENEMY_IDLE              13
#define ENEMY_ESCAPE            14








//-----------------------------------------------------------------------------//
//                                                                             //
//                                 SOUND EFFECTS                               //
//                                                                             //
//-----------------------------------------------------------------------------//

#define SOUND_HIT_KICK              69
#define SOUND_HIT_PUNCH             70
#define SOUND_NUNCHUCK              71








//**************************************************************************************//
//                                                                                      //
//                                  GENERAL VARIABLES                                   //
//                                                                                      //
//**************************************************************************************//

extern char text_output[5];

extern u16 palette_64[64];


extern u8 G_SEQUENCE;

extern bool G_SEQUENCE_LOADED;

extern u16 G_POINTS;

extern u16 G_COUNTER;

extern bool G_PAUSE;

extern u16 G_HI_SCORE;

//extern s32 player.life;

extern u8 G_NUMBER_LIFE;

extern u8 G_TIME;

extern u8 G_CHRONOMETER;

extern u16 G_ADR_VRAM_LIFE_ICON;


//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                        LOGO                                          //
//                                                                                      //
//--------------------------------------------------------------------------------------//

extern u16 G_COUNTER_LOGO;


//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                        TITLE                                         //
//                                                                                      //
//--------------------------------------------------------------------------------------//

extern u16 G_COUNTER_TITLE;

extern bool G_OPTIONS;

extern bool G_COLORS_OPTION;


//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                      INTERMEDE                                       //
//                                                                                      //
//--------------------------------------------------------------------------------------//

extern u16 G_ADR_VRAM_TEXT;

extern u16 G_COUNTER_INTERMEDE;

extern u8 G_INDEX_MADONNA;

extern u8 G_LINE_INDEX;

extern u8 G_LETTER_INDEX;

extern u8 G_TEXT_MAX_LINES;


//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                        LEVEL                                         //
//                                                                                      //
//--------------------------------------------------------------------------------------//

extern u8 G_LEVEL;

extern u16 G_CAMERA_LIMIT;
extern u8 G_LEVEL_LIMIT;

extern u16 G_ADR_VRAM_BG_B;
extern u16 G_ADR_VRAM_BG_A;
extern u16 G_ADR_VRAM_HUB;

extern u16 G_ADR_VRAM_LIFE_PLAYER;
extern u16 G_ADR_VRAM_LIFE_BOSS;

extern s16 G_POS_X_CAMERA;

extern u8 G_GROUND_POSITION;

extern u8 G_INDEX_JUMP_V;
extern u8 G_INDEX_JUMP_H;




extern u8 G_PHASE_LEVEL;

extern u8 G_NUMBER_ENEMY;
extern u8 G_NUMBER_ENEMY_MAX;

//extern bool G_COLLISION;

extern bool G_SPAWN_AUTHORIZED;




extern u8 G_JUMP_KICK;
extern u8 G_JUMP_PUNCH;

extern bool G_JUMP_PUNCH;

extern fix32 G_GRAVITY;

extern u8 G_NUMBER_GRAB_LEFT;
extern u8 G_NUMBER_GRAB_RIGHT;

extern u8 G_NUMBER_GRAB_2_LEFT;
extern u8 G_NUMBER_GRAB_2_RIGHT;

extern bool G_WEAPON_GRABBED;




extern u8 G_INDEX_LIFE_PLAYER;

extern u8 G_STEP_LIFE_PLAYER;

extern u8 G_INDEX_LIFE_BOSS;




extern Map *map_BG_B;
extern Map *map_BG_A;




extern struct_PLAYER_ player;
extern bool player_AXIS;
extern bool G_REPEAT;
extern u8 G_INDEX_ANIM_PUNCH;



extern s16 scrollTable_BG_B[23];
extern s16 scrollTable_BG_A[23];



extern struct_ENEMY_ LIST_ENEMIES[4];

extern u16 G_SPAWN_COUNTER;
extern u8 G_SPAWN_INDEX;
extern u8 G_SPAWN_MAX_INDEX;


//extern bool G_TOTO;





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

extern Sprite *sprite_ARROW;


//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                      INTERMEDE                                       //
//                                                                                      //
//--------------------------------------------------------------------------------------//

extern Sprite *sprite_MADONNA;
extern Sprite *sprite_BOX;
extern Sprite *sprite_CHAIN;


//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                        LEVEL                                         //
//                                                                                      //
//--------------------------------------------------------------------------------------//

extern Sprite *sprite_PAUSE;

extern Sprite *sprite_STAGE;

extern Sprite *sprite_WEAPON;

extern Sprite *sprite_NUNCHUK;













#endif // _VARIABLES_H