#ifndef _STRUCTURES_H
#define _STRUCTURES_H






typedef struct
{
    u8 number_LETTERS;
    
    u8 horizontal_POSITION;
    u8 vertical_POSITION;

} struct_LINE_;




typedef struct
{
    s16 pos_X;
    s16 pos_Y;

    bool axis;
    u8 state;

    fix32 life;


    u8 counter_ANIM_SPRITE;
    

    u8 counter_ANIM_H;
    u8 counter_ANIM_V;

    s16 pos_X_RESPAWN;

    u8 counter_UNGRAB;

    bool armed;

    bool vulnerable;

    bool invincible;

    Sprite *spr_PLAYER;

} struct_PLAYER_;




typedef struct
{
    u8 frame;
    s16 pos_VALUE;

} struct_JUMP_;




typedef struct
{
    u8 enemy_ID;
    
    s16 pos_X;
    s16 pos_Y;

    u8 width;

    u8 state;

    bool axis;

    u8 life;

    u8 points;
    
    u8 counter_ANIM;

    u8 index_ANIM;

    u8 index_FRAME;
    
    Sprite *spr_ENEMY;

    bool vulnerable;

} struct_ENEMY_;




typedef struct
{
    u8 life;
    
    u8 width;

    u8 pal;

    u8 points;

    const SpriteDefinition *tiles_SPRITE;

    fix32 damages;

    bool vulnerable;  

} struct_ENEMY_TYPE;




typedef struct
{
    u8 enemy_ID;
    u16 spawn_TIME;
    bool special;

} struct_SPAWN_DATA_;




typedef struct
{
    u16 score;

    u8 letter_1;
    u8 letter_2;
    u8 letter_3;

} struct_RANK_;








#endif // _MAIN