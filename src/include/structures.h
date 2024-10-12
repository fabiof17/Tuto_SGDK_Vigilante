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

    u8 state;

    u8 counter_ANIM;
    bool axis;

} struct_PLAYER_;




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
    
    Sprite *spr_ENEMY;

} struct_ENEMY_;




typedef struct
{
    u8 life;
    
    u8 width;

    u8 pal;

    u8 points;

    const SpriteDefinition *tiles_SPRITE;

} struct_ENEMY_TYPE;




typedef struct
{
    u8 enemy_ID;
    u16 spawn_TIME;
    bool special;

} struct_SPAWN_DATA_;








#endif // _MAIN