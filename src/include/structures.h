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
    s16 pos_X;
    s16 pos_Y;

    u8 state;

    u8 counter_ANIM;
    bool axis;

    Sprite *spr_ENEMY;

    u8 pal;

} struct_ENEMY_;






#endif // _MAIN