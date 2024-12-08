#include <genesis.h>



#include "custom_tools.h"
#include "palettes.h"
#include "structures.h"
#include "variables.h"




#include "maps_GLOBAL.h"
#include "maps_LEVELS.h"




#include "musics.h"



#include "sprites_LEVEL.h"
#include "TABLES_LEVELS.h"








inline static void update_HISCORE()
{
    if(G_POINTS < 10000)
    {
        VDP_drawIntEx_WINDOW_QUEUE_PRIO(G_POINTS,4,15,2,PAL3);
    }

    else
    {
        VDP_drawIntEx_WINDOW_QUEUE_PRIO(G_POINTS,5,14,2,PAL3);
    }   
}


inline static void update_SCORE()
{
    if(G_POINTS < 100)
    {
        VDP_drawIntEx_WINDOW_QUEUE_PRIO(G_POINTS,2,6,2,PAL3);
    }

    else if(G_POINTS < 1000)
    {
        VDP_drawIntEx_WINDOW_QUEUE_PRIO(G_POINTS,3,5,2,PAL3);
    }

    else if(G_POINTS < 10000)
    {
        VDP_drawIntEx_WINDOW_QUEUE_PRIO(G_POINTS,4,4,2,PAL3);
    }


    if(G_POINTS > G_HI_SCORE)
    {
        G_HI_SCORE = G_POINTS;

        update_HISCORE();
    }
}


inline static void update_LIFE_PLAYER()
{
    u8 i;


    u8 life  = fix32ToInt(player.life);
    
    if(life > 0)
    {
        u8 number_tiles = life >> 3;

        u8 remainder    = life - (number_tiles << 3);

        //VDP_drawIntEx_WINDOW_QUEUE_PRIO(number_tiles,2,0,0,PAL3);
        //VDP_drawIntEx_WINDOW_QUEUE_PRIO(remainder,2,0,1,PAL3);

        // FILL TILES WITH FULL ENERGY TILE //
        for(i=0 ; i<number_tiles - 1 ; i++)
        {
            VDP_setTileMapEx(WINDOW, image_LIFE_PLAYER.tilemap, TILE_ATTR_FULL(PAL3, TRUE, FALSE, FALSE, G_ADR_VRAM_LIFE_PLAYER), 7 + i, 3, 8, 0, 1, 1, DMA_QUEUE);
        }

        // FILL TILE WITH REMAINING ENERGY TILE //
        VDP_setTileMapEx(WINDOW, image_LIFE_PLAYER.tilemap, TILE_ATTR_FULL(PAL3, TRUE, FALSE, FALSE, G_ADR_VRAM_LIFE_PLAYER), 7 + number_tiles, 3, remainder, 0, 1, 1, DMA_QUEUE);

        // FILL THE REST OF THE BAR WITH EMPTY TILE //
        for(i=number_tiles + 1 ; i<14 ; i++)
        {
            VDP_setTileMapEx(WINDOW, image_LIFE_PLAYER.tilemap, TILE_ATTR_FULL(PAL3, TRUE, FALSE, FALSE, G_ADR_VRAM_LIFE_PLAYER), 7 + i, 3, 0, 0, 1, 1, DMA_QUEUE);
        }
    }


    // FILL ENTIRE LIFE BAR WITH EMPTY TILES //
    else
    {
        for(i=0 ; i<14 ; i++)
        {
            VDP_setTileMapEx(WINDOW, image_LIFE_PLAYER.tilemap, TILE_ATTR_FULL(PAL3, TRUE, FALSE, FALSE, G_ADR_VRAM_LIFE_PLAYER), 7 + i, 3, 0, 0, 1, 1, DMA_QUEUE);
        }
    }
}


inline static void update_WEAPON(int offset)
{
    if(G_WEAPON_GRABBED == FALSE)
    {
        s16 pos_x_weapon = SPR_getPositionX(sprite_WEAPON);
        s16 pos_y_weapon = SPR_getPositionY(sprite_WEAPON);

        pos_x_weapon += offset;

        if(G_POS_X_CAMERA >= TABLE_SPAWN_WEAPON_LEVEL_1[G_LEVEL -1][0] && G_POS_X_CAMERA <= (TABLE_SPAWN_WEAPON_LEVEL_1[G_LEVEL -1][0] + 288))
        {
            pos_y_weapon = TABLE_SPAWN_WEAPON_LEVEL_1[G_LEVEL -1][1];
        }

        else
        {
            pos_y_weapon = -32;
        }

        SPR_setPosition(sprite_WEAPON,pos_x_weapon,pos_y_weapon);
    }
}


inline static void update_TIME()
{
    G_CHRONOMETER += 1;

    if(G_CHRONOMETER == 120)
    {
        G_CHRONOMETER = 0;

        if(G_TIME > 0)
        {
            G_TIME -= 1;
        }

        VDP_drawIntEx_WINDOW_CPU_PRIO(G_TIME,2,23,4,PAL3);
    }
}


inline static void hide_NUNCHUCK()
{
    SPR_setPosition(sprite_NUNCHUK,0,-32);
}





//**************************************************************************************//
//                                                                                      //
//                                      SCROLLING                                       //
//                                                                                      //
//**************************************************************************************//

void scroll_PLANE_LEVEL_1(s16 increment)
{
    G_POS_X_CAMERA += increment;

    MAP_scrollTo(map_BG_B, G_POS_X_CAMERA , 0);
    MAP_scrollTo(map_BG_A, G_POS_X_CAMERA , 0);
}


void scroll_PLANE_LEVEL_2(s16 increment)
{
    G_POS_X_CAMERA += increment;

    MAP_scrollTo(map_BG_B, G_POS_X_CAMERA , 0);
    MAP_scrollTo(map_BG_A, G_POS_X_CAMERA , 224);
}


void scroll_PLANE_PARALLAX(s16 increment)
{
    G_POS_X_CAMERA += increment;

    MAP_scrollTo(map_BG_B, G_POS_X_CAMERA / 3 , 0);
    MAP_scrollTo(map_BG_A, G_POS_X_CAMERA , 0);
}


void scroll_TILE(s16 increment)
{
    G_POS_X_CAMERA += increment;

    u8 i;

    for (i=0; i<11; i++)
    {        
        //if(G_POS_X_CAMERA%8 == TRUE)
        //{
            scrollTable_BG_B[i] = -(G_POS_X_CAMERA >> 3);
        //}
        scrollTable_BG_A[i] = -G_POS_X_CAMERA; 
    }

    for (i=11; i<23; i++)
    {
        scrollTable_BG_B[i] = -G_POS_X_CAMERA;
        scrollTable_BG_A[i] = -G_POS_X_CAMERA; 
    }

    VDP_setHorizontalScrollTile(BG_B, 5, scrollTable_BG_B, 23, DMA_QUEUE);
    VDP_setHorizontalScrollTile(BG_A, 5, scrollTable_BG_A, 23, DMA_QUEUE);
}




void (*TABLE_SCROLLING_ROUTINE[5])(s16 increment)   =   {
                                                            scroll_PLANE_LEVEL_1,
                                                            scroll_PLANE_LEVEL_2,
                                                            scroll_TILE,
                                                            scroll_PLANE_LEVEL_1,
                                                            scroll_PLANE_PARALLAX
                                                        };




inline static void update_TILEMAP_RIGHT()
{
    if(G_POS_X_CAMERA > 15)
    {
        if(G_POS_X_CAMERA%8 == TRUE)
        {
            VDP_setTileMapColumnEx(BG_B, image_LEVEL_3_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), (G_POS_X_CAMERA >> 3) - 2, (G_POS_X_CAMERA >> 3) + 62, 16, 12, DMA_QUEUE);
            VDP_setTileMapColumnEx(BG_A, image_LEVEL_3_BG_A.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_A), (G_POS_X_CAMERA >> 3) - 2, (G_POS_X_CAMERA >> 3) + 62,  5, 23, DMA_QUEUE);
        }
    }
}


inline static void update_TILEMAP_LEFT()
{
    if(G_POS_X_CAMERA > 15)
    {
        if(G_POS_X_CAMERA%8 == TRUE)
        {
            VDP_setTileMapColumnEx(BG_B, image_LEVEL_3_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), (G_POS_X_CAMERA >> 3) - 2, (G_POS_X_CAMERA >> 3) - 2, 16, 12, DMA_QUEUE);
            VDP_setTileMapColumnEx(BG_A, image_LEVEL_3_BG_A.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_A), (G_POS_X_CAMERA >> 3) - 2, (G_POS_X_CAMERA >> 3) - 2,  5, 23, DMA_QUEUE);
        }
    }
}








//**************************************************************************************//
//                                                                                      //
//                                        PLAYER                                        //
//                                                                                      //
//**************************************************************************************//

inline bool collision_PLAYER_ENEMY_RIGHT()
{
    bool collision = FALSE;

    u8 i;

    for(i=0 ; i<4 ; i++)
    {
        // WE CHECK ENEMIES ONLY IF THEY ARE NOT IN DEAD STATE //
        if(LIST_ENEMIES[i].state != STATE_DEAD)
        {
            if(LIST_ENEMIES[i].pos_Y == player.pos_Y)
            {
                // IF ENEMY IS FACING LEFT //
                if(LIST_ENEMIES[i].axis == AXIS_LEFT)
                {
                    if(player.pos_X >= LIST_ENEMIES[i].pos_X - ENEMY_LEFT_BOUND && player.pos_X <= LIST_ENEMIES[i].pos_X + 42)
                    {
                        collision = TRUE;

                        break;
                    }
                }
            }
        }
    }

    return collision;
}




inline bool collision_PLAYER_ENEMY_LEFT()
{
    bool collision = FALSE;

    u8 i;

    for(i=0 ; i<4 ; i++)
    {
        if(LIST_ENEMIES[i].spr_ENEMY != NULL)
        {
            // WE CHECK ENEMIES ONLY IF THEY ARE NOT IN DEAD STATE //
            if(LIST_ENEMIES[i].state != STATE_DEAD)
            {
                if(LIST_ENEMIES[i].pos_Y == player.pos_Y)
                {
                    // IF ENEMY IS FACING RIGHT //
                    if(LIST_ENEMIES[i].axis == AXIS_RIGHT)
                    {
                        if(player.pos_X < LIST_ENEMIES[i].pos_X + ENEMY_RIGHT_BOUND && player.pos_X > LIST_ENEMIES[i].pos_X - 21)
                        {
                            collision = TRUE;

                            break;
                        }
                    }
                }
            }
        }
    }

    return collision;
}




void joypad_PLAYER()
{
    if(G_PHASE_LEVEL == LEVEL_PLAY)
    {
        u16 value=JOY_readJoypad(JOY_1);
        

        if((value & BUTTON_DIR) == 0)
        {
            if(player.state == STATE_WALK || player.state == STATE_CROUCH)
            {
                G_REPEAT = 0;
                
                player.counter_ANIM_SPRITE = 0;

                if(player.armed == FALSE)
                {
                    SPR_setAnimAndFrame(player.spr_PLAYER,0,0);
                }

                else
                {
                    SPR_setAnimAndFrame(player.spr_PLAYER,14,0);

                    if(player.axis == AXIS_RIGHT)
                    {
                        SPR_setPosition(sprite_NUNCHUK,player.pos_X + 40,player.pos_Y + 20);

                        SPR_setHFlip(sprite_NUNCHUK,FALSE);
                    }

                    else
                    {
                        SPR_setPosition(sprite_NUNCHUK,player.pos_X,player.pos_Y + 20);

                        SPR_setHFlip(sprite_NUNCHUK,TRUE);
                    }
                }

                player.state = STATE_IDLE;

                player.vulnerable = TRUE;
            }
        }


        else if(value & BUTTON_DOWN)
        {
            if(player.state == STATE_IDLE || player.state == STATE_WALK)
            {
                if(player.armed == TRUE)
                {
                    SPR_setAnimAndFrame(player.spr_PLAYER,15,0);

                    if(player.axis == AXIS_RIGHT)
                    {
                        SPR_setPosition(sprite_NUNCHUK,player.pos_X + 42,player.pos_Y + 36);

                        SPR_setHFlip(sprite_NUNCHUK,FALSE);
                    }

                    else
                    {
                        SPR_setPosition(sprite_NUNCHUK,player.pos_X - 2,player.pos_Y + 36);

                        SPR_setHFlip(sprite_NUNCHUK,TRUE);
                    }
                }

                else
                {
                    SPR_setAnimAndFrame(player.spr_PLAYER,3,0);
                }


                player.state = STATE_CROUCH;

                player.vulnerable = TRUE;

                player.counter_ANIM_SPRITE = 0;
            }


            else if(player.state == STATE_CROUCH)
            {
                if(value & BUTTON_LEFT)
                {
                    if(player.axis != AXIS_LEFT)
                    {
                        player.axis = AXIS_LEFT;
                    }

                    SPR_setHFlip(player.spr_PLAYER,TRUE);

                    SPR_setPosition(player.spr_PLAYER,player.pos_X,player.pos_Y);

                    if(player.armed == TRUE)
                    {
                        SPR_setPosition(sprite_NUNCHUK,player.pos_X - 2,player.pos_Y + 36);

                        SPR_setHFlip(sprite_NUNCHUK,TRUE);
                    }
                }

                else if(value & BUTTON_RIGHT)
                {
                    if(player.axis != AXIS_RIGHT)
                    {
                        player.axis = AXIS_RIGHT;
                    }

                    SPR_setHFlip(player.spr_PLAYER,FALSE);

                    SPR_setPosition(player.spr_PLAYER,player.pos_X,player.pos_Y);

                    if(player.armed == TRUE)
                    {
                        SPR_setPosition(sprite_NUNCHUK,player.pos_X + 42,player.pos_Y + 36);

                        SPR_setHFlip(sprite_NUNCHUK,FALSE);
                    }
                }
            }


            else if(player.state == STATE_PUNCH_CROUCH)
            {
                if(value & BUTTON_LEFT)
                {
                    if(player.axis != AXIS_LEFT)
                    {
                        player.axis = AXIS_LEFT;
                    }

                    SPR_setHFlip(player.spr_PLAYER,TRUE);

                    SPR_setPosition(player.spr_PLAYER,player.pos_X,player.pos_Y);
                }

                else if(value & BUTTON_RIGHT)
                {
                    if(player.axis != AXIS_RIGHT)
                    {
                        player.axis = AXIS_RIGHT;
                    }

                    SPR_setHFlip(player.spr_PLAYER,FALSE);

                    SPR_setPosition(player.spr_PLAYER,player.pos_X,player.pos_Y);
                }
            }    
        }

    
        else if(value & BUTTON_LEFT)
        {
            if(player.state == STATE_IDLE || player.state == STATE_WALK || player.state == STATE_CROUCH)
            {
                if(collision_PLAYER_ENEMY_LEFT() == FALSE)
                {
                    // IF SCROLLING HAS NOT STARTED //
                    if(G_POS_X_CAMERA == 0)
                    {
                        // SCREEN LEFT LIMIT //
                        if(player.pos_X != -19)
                        {
                            player.pos_X -= 1;

                            if(player.axis != AXIS_LEFT)
                            {
                                //SPR_setHFlip(player.spr_PLAYER,TRUE);

                                player.axis = AXIS_LEFT;
                            }
                        }
                    }


                    // IF SCROLLING HAS STARTED //
                    else if(G_POS_X_CAMERA > 0 && G_POS_X_CAMERA < G_CAMERA_LIMIT)
                    {
                        //--------------------------------------------------------------------------------------//
                        //                                                                                      //
                        //                                    TILEMAP UPDATE                                    //
                        //                                                                                      //
                        //--------------------------------------------------------------------------------------//

                        if(G_LEVEL == 3)
                        {
                            update_TILEMAP_LEFT();
                        }


                        //--------------------------------------------------------------------------------------//
                        //                                                                                      //
                        //                                      SCROLLING                                       //
                        //                                                                                      //
                        //--------------------------------------------------------------------------------------//

                        // POINTER DECLARATION //
                        void (*ptr_SCROLLING_ROUTINE)(s16 increment);

                        // SETTING POINTER TO SCROLLING FUNCTION //
                        ptr_SCROLLING_ROUTINE = TABLE_SCROLLING_ROUTINE[G_LEVEL - 1];

                        // RUNNING SCROLLING FUNCTION //
                        (*ptr_SCROLLING_ROUTINE)(-1);


                        // UPDATE WEAPON POSITION //
                        update_WEAPON(1);


                        // UPDATE ENEMIES POSITION //
                        u8 i;

                        for(i=0 ; i<4 ; i++)
                        {
                            if(LIST_ENEMIES[i].spr_ENEMY != NULL)
                            {
                                LIST_ENEMIES[i].pos_X += 1;

                                SPR_setPosition(LIST_ENEMIES[i].spr_ENEMY , LIST_ENEMIES[i].pos_X , LIST_ENEMIES[i].pos_Y);
                            }
                        }


                        if(player.axis != AXIS_LEFT)
                        {
                            //SPR_setHFlip(player.spr_PLAYER,TRUE);

                            player.axis = AXIS_LEFT;
                        }
                    }


                    // IF SCROLLING HAS ENDED //
                    else if(G_POS_X_CAMERA == G_CAMERA_LIMIT)
                    {
                        if(player.pos_X > 98)
                        {
                            player.pos_X -= 1;

                            if(player.axis != AXIS_LEFT)
                            {
                                //SPR_setHFlip(player.spr_PLAYER,TRUE);
                                
                                player.axis = AXIS_LEFT;
                            }
                        }

                        else
                        {
                            //--------------------------------------------------------------------------------------//
                            //                                                                                      //
                            //                                    TILEMAP UPDATE                                    //
                            //                                                                                      //
                            //--------------------------------------------------------------------------------------//

                            if(G_LEVEL == 3)
                            {
                                update_TILEMAP_LEFT();
                            }


                            //--------------------------------------------------------------------------------------//
                            //                                                                                      //
                            //                                      SCROLLING                                       //
                            //                                                                                      //
                            //--------------------------------------------------------------------------------------//

                            // POINTER DECLARATION //
                            void (*ptr_SCROLLING_ROUTINE)(s16 increment);

                            // SETTING POINTER TO SCROLLING FUNCTION //
                            ptr_SCROLLING_ROUTINE = TABLE_SCROLLING_ROUTINE[G_LEVEL - 1];

                            // RUNNING SCROLLING FUNCTION //
                            (*ptr_SCROLLING_ROUTINE)(-1);


                            // UPDATE ENEMIES POSITION //
                            u8 i;

                            for(i=0 ; i<4 ; i++)
                            {
                                if(LIST_ENEMIES[i].spr_ENEMY != NULL)
                                {
                                    LIST_ENEMIES[i].pos_X += 1;

                                    SPR_setPosition(LIST_ENEMIES[i].spr_ENEMY , LIST_ENEMIES[i].pos_X , LIST_ENEMIES[i].pos_Y);
                                }
                            }


                            if(player.axis != AXIS_LEFT)
                            {
                                //SPR_setHFlip(player.spr_PLAYER,TRUE);
                                
                                player.axis = AXIS_LEFT;
                            }   
                        }
                    }


                    SPR_setPosition(player.spr_PLAYER,player.pos_X,player.pos_Y);

                    SPR_setHFlip(player.spr_PLAYER,TRUE);

                    player.state = STATE_WALK;

                    player.vulnerable = TRUE;
                }

                if(player.armed == TRUE)
                {
                    hide_NUNCHUCK();
                }
            }


            else if(player.state == STATE_KICK || player.state == STATE_PUNCH || player.state == STATE_PUNCH_CROUCH)
            {
                if(player.axis != AXIS_LEFT)
                {
                    player.axis = AXIS_LEFT;

                    SPR_setHFlip(player.spr_PLAYER,TRUE);

                    SPR_setPosition(player.spr_PLAYER,player.pos_X,player.pos_Y);
                }
            }
        }


        else if(value & BUTTON_RIGHT)
        {
            if(player.state == STATE_IDLE || player.state == STATE_WALK || player.state == STATE_CROUCH)
            {
                if(collision_PLAYER_ENEMY_RIGHT() == FALSE)
                {
                    // IF SCROLLING HAS NOT STARTED //
                    if(G_POS_X_CAMERA == 0)
                    {
                        if(player.pos_X < 98)
                        {
                            player.pos_X += 1;


                            if(player.axis != AXIS_RIGHT)
                            {
                                player.axis = AXIS_RIGHT;
                            }
                        }

                        else
                        {
                            if(G_POS_X_CAMERA < G_CAMERA_LIMIT)
                            {
                                //--------------------------------------------------------------------------------------//
                                //                                                                                      //
                                //                                    TILEMAP UPDATE                                    //
                                //                                                                                      //
                                //--------------------------------------------------------------------------------------//

                                if(G_LEVEL == 3)
                                {
                                    update_TILEMAP_RIGHT();
                                }


                                //--------------------------------------------------------------------------------------//
                                //                                                                                      //
                                //                                      SCROLLING                                       //
                                //                                                                                      //
                                //--------------------------------------------------------------------------------------//

                                // POINTER DECLARATION //
                                void (*ptr_SCROLLING_ROUTINE)(s16 increment);

                                // SETTING POINTER TO SCROLLING FUNCTION //
                                ptr_SCROLLING_ROUTINE = TABLE_SCROLLING_ROUTINE[G_LEVEL - 1];

                                // RUNNING SCROLLING FUNCTION //
                                (*ptr_SCROLLING_ROUTINE)(1);


                                // UPDATE ENEMIES POSITION //
                                u8 i;

                                for(i=0 ; i<4 ; i++)
                                {
                                    if(LIST_ENEMIES[i].spr_ENEMY != NULL)
                                    {
                                        LIST_ENEMIES[i].pos_X -= 1;
                                    }
                                }

                                // UPDATE WEAPON POSITION //


                                if(player.axis != AXIS_RIGHT)
                                {

                                    player.axis = AXIS_RIGHT;
                                }

                                //SPR_setHFlip(player.spr_PLAYER,FALSE);
                            }
                        }
                    }
                    

                    // IF SCROLLING HAS STARTED //
                    else if(G_POS_X_CAMERA < G_CAMERA_LIMIT)
                    {
                        //--------------------------------------------------------------------------------------//
                        //                                                                                      //
                        //                                    TILEMAP UPDATE                                    //
                        //                                                                                      //
                        //--------------------------------------------------------------------------------------//

                        if(G_LEVEL == 3)
                        {
                            update_TILEMAP_RIGHT();
                        }


                        //--------------------------------------------------------------------------------------//
                        //                                                                                      //
                        //                                      SCROLLING                                       //
                        //                                                                                      //
                        //--------------------------------------------------------------------------------------//

                        // POINTER DECLARATION //
                        void (*ptr_SCROLLING_ROUTINE)(s16 increment);

                        // SETTING POINTER TO SCROLLING FUNCTION //
                        ptr_SCROLLING_ROUTINE = TABLE_SCROLLING_ROUTINE[G_LEVEL - 1];

                        // RUNNING SCROLLING FUNCTION //
                        (*ptr_SCROLLING_ROUTINE)(1);


                        // UPDATE WEAPON POSITION //
                        update_WEAPON(-1);


                        // UPDATE ENEMIES POSITION //
                        u8 i;

                        for(i=0 ; i<4 ; i++)
                        {
                            if(LIST_ENEMIES[i].spr_ENEMY != NULL)
                            {
                                LIST_ENEMIES[i].pos_X -= 1;
                            }
                        }


                        if(player.axis != AXIS_RIGHT)
                        {
                            player.axis = AXIS_RIGHT;
                        }
                    }


                    // IF SCROLLING HAS ENDED //
                    else if(G_POS_X_CAMERA == G_CAMERA_LIMIT)
                    {
                        if(player.pos_X < G_LEVEL_LIMIT)
                        {
                            player.pos_X += 1;
                        }
                    }


                    SPR_setPosition(player.spr_PLAYER,player.pos_X,player.pos_Y);

                    SPR_setHFlip(player.spr_PLAYER,FALSE);

                    player.state = STATE_WALK;

                    player.vulnerable = TRUE;
                }

                if(player.armed == TRUE)
                {
                    hide_NUNCHUCK();
                }
            }


            else if(player.state == STATE_KICK || player.state == STATE_PUNCH || player.state == STATE_PUNCH_CROUCH)
            {
                if(player.axis != AXIS_RIGHT)
                {
                    player.axis = AXIS_RIGHT;   

                    SPR_setHFlip(player.spr_PLAYER,FALSE);

                    SPR_setPosition(player.spr_PLAYER,player.pos_X,player.pos_Y);
                }
            }
        }


        else if(value & BUTTON_UP)
        {
            if(player.state == STATE_CROUCH)
            {
                if(player.armed == FALSE)
                {
                    SPR_setAnimAndFrame(player.spr_PLAYER,0,0);
                }

                else
                {
                    SPR_setAnimAndFrame(player.spr_PLAYER,14,0);
                }

                player.state = STATE_IDLE;

                player.vulnerable = TRUE;
            }
        }
    }
}




void update_PLAYER_SPRITE()
{
    if(player.state == STATE_WALK)
    {        
        if(player.counter_ANIM_SPRITE == 0)
        {
            SPR_setAnim(player.spr_PLAYER,0);
            SPR_setFrame(player.spr_PLAYER,0);
        }
        
        else if(player.counter_ANIM_SPRITE == 8)
        {
            SPR_setFrame(player.spr_PLAYER,1);
        }

        else if(player.counter_ANIM_SPRITE == 16)
        {
            SPR_setFrame(player.spr_PLAYER,2);
        }

        else if(player.counter_ANIM_SPRITE == 24)
        {
            SPR_setFrame(player.spr_PLAYER,3);
        }   

        else if(player.counter_ANIM_SPRITE == 32)
        {
            player.counter_ANIM_SPRITE = 0;

            return;
        }

        player.counter_ANIM_SPRITE += 1;
    }


    else if(player.state == STATE_PUNCH)
    {
        // IF PLAYER DOESN'T HAVE THE NUNCHUCK //
        if(player.armed == FALSE)
        {
            if(player.counter_ANIM_SPRITE == 0)
            {
                SPR_setAnimAndFrame(player.spr_PLAYER,G_INDEX_ANIM_PUNCH,0);
            }
            
            else if(player.counter_ANIM_SPRITE == 6)
            {
                SPR_setAnimAndFrame(player.spr_PLAYER,G_INDEX_ANIM_PUNCH,1);
            }

            else if(player.counter_ANIM_SPRITE == 12)
            {
                SPR_setAnimAndFrame(player.spr_PLAYER,G_INDEX_ANIM_PUNCH,2);

                G_REPEAT = 0;
            }


            player.counter_ANIM_SPRITE += 1;


            if(player.counter_ANIM_SPRITE == 23)
            {
                if(G_REPEAT == 0)
                {
                    if(player.armed == FALSE)
                    {
                        SPR_setAnimAndFrame(player.spr_PLAYER,0,0);
                    }

                    else
                    {
                        SPR_setAnimAndFrame(player.spr_PLAYER,14,0);
                    }

                    G_INDEX_ANIM_PUNCH = 1;

                    player.counter_ANIM_SPRITE = 0;

                    player.state = STATE_IDLE;

                    player.vulnerable = TRUE;
                }

                else
                {
                    SPR_setAnimAndFrame(player.spr_PLAYER,G_INDEX_ANIM_PUNCH,0);
                    
                    player.counter_ANIM_SPRITE = 1;
                } 
            }
        }

        // IF PLAYER HAS THE NUNCHUCK //
        else
        {
            if(player.counter_ANIM_SPRITE == 0)
            {
                SPR_setAnimAndFrame(player.spr_PLAYER,14,1);


                SPR_setFrame(sprite_NUNCHUK,1);

                if(player.axis == AXIS_RIGHT)
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X + 41,player.pos_Y + 18);

                    SPR_setHFlip(sprite_NUNCHUK,FALSE);
                }

                else
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X - 1,player.pos_Y + 18);

                    SPR_setHFlip(sprite_NUNCHUK,TRUE);
                }

                XGM_startPlayPCM(SOUND_NUNCHUCK,14,SOUND_PCM_CH3);

            }

            else if(player.counter_ANIM_SPRITE == 2)
            {
                SPR_setFrame(player.spr_PLAYER,2);


                SPR_setFrame(sprite_NUNCHUK,2);

                if(player.axis == AXIS_RIGHT)
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X + 57,player.pos_Y + 9);

                    SPR_setHFlip(sprite_NUNCHUK,FALSE);
                }

                else
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X - 17,player.pos_Y + 9);

                    SPR_setHFlip(sprite_NUNCHUK,TRUE);
                }
            }

            else if(player.counter_ANIM_SPRITE == 4)
            {
                SPR_setFrame(sprite_NUNCHUK,3);

                if(player.axis == AXIS_RIGHT)
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X + 58,player.pos_Y + 10);

                    SPR_setHFlip(sprite_NUNCHUK,FALSE);
                }

                else
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X - 18,player.pos_Y + 10);

                    SPR_setHFlip(sprite_NUNCHUK,TRUE);
                }
            }

            else if(player.counter_ANIM_SPRITE == 6)
            {
                SPR_setFrame(sprite_NUNCHUK,4);

                if(player.axis == AXIS_RIGHT)
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X + 58,player.pos_Y + 30);

                    SPR_setHFlip(sprite_NUNCHUK,FALSE);
                }

                else
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X - 18,player.pos_Y + 30);

                    SPR_setHFlip(sprite_NUNCHUK,TRUE);
                }
            }

            else if(player.counter_ANIM_SPRITE == 8)
            {
                SPR_setFrame(player.spr_PLAYER,3);
                

                SPR_setFrame(sprite_NUNCHUK,5);

                if(player.axis == AXIS_RIGHT)
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X + 50,player.pos_Y + 32);

                    SPR_setHFlip(sprite_NUNCHUK,FALSE);
                }

                else
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X - 10,player.pos_Y + 32);

                    SPR_setHFlip(sprite_NUNCHUK,TRUE);
                }
            }

            else if(player.counter_ANIM_SPRITE == 9)
            {             
                SPR_setFrame(sprite_NUNCHUK,6);

                if(player.axis == AXIS_RIGHT)
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X + 47,player.pos_Y + 35);

                    SPR_setHFlip(sprite_NUNCHUK,FALSE);
                }

                else
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X - 7,player.pos_Y + 35);

                    SPR_setHFlip(sprite_NUNCHUK,TRUE);
                }
            }

            else if(player.counter_ANIM_SPRITE == 11)
            {
                if(player.axis == AXIS_RIGHT)
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X + 40,player.pos_Y + 20);

                    SPR_setHFlip(sprite_NUNCHUK,FALSE);
                }

                else
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X,player.pos_Y + 20);

                    SPR_setHFlip(sprite_NUNCHUK,TRUE);
                }

                SPR_setFrame(sprite_NUNCHUK,0);

                SPR_setAnimAndFrame(player.spr_PLAYER,14,0);


                player.counter_ANIM_SPRITE = 0;

                player.state = STATE_IDLE;

                player.vulnerable = TRUE;

                return;
            }


            player.counter_ANIM_SPRITE += 1;
        }
    }


    else if(player.state == STATE_PUNCH_CROUCH)
    {
        // IF PLAYER DOESN'T HAVE THE NUNCHUCK //
        if(player.armed == FALSE)
        {
            if(player.counter_ANIM_SPRITE == 8)
            {
                SPR_setAnimAndFrame(player.spr_PLAYER,G_INDEX_ANIM_PUNCH + 3,1);
            }

            else if(player.counter_ANIM_SPRITE == 16)
            {
                SPR_setAnimAndFrame(player.spr_PLAYER,G_INDEX_ANIM_PUNCH + 3,2);

                G_REPEAT = 0;
            }

            else if(player.counter_ANIM_SPRITE == 24)
            {
                if(G_REPEAT == 0)
                {
                    SPR_setAnimAndFrame(player.spr_PLAYER,3,0);

                    G_INDEX_ANIM_PUNCH = 1;

                    player.counter_ANIM_SPRITE = 0;

                    player.state = STATE_CROUCH;

                    player.vulnerable = TRUE;

                    return;
                }

                else
                {
                    SPR_setAnimAndFrame(player.spr_PLAYER,G_INDEX_ANIM_PUNCH + 3,0);
                    
                    player.counter_ANIM_SPRITE = 0;

                    return;
                } 
            }

            player.counter_ANIM_SPRITE += 1;
        }

        // IF PLAYER HAS THE NUNCHUCK //
        else
        {
            if(player.counter_ANIM_SPRITE == 0 || player.counter_ANIM_SPRITE == 1)
            {
                SPR_setAnimAndFrame(player.spr_PLAYER,15,1);


                SPR_setFrame(sprite_NUNCHUK,1);

                if(player.axis == AXIS_RIGHT)
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X + 41,player.pos_Y + 34);

                    SPR_setHFlip(sprite_NUNCHUK,FALSE);
                }

                else
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X - 1,player.pos_Y + 34);

                    SPR_setHFlip(sprite_NUNCHUK,TRUE);
                }

                XGM_startPlayPCM(SOUND_NUNCHUCK,14,SOUND_PCM_CH3);
            }

            else if(player.counter_ANIM_SPRITE >= 2 && player.counter_ANIM_SPRITE < 4)
            {
                SPR_setFrame(player.spr_PLAYER,2);


                SPR_setFrame(sprite_NUNCHUK,2);

                if(player.axis == AXIS_RIGHT)
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X + 59,player.pos_Y + 25);

                    SPR_setHFlip(sprite_NUNCHUK,FALSE);
                }

                else
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X - 19,player.pos_Y + 25);

                    SPR_setHFlip(sprite_NUNCHUK,TRUE);
                }
            }

            else if(player.counter_ANIM_SPRITE >= 4 && player.counter_ANIM_SPRITE < 6)
            {
                SPR_setFrame(sprite_NUNCHUK,3);

                if(player.axis == AXIS_RIGHT)
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X + 60,player.pos_Y + 26);

                    SPR_setHFlip(sprite_NUNCHUK,FALSE);
                }

                else
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X - 20,player.pos_Y + 26);

                    SPR_setHFlip(sprite_NUNCHUK,TRUE);
                }
            }

            else if(player.counter_ANIM_SPRITE >= 6 && player.counter_ANIM_SPRITE < 8)
            {
                SPR_setFrame(sprite_NUNCHUK,4);

                if(player.axis == AXIS_RIGHT)
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X + 60,player.pos_Y + 46);

                    SPR_setHFlip(sprite_NUNCHUK,FALSE);
                }

                else
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X - 19,player.pos_Y + 46);

                    SPR_setHFlip(sprite_NUNCHUK,TRUE);
                }
            }

            else if(player.counter_ANIM_SPRITE == 8)
            {
                SPR_setFrame(player.spr_PLAYER,3);
                

                SPR_setFrame(sprite_NUNCHUK,5);

                if(player.axis == AXIS_RIGHT)
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X + 52,player.pos_Y + 48);

                    SPR_setHFlip(sprite_NUNCHUK,FALSE);
                }

                else
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X - 12,player.pos_Y + 48);

                    SPR_setHFlip(sprite_NUNCHUK,TRUE);
                }
            }

            else if(player.counter_ANIM_SPRITE >= 9 && player.counter_ANIM_SPRITE < 11)
            {
                SPR_setFrame(sprite_NUNCHUK,7);

                if(player.axis == AXIS_RIGHT)
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X + 49,player.pos_Y + 51);

                    SPR_setHFlip(sprite_NUNCHUK,FALSE);
                }

                else
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X - 9,player.pos_Y + 51);

                    SPR_setHFlip(sprite_NUNCHUK,TRUE);
                }
            }

            else if(player.counter_ANIM_SPRITE == 11)
            {
                if(player.axis == AXIS_RIGHT)
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X + 40,player.pos_Y + 20);

                    SPR_setHFlip(sprite_NUNCHUK,FALSE);

                    SPR_setPosition(sprite_NUNCHUK,player.pos_X + 42,player.pos_Y + 36);

                    SPR_setHFlip(sprite_NUNCHUK,FALSE);
                }

                else
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X,player.pos_Y + 20);

                    SPR_setHFlip(sprite_NUNCHUK,TRUE);

                    SPR_setPosition(sprite_NUNCHUK,player.pos_X - 2,player.pos_Y + 36);

                    SPR_setHFlip(sprite_NUNCHUK,TRUE);
                }

                SPR_setFrame(sprite_NUNCHUK,0);

                SPR_setAnimAndFrame(player.spr_PLAYER,15,0);


                player.counter_ANIM_SPRITE = 0;

                player.state = STATE_CROUCH;

                player.vulnerable = TRUE;

                return;
            }


            player.counter_ANIM_SPRITE += 1;
        }

    }


    else if(player.state == STATE_KICK)
    {
        if(player.counter_ANIM_SPRITE == 0)
        {
            SPR_setAnimAndFrame(player.spr_PLAYER,6,0);
        }
        
        else if(player.counter_ANIM_SPRITE == 5)
        {
            SPR_setAnimAndFrame(player.spr_PLAYER,6,1);

            G_REPEAT = 0;
        }

        else if(player.counter_ANIM_SPRITE == 13)
        {
            SPR_setAnimAndFrame(player.spr_PLAYER,6,0);
        }

        else if(player.counter_ANIM_SPRITE == 24)
        {
            if(G_REPEAT == 0)
            {
                if(player.armed == FALSE)
                {
                    SPR_setAnimAndFrame(player.spr_PLAYER,0,0);
                }

                else
                {
                    SPR_setAnimAndFrame(player.spr_PLAYER,14,0);

                    if(player.axis == AXIS_RIGHT)
                    {
                        SPR_setPosition(sprite_NUNCHUK,player.pos_X + 40,player.pos_Y + 20);

                        SPR_setHFlip(sprite_NUNCHUK,FALSE);
                    }

                    else
                    {
                        SPR_setPosition(sprite_NUNCHUK,player.pos_X,player.pos_Y + 20);

                        SPR_setHFlip(sprite_NUNCHUK,TRUE);
                    }
                }

                player.counter_ANIM_SPRITE = 0;

                player.state = STATE_IDLE;

                player.vulnerable = TRUE;

                return;
            }

            else
            {
                SPR_setAnimAndFrame(player.spr_PLAYER,6,1);
                
                player.counter_ANIM_SPRITE = 5;

                return;
            } 
        }

        player.counter_ANIM_SPRITE += 1;
    }


    else if(player.state == STATE_KICK_CROUCH)
    {
        hide_NUNCHUCK();
        

        if(player.counter_ANIM_SPRITE == 0)
        {
            SPR_setAnimAndFrame(player.spr_PLAYER,7,0);

            SPR_setZ(player.spr_PLAYER,1);
        }        

        else if(player.counter_ANIM_SPRITE == 9)
        {
            if(player.armed == TRUE)
            {
                if(player.axis == AXIS_RIGHT)
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X + 40,player.pos_Y + 20);

                    SPR_setHFlip(sprite_NUNCHUK,FALSE);

                    SPR_setPosition(sprite_NUNCHUK,player.pos_X + 42,player.pos_Y + 36);

                    SPR_setHFlip(sprite_NUNCHUK,FALSE);
                }

                else
                {
                    SPR_setPosition(sprite_NUNCHUK,player.pos_X,player.pos_Y + 20);

                    SPR_setHFlip(sprite_NUNCHUK,TRUE);

                    SPR_setPosition(sprite_NUNCHUK,player.pos_X - 2,player.pos_Y + 36);

                    SPR_setHFlip(sprite_NUNCHUK,TRUE);
                }

                SPR_setFrame(sprite_NUNCHUK,0);

                SPR_setAnimAndFrame(player.spr_PLAYER,15,0);
            }

            else
            {
                SPR_setAnimAndFrame(player.spr_PLAYER,3,0);
            }
                

            player.counter_ANIM_SPRITE = 0;

            player.state = STATE_CROUCH;

            player.vulnerable = TRUE;

            return;
        }

        player.counter_ANIM_SPRITE += 1;
    }


    else if(player.state == STATE_JUMP_V)
    {
        //**************************************************//
        //                                                  //
        //          UPDATE PLAYER VERTICAL POSITION         //
        //                                                  //
        //**************************************************//

        if(player.counter_ANIM_V > 0)
        {
            //--------------------------------------------------//
            //                PLAYER GOING UPWARD               //
            //--------------------------------------------------//
            if(player.counter_ANIM_V <= JUMP_HIGH_POINT)
            {
                G_GRAVITY -= FIX32(0.2);
            }

            //--------------------------------------------------//
            //               PLAYER GOING DOWNWARD              //
            //--------------------------------------------------//
            else
            {
                G_GRAVITY -= FIX32(0.3);
            }


            player.pos_Y -= fix32ToInt(G_GRAVITY);


            //--------------------------------------------------//
            //           IF PLAYER TOUCHES THE GROUND           //
            //--------------------------------------------------//
            if(player.pos_Y >= G_GROUND_POSITION)
            {                
                player.pos_Y = G_GROUND_POSITION;

                SPR_setPosition(player.spr_PLAYER,player.pos_X,player.pos_Y);

                


                G_JUMP_KICK = NO_JUMP_KICK;

                G_JUMP_PUNCH = NO_JUMP_PUNCH;

                player.counter_ANIM_SPRITE = 0;


                u16 value=JOY_readJoypad(JOY_1);

                if(value & BUTTON_LEFT || value & BUTTON_RIGHT)
                {
                    player.state = STATE_WALK;

                    player.vulnerable = TRUE;

                    SPR_setAnimAndFrame(player.spr_PLAYER,0,0);
                }

                else if((value & BUTTON_DIR) == 0)
                {
                    player.state = STATE_IDLE;

                    player.vulnerable = TRUE;

                    if(player.armed == TRUE)
                    {
                        if(player.axis == AXIS_RIGHT)
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X + 40,player.pos_Y + 20);

                            SPR_setHFlip(sprite_NUNCHUK,FALSE);
                        }

                        else
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X,player.pos_Y + 20);

                            SPR_setHFlip(sprite_NUNCHUK,TRUE);
                        }

                        SPR_setFrame(sprite_NUNCHUK,0);

                        SPR_setAnimAndFrame(player.spr_PLAYER,14,0);
                    }

                    else
                    {
                        SPR_setAnimAndFrame(player.spr_PLAYER,0,0);
                    }
                }

                return;
            }


            SPR_setPosition(player.spr_PLAYER,player.pos_X,player.pos_Y);
        }



        

        //--------------------------------------------------//
        //             UPDATE JUMP SPRITE FRAME             //
        //--------------------------------------------------//

        // IF PLAYER HAS NOT PRESSED THE KICK BUTTON //
        if(G_JUMP_KICK == NO_JUMP_KICK)
        {
            // IF PLAYER HAS NOT PRESSED THE PUNCH BUTTON //
            if(G_JUMP_PUNCH == NO_JUMP_PUNCH)
            {
                // WE PLAY THE REGULAR JUMP ANIMATION //
                if(player.counter_ANIM_V == 0)
                {
                    SPR_setAnim(player.spr_PLAYER,11);
                    SPR_setFrame(player.spr_PLAYER,1);
                }

                else if(player.counter_ANIM_V == 5)
                {
                    SPR_setAnim(player.spr_PLAYER,11);
                    SPR_setFrame(player.spr_PLAYER,2);
                }

                else if(player.counter_ANIM_V == JUMP_KICK_COLL_START)
                {
                    SPR_setAnim(player.spr_PLAYER,11);
                    SPR_setFrame(player.spr_PLAYER,3);
                }

                else if(player.counter_ANIM_V == JUMP_KICK_COLL_END)
                {
                    SPR_setAnim(player.spr_PLAYER,11);
                    SPR_setFrame(player.spr_PLAYER,2);
                }

                else if(player.counter_ANIM_V == 24)//26
                {
                    SPR_setAnim(player.spr_PLAYER,11);
                    SPR_setFrame(player.spr_PLAYER,1);
                }
            }

            // IF PLAYER HAS PRESSED THE PUNCH BUTTON //
            else
            {
                if(player.armed == TRUE)
                {
                    if(player.counter_ANIM_V == 0)
                    {
                        SPR_setAnim(player.spr_PLAYER,11);
                        SPR_setFrame(player.spr_PLAYER,1);
                    }

                    else if(player.counter_ANIM_V == 5)
                    {
                        SPR_setAnim(player.spr_PLAYER,11);
                        SPR_setFrame(player.spr_PLAYER,2);
                    }

                    else if(player.counter_ANIM_V == 7)
                    {
                        SPR_setAnim(player.spr_PLAYER,16);
                        SPR_setFrame(player.spr_PLAYER,0);

                        if(player.axis == AXIS_RIGHT)
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X + 39, player.pos_Y + 11);
                        }

                        else
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X, player.pos_Y + 11);
                        }
                    }

                    else if(player.counter_ANIM_V == 8)
                    {
                        SPR_setAnim(player.spr_PLAYER,16);
                        SPR_setFrame(player.spr_PLAYER,1);

                        SPR_setFrame(sprite_NUNCHUK,1);

                        if(player.axis == AXIS_RIGHT)
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X + 40, player.pos_Y + 9);
                        }

                        else
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X, player.pos_Y + 9);
                        }
                    }

                    else if(player.counter_ANIM_V == 9)
                    {
                        SPR_setAnim(player.spr_PLAYER,16);
                        SPR_setFrame(player.spr_PLAYER,1);

                        SPR_setFrame(sprite_NUNCHUK,1);

                        if(player.axis == AXIS_RIGHT)
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X + 40, player.pos_Y + 9);
                        }

                        else
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X, player.pos_Y + 9);
                        }
                    }

                    else if(player.counter_ANIM_V >= 10 && player.counter_ANIM_V < 12)
                    {
                        SPR_setAnim(player.spr_PLAYER,16);
                        SPR_setFrame(player.spr_PLAYER,2);

                        SPR_setFrame(sprite_NUNCHUK,2);

                        if(player.axis == AXIS_RIGHT)
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X + 56, player.pos_Y);
                        }

                        else
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X - 16, player.pos_Y);
                        }
                    }

                    else if(player.counter_ANIM_V >= 12 && player.counter_ANIM_V < 14)
                    {
                        SPR_setAnim(player.spr_PLAYER,16);
                        SPR_setFrame(player.spr_PLAYER,2);

                        SPR_setFrame(sprite_NUNCHUK,3);

                        if(player.axis == AXIS_RIGHT)
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X + 57, player.pos_Y + 1);
                        }

                        else
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X - 17, player.pos_Y + 1);
                        }
                    }

                    else if(player.counter_ANIM_V >= 14 && player.counter_ANIM_V < 16)
                    {
                        SPR_setAnim(player.spr_PLAYER,16);
                        SPR_setFrame(player.spr_PLAYER,2);

                        SPR_setFrame(sprite_NUNCHUK,4);

                        if(player.axis == AXIS_RIGHT)
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X + 57, player.pos_Y + 21);
                        }

                        else
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X - 17, player.pos_Y + 21);
                        }
                    }

                    else if(player.counter_ANIM_V == 16)
                    {
                        SPR_setAnim(player.spr_PLAYER,16);
                        SPR_setFrame(player.spr_PLAYER,3);

                        SPR_setFrame(sprite_NUNCHUK,5);

                        if(player.axis == AXIS_RIGHT)
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X + 49, player.pos_Y + 23);
                        }

                        else
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X - 9, player.pos_Y + 23);
                        }
                    }

                    else if(player.counter_ANIM_V >= 17 && player.counter_ANIM_V < 19)
                    {
                        SPR_setFrame(sprite_NUNCHUK,6);
                        
                        if(player.axis == AXIS_RIGHT)
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X + 46, player.pos_Y + 26);
                        }

                        else
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X - 6, player.pos_Y + 26);
                        }
                    }

                    else if(player.counter_ANIM_V == 19)
                    {
                        SPR_setAnim(player.spr_PLAYER,11);
                        SPR_setFrame(player.spr_PLAYER,2);

                        SPR_setPosition(sprite_NUNCHUK,0, -32);

                        //player.armed = FALSE;
                    }

                    else if(player.counter_ANIM_V == 24)
                    {
                        SPR_setFrame(player.spr_PLAYER,1);
                    }
                }

                else
                {
                    if(player.counter_ANIM_V == 0)
                    {
                        SPR_setAnim(player.spr_PLAYER,11);
                        SPR_setFrame(player.spr_PLAYER,1);
                    }

                    else if(player.counter_ANIM_V == 5)
                    {
                        SPR_setAnim(player.spr_PLAYER,11);
                        SPR_setFrame(player.spr_PLAYER,2);
                    }

                    else if(player.counter_ANIM_V == 11)
                    {
                        SPR_setAnim(player.spr_PLAYER,13);
                        SPR_setFrame(player.spr_PLAYER,0);
                    }

                    else if(player.counter_ANIM_V == 13)
                    {
                        SPR_setAnim(player.spr_PLAYER,13);
                        SPR_setFrame(player.spr_PLAYER,1);
                    }

                    else if(player.counter_ANIM_V == 20)
                    {
                        SPR_setAnim(player.spr_PLAYER,11);
                        SPR_setFrame(player.spr_PLAYER,2);
                    }

                    else if(player.counter_ANIM_V == 24)
                    {
                        SPR_setAnim(player.spr_PLAYER,11);
                        SPR_setFrame(player.spr_PLAYER,1);
                    }
                }
            }
        }


        //--------------------------------------------------//
        //           UPDATE JUMP KICK SPRITE FRAME          //
        //--------------------------------------------------//

        // IF PLAYER HAS PRESSED THE KICK BUTTON //
        else
        {
            if(player.counter_ANIM_V >= JUMP_KICK_COLL_START && player.counter_ANIM_V <= JUMP_HIGH_POINT)
            {
                SPR_setAnim(player.spr_PLAYER,12);
                SPR_setFrame(player.spr_PLAYER,0);
            }

            else if(player.counter_ANIM_V == JUMP_KICK_COLL_END)
            {
                SPR_setAnim(player.spr_PLAYER,12);
                SPR_setFrame(player.spr_PLAYER,1);

                G_JUMP_KICK = NO_JUMP_KICK;
            }

            else if(player.counter_ANIM_V == 24)//26
            {
                SPR_setAnim(player.spr_PLAYER,11);
                SPR_setFrame(player.spr_PLAYER,1);
            }
        }




        //---------------------------------------------------------------//
        // IF PLAYER HAS REACHED THE HIGHEST POSITION IN JUMP (FRAME 15) //
        // IF PLAYER HAS HIT AN ENNEMY (G_JUMP_KICK = JUMP_KICK_HIT      //
        // PLAYER GOES TO STATE_JUMP_KICK_BW                             //
        //---------------------------------------------------------------//

        if(player.counter_ANIM_V > JUMP_HIGH_POINT)
        {
            if(G_JUMP_KICK == JUMP_KICK_HIT)
            {
                player.counter_ANIM_SPRITE  = 0;
                
                player.counter_ANIM_V       = 0;
                player.counter_ANIM_H       = 0;

                G_INDEX_JUMP_V              = 0;
                G_INDEX_JUMP_H              = 0;

                G_GRAVITY                   = FIX32(3.34L);//4L

                player.state = STATE_JUMP_KICK_BW;

                player.vulnerable = TRUE;

                return;
            }
        }



        player.counter_ANIM_V += 1;
    }


    else if(player.state == STATE_JUMP_H)
    {
        //**************************************************//
        //                                                  //
        //         UPDATE PLAYER HORIZONTAL POSITION        //
        //                                                  //
        //**************************************************//

        if(player.counter_ANIM_H == TABLE_JUMP_H[G_INDEX_JUMP_H].frame)
        {            
            u8 i;
            

            //--------------------------------------------------//
            //             IF PLAYER IS FACING LEFT             //
            //--------------------------------------------------//
            if(player.axis == AXIS_LEFT)
            {
                // WE GET THE AMOUNT OF PIXELS THE PLAYER WILL MOVE //
                s16 pos_x_offset = TABLE_JUMP_H_BW[G_INDEX_JUMP_H].pos_VALUE;
                
                //------------------------------------------------------//
                //         IF SCROLLING IS AT BEGINNING OF LEVEL        //
                //------------------------------------------------------//
                if(G_POS_X_CAMERA == 0)
                {
                    //--------------------------------------------------//
                    //           IF PLAYER REACHED LEFT LIMIT           //
                    //--------------------------------------------------//
                    if( (player.pos_X + pos_x_offset) < -19)
                    {
                        player.pos_X = -19;

                        pos_x_offset = 0;
                    }

                    //--------------------------------------------------//
                    //              ELSE PLAYER MOVES LEFT              //
                    //--------------------------------------------------//                        
                    else
                    {
                        player.pos_X += pos_x_offset;

                        pos_x_offset = 0;
                    }
                }


                //------------------------------------------------------//
                //  IF SCROLLING IS BETWEEN BEGINNING AND END OF LEVEL  //
                //------------------------------------------------------//
                else if(G_POS_X_CAMERA > 0 && G_POS_X_CAMERA < G_CAMERA_LIMIT)
                {
                    // WE CHECK COLLISIONS WITH ENEMIES //
                    for(i=0 ; i<4 ; i++)
                    {
                        // IF ENEMY EXISTS //
                        if(LIST_ENEMIES[i].spr_ENEMY != NULL)
                        {
                            // IF ENEMY IS FACING RIGHT //
                            if(LIST_ENEMIES[i].axis == AXIS_RIGHT)
                            {
                                // IF PLAYER HAS NOT YET COLLIDED WITH AN ENEMY //
                                if(player.pos_X > LIST_ENEMIES[i].pos_X + ENEMY_RIGHT_BOUND)
                                {
                                    // IF PLAYER COLLIDES WITH AN ENEMY //
                                    if(player.pos_X + pos_x_offset <= LIST_ENEMIES[i].pos_X + ENEMY_RIGHT_BOUND)
                                    {
                                        // WE CALCULE THE NEW AMOUNT OF PIXELS THE PLAYER WILL MOVE //
                                        pos_x_offset = player.pos_X + pos_x_offset - (LIST_ENEMIES[i].pos_X + ENEMY_RIGHT_BOUND);
                                    }
                                }

                                else
                                {
                                    pos_x_offset = 0;
                                }
                            }
                        }
                    }


                    // WE CALCULATE HOW MANY PIXELS THE CAMERA IS SUPPOSED TO MOVE //
                    s16 new_pos_x_camera = G_POS_X_CAMERA + pos_x_offset;


                    if(new_pos_x_camera < 0)
                    {                            
                        player.pos_X += new_pos_x_camera;

                        pos_x_offset -= new_pos_x_camera;
                    }
                }


                //------------------------------------------------------//
                //        IF SCROLLING HAS REACHED END OF LEVEL         //
                //------------------------------------------------------//
                else if(G_POS_X_CAMERA == G_CAMERA_LIMIT)
                {
                    if(player.pos_X > 98)
                    {
                        if(player.pos_X - pos_x_offset < 98)
                        {
                            pos_x_offset = player.pos_X - 98;

                            player.pos_X = 98;
                        }
                    }
                }
            
            
            

                //**************************************************//
                //                                                  //
                //                 UPDATE SCROLLING                 //
                //                                                  //
                //**************************************************//

                // POINTER DECLARATION //
                void (*ptr_SCROLLING_ROUTINE)(s16 increment);

                // SETTING POINTER TO SCROLLING FUNCTION //
                ptr_SCROLLING_ROUTINE = TABLE_SCROLLING_ROUTINE[G_LEVEL - 1];

                // RUNNING SCROLLING FUNCTION //
                (*ptr_SCROLLING_ROUTINE)(pos_x_offset);




                // UPDATE WEAPON POSITION //
                update_WEAPON(-pos_x_offset);




                //**************************************************//
                //                                                  //
                //              UPDATE ENEMIES POSITION             //
                //                                                  //
                //**************************************************//

                for(i=0 ; i<4 ; i++)
                {
                    if(LIST_ENEMIES[i].spr_ENEMY != NULL)
                    {
                        LIST_ENEMIES[i].pos_X -= pos_x_offset;

                        SPR_setPosition(LIST_ENEMIES[i].spr_ENEMY , LIST_ENEMIES[i].pos_X , LIST_ENEMIES[i].pos_Y);
                    }
                }
            }


            //--------------------------------------------------//
            //             IF PLAYER IS FACING RIGHT            //
            //--------------------------------------------------//
            else if(player.axis == AXIS_RIGHT)
            {
                // WE GET THE AMOUNT OF PIXELS THE PLAYER WILL MOVE //
                s16 pos_x_offset = -TABLE_JUMP_H_BW[G_INDEX_JUMP_H].pos_VALUE;

                //------------------------------------------------------//
                //         IF SCROLLING IS AT BEGINNING OF LEVEL        //
                //------------------------------------------------------//
                if(G_POS_X_CAMERA == 0)
                {
                    //--------------------------------------------------//
                    //      IF PLAYER MOVES BEYOND MIDDLE OF SCREEN     //
                    //--------------------------------------------------//
                    if( (player.pos_X + pos_x_offset) > 98)
                    {
                        pos_x_offset = (player.pos_X + pos_x_offset - 98);

                        player.pos_X = 98;
                    }

                    //--------------------------------------------------//
                    //              ELSE PLAYER MOVES RIGHT             //
                    //--------------------------------------------------//                        
                    else
                    {
                        player.pos_X += pos_x_offset;

                        pos_x_offset = 0;
                    }
                }                    
            

                //------------------------------------------------------//
                //  IF SCROLLING IS BETWEEN BEGINNING AND END OF LEVEL  //
                //------------------------------------------------------//
                else if(G_POS_X_CAMERA > 0 && G_POS_X_CAMERA < G_CAMERA_LIMIT)
                {
                    // WE CHECK COLLISIONS WITH ENEMIES //
                    for(i=0 ; i<4 ; i++)
                    {
                        // IF ENEMY EXISTS //
                        if(LIST_ENEMIES[i].spr_ENEMY != NULL)
                        {
                            // IF ENEMY IS FACING LEFT //
                            if(LIST_ENEMIES[i].axis == AXIS_LEFT)
                            {
                                // IF PLAYER HAS NOT YET COLLIDED WITH AN ENEMY //
                                if(player.pos_X < LIST_ENEMIES[i].pos_X - ENEMY_LEFT_BOUND) // + ENEMY_LEFT_BOUND
                                {
                                    // IF PLAYER COLLIDES WITH AN ENEMY //
                                    if(player.pos_X + pos_x_offset >= LIST_ENEMIES[i].pos_X - ENEMY_LEFT_BOUND) // + ENEMY_LEFT_BOUND
                                    {
                                        // WE CALCULE THE NEW AMOUNT OF PIXELS THE PLAYER WILL MOVE //
                                        pos_x_offset = player.pos_X + pos_x_offset - (LIST_ENEMIES[i].pos_X - ENEMY_LEFT_BOUND); // + ENEMY_LEFT_BOUND
                                    }
                                }

                                else
                                {
                                    pos_x_offset = 0;
                                }
                            }
                        }
                    }


                    // WE CALCULATE HOW MANY PIXELS THE CAMERA IS SUPPOSED TO MOVE //
                    s16 new_pos_x_camera = G_POS_X_CAMERA + pos_x_offset;


                    if(new_pos_x_camera > G_CAMERA_LIMIT)
                    {                            
                        player.pos_X += (new_pos_x_camera - G_CAMERA_LIMIT);

                        pos_x_offset -= (new_pos_x_camera - G_CAMERA_LIMIT);
                    }
                }


                //------------------------------------------------------//
                //        IF SCROLLING HAS REACHED END OF LEVEL         //
                //------------------------------------------------------//
                else if(G_POS_X_CAMERA == G_CAMERA_LIMIT)
                {
                    //VDP_drawIntEx_WINDOW_QUEUE_PRIO(99, 1 , 0 , 0, PAL3);
                    // WE CHECK COLLISIONS WITH ENEMIES //
                    for(i=0 ; i<4 ; i++)
                    {
                        // IF ENEMY EXISTS //
                        if(LIST_ENEMIES[i].spr_ENEMY != NULL)
                        {
                            // IF ENEMY IS FACING LEFT //
                            if(LIST_ENEMIES[i].axis == AXIS_LEFT)
                            {
                                // IF PLAYER HAS NOT YET COLLIDED WITH AN ENEMY //
                                if(player.pos_X <= LIST_ENEMIES[i].pos_X + ENEMY_LEFT_BOUND)
                                {
                                    // IF PLAYER COLLIDES WITH AN ENEMY //
                                    if(player.pos_X + pos_x_offset > LIST_ENEMIES[i].pos_X + ENEMY_LEFT_BOUND)
                                    {
                                        // WE CALCULE THE NEW AMOUNT OF PIXELS THE PLAYER WILL MOVE //
                                        pos_x_offset = player.pos_X + pos_x_offset - (LIST_ENEMIES[i].pos_X + ENEMY_LEFT_BOUND);
                                    }
                                }
                            }
                        }
                    }

                    if(player.pos_X + pos_x_offset > G_LEVEL_LIMIT)
                    {
                        player.pos_X = G_LEVEL_LIMIT;
                    }

                    else
                    {
                        player.pos_X += pos_x_offset;
                    }

                    pos_x_offset = 0;
                }




                //**************************************************//
                //                                                  //
                //                 UPDATE SCROLLING                 //
                //                                                  //
                //**************************************************//

                // POINTER DECLARATION //
                void (*ptr_SCROLLING_ROUTINE)(s16 increment);

                // SETTING POINTER TO SCROLLING FUNCTION //
                ptr_SCROLLING_ROUTINE = TABLE_SCROLLING_ROUTINE[G_LEVEL - 1];

                // RUNNING SCROLLING FUNCTION //
                (*ptr_SCROLLING_ROUTINE)(pos_x_offset);




                // UPDATE WEAPON POSITION //
                update_WEAPON(-pos_x_offset);




                //**************************************************//
                //                                                  //
                //              UPDATE ENEMIES POSITION             //
                //                                                  //
                //**************************************************//

                for(i=0 ; i<4 ; i++)
                {
                    if(LIST_ENEMIES[i].spr_ENEMY != NULL)
                    {
                        LIST_ENEMIES[i].pos_X -= pos_x_offset;

                        SPR_setPosition(LIST_ENEMIES[i].spr_ENEMY , LIST_ENEMIES[i].pos_X , LIST_ENEMIES[i].pos_Y);
                    }
                }
            }




            G_INDEX_JUMP_H += 1;


            if(G_INDEX_JUMP_H > 30)
            {
                G_INDEX_JUMP_H = 30;
            }
        }




        //**************************************************//
        //                                                  //
        //          UPDATE PLAYER VERTICAL POSITION         //
        //                                                  //
        //**************************************************//

        if(player.counter_ANIM_V > 0)
        {
            //--------------------------------------------------//
            //                PLAYER GOING UPWARD               //
            //--------------------------------------------------//
            if(player.counter_ANIM_V <= JUMP_HIGH_POINT)
            {
                G_GRAVITY -= FIX32(0.2);
            }

            //--------------------------------------------------//
            //               PLAYER GOING DOWNWARD              //
            //--------------------------------------------------//
            else
            {
                G_GRAVITY -= FIX32(0.274);
            }


            player.pos_Y -= fix32ToInt(G_GRAVITY);

            
            //--------------------------------------------------//
            //           IF PLAYER TOUCHES THE GROUND           //
            //--------------------------------------------------//
            if(player.pos_Y >= G_GROUND_POSITION)
            {                
                player.pos_Y = G_GROUND_POSITION;

                SPR_setPosition(player.spr_PLAYER,player.pos_X,player.pos_Y);


                G_JUMP_KICK = NO_JUMP_KICK;

                G_JUMP_PUNCH = NO_JUMP_PUNCH;

                player.counter_ANIM_SPRITE = 0;


                u16 value=JOY_readJoypad(JOY_1);

                if(value & BUTTON_LEFT || value & BUTTON_RIGHT)
                {
                    player.state = STATE_WALK;

                    player.vulnerable = TRUE;

                    SPR_setAnimAndFrame(player.spr_PLAYER,0,0);
                }

                else if((value & BUTTON_DIR) == 0)
                {
                    player.state = STATE_IDLE;

                    player.vulnerable = TRUE;

                    if(player.armed == TRUE)
                    {
                        if(player.axis == AXIS_RIGHT)
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X + 40,player.pos_Y + 20);

                            SPR_setHFlip(sprite_NUNCHUK,FALSE);
                        }

                        else
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X,player.pos_Y + 20);

                            SPR_setHFlip(sprite_NUNCHUK,TRUE);
                        }

                        SPR_setFrame(sprite_NUNCHUK,0);

                        SPR_setAnimAndFrame(player.spr_PLAYER,14,0);
                    }

                    else
                    {
                        SPR_setAnimAndFrame(player.spr_PLAYER,0,0);
                    }
                }

                return;
            }
        }




        //**************************************************//
        //                                                  //
        //               UPDATE PLAYER SPRITE               //
        //                                                  //
        //**************************************************//

        SPR_setPosition(player.spr_PLAYER,player.pos_X,player.pos_Y);




        //**************************************************//
        //                                                  //
        //            UPDATE PLAYER SPRITE FRAME            //
        //                                                  //
        //**************************************************//

        // IF PLAYER HAS NOT PRESSED THE KICK BUTTON //
        if(G_JUMP_KICK == NO_JUMP_KICK)
        {
            // IF PLAYER HAS NOT PRESSED THE PUNCH BUTTON //
            if(G_JUMP_PUNCH == NO_JUMP_PUNCH)
            {
                // WE PLAY THE REGULAR JUMP ANIMATION //
                if(player.counter_ANIM_V == 0)
                {
                    SPR_setAnim(player.spr_PLAYER,11);
                    SPR_setFrame(player.spr_PLAYER,1);
                }

                else if(player.counter_ANIM_V == 5)
                {
                    SPR_setAnim(player.spr_PLAYER,11);
                    SPR_setFrame(player.spr_PLAYER,2);
                }

                else if(player.counter_ANIM_V == JUMP_KICK_COLL_START)
                {
                    SPR_setAnim(player.spr_PLAYER,11);
                    SPR_setFrame(player.spr_PLAYER,3);
                }

                else if(player.counter_ANIM_V == JUMP_KICK_COLL_END)
                {
                    SPR_setAnim(player.spr_PLAYER,11);
                    SPR_setFrame(player.spr_PLAYER,2);
                }

                else if(player.counter_ANIM_V == 24)
                {
                    SPR_setAnim(player.spr_PLAYER,11);
                    SPR_setFrame(player.spr_PLAYER,1);
                }
            }

            // IF PLAYER HAS PRESSED THE PUNCH BUTTON //
            else
            {
                if(player.armed == TRUE)
                {
                    if(player.counter_ANIM_V == 0)
                    {
                        SPR_setAnim(player.spr_PLAYER,11);
                        SPR_setFrame(player.spr_PLAYER,1);
                    }

                    else if(player.counter_ANIM_V == 5)
                    {
                        SPR_setAnim(player.spr_PLAYER,11);
                        SPR_setFrame(player.spr_PLAYER,2);
                    }

                    else if(player.counter_ANIM_V == 7)
                    {
                        SPR_setAnim(player.spr_PLAYER,16);
                        SPR_setFrame(player.spr_PLAYER,0);

                        if(player.axis == AXIS_RIGHT)
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X + 39, player.pos_Y + 11);

                            SPR_setHFlip(sprite_NUNCHUK,FALSE);
                        }

                        else
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X, player.pos_Y + 11);

                            SPR_setHFlip(sprite_NUNCHUK,TRUE);
                        }
                    }

                    else if(player.counter_ANIM_V == 8)
                    {
                        SPR_setAnim(player.spr_PLAYER,16);
                        SPR_setFrame(player.spr_PLAYER,1);

                        SPR_setFrame(sprite_NUNCHUK,1);

                        if(player.axis == AXIS_RIGHT)
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X + 40, player.pos_Y + 9);

                            SPR_setHFlip(sprite_NUNCHUK,FALSE);
                        }

                        else
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X, player.pos_Y + 9);

                            SPR_setHFlip(sprite_NUNCHUK,TRUE);
                        }
                    }

                    else if(player.counter_ANIM_V == 9)
                    {
                        SPR_setAnim(player.spr_PLAYER,16);
                        SPR_setFrame(player.spr_PLAYER,1);

                        SPR_setFrame(sprite_NUNCHUK,1);

                        if(player.axis == AXIS_RIGHT)
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X + 40, player.pos_Y + 9);

                            SPR_setHFlip(sprite_NUNCHUK,FALSE);
                        }

                        else
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X, player.pos_Y + 9);

                            SPR_setHFlip(sprite_NUNCHUK,TRUE);
                        }
                    }

                    else if(player.counter_ANIM_V >= 10 && player.counter_ANIM_V < 12)
                    {
                        SPR_setAnim(player.spr_PLAYER,16);
                        SPR_setFrame(player.spr_PLAYER,2);

                        SPR_setFrame(sprite_NUNCHUK,2);

                        if(player.axis == AXIS_RIGHT)
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X + 56, player.pos_Y);

                            SPR_setHFlip(sprite_NUNCHUK,FALSE);
                        }

                        else
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X - 16, player.pos_Y);

                            SPR_setHFlip(sprite_NUNCHUK,TRUE);
                        }
                    }

                    else if(player.counter_ANIM_V >= 12 && player.counter_ANIM_V < 14)
                    {
                        SPR_setAnim(player.spr_PLAYER,16);
                        SPR_setFrame(player.spr_PLAYER,2);

                        SPR_setFrame(sprite_NUNCHUK,3);

                        if(player.axis == AXIS_RIGHT)
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X + 57, player.pos_Y + 1);

                            SPR_setHFlip(sprite_NUNCHUK,FALSE);
                        }

                        else
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X - 17, player.pos_Y + 1);

                            SPR_setHFlip(sprite_NUNCHUK,TRUE);
                        }
                    }

                    else if(player.counter_ANIM_V >= 14 && player.counter_ANIM_V < 16)
                    {
                        SPR_setAnim(player.spr_PLAYER,16);
                        SPR_setFrame(player.spr_PLAYER,2);

                        SPR_setFrame(sprite_NUNCHUK,4);

                        if(player.axis == AXIS_RIGHT)
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X + 57, player.pos_Y + 21);

                            SPR_setHFlip(sprite_NUNCHUK,FALSE);
                        }

                        else
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X - 17, player.pos_Y + 21);

                            SPR_setHFlip(sprite_NUNCHUK,TRUE);
                        }
                    }

                    else if(player.counter_ANIM_V == 16)
                    {
                        SPR_setAnim(player.spr_PLAYER,16);
                        SPR_setFrame(player.spr_PLAYER,3);

                        SPR_setFrame(sprite_NUNCHUK,5);

                        if(player.axis == AXIS_RIGHT)
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X + 49, player.pos_Y + 23);

                            SPR_setHFlip(sprite_NUNCHUK,FALSE);
                        }

                        else
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X - 9, player.pos_Y + 23);

                            SPR_setHFlip(sprite_NUNCHUK,TRUE);
                        }
                    }

                    else if(player.counter_ANIM_V >= 17 && player.counter_ANIM_V < 19)
                    {
                        SPR_setFrame(sprite_NUNCHUK,6);
                        
                        if(player.axis == AXIS_RIGHT)
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X + 46, player.pos_Y + 26);

                            SPR_setHFlip(sprite_NUNCHUK,FALSE);
                        }

                        else
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X - 6, player.pos_Y + 26);

                            SPR_setHFlip(sprite_NUNCHUK,TRUE);
                        }
                    }

                    else if(player.counter_ANIM_V == 19)
                    {
                        SPR_setAnim(player.spr_PLAYER,11);
                        SPR_setFrame(player.spr_PLAYER,2);

                        SPR_setPosition(sprite_NUNCHUK,0, -32);
                    }

                    else if(player.counter_ANIM_V == 24)
                    {
                        SPR_setFrame(player.spr_PLAYER,1);
                    }
                }

                else
                {
                    if(player.counter_ANIM_V == 0)
                    {
                        SPR_setAnim(player.spr_PLAYER,11);
                        SPR_setFrame(player.spr_PLAYER,1);
                    }

                    else if(player.counter_ANIM_V == 5)
                    {
                        SPR_setAnim(player.spr_PLAYER,11);
                        SPR_setFrame(player.spr_PLAYER,2);
                    }

                    else if(player.counter_ANIM_V == 11)
                    {
                        SPR_setAnim(player.spr_PLAYER,13);
                        SPR_setFrame(player.spr_PLAYER,0);
                    }

                    else if(player.counter_ANIM_V == 13)
                    {
                        SPR_setAnim(player.spr_PLAYER,13);
                        SPR_setFrame(player.spr_PLAYER,1);
                    }

                    else if(player.counter_ANIM_V == 20)
                    {
                        SPR_setAnim(player.spr_PLAYER,11);
                        SPR_setFrame(player.spr_PLAYER,2);
                    }

                    else if(player.counter_ANIM_V == 24)
                    {
                        SPR_setAnim(player.spr_PLAYER,11);
                        SPR_setFrame(player.spr_PLAYER,1);
                    }
                }
            }
        }


        //--------------------------------------------------//
        //           UPDATE JUMP KICK SPRITE FRAME          //
        //--------------------------------------------------//

        // IF PLAYER HAS PRESSED THE KICK BUTTON //
        else
        {
            if(player.counter_ANIM_V >= JUMP_KICK_COLL_START && player.counter_ANIM_V <= JUMP_HIGH_POINT)
            {
                SPR_setAnim(player.spr_PLAYER,12);
                SPR_setFrame(player.spr_PLAYER,0);
            }

            else if(player.counter_ANIM_V == JUMP_KICK_COLL_END)
            {
                SPR_setAnim(player.spr_PLAYER,12);
                SPR_setFrame(player.spr_PLAYER,1);

                G_JUMP_KICK = NO_JUMP_KICK;
            }

            else if(player.counter_ANIM_V == 24)
            {
                SPR_setAnim(player.spr_PLAYER,11);
                SPR_setFrame(player.spr_PLAYER,1);
            }
        }


        //---------------------------------------------------------------//
        // IF PLAYER HAS REACHED THE HIGHEST POSITION IN JUMP (FRAME 15) //
        // IF PLAYER HAS HIT AN ENNEMY (G_JUMP_KICK = JUMP_KICK_HIT      //
        // PLAYER GOES TO STATE_JUMP_KICK_BW                             //
        //---------------------------------------------------------------//

        if(player.counter_ANIM_V > JUMP_HIGH_POINT)
        {
            if(G_JUMP_KICK == JUMP_KICK_HIT)
            {
                player.counter_ANIM_SPRITE  = 0;
                
                player.counter_ANIM_V       = 0;
                player.counter_ANIM_H       = 0;

                G_INDEX_JUMP_V              = 0;
                G_INDEX_JUMP_H              = 0;

                G_GRAVITY                   = FIX32(3.34L);//4L

                player.state = STATE_JUMP_KICK_BW;

                player.vulnerable = TRUE;

                return;
            }
        }


        player.counter_ANIM_V += 1;
        player.counter_ANIM_H += 1;
    }


    else if(player.state == STATE_JUMP_KICK_BW)
    {
        //**************************************************//
        //                                                  //
        //         UPDATE PLAYER HORIZONTAL POSITION        //
        //                                                  //
        //**************************************************//

        if(player.counter_ANIM_H == TABLE_JUMP_H_BW[G_INDEX_JUMP_H].frame)
        {
            u8 i;
            

            //--------------------------------------------------//
            //             IF PLAYER IS FACING RIGHT            //
            //--------------------------------------------------//
            if(player.axis == AXIS_RIGHT)
            {
                // WE GET THE AMOUNT OF PIXELS THE PLAYER WILL MOVE //
                s16 pos_x_offset = TABLE_JUMP_H_BW[G_INDEX_JUMP_H].pos_VALUE;
                
                //------------------------------------------------------//
                //         IF SCROLLING IS AT BEGINNING OF LEVEL        //
                //------------------------------------------------------//
                if(G_POS_X_CAMERA == 0)
                {
                    //--------------------------------------------------//
                    //           IF PLAYER REACHED LEFT LIMIT           //
                    //--------------------------------------------------//
                    if( (player.pos_X + pos_x_offset) < -19)
                    {
                        player.pos_X = -19;

                        pos_x_offset = 0;
                    }

                    //--------------------------------------------------//
                    //              ELSE PLAYER MOVES LEFT              //
                    //--------------------------------------------------//                        
                    else
                    {
                        player.pos_X += pos_x_offset;

                        pos_x_offset = 0;
                    }
                }


                //------------------------------------------------------//
                //  IF SCROLLING IS BETWEEN BEGINNING AND END OF LEVEL  //
                //------------------------------------------------------//
                else if(G_POS_X_CAMERA > 0 && G_POS_X_CAMERA < G_CAMERA_LIMIT)
                {
                    // WE CHECK COLLISIONS WITH ENEMIES //
                    for(i=0 ; i<4 ; i++)
                    {
                        // IF ENEMY EXISTS //
                        if(LIST_ENEMIES[i].spr_ENEMY != NULL)
                        {
                            // IF ENEMY IS FACING RIGHT //
                            if(LIST_ENEMIES[i].axis == AXIS_RIGHT)
                            {
                                // IF PLAYER HAS NOT YET COLLIDED WITH AN ENEMY //
                                if(player.pos_X > LIST_ENEMIES[i].pos_X + ENEMY_RIGHT_BOUND)
                                {
                                    // IF PLAYER COLLIDES WITH AN ENEMY //
                                    if(player.pos_X + pos_x_offset <= LIST_ENEMIES[i].pos_X + ENEMY_RIGHT_BOUND)
                                    {
                                        // WE CALCULE THE NEW AMOUNT OF PIXELS THE PLAYER WILL MOVE //
                                        pos_x_offset = player.pos_X + pos_x_offset - (LIST_ENEMIES[i].pos_X + ENEMY_RIGHT_BOUND);
                                    }
                                }

                                else
                                {
                                    pos_x_offset = 0;
                                }
                            }
                        }
                    }


                    // WE CALCULATE HOW MANY PIXELS THE CAMERA IS SUPPOSED TO MOVE //
                    s16 new_pos_x_camera = G_POS_X_CAMERA + pos_x_offset;


                    if(new_pos_x_camera < 0)
                    {                            
                        player.pos_X += new_pos_x_camera;

                        pos_x_offset -= new_pos_x_camera;
                    }
                }


                //------------------------------------------------------//
                //        IF SCROLLING HAS REACHED END OF LEVEL         //
                //------------------------------------------------------//
                else if(G_POS_X_CAMERA == G_CAMERA_LIMIT)
                {
                    if(player.pos_X > 98)
                    {
                        if(player.pos_X - pos_x_offset < 98)
                        {
                            pos_x_offset = player.pos_X - 98;

                            player.pos_X = 98;
                        }
                    }

                    // POINTER DECLARATION //
                    /*void (*ptr_SCROLLING_ROUTINE)(s16 increment);

                    // SETTING POINTER TO SCROLLING FUNCTION //
                    ptr_SCROLLING_ROUTINE = TABLE_SCROLLING_ROUTINE[G_LEVEL - 1];

                    // RUNNING SCROLLING FUNCTION //
                    (*ptr_SCROLLING_ROUTINE)(pos_x_offset);*/
                }
            
            
            

                //**************************************************//
                //                                                  //
                //                 UPDATE SCROLLING                 //
                //                                                  //
                //**************************************************//

                // POINTER DECLARATION //
                void (*ptr_SCROLLING_ROUTINE)(s16 increment);

                // SETTING POINTER TO SCROLLING FUNCTION //
                ptr_SCROLLING_ROUTINE = TABLE_SCROLLING_ROUTINE[G_LEVEL - 1];

                // RUNNING SCROLLING FUNCTION //
                (*ptr_SCROLLING_ROUTINE)(pos_x_offset);




                // UPDATE WEAPON POSITION //
                update_WEAPON(-pos_x_offset);




                //**************************************************//
                //                                                  //
                //              UPDATE ENEMIES POSITION             //
                //                                                  //
                //**************************************************//

                for(i=0 ; i<4 ; i++)
                {
                    if(LIST_ENEMIES[i].spr_ENEMY != NULL)
                    {
                        LIST_ENEMIES[i].pos_X -= pos_x_offset;

                        SPR_setPosition(LIST_ENEMIES[i].spr_ENEMY , LIST_ENEMIES[i].pos_X , LIST_ENEMIES[i].pos_Y);
                    }
                }            
            }


            //--------------------------------------------------//
            //             IF PLAYER IS FACING LEFT             //
            //--------------------------------------------------//
            else if(player.axis == AXIS_LEFT)
            {
                // WE GET THE AMOUNT OF PIXELS THE PLAYER WILL MOVE //
                s16 pos_x_offset = -TABLE_JUMP_H_BW[G_INDEX_JUMP_H].pos_VALUE;

                //------------------------------------------------------//
                //         IF SCROLLING IS AT BEGINNING OF LEVEL        //
                //------------------------------------------------------//
                if(G_POS_X_CAMERA == 0)
                {
                    //--------------------------------------------------//
                    //      IF PLAYER MOVES BEYOND MIDDLE OF SCREEN     //
                    //--------------------------------------------------//
                    if( (player.pos_X + pos_x_offset) > 98)
                    {
                        pos_x_offset = (player.pos_X + pos_x_offset - 98);

                        player.pos_X = 98;
                    }

                    //--------------------------------------------------//
                    //              ELSE PLAYER MOVES RIGHT             //
                    //--------------------------------------------------//                        
                    else
                    {
                        player.pos_X += pos_x_offset;

                        pos_x_offset = 0;
                    }
                }                    
            

                //------------------------------------------------------//
                //  IF SCROLLING IS BETWEEN BEGINNING AND END OF LEVEL  //
                //------------------------------------------------------//
                else if(G_POS_X_CAMERA > 0 && G_POS_X_CAMERA < G_CAMERA_LIMIT)
                {
                    // WE CHECK COLLISIONS WITH ENEMIES //
                    for(i=0 ; i<4 ; i++)
                    {
                        // IF ENEMY EXISTS //
                        if(LIST_ENEMIES[i].spr_ENEMY != NULL)
                        {
                            // IF ENEMY IS FACING LEFT //
                            if(LIST_ENEMIES[i].axis == AXIS_LEFT)
                            {
                                // IF PLAYER HAS NOT YET COLLIDED WITH AN ENEMY //
                                if(player.pos_X < LIST_ENEMIES[i].pos_X - ENEMY_LEFT_BOUND)
                                {
                                    // IF PLAYER COLLIDES WITH AN ENEMY //
                                    if(player.pos_X + pos_x_offset >= LIST_ENEMIES[i].pos_X - ENEMY_LEFT_BOUND)
                                    {
                                        // WE CALCULE THE NEW AMOUNT OF PIXELS THE PLAYER WILL MOVE //
                                        pos_x_offset = player.pos_X + pos_x_offset - (LIST_ENEMIES[i].pos_X - ENEMY_LEFT_BOUND);
                                    }
                                }

                                else
                                {
                                    pos_x_offset = 0;
                                }
                            }                          
                        }
                    }


                    // WE CALCULATE HOW MANY PIXELS THE CAMERA IS SUPPOSED TO MOVE //
                    s16 new_pos_x_camera = G_POS_X_CAMERA + pos_x_offset;


                    if(new_pos_x_camera > G_CAMERA_LIMIT)
                    {                            
                        player.pos_X += (new_pos_x_camera - G_CAMERA_LIMIT);

                        pos_x_offset -= (new_pos_x_camera - G_CAMERA_LIMIT);
                    }
                }


                //------------------------------------------------------//
                //        IF SCROLLING HAS REACHED END OF LEVEL         //
                //------------------------------------------------------//
                else if(G_POS_X_CAMERA == G_CAMERA_LIMIT)
                {
                    //VDP_drawIntEx_WINDOW_QUEUE_PRIO(99, 1 , 0 , 0, PAL3);
                    // WE CHECK COLLISIONS WITH ENEMIES //
                    for(i=0 ; i<4 ; i++)
                    {
                        // IF ENEMY EXISTS //
                        if(LIST_ENEMIES[i].spr_ENEMY != NULL)
                        {
                            // IF ENEMY IS FACING LEFT //
                            if(LIST_ENEMIES[i].axis == AXIS_LEFT)
                            {
                                // IF PLAYER HAS NOT YET COLLIDED WITH AN ENEMY //
                                if(player.pos_X < LIST_ENEMIES[i].pos_X - ENEMY_LEFT_BOUND)
                                {
                                    // IF PLAYER COLLIDES WITH AN ENEMY //
                                    if(player.pos_X + pos_x_offset >= LIST_ENEMIES[i].pos_X - ENEMY_LEFT_BOUND)
                                    {
                                        // WE CALCULE THE NEW AMOUNT OF PIXELS THE PLAYER WILL MOVE //
                                        pos_x_offset = player.pos_X + pos_x_offset - (LIST_ENEMIES[i].pos_X - ENEMY_LEFT_BOUND);
                                    }
                                }
                            }
                        }
                    }

                    if(player.pos_X + pos_x_offset > G_LEVEL_LIMIT)
                    {
                        player.pos_X = G_LEVEL_LIMIT;
                    }

                    else
                    {
                        player.pos_X += pos_x_offset;
                    }

                    pos_x_offset = 0;
                }




                //**************************************************//
                //                                                  //
                //                 UPDATE SCROLLING                 //
                //                                                  //
                //**************************************************//

                // POINTER DECLARATION //
                void (*ptr_SCROLLING_ROUTINE)(s16 increment);

                // SETTING POINTER TO SCROLLING FUNCTION //
                ptr_SCROLLING_ROUTINE = TABLE_SCROLLING_ROUTINE[G_LEVEL - 1];

                // RUNNING SCROLLING FUNCTION //
                (*ptr_SCROLLING_ROUTINE)(pos_x_offset);



                // UPDATE WEAPON POSITION //
                update_WEAPON(-pos_x_offset);




                //**************************************************//
                //                                                  //
                //              UPDATE ENEMIES POSITION             //
                //                                                  //
                //**************************************************//

                for(i=0 ; i<4 ; i++)
                {
                    if(LIST_ENEMIES[i].spr_ENEMY != NULL)
                    {
                        LIST_ENEMIES[i].pos_X -= pos_x_offset;

                        SPR_setPosition(LIST_ENEMIES[i].spr_ENEMY , LIST_ENEMIES[i].pos_X , LIST_ENEMIES[i].pos_Y);
                    }
                }
            }




            G_INDEX_JUMP_H += 1;


            if(G_INDEX_JUMP_H > 26)
            {
                G_INDEX_JUMP_H = 26;
            }
        }




        //**************************************************//
        //                                                  //
        //          UPDATE PLAYER VERTICAL POSITION         //
        //                                                  //
        //**************************************************//

        if(player.counter_ANIM_V < 5)
        {
            G_GRAVITY -= FIX32(0.4);
        }

        else
        {
            G_GRAVITY -= FIX32(0.2);
        }

        player.pos_Y -= fix32ToInt(G_GRAVITY);


        //--------------------------------------------------//
        //           IF PLAYER TOUCHES THE GROUND           //
        //--------------------------------------------------//
        if(player.pos_Y >= G_GROUND_POSITION)
        {
            player.pos_Y = G_GROUND_POSITION;

            SPR_setPosition(player.spr_PLAYER,player.pos_X,player.pos_Y);


            G_JUMP_KICK = NO_JUMP_KICK;

            G_JUMP_PUNCH = NO_JUMP_PUNCH;

            player.counter_ANIM_SPRITE = 0;

            
            u16 value=JOY_readJoypad(JOY_1);

            if(value & BUTTON_LEFT || value & BUTTON_RIGHT)
            {
                player.state = STATE_WALK;

                player.vulnerable = TRUE;

                SPR_setAnimAndFrame(player.spr_PLAYER,0,0);
            }

            else if((value & BUTTON_DIR) == 0)
            {
                player.state = STATE_IDLE;

                player.vulnerable = TRUE;

                if(player.armed == TRUE)
                {
                    if(player.axis == AXIS_RIGHT)
                    {
                        SPR_setPosition(sprite_NUNCHUK,player.pos_X + 40,player.pos_Y + 20);

                        SPR_setHFlip(sprite_NUNCHUK,FALSE);
                    }

                    else
                    {
                        SPR_setPosition(sprite_NUNCHUK,player.pos_X,player.pos_Y + 20);

                        SPR_setHFlip(sprite_NUNCHUK,TRUE);
                    }

                    SPR_setFrame(sprite_NUNCHUK,0);

                    SPR_setAnimAndFrame(player.spr_PLAYER,14,0);
                }

                else
                {
                    SPR_setAnimAndFrame(player.spr_PLAYER,0,0);
                }
            }

            return;
        }




        //**************************************************//
        //                                                  //
        //               UPDATE PLAYER SPRITE               //
        //                                                  //
        //**************************************************//

        SPR_setPosition(player.spr_PLAYER,player.pos_X,player.pos_Y);




        //**************************************************//
        //                                                  //
        //            UPDATE PLAYER SPRITE FRAME            //
        //                                                  //
        //**************************************************//

        if(player.counter_ANIM_V == 0)
        {
            SPR_setAnim(player.spr_PLAYER,11);
            SPR_setFrame(player.spr_PLAYER,2);
        }

        else if(player.counter_ANIM_V == 5)
        {
            SPR_setFrame(player.spr_PLAYER,3);
        }

        else if(player.counter_ANIM_V == 13)
        {
            SPR_setFrame(player.spr_PLAYER,2);
        }

        else if(player.counter_ANIM_V == 17)
        {
            SPR_setFrame(player.spr_PLAYER,1);
        }




        player.counter_ANIM_V += 1;
        player.counter_ANIM_H += 1;
    }


    else if(player.state == STATE_HIT_UP)
    {
        if(player.pos_Y < G_GROUND_POSITION)
        {
            player.pos_Y += 1;

            SPR_setPosition(player.spr_PLAYER,player.pos_X,player.pos_Y);
        }
        
        
        
        if(player.counter_ANIM_SPRITE == 0)
        {
            SPR_setAnimAndFrame(player.spr_PLAYER,8,0);
        }

        else if(player.counter_ANIM_SPRITE == 8)
        {
            if(player.pos_Y == G_GROUND_POSITION)
            {
                u16 value=JOY_readJoypad(JOY_1);


                if(value & BUTTON_LEFT || value & BUTTON_RIGHT)
                {
                    player.state = STATE_WALK;

                    player.vulnerable = TRUE;

                    SPR_setAnimAndFrame(player.spr_PLAYER,0,0);
                }

                else if((value & BUTTON_DIR) == 0)
                {
                    player.state = STATE_IDLE;

                    player.vulnerable = TRUE;

                    if(player.armed == TRUE)
                    {
                        if(player.axis == AXIS_RIGHT)
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X + 40,player.pos_Y + 20);

                            SPR_setHFlip(sprite_NUNCHUK,FALSE);
                        }

                        else
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X,player.pos_Y + 20);

                            SPR_setHFlip(sprite_NUNCHUK,TRUE);
                        }

                        SPR_setFrame(sprite_NUNCHUK,0);

                        SPR_setAnimAndFrame(player.spr_PLAYER,14,0);
                    }

                    else
                    {
                        SPR_setAnimAndFrame(player.spr_PLAYER,0,0);
                    }
                }

                else if((value & BUTTON_DIR) == BUTTON_DOWN)
                {
                    if(player.armed == TRUE)
                    {
                        SPR_setAnimAndFrame(player.spr_PLAYER,15,0);

                        if(player.axis == AXIS_RIGHT)
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X + 42,player.pos_Y + 36);

                            SPR_setHFlip(sprite_NUNCHUK,FALSE);
                        }

                        else
                        {
                            SPR_setPosition(sprite_NUNCHUK,player.pos_X - 2,player.pos_Y + 36);

                            SPR_setHFlip(sprite_NUNCHUK,TRUE);
                        }
                    }

                    else
                    {
                        SPR_setAnimAndFrame(player.spr_PLAYER,3,0);
                    }

                    player.state = STATE_CROUCH;

                    player.vulnerable = TRUE;
                }

                player.counter_ANIM_SPRITE = 0;

                return;
            }
        }


        player.counter_ANIM_SPRITE += 1;

        if(player.counter_ANIM_SPRITE > 8)
        {
            player.counter_ANIM_SPRITE = 8;
        }
    }


    else if(player.state == STATE_HIT_DOWN)
    {
        if(player.counter_ANIM_SPRITE == 0)
        {
            SPR_setAnimAndFrame(player.spr_PLAYER,8,0);
        }

        else if(player.counter_ANIM_SPRITE == 8)
        {
            u16 value=JOY_readJoypad(JOY_1);


            if(value & BUTTON_LEFT || value & BUTTON_RIGHT)
            {
                player.state = STATE_WALK;

                player.vulnerable = TRUE;

                SPR_setAnimAndFrame(player.spr_PLAYER,0,0);
            }

            else if((value & BUTTON_DIR) == 0)
            {
                player.state = STATE_IDLE;

                player.vulnerable = TRUE;

                if(player.armed == TRUE)
                {
                    if(player.axis == AXIS_RIGHT)
                    {
                        SPR_setPosition(sprite_NUNCHUK,player.pos_X + 40,player.pos_Y + 20);

                        SPR_setHFlip(sprite_NUNCHUK,FALSE);
                    }

                    else
                    {
                        SPR_setPosition(sprite_NUNCHUK,player.pos_X,player.pos_Y + 20);

                        SPR_setHFlip(sprite_NUNCHUK,TRUE);
                    }

                    SPR_setFrame(sprite_NUNCHUK,0);

                    SPR_setAnimAndFrame(player.spr_PLAYER,14,0);
                }
            }

            else if((value & BUTTON_DIR) == BUTTON_DOWN)
            {
                if(player.armed == TRUE)
                {
                    SPR_setAnimAndFrame(player.spr_PLAYER,15,0);

                    if(player.axis == AXIS_RIGHT)
                    {
                        SPR_setPosition(sprite_NUNCHUK,player.pos_X + 42,player.pos_Y + 36);

                        SPR_setHFlip(sprite_NUNCHUK,FALSE);
                    }

                    else
                    {
                        SPR_setPosition(sprite_NUNCHUK,player.pos_X - 2,player.pos_Y + 36);

                        SPR_setHFlip(sprite_NUNCHUK,TRUE);
                    }
                }

                else
                {
                    SPR_setAnimAndFrame(player.spr_PLAYER,3,0);
                }

                player.state = STATE_CROUCH;

                player.vulnerable = TRUE;
            }

            player.counter_ANIM_SPRITE = 0;

            return;
        }


        player.counter_ANIM_SPRITE += 1;

        if(player.counter_ANIM_SPRITE > 8)
        {
            player.counter_ANIM_SPRITE = 8;
        }
    }


    else if(player.state == STATE_GRAB)
    {
        /*fix32 total_grab = intToFix32(G_NUMBER_GRAB_LEFT + G_NUMBER_GRAB_RIGHT + G_NUMBER_GRAB_2_LEFT + G_NUMBER_GRAB_2_RIGHT);
        
        VDP_drawIntEx_WINDOW_QUEUE_PRIO(fix32ToInt(total_grab),1,0,0,PAL3);

        player.life -= fix32Mul(FIX32(0.5),total_grab);*/

        u8 total_grab = G_NUMBER_GRAB_LEFT + G_NUMBER_GRAB_RIGHT + G_NUMBER_GRAB_2_LEFT + G_NUMBER_GRAB_2_RIGHT;

        u8 i;

        for(i=0 ; i<total_grab ; i++)
        {
            player.life -= FIX32(0.5);
        }

        if(player.life < FIX32(0))
        {
            player.life = FIX32(0);
        }

        if(player.pos_Y + fix32ToInt(G_GRAVITY) < G_GROUND_POSITION)
        {
            G_GRAVITY += FIX32(0.5);

            SPR_setPosition(player.spr_PLAYER,player.pos_X,player.pos_Y += fix32ToInt(G_GRAVITY));
        }

        else
        {
            player.pos_Y = G_GROUND_POSITION;

            SPR_setPosition(player.spr_PLAYER,player.pos_X,player.pos_Y);
        }

        update_LIFE_PLAYER();
    }
}




inline static void collision_PLAYER_ATTACK()
{
    if(player.state == STATE_KICK || player.state == STATE_KICK_CROUCH)
    {
        // SETS AT WHAT ANIMATION FRAME THE COLLISION HAPPENS //
        // STATE_KICK_CROUCH : FRAME 0
        // STATE_KICK        : FRAME 5

        u8 attack_time = 0;

        if(player.state == STATE_KICK)
        {
            attack_time = 5;
        }
        

        // LOOP EVERY ENEMY //
        u8 i;

        for(i=0 ; i<4 ; i++)
        {
            // IF ENEMY EXISTS //
            if(LIST_ENEMIES[i].spr_ENEMY != NULL)
            {
                // IF ENEMY CAN BE HIT //
                if(LIST_ENEMIES[i].vulnerable == TRUE)
                {
                    // IF WE ARE WITHIN THE COLLISION FRAMES //
                    if(player.counter_ANIM_SPRITE >= attack_time && player.counter_ANIM_SPRITE < 12)
                    {
                        // IF PLAYER IS FACING RIGHT //
                        if(player.axis == AXIS_RIGHT)
                        {
                            // WE CHECK ONLY ENEMIES FACING LEFT //
                            if(LIST_ENEMIES[i].axis == AXIS_LEFT)
                            {
                                // WE DEFINE KICK COLLISION DISTANCE //
                                u16 distance = player.pos_X + 10 + PLAYER_KICK_MARGIN;
                                
                                // IF ENNEMY COLLIDES WHEN PLAYER RISES HIS LEG //
                                if( LIST_ENEMIES[i].pos_X <= distance && LIST_ENEMIES[i].pos_X >= distance - 32 )
                                {
                                    // WE RESET THE ANIMATION COUNTER //
                                    LIST_ENEMIES[i].counter_ANIM = 0;

                                    // ENEMY LOSES 1 LIFE POINT //
                                    LIST_ENEMIES[i].life -= 1;

                                    // IF ENEMY LIFE REACHES 0, HE'S DEAD //
                                    if(LIST_ENEMIES[i].life == 0)
                                    {
                                        LIST_ENEMIES[i].state = ENEMY_DEAD;

                                        LIST_ENEMIES[i].vulnerable = FALSE;

                                        G_POINTS += LIST_ENEMIES[i].points;

                                        update_SCORE();
                                    }

                                    else
                                    {
                                        // ENEMY IS HIT ON HEAD //
                                        if(player.state == STATE_KICK)
                                        {
                                            LIST_ENEMIES[i].state = ENEMY_HIT_UP_SLIDE;

                                            LIST_ENEMIES[i].vulnerable = FALSE;
                                        }

                                        // ENEMY IS HIT ON LEGS //
                                        else
                                        {
                                            LIST_ENEMIES[i].state = ENEMY_HIT_DOWN_SLIDE;

                                            LIST_ENEMIES[i].vulnerable = FALSE;
                                        }
                                    }

                                    XGM_startPlayPCM(SOUND_HIT_KICK,15,SOUND_PCM_CH2);
                                }
                            }
                        }


                        // IF PLAYER IS FACING LEFT //
                        else if(player.axis == AXIS_LEFT)
                        {
                            // WE CHECK ONLY ENEMIES FACING RIGHT //
                            if(LIST_ENEMIES[i].axis == AXIS_RIGHT)
                            {
                                // WE DEFINE KICK COLLISION DISTANCE //
                                u16 distance = player.pos_X - 26 - PLAYER_KICK_MARGIN;
                                
                                // IF ENNEMY COLLIDES WHEN PLAYER RISES HIS LEG //
                                if( LIST_ENEMIES[i].pos_X >= distance && LIST_ENEMIES[i].pos_X <= distance + 32 )
                                {
                                    // WE RESET THE ANIMATION COUNTER //
                                    LIST_ENEMIES[i].counter_ANIM = 0;

                                    // ENEMY LOSES 1 LIFE POINT //
                                    LIST_ENEMIES[i].life -= 1;

                                    // IF ENEMY LIFE REACHES 0, HE'S DEAD //
                                    if(LIST_ENEMIES[i].life == 0)
                                    {
                                        LIST_ENEMIES[i].state = ENEMY_DEAD;

                                        LIST_ENEMIES[i].vulnerable = FALSE;

                                        G_POINTS += LIST_ENEMIES[i].points;

                                        update_SCORE();
                                    }

                                    else
                                    {
                                        // ENEMY IS HIT ON HEAD //
                                        if(player.state == STATE_KICK)
                                        {
                                            LIST_ENEMIES[i].vulnerable = FALSE;
                                            
                                            LIST_ENEMIES[i].state = ENEMY_HIT_UP_SLIDE;
                                        }

                                        // ENEMY IS HIT ON LEGS //
                                        else
                                        {
                                            LIST_ENEMIES[i].vulnerable = FALSE;
                                            
                                            LIST_ENEMIES[i].state = ENEMY_HIT_DOWN_SLIDE;
                                        }
                                    }

                                    XGM_startPlayPCM(SOUND_HIT_KICK,15,SOUND_PCM_CH2);
                                }
                            }
                        }
                    }
                }
            }
        }
    }


    else if(player.state == STATE_PUNCH || player.state == STATE_PUNCH_CROUCH)
    {
        // LOOP EVERY ENEMY //
        u8 i;

        for(i=0 ; i<4 ; i++)
        {
            // IF ENEMY EXISTS //
            if(LIST_ENEMIES[i].spr_ENEMY != NULL)
            {
                // IF ENEMY IS NOT ALREADY DEAD //
                if(LIST_ENEMIES[i].vulnerable == TRUE)
                {
                    // IF WE REACHED COLLISION FRAME //
                    if(player.counter_ANIM_SPRITE > 5 && player.counter_ANIM_SPRITE < 13)
                    {
                        // IF PLAYER IS FACING RIGHT //
                        if(player.axis == AXIS_RIGHT)
                        {
                            // WE CHECK ONLY ENEMIES FACING LEFT //
                            if(LIST_ENEMIES[i].axis == AXIS_LEFT)
                            {
                                u16 distance = player.pos_X + 10 + PLAYER_PUNCH_MARGIN;
                                
                                if( LIST_ENEMIES[i].pos_X <= distance + (player.armed << 4) && LIST_ENEMIES[i].pos_X >= distance - 32 )
                                {
                                    LIST_ENEMIES[i].counter_ANIM = 0;


                                    LIST_ENEMIES[i].life -= 1;

                                    // IF ENEMY LIFE REACHES 0, HE'S DEAD //
                                    if(LIST_ENEMIES[i].life == 0)
                                    {
                                        LIST_ENEMIES[i].state = ENEMY_DEAD;

                                        LIST_ENEMIES[i].vulnerable = FALSE;

                                        G_POINTS += LIST_ENEMIES[i].points;

                                        update_SCORE();
                                    }

                                    else
                                    {
                                         // ENEMY IS HIT ON HEAD //
                                        if(player.state == STATE_PUNCH)
                                        {
                                            if(player.armed == FALSE)
                                            {
                                                LIST_ENEMIES[i].state = ENEMY_HIT_UP;
                                            }

                                            else
                                            {
                                                LIST_ENEMIES[i].state = ENEMY_HIT_UP_SLIDE;
                                            }

                                            LIST_ENEMIES[i].vulnerable = FALSE;
                                        }

                                        // ENEMY IS HIT ON LEGS //
                                        else
                                        {
                                            if(player.armed == FALSE)
                                            {
                                                LIST_ENEMIES[i].state = ENEMY_HIT_DOWN;
                                            }

                                            else
                                            {
                                                LIST_ENEMIES[i].state = ENEMY_HIT_UP_SLIDE;
                                            }

                                            LIST_ENEMIES[i].vulnerable = FALSE;
                                        }
                                    }

                                    XGM_startPlayPCM(SOUND_HIT_PUNCH,15,SOUND_PCM_CH2);
                                }
                            }
                        }


                        // IF PLAYER IS FACING LEFT //
                        else if(player.axis == AXIS_LEFT)
                        {
                            // WE CHECK ONLY ENEMIES FACING RIGHT //
                            if(LIST_ENEMIES[i].axis == AXIS_RIGHT)
                            {
                                u16 distance = player.pos_X - 26 - PLAYER_PUNCH_MARGIN;
                                
                                if( LIST_ENEMIES[i].pos_X >= distance - (player.armed << 4) && LIST_ENEMIES[i].pos_X <= distance + 32 )
                                {
                                    LIST_ENEMIES[i].counter_ANIM = 0;


                                    LIST_ENEMIES[i].life -= 1;

                                    // IF ENEMY LIFE REACHES 0, HE'S DEAD //
                                    if(LIST_ENEMIES[i].life == 0)
                                    {
                                        LIST_ENEMIES[i].state = ENEMY_DEAD;

                                        LIST_ENEMIES[i].vulnerable = FALSE;

                                        G_POINTS += LIST_ENEMIES[i].points;

                                        update_SCORE();
                                    }

                                    else
                                    {
                                        // ENEMY IS HIT ON HEAD //
                                        if(player.state == STATE_PUNCH)
                                        {
                                            if(player.armed == FALSE)
                                            {
                                                LIST_ENEMIES[i].state = ENEMY_HIT_UP;
                                            }

                                            else
                                            {
                                                LIST_ENEMIES[i].state = ENEMY_HIT_UP_SLIDE;
                                            }

                                            LIST_ENEMIES[i].vulnerable = FALSE;
                                        }

                                        // ENEMY IS HIT ON LEGS //
                                        else
                                        {
                                            if(player.armed == FALSE)
                                            {
                                                LIST_ENEMIES[i].state = ENEMY_HIT_DOWN;
                                            }

                                            else
                                            {
                                                LIST_ENEMIES[i].state = ENEMY_HIT_UP_SLIDE;
                                            }

                                            LIST_ENEMIES[i].vulnerable = FALSE;
                                        }
                                    }

                                    XGM_startPlayPCM(SOUND_HIT_PUNCH,15,SOUND_PCM_CH2);
                                }
                            }
                        }
                    }
                }
            }
        }
    }


    if(player.state == STATE_JUMP_V || player.state == STATE_JUMP_H)
    {
        if(G_JUMP_KICK != NO_JUMP_KICK)
        {
            // IF WE REACHED COLLISION FRAME //
            if(player.counter_ANIM_V >= JUMP_KICK_COLL_START && player.counter_ANIM_V < JUMP_KICK_COLL_END) // 11
            {
                // LOOP EVERY ENEMY //
                u8 i;

                for(i=0 ; i<4 ; i++)
                {
                    // IF ENEMY EXISTS //
                    if(LIST_ENEMIES[i].spr_ENEMY != NULL)
                    {
                        // IF ENEMY IS NOT ALREADY DEAD //
                        if(LIST_ENEMIES[i].vulnerable == TRUE)
                        {
                            // IF PLAYER IS FACING RIGHT //
                            if(player.axis == AXIS_RIGHT)
                            {
                                // WE CHECK ONLY ENEMIES FACING LEFT //
                                if(LIST_ENEMIES[i].axis == AXIS_LEFT)
                                {
                                    u16 distance = player.pos_X + 10 + PLAYER_KICK_MARGIN;
                                    
                                    if( LIST_ENEMIES[i].pos_X <= distance && LIST_ENEMIES[i].pos_X >= distance - 32 )
                                    {
                                        LIST_ENEMIES[i].counter_ANIM = 0;


                                        LIST_ENEMIES[i].life -= 1;

                                        // IF ENEMY LIFE REACHES 0, HE'S DEAD //
                                        if(LIST_ENEMIES[i].life == 0)
                                        {
                                            LIST_ENEMIES[i].state = ENEMY_DEAD;

                                            LIST_ENEMIES[i].vulnerable = FALSE;

                                            G_POINTS += LIST_ENEMIES[i].points;

                                            update_SCORE();
                                        }

                                        else
                                        {
                                            LIST_ENEMIES[i].state = ENEMY_HIT_UP_SLIDE;

                                            LIST_ENEMIES[i].vulnerable = FALSE;
                                        }

                                        G_JUMP_KICK = JUMP_KICK_HIT;

                                        XGM_startPlayPCM(SOUND_HIT_KICK,15,SOUND_PCM_CH2);
                                    }
                                }
                            }


                            // IF PLAYER IS FACING LEFT //
                            else if(player.axis == AXIS_LEFT)
                            {
                                // WE CHECK ONLY ENEMIES FACING RIGHT //
                                if(LIST_ENEMIES[i].axis == AXIS_RIGHT)
                                {
                                    u16 distance = player.pos_X - 26 - PLAYER_KICK_MARGIN;
                                    
                                    if( LIST_ENEMIES[i].pos_X >= distance && LIST_ENEMIES[i].pos_X <= distance + 32 )
                                    {
                                        LIST_ENEMIES[i].counter_ANIM = 0;


                                        LIST_ENEMIES[i].life -= 1;

                                        // IF ENEMY LIFE REACHES 0, HE'S DEAD //
                                        if(LIST_ENEMIES[i].life == 0)
                                        {
                                            LIST_ENEMIES[i].state = ENEMY_DEAD;

                                            LIST_ENEMIES[i].vulnerable = FALSE;

                                            G_POINTS += LIST_ENEMIES[i].points;

                                            update_SCORE();
                                        }

                                        else
                                        {
                                            LIST_ENEMIES[i].vulnerable = FALSE;
                                            
                                            LIST_ENEMIES[i].state = ENEMY_HIT_UP_SLIDE;
                                        }

                                        G_JUMP_KICK = JUMP_KICK_HIT;

                                        XGM_startPlayPCM(SOUND_HIT_KICK,15,SOUND_PCM_CH2);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        else if(G_JUMP_PUNCH == JUMP_PUNCH)
        {
            if(player.armed == TRUE)
            {
                // LOOP EVERY ENEMY //
                u8 i;

                for(i=0 ; i<4 ; i++)
                {
                    // IF ENEMY EXISTS //
                    if(LIST_ENEMIES[i].spr_ENEMY != NULL)
                    {
                        // IF ENEMY IS NOT ALREADY DEAD //
                        if(LIST_ENEMIES[i].vulnerable == TRUE)
                        {
                            // IF WE REACHED COLLISION FRAME //
                            if(player.counter_ANIM_V >= JUMP_PUNCH_COLL_START && player.counter_ANIM_V < JUMP_PUNCH_COLL_END)
                            {
                                // IF PLAYER IS FACING RIGHT //
                                if(player.axis == AXIS_RIGHT)
                                {
                                    // WE CHECK ONLY ENEMIES FACING LEFT //
                                    if(LIST_ENEMIES[i].axis == AXIS_LEFT)
                                    {
                                        u16 distance = player.pos_X + 10 + PLAYER_PUNCH_MARGIN;
                                        
                                        if( LIST_ENEMIES[i].pos_X <= distance + (player.armed << 4) && LIST_ENEMIES[i].pos_X >= distance - 32 )
                                        {
                                            LIST_ENEMIES[i].counter_ANIM = 0;


                                            LIST_ENEMIES[i].life -= 1;

                                            // IF ENEMY LIFE REACHES 0, HE'S DEAD //
                                            if(LIST_ENEMIES[i].life == 0)
                                            {
                                                LIST_ENEMIES[i].state = ENEMY_DEAD;

                                                LIST_ENEMIES[i].vulnerable = FALSE;

                                                G_POINTS += LIST_ENEMIES[i].points;

                                                update_SCORE();
                                            }

                                            else
                                            {
                                                LIST_ENEMIES[i].state = ENEMY_HIT_UP_SLIDE;

                                                LIST_ENEMIES[i].vulnerable = FALSE;
                                            }

                                            XGM_startPlayPCM(SOUND_HIT_PUNCH,15,SOUND_PCM_CH2);
                                        }
                                    }
                                }


                                // IF PLAYER IS FACING LEFT //
                                else if(player.axis == AXIS_LEFT)
                                {
                                    // WE CHECK ONLY ENEMIES FACING RIGHT //
                                    if(LIST_ENEMIES[i].axis == AXIS_RIGHT)
                                    {
                                        u16 distance = player.pos_X - 26 - PLAYER_PUNCH_MARGIN;
                                        
                                        if( LIST_ENEMIES[i].pos_X >= distance - (player.armed << 4) && LIST_ENEMIES[i].pos_X <= distance + 32 )
                                        {
                                            LIST_ENEMIES[i].counter_ANIM = 0;


                                            LIST_ENEMIES[i].life -= 1;

                                            // IF ENEMY LIFE REACHES 0, HE'S DEAD //
                                            if(LIST_ENEMIES[i].life == 0)
                                            {
                                                LIST_ENEMIES[i].state = ENEMY_DEAD;

                                                LIST_ENEMIES[i].vulnerable = FALSE;

                                                G_POINTS += LIST_ENEMIES[i].points;

                                                update_SCORE();
                                            }

                                            else
                                            {
                                                LIST_ENEMIES[i].state = ENEMY_HIT_UP_SLIDE;

                                                LIST_ENEMIES[i].vulnerable = FALSE;
                                            }

                                            XGM_startPlayPCM(SOUND_HIT_PUNCH,15,SOUND_PCM_CH2);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}








//**************************************************************************************//
//                                                                                      //
//                                     ENEMY SPAWN                                      //
//                                                                                      //
//**************************************************************************************//

inline static void spawn_PUNK_RIGHT()
{
    if(G_SPAWN_AUTHORIZED == TRUE)
    {
        if(LIST_ENEMIES[0].spr_ENEMY == NULL)
        {
            LIST_ENEMIES[0].pos_X = RIGHT_SPAWN_POSITION;
            LIST_ENEMIES[0].pos_Y = G_GROUND_POSITION;

            LIST_ENEMIES[0].axis  = AXIS_LEFT;

            // SET ENEMY LIFE POINTS //
            LIST_ENEMIES[0].life = 4;

            // ENEMY CAN BE HIT OR NOT AT CREATION TIME //
            LIST_ENEMIES[0].vulnerable = TRUE;

            // SET ENEMY ID //
            LIST_ENEMIES[0].enemy_ID = PUNK;

            // RESET ANIM COUNTER //
            LIST_ENEMIES[0].counter_ANIM = 0;

            // SET ENEMY REWARD POINTS WHEN KILLED//
            LIST_ENEMIES[0].points = 20;

            // 1 ENEMY SPAWNED //
            G_NUMBER_ENEMY += 1;
            
            // SET ENEMY STATE //
            LIST_ENEMIES[0].state = ENEMY_WALK;

            // WE CREATE ENEMY SPRITE //
            LIST_ENEMIES[0].spr_ENEMY = SPR_addSprite(&tiles_SPR_PUNK,  LIST_ENEMIES[0].pos_X , LIST_ENEMIES[0].pos_Y , TILE_ATTR(PAL3, FALSE, FALSE, LIST_ENEMIES[0].axis));


            LIST_ENEMIES[0].index_ANIM = 0;

            LIST_ENEMIES[0].index_FRAME = 0;

            SPR_setAnimAndFrame(LIST_ENEMIES[0].spr_ENEMY , LIST_ENEMIES[0].index_ANIM , LIST_ENEMIES[0].index_FRAME);

            // WE RESET SPAWN COUNTER //
            G_SPAWN_COUNTER = 0;

            // WE RESET SPAWN INDEX //
            G_SPAWN_INDEX += 1;
        }
    }
}


inline static void spawn_PUNK_LEFT()
{
    if(G_SPAWN_AUTHORIZED == TRUE)
    {
        if(LIST_ENEMIES[0].spr_ENEMY == NULL)
        {
            LIST_ENEMIES[0].pos_X = LEFT_SPAWN_POSITION;
            LIST_ENEMIES[0].pos_Y = G_GROUND_POSITION;

            LIST_ENEMIES[0].axis  = AXIS_RIGHT;

            // SET ENEMY LIFE POINTS //
            LIST_ENEMIES[0].life = 4;

            // ENEMY CAN BE HIT OR NOT AT CREATION TIME //
            LIST_ENEMIES[0].vulnerable = TRUE;

            // SET ENEMY ID //
            LIST_ENEMIES[0].enemy_ID = PUNK;

            // RESET ANIM COUNTER //
            LIST_ENEMIES[0].counter_ANIM = 0;

            // SET ENEMY REWARD POINTS WHEN KILLED//
            LIST_ENEMIES[0].points = 20;

            // 1 ENEMY SPAWNED //
            G_NUMBER_ENEMY += 1;
            
            // SET ENEMY STATE //
            LIST_ENEMIES[0].state = ENEMY_WALK;

            // WE CREATE ENEMY SPRITE //
            LIST_ENEMIES[0].spr_ENEMY = SPR_addSprite(&tiles_SPR_PUNK,  LIST_ENEMIES[0].pos_X , LIST_ENEMIES[0].pos_Y , TILE_ATTR(PAL3, FALSE, FALSE, LIST_ENEMIES[0].axis));


            LIST_ENEMIES[0].index_ANIM = 0;

            LIST_ENEMIES[0].index_FRAME = 0;

            SPR_setAnimAndFrame(LIST_ENEMIES[0].spr_ENEMY , LIST_ENEMIES[0].index_ANIM , LIST_ENEMIES[0].index_FRAME);

            // WE RESET SPAWN COUNTER //
            G_SPAWN_COUNTER = 0;

            // WE RESET SPAWN INDEX //
            G_SPAWN_INDEX += 1;
        }
    }
}


inline static void spawn_DUDE_RIGHT()
{
    if(G_SPAWN_AUTHORIZED == TRUE)
    {
        if(LIST_ENEMIES[0].spr_ENEMY == NULL)
        {
            LIST_ENEMIES[0].pos_X = RIGHT_SPAWN_POSITION;
            LIST_ENEMIES[0].pos_Y = G_GROUND_POSITION;

            LIST_ENEMIES[0].axis  = AXIS_LEFT;

            // SET ENEMY LIFE POINTS //
            LIST_ENEMIES[0].life = 1;

            // ENEMY CAN BE HIT OR NOT AT CREATION TIME //
            LIST_ENEMIES[0].vulnerable = TRUE;

            // SET ENEMY ID //
            LIST_ENEMIES[0].enemy_ID = DUDE;

            // RESET ANIM COUNTER //
            LIST_ENEMIES[0].counter_ANIM = 0;

            // SET ENEMY REWARD POINTS WHEN KILLED//
            LIST_ENEMIES[0].points = 20;

            // 1 ENEMY SPAWNED //
            G_NUMBER_ENEMY += 1;
            
            // SET ENEMY STATE //
            LIST_ENEMIES[0].state = ENEMY_WALK;

            // WE CREATE ENEMY SPRITE //
            LIST_ENEMIES[0].spr_ENEMY = SPR_addSprite(&tiles_SPR_DUDE,  LIST_ENEMIES[0].pos_X , LIST_ENEMIES[0].pos_Y , TILE_ATTR(PAL2, FALSE, FALSE, TRUE));


            LIST_ENEMIES[0].index_ANIM = 0;

            LIST_ENEMIES[0].index_FRAME = 0;

            SPR_setAnimAndFrame(LIST_ENEMIES[0].spr_ENEMY , LIST_ENEMIES[0].index_ANIM , LIST_ENEMIES[0].index_FRAME);

            // WE RESET SPAWN COUNTER //
            G_SPAWN_COUNTER = 0;

            // WE RESET SPAWN INDEX //
            G_SPAWN_INDEX += 1;
        }
    }
}


inline static void spawn_CHAIN_MAN_RIGHT()
{
    if(G_SPAWN_AUTHORIZED == TRUE)
    {
        if(LIST_ENEMIES[0].spr_ENEMY == NULL)
        {
            LIST_ENEMIES[0].pos_X = RIGHT_SPAWN_POSITION;
            LIST_ENEMIES[0].pos_Y = G_GROUND_POSITION;

            LIST_ENEMIES[0].axis  = AXIS_LEFT;

            // SET ENEMY LIFE POINTS //
            LIST_ENEMIES[0].life = 4;

            // ENEMY CAN BE HIT OR NOT AT CREATION TIME //
            LIST_ENEMIES[0].vulnerable = TRUE;

            // SET ENEMY ID //
            LIST_ENEMIES[0].enemy_ID = CHAIN_MAN;

            // RESET ANIM COUNTER //
            LIST_ENEMIES[0].counter_ANIM = 0;

            // SET ENEMY REWARD POINTS WHEN KILLED//
            LIST_ENEMIES[0].points = 20;

            // 1 ENEMY SPAWNED //
            G_NUMBER_ENEMY += 1;
            
            // SET ENEMY STATE //
            LIST_ENEMIES[0].state = ENEMY_WALK;

            // WE CREATE ENEMY SPRITE //
            LIST_ENEMIES[0].spr_ENEMY = SPR_addSprite(&tiles_SPR_CHAIN_MAN,  LIST_ENEMIES[0].pos_X , LIST_ENEMIES[0].pos_Y , TILE_ATTR(PAL2, FALSE, FALSE, LIST_ENEMIES[0].axis));


            LIST_ENEMIES[0].index_ANIM = 0;

            LIST_ENEMIES[0].index_FRAME = 0;

            SPR_setAnimAndFrame(LIST_ENEMIES[0].spr_ENEMY , LIST_ENEMIES[0].index_ANIM , LIST_ENEMIES[0].index_FRAME);

            // WE RESET SPAWN COUNTER //
            G_SPAWN_COUNTER = 0;

            // WE RESET SPAWN INDEX //
            G_SPAWN_INDEX += 1;
        }
    }
}


inline static void spawn_KNIFE_MAN_RIGHT()
{
    if(G_SPAWN_AUTHORIZED == TRUE)
    {
        if(LIST_ENEMIES[0].spr_ENEMY == NULL)
        {
            LIST_ENEMIES[0].pos_X = RIGHT_SPAWN_POSITION;
            LIST_ENEMIES[0].pos_Y = G_GROUND_POSITION;

            LIST_ENEMIES[0].axis  = AXIS_LEFT;

            // SET ENEMY LIFE POINTS //
            LIST_ENEMIES[0].life = 4;

            // ENEMY CAN BE HIT OR NOT AT CREATION TIME //
            LIST_ENEMIES[0].vulnerable = TRUE;

            // SET ENEMY ID //
            LIST_ENEMIES[0].enemy_ID = KNIFE_MAN;

            // RESET ANIM COUNTER //
            LIST_ENEMIES[0].counter_ANIM = 0;

            // SET ENEMY REWARD POINTS WHEN KILLED//
            LIST_ENEMIES[0].points = 20;

            // 1 ENEMY SPAWNED //
            G_NUMBER_ENEMY += 1;
            
            // SET ENEMY STATE //
            LIST_ENEMIES[0].state = ENEMY_WALK;

            // WE CREATE ENEMY SPRITE //
            LIST_ENEMIES[0].spr_ENEMY = SPR_addSprite(&tiles_SPR_KNIFE_MAN,  LIST_ENEMIES[0].pos_X , LIST_ENEMIES[0].pos_Y , TILE_ATTR(PAL3, FALSE, FALSE, LIST_ENEMIES[0].axis));


            LIST_ENEMIES[0].index_ANIM = 0;

            LIST_ENEMIES[0].index_FRAME = 0;

            SPR_setAnimAndFrame(LIST_ENEMIES[0].spr_ENEMY , LIST_ENEMIES[0].index_ANIM , LIST_ENEMIES[0].index_FRAME);

            // WE RESET SPAWN COUNTER //
            G_SPAWN_COUNTER = 0;

            // WE RESET SPAWN INDEX //
            G_SPAWN_INDEX += 1;
        }
    }
}




inline static void spawn_ENEMY_LEVEL_1()
{
    // IF PLAYER HASN'T REACHED THE BOSS, ENEMIES CAN RESPAWN //
    if(G_SPAWN_AUTHORIZED == TRUE)
    {
        // THERE CAN UP TO 4 ENEMIES ON SCREEN //
        // SO IF THERE ARE LESS THAN 4, WE CAN SPAWN A NEW ONE //
        if(G_NUMBER_ENEMY < G_NUMBER_ENEMY_MAX)
        {
            // WE INCREASE THE COUNTER //
            //G_SPAWN_COUNTER += 1;
            
            // WE CHECK IF WE HAVE REACHED SPAWN TIME //
            if(G_SPAWN_COUNTER == TABLE_SPAWN_LEVEL_1[G_SPAWN_INDEX].spawn_TIME)
            {
                // WE SEARCH FOR A FREE ENTRY IN THE ENEMIES LIST //
                u8 i;

                for(i=0 ; i<4 ; i++)
                {
                    if(LIST_ENEMIES[i].spr_ENEMY == NULL)
                    {
                        //----------------------------------------------------------------//
                        //                                                                //
                        //                        SPRITE PROPERTIES                       //
                        //                                                                //
                        //----------------------------------------------------------------//

                        // WE GET ENEMY TYPE //
                        u8 enemy_TYPE = TABLE_SPAWN_LEVEL_1[G_SPAWN_INDEX].enemy_ID;

                        // WE GET ENEMY SPRITE TILES;
                        const SpriteDefinition *ptr_TILE = TABLE_ENEMY_TYPE[enemy_TYPE].tiles_SPRITE;

                        // WE GET ENEMY PALETTE //
                        u8 enemy_PALETTE = TABLE_ENEMY_TYPE[enemy_TYPE].pal;


                        //----------------------------------------------------------------//
                        //                                                                //
                        //                         SPRITE POSITION                        //
                        //                                                                //
                        //----------------------------------------------------------------//

                        // AFTER SCROLLING REACHED 128, ENEMIES CAN SPAWN ON BOTH SIDES OF THE SCREEN //
                        if(G_POS_X_CAMERA > 127)
                        {
                            // ENEMY SPAWN ON THE RIGHT //
                            if(random_NUMBER(0,1) == 0)
                            {
                                LIST_ENEMIES[i].pos_X = RIGHT_SPAWN_POSITION;
                                LIST_ENEMIES[i].pos_Y = G_GROUND_POSITION;

                                LIST_ENEMIES[i].axis  = AXIS_LEFT;
                                
                                // WE CREATE ENEMY SPRITE //
                                LIST_ENEMIES[i].spr_ENEMY = SPR_addSprite(ptr_TILE,  LIST_ENEMIES[i].pos_X , LIST_ENEMIES[i].pos_Y , TILE_ATTR(enemy_PALETTE, FALSE, FALSE, TRUE));
                            }

                            // ENEMY SPAWN ON THE LEFT //
                            else
                            {
                                LIST_ENEMIES[i].pos_X = LEFT_SPAWN_POSITION;
                                LIST_ENEMIES[i].pos_Y = G_GROUND_POSITION;

                                LIST_ENEMIES[i].axis  = AXIS_RIGHT;
                                
                                // WE CREATE ENEMY SPRITE //
                                LIST_ENEMIES[i].spr_ENEMY = SPR_addSprite(ptr_TILE,  LIST_ENEMIES[i].pos_X , LIST_ENEMIES[i].pos_Y , TILE_ATTR(enemy_PALETTE, FALSE, FALSE, FALSE));
                            }
                        }

                        // BEFORE SCROLLING REACHES 128, ENEMIES CAN ONLY SPAWN ON THE RIGHT SIDE OF THE SCREEN //
                        else
                        {
                            //
                            LIST_ENEMIES[i].pos_X = RIGHT_SPAWN_POSITION;
                            LIST_ENEMIES[i].pos_Y = G_GROUND_POSITION;

                            LIST_ENEMIES[i].axis  = AXIS_LEFT;
                            
                            // WE CREATE ENEMY SPRITE //
                            LIST_ENEMIES[i].spr_ENEMY = SPR_addSprite(ptr_TILE,  LIST_ENEMIES[i].pos_X , LIST_ENEMIES[i].pos_Y , TILE_ATTR(enemy_PALETTE, FALSE, FALSE, TRUE));
                        }




                        //----------------------------------------------------------------//
                        //                                                                //
                        //                        ENEMY PROPERTIES                        //
                        //                                                                //
                        //----------------------------------------------------------------//

                        // LIFE POINTS //
                        LIST_ENEMIES[i].life = TABLE_ENEMY_TYPE[enemy_TYPE].life;

                        // ENEMY CAN BE HIT OR NOT AT CREATION TIME //
                        LIST_ENEMIES[i].vulnerable = TABLE_ENEMY_TYPE[enemy_TYPE].vulnerable;

                        // ENEMY ID //
                        LIST_ENEMIES[i].enemy_ID = enemy_TYPE;

                        // ANIM COUNTER //
                        LIST_ENEMIES[i].counter_ANIM = 0;

                        // SET ENEMY REWARD POINTS WHEN KILLED//
                        LIST_ENEMIES[i].points = TABLE_ENEMY_TYPE[enemy_TYPE].points;

                        // ENEMY ANIMATION AND FRAME //
                        LIST_ENEMIES[i].index_ANIM = 0;

                        LIST_ENEMIES[i].index_FRAME = 0;                    

                        SPR_setAnimAndFrame(LIST_ENEMIES[i].spr_ENEMY , LIST_ENEMIES[i].index_ANIM , LIST_ENEMIES[i].index_FRAME);

                        // 1 ENEMY SPAWNED //
                        G_NUMBER_ENEMY += 1;
                        
                        // ENEMY STATE //
                        LIST_ENEMIES[i].state = ENEMY_WALK;


                        break;
                    }
                }
                

                // WE RESET SPAWN COUNTER //
                G_SPAWN_COUNTER = 0;

                // WE RESET SPAWN INDEX //
                G_SPAWN_INDEX += 1;

                // IF WE HAVE REACHED THE SPAWN TABLE LENGH, WE GO BACK TO 0 //
                if(G_SPAWN_INDEX == G_SPAWN_MAX_INDEX)
                {
                    G_SPAWN_INDEX = 0;
                }
            }  
        }

        // WE INCREASE THE COUNTER //
        G_SPAWN_COUNTER += 1;


        // IF THERE ARE ALREADY 4 ENEMIES ON SCREEN //
        //else
        //{
            // WE KEEP INCREASING THE COUNTER //
            //G_SPAWN_COUNTER += 1;

            // IF WE REACH THE NEXT ENEMY SPAWN TIME //
            if(G_SPAWN_COUNTER > TABLE_SPAWN_LEVEL_1[G_SPAWN_INDEX].spawn_TIME)
            {
                // WE BLOCK THE COUNTER //
                // SO IT'S GOING TO RESPAWN AS SOON AS THERE IS A FREE ENTRY IN THE "LIST_ENEMIES[]"" LIST //
                G_SPAWN_COUNTER = TABLE_SPAWN_LEVEL_1[G_SPAWN_INDEX].spawn_TIME;
            }
        //}
    }
}




//**************************************************************************************//
//                                                                                      //
//                                       ENEMY AI                                       //
//                                                                                      //
//**************************************************************************************//

void update_DUDE(struct_ENEMY_ *enemy)
{
    //****************************************************************//
    //                                                                //
    //                              WALK                              //
    //                                                                //
    //****************************************************************//

    if(enemy->state == ENEMY_WALK)
    {
        //----------------------------------------------------------------//
        //                                                                //
        //                 CHECK GRAB AND THREAT DISTANCE                 //
        //                                                                //
        //----------------------------------------------------------------//

        //----------------------------------------------------------------//
        //                            AXIS LEFT                           //
        //----------------------------------------------------------------//

        if(enemy->axis == AXIS_LEFT)
        {
            //----------------------------------------------------------------//
            //                         GRAB DISTANCE                          //
            //----------------------------------------------------------------//
            if(enemy->pos_X <= player.pos_X - 8)
            {
                if(enemy->pos_X >= player.pos_X - 16)
                {
                    if(G_NUMBER_GRAB_RIGHT == 0)
                    {
                        enemy->pos_X = player.pos_X - 2;

                        enemy->state = ENEMY_GRAB;

                        SPR_setDepth(enemy->spr_ENEMY,1);

                        G_NUMBER_GRAB_RIGHT += 1;

                        if(player.state != STATE_GRAB && player.state != STATE_DEAD)
                        {
                            player.state = STATE_GRAB;

                            player.vulnerable = TRUE;

                            G_GRAVITY = FIX32(0);

                            SPR_setAnimAndFrame(player.spr_PLAYER,9,0);
                        }
                    }

                    else
                    {
                        G_NUMBER_GRAB_2_RIGHT += 1;

                        enemy->pos_X = player.pos_X - 2 + (G_NUMBER_GRAB_2_RIGHT << 2);

                        enemy->state = ENEMY_GRAB_2;
                    }




                    SPR_setPosition(enemy->spr_ENEMY,enemy->pos_X,enemy->pos_Y);
                    



                    enemy->counter_ANIM = 0;

                    enemy->index_ANIM = 2;

                    enemy->index_FRAME = 0;

                    SPR_setAnimAndFrame(enemy->spr_ENEMY,enemy->index_ANIM,enemy->index_FRAME);




                    SPR_setDepth(enemy->spr_ENEMY,3);

                    //SPR_setDepth(sprite_NUNCHUK,6);

                    //SPR_setDepth(player.spr_PLAYER,7);





                    if(player.armed == TRUE)
                    {
                        hide_NUNCHUCK();
                    }


                    return;
                }
            } 

            //----------------------------------------------------------------//
            //                        THREAT DISTANCE                         //
            //----------------------------------------------------------------//
            else if(enemy->pos_X <= player.pos_X + 44)
            {
                enemy->index_ANIM = 1;

                SPR_setAnimAndFrame(enemy->spr_ENEMY,enemy->index_ANIM,enemy->index_FRAME);
            }           
        }

        //----------------------------------------------------------------//
        //                            AXIS RIGHT                          //
        //----------------------------------------------------------------//

        else
        {
            //----------------------------------------------------------------//
            //                         GRAB DISTANCE                          //
            //----------------------------------------------------------------//
            if(enemy->pos_X >= player.pos_X - 16)
            {
                if(enemy->pos_X <= player.pos_X - 8)
                {
                    if(G_NUMBER_GRAB_LEFT == 0)
                    {
                        enemy->pos_X = player.pos_X - 14;

                        enemy->state = ENEMY_GRAB;

                        G_NUMBER_GRAB_LEFT += 1;

                        if(player.state != STATE_GRAB && player.state != STATE_DEAD)
                        {
                            player.state = STATE_GRAB;

                            player.vulnerable = TRUE;

                            G_GRAVITY = FIX32(0);

                            SPR_setAnimAndFrame(player.spr_PLAYER,9,0);
                        }
                    }

                    else
                    {
                        G_NUMBER_GRAB_2_LEFT += 1;

                        enemy->pos_X = player.pos_X - 14 - (G_NUMBER_GRAB_2_LEFT << 2);

                        enemy->state = ENEMY_GRAB_2;
                    }




                    SPR_setPosition(enemy->spr_ENEMY,enemy->pos_X,enemy->pos_Y);
                    


                    
                    enemy->counter_ANIM = 0;
                    
                    enemy->index_ANIM = 2;

                    enemy->index_FRAME = 0;

                    SPR_setAnimAndFrame(enemy->spr_ENEMY,enemy->index_ANIM,enemy->index_FRAME);




                    SPR_setDepth(enemy->spr_ENEMY,1);




                    if(player.armed == TRUE)
                    {
                        hide_NUNCHUCK();
                    }


                    return;
                }
            }

            //----------------------------------------------------------------//
            //                        THREAT DISTANCE                         //
            //----------------------------------------------------------------//
            else if(enemy->pos_X >= player.pos_X - 63)
            {
                enemy->index_ANIM = 1;

                SPR_setAnimAndFrame(enemy->spr_ENEMY,enemy->index_ANIM,enemy->index_FRAME);
            }
        }




        enemy->counter_ANIM += 1;

        //----------------------------------------------------------------//
        //                                                                //
        //                         UPDATE POSITION                        //
        //                                                                //
        //----------------------------------------------------------------//

        //----------------------------------------------------------------//
        //                            AXIS LEFT                           //
        //----------------------------------------------------------------//

        if(enemy->axis == AXIS_LEFT)
        {
            if(enemy->counter_ANIM%2 == TRUE)
            {
                enemy->pos_X -= 2;
            }

            else
            {
                enemy->pos_X -= 1;
            }
        }
        
        //----------------------------------------------------------------//
        //                            AXIS RIGHT                          //
        //----------------------------------------------------------------//

        else
        {
            if(enemy->counter_ANIM%2 == TRUE)
            {
                enemy->pos_X += 2;
            }

            else
            {
                enemy->pos_X += 1;
            }
        }


        SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);




        //----------------------------------------------------------------//
        //                                                                //
        //                          UPDATE FRAME                          //
        //                                                                //
        //----------------------------------------------------------------//

        if(enemy->counter_ANIM == 21)
        {
            enemy->counter_ANIM = 0;
        }




        if(enemy->counter_ANIM == 0)
        {
            enemy->index_FRAME = 0;
            
            SPR_setAnimAndFrame(enemy->spr_ENEMY , enemy->index_ANIM , enemy->index_FRAME);
        }

        else if(enemy->counter_ANIM == 5)
        {
            enemy->index_FRAME = 1;
            
            SPR_setAnimAndFrame(enemy->spr_ENEMY , enemy->index_ANIM , enemy->index_FRAME);
        }

        else if(enemy->counter_ANIM == 11)
        {
            enemy->index_FRAME = 2;
            
            SPR_setAnimAndFrame(enemy->spr_ENEMY , enemy->index_ANIM , enemy->index_FRAME);
        }

        else if(enemy->counter_ANIM == 16)
        {
            enemy->index_FRAME = 3;
            
            SPR_setAnimAndFrame(enemy->spr_ENEMY , enemy->index_ANIM , enemy->index_FRAME);
        }




        //----------------------------------------------------------------//
        //                                                                //
        //                      ENEMY GOES OFF SCREEN                     //
        //                                                                //
        //----------------------------------------------------------------//

        if(enemy->axis == AXIS_LEFT)
        {
            if(enemy->pos_X < -72)
            {
                SPR_releaseSprite(enemy->spr_ENEMY);
                
                enemy->spr_ENEMY = NULL;

                G_NUMBER_ENEMY -= 1;
            }
        }

        //----------------------------------------------------------------//
        //                            AXIS RIGHT                          //
        //----------------------------------------------------------------//

        else
        {
            if(enemy->pos_X > 236)
            {
                SPR_releaseSprite(enemy->spr_ENEMY);
                
                enemy->spr_ENEMY = NULL;

                G_NUMBER_ENEMY -= 1;
            }
        }
    }


    //****************************************************************//
    //                                                                //
    //                             GRAB 2                             //
    //                                                                //
    //****************************************************************//

    else if(enemy->state == ENEMY_GRAB_2)
    {
        if(enemy->axis == AXIS_LEFT)
        {
            if(G_NUMBER_GRAB_RIGHT == 0)
            {
                enemy->state = ENEMY_WALK;

                G_NUMBER_GRAB_2_RIGHT -= 1;
            }
        }

        else if(enemy->axis == AXIS_RIGHT)
        {
            if(G_NUMBER_GRAB_LEFT == 0)
            {
                enemy->state = ENEMY_WALK;

                G_NUMBER_GRAB_2_LEFT -= 1;
            }
        }
    }


    //****************************************************************//
    //                                                                //
    //                              DEAD                              //
    //                                                                //
    //****************************************************************//

    else if(enemy->state == ENEMY_DEAD)
    {
        //----------------------------------------------------------------//
        //                                                                //
        //                          UPDATE FRAME                          //
        //                                                                //
        //----------------------------------------------------------------//

        if(enemy->counter_ANIM == 0)
        {
            SPR_setAnimAndFrame(enemy->spr_ENEMY , 3 , 0);
        }

        else if(enemy->counter_ANIM == 11)
        {
            SPR_setAnimAndFrame(enemy->spr_ENEMY , 3 , 1);
        }

        else if(enemy->counter_ANIM == 22)
        {
            SPR_setAnimAndFrame(enemy->spr_ENEMY , 3 , 2);
        }

        enemy->counter_ANIM += 1;




        //----------------------------------------------------------------//
        //                                                                //
        //                         UPDATE POSITION                        //
        //                                                                //
        //----------------------------------------------------------------//

        //----------------------------------------------------------------//
        //                            AXIS LEFT                           //
        //----------------------------------------------------------------//

        if(enemy->axis == AXIS_LEFT)
        {
            enemy->pos_X += 2;
        }


        //----------------------------------------------------------------//
        //                            AXIS RIGHT                          //
        //----------------------------------------------------------------//

        else
        {
            enemy->pos_X -= 2;
        }


        enemy->pos_Y += 3;


        SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);




        //----------------------------------------------------------------//
        //                                                                //
        //                      ENEMY GOES OFF SCREEN                     //
        //                                                                //
        //----------------------------------------------------------------//

        if(enemy->pos_Y > 224)
        {
            SPR_releaseSprite(enemy->spr_ENEMY);

            enemy->spr_ENEMY = NULL;

            G_NUMBER_ENEMY -= 1;
        }
    }
}




void update_PUNK(struct_ENEMY_ *enemy)
{
    //****************************************************************//
    //                                                                //
    //                              WALK                              //
    //                                                                //
    //****************************************************************//

    if(enemy->state == ENEMY_WALK)
    {
        //----------------------------------------------------------------//
        //                                                                //
        //                     CHECK THREAT DISTANCE                      //
        //                                                                //
        //----------------------------------------------------------------//

        //----------------------------------------------------------------//
        //                            AXIS LEFT                           //
        //----------------------------------------------------------------//

        if(enemy->axis == AXIS_LEFT)
        {
            if((enemy->pos_X - 42) < player.pos_X)
            {
                enemy->state = ENEMY_THREAT_FW;

                enemy->counter_ANIM = 0;

                enemy->vulnerable = TRUE;

                return;
            }
        }

        //----------------------------------------------------------------//
        //                            AXIS RIGHT                          //
        //----------------------------------------------------------------//

        else
        {
            if((enemy->pos_X + 58) > player.pos_X)
            {
                enemy->state = ENEMY_THREAT_FW;

                enemy->counter_ANIM = 0;

                enemy->vulnerable = TRUE;

                return;
            }
        }
        
        
        
        enemy->counter_ANIM += 1;


        //----------------------------------------------------------------//
        //                                                                //
        //                         UPDATE POSITION                        //
        //                                                                //
        //----------------------------------------------------------------//

        //----------------------------------------------------------------//
        //                            AXIS LEFT                           //
        //----------------------------------------------------------------//

        if(enemy->axis == AXIS_LEFT)
        {
            if(enemy->counter_ANIM%2 == TRUE)
            {
                enemy->pos_X -= 2;
            }

            else
            {
                enemy->pos_X -= 1;
            }
        }
        
        //----------------------------------------------------------------//
        //                            AXIS RIGHT                          //
        //----------------------------------------------------------------//

        else
        {
            if(enemy->counter_ANIM%2 == TRUE)
            {
                enemy->pos_X += 2;
            }

            else
            {
                enemy->pos_X += 1;
            }
        }


        SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);




        //----------------------------------------------------------------//
        //                                                                //
        //                          UPDATE FRAME                          //
        //                                                                //
        //----------------------------------------------------------------//

        if(enemy->counter_ANIM == 21)
        {
            enemy->counter_ANIM = 0;
        }




        if(enemy->counter_ANIM == 0)
        {
            SPR_setAnimAndFrame(enemy->spr_ENEMY , 0 , 0);
        }

        else if(enemy->counter_ANIM == 5)
        {
            SPR_setAnimAndFrame(enemy->spr_ENEMY , 0 , 1);
        }

        else if(enemy->counter_ANIM == 11)
        {
            SPR_setAnimAndFrame(enemy->spr_ENEMY , 0 , 2);
        }

        else if(enemy->counter_ANIM == 16)
        {
            SPR_setAnimAndFrame(enemy->spr_ENEMY , 0 , 3);
        }
    }


    //****************************************************************//
    //                                                                //
    //                            THREAT FW                           //
    //                                                                //
    //****************************************************************//

    else if(enemy->state == ENEMY_THREAT_FW)
    {
        //----------------------------------------------------------------//
        //                                                                //
        //                     CHECK ATTACK DISTANCE                      //
        //                                                                //
        //----------------------------------------------------------------//

        //----------------------------------------------------------------//
        //                            AXIS LEFT                           //
        //----------------------------------------------------------------//

        if(enemy->axis == AXIS_LEFT)
        {
            //------------------------------------------------------//
            //             IF PLAYER IS AT PUNCH RANGE              //
            //------------------------------------------------------//
            if(player.state != STATE_DEAD)
            {
                if(enemy->pos_X <= (player.pos_X + 10)) // PLAYER_CENTER
                {
                    enemy->counter_ANIM = 0;

                    enemy->vulnerable = TRUE;

                    enemy->state = random_NUMBER(6,7);

                    //enemy->state = ENEMY_ATTACK_UP;

                    return;
                }
            }
        }

        //----------------------------------------------------------------//
        //                            AXIS RIGHT                          //
        //----------------------------------------------------------------//

        else if(enemy->axis == AXIS_RIGHT)
        {
            //------------------------------------------------------//
            //             IF PLAYER IS AT PUNCH RANGE              //
            //------------------------------------------------------//
            if(player.state != STATE_DEAD)
            {
                if(player.pos_X <= (enemy->pos_X + ENEMY_RIGHT_BOUND)) //26
                {
                    enemy->counter_ANIM = 0;

                    enemy->vulnerable = TRUE;

                    enemy->state = random_NUMBER(6,7);

                    //enemy->state = ENEMY_ATTACK_UP;

                    return;
                }
            }
        }




        //----------------------------------------------------------------//
        //                                                                //
        //                    UPDATE FRAME AND POSITION                   //
        //                                                                //
        //----------------------------------------------------------------//

        if(enemy->counter_ANIM == 0)
        {
            SPR_setAnim(enemy->spr_ENEMY,1);
            SPR_setFrame(enemy->spr_ENEMY,0);
        }


        else if(enemy->counter_ANIM == 7 || enemy->counter_ANIM == 8 || enemy->counter_ANIM == 9 || enemy->counter_ANIM == 11 || enemy->counter_ANIM == 12 || enemy->counter_ANIM == 13)
        {
            SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X ,  enemy->pos_Y);
            
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X -= 1;
            }

            else
            {
                enemy->pos_X += 1;
            }
        }


        else if(enemy->counter_ANIM == 14)
        {
            SPR_setFrame(enemy->spr_ENEMY,1);
        }


        else if(enemy->counter_ANIM == 15 || enemy->counter_ANIM == 16 || enemy->counter_ANIM == 17 || enemy->counter_ANIM == 19 || enemy->counter_ANIM == 20 || enemy->counter_ANIM == 21)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X -= 1;
            }

            else
            {
                enemy->pos_X += 1;
            }

            SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X ,  enemy->pos_Y);
        }


        else if(enemy->counter_ANIM == 22)
        {
            SPR_setFrame(enemy->spr_ENEMY,2);
        }


        else if(enemy->counter_ANIM == 23 || enemy->counter_ANIM == 24 || enemy->counter_ANIM == 25 || enemy->counter_ANIM == 27 || enemy->counter_ANIM == 28 || enemy->counter_ANIM == 29)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X -= 1;
            }

            else
            {
                enemy->pos_X += 1;
            }

            SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X ,  enemy->pos_Y);
        }


        else if(enemy->counter_ANIM == 30)
        {
            SPR_setFrame(enemy->spr_ENEMY,3);
        }


        else if(enemy->counter_ANIM == 31 || enemy->counter_ANIM == 32 || enemy->counter_ANIM == 33 || enemy->counter_ANIM == 35 || enemy->counter_ANIM == 36 || enemy->counter_ANIM == 37)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X -= 1;
            }

            else
            {
                enemy->pos_X += 1;
            }

            SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X ,  enemy->pos_Y);
        }


        else if(enemy->counter_ANIM == 38)
        {
            // CHECK DISTANCE BETWEEN PUNK AND PLAYER //
            if(enemy->axis == AXIS_LEFT)
            {
                if((enemy->pos_X - 56) < player.pos_X)
                {
                    enemy->state = ENEMY_THREAT_FW;

                    enemy->counter_ANIM = 0;

                    SPR_setFrame(enemy->spr_ENEMY,0);

                    return;
                }

                else
                {
                    enemy->state = ENEMY_WALK;

                    enemy->counter_ANIM = 0;

                    SPR_setAnimAndFrame(enemy->spr_ENEMY,0,0);

                    return;
                }
            }

            else if(enemy->axis == AXIS_RIGHT)
            {
                if((enemy->pos_X + 48) > player.pos_X)
                {
                    enemy->state = ENEMY_THREAT_FW;

                    enemy->counter_ANIM = 0;

                    SPR_setFrame(enemy->spr_ENEMY,0);

                    return;
                }

                else
                {
                    enemy->state = ENEMY_WALK;

                    enemy->counter_ANIM = 0;

                    SPR_setAnimAndFrame(enemy->spr_ENEMY,0,0);

                    return;
                }
            }
        }


        enemy->counter_ANIM += 1;


        SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);
    }


    //****************************************************************//
    //                                                                //
    //                            THREAT BW                           //
    //                                                                //
    //****************************************************************//

    else if(enemy->state == ENEMY_THREAT_BW)
    {
        //----------------------------------------------------------------//
        //                                                                //
        //                    UPDATE FRAME AND POSITION                   //
        //                                                                //
        //----------------------------------------------------------------//

        if(enemy->counter_ANIM == 0)
        {
            SPR_setAnim(enemy->spr_ENEMY,1);
            SPR_setFrame(enemy->spr_ENEMY,3);
        }


        else if(enemy->counter_ANIM == 7 || enemy->counter_ANIM == 8 || enemy->counter_ANIM == 9 || enemy->counter_ANIM == 11 || enemy->counter_ANIM == 12 || enemy->counter_ANIM == 13)
        {
            SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X ,  enemy->pos_Y);
            
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            }
        }


        else if(enemy->counter_ANIM == 14)
        {
            SPR_setFrame(enemy->spr_ENEMY,2);
        }


        else if(enemy->counter_ANIM == 15 || enemy->counter_ANIM == 16 || enemy->counter_ANIM == 17 || enemy->counter_ANIM == 19 || enemy->counter_ANIM == 20 || enemy->counter_ANIM == 21)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            }

            SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X ,  enemy->pos_Y);
        }


        else if(enemy->counter_ANIM == 22)
        {
            SPR_setFrame(enemy->spr_ENEMY,1);
        }


        else if(enemy->counter_ANIM == 23 || enemy->counter_ANIM == 24 || enemy->counter_ANIM == 25 || enemy->counter_ANIM == 27 || enemy->counter_ANIM == 28 || enemy->counter_ANIM == 29)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            }

            SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X ,  enemy->pos_Y);
        }


        else if(enemy->counter_ANIM == 30)
        {
            SPR_setFrame(enemy->spr_ENEMY,0);
        }


        else if(enemy->counter_ANIM == 31 || enemy->counter_ANIM == 32 || enemy->counter_ANIM == 33 || enemy->counter_ANIM == 35 || enemy->counter_ANIM == 36 || enemy->counter_ANIM == 37)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            }

            SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X ,  enemy->pos_Y);
        }


        else if(enemy->counter_ANIM == 38)
        {
            enemy->state = ENEMY_THREAT_FW;

            enemy->counter_ANIM = 0;

            SPR_setFrame(enemy->spr_ENEMY,0);

            return;
        }


        enemy->counter_ANIM += 1;


        SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);
    }


    //****************************************************************//
    //                                                                //
    //                           ATTACK UP                            //
    //                                                                //
    //****************************************************************//

    else if(enemy->state == ENEMY_ATTACK_UP)
    {
        //----------------------------------------------------------------//
        //                                                                //
        //                          UPDATE FRAME                          //
        //                                                                //
        //----------------------------------------------------------------//

        if(enemy->counter_ANIM == 0)
        {
            SPR_setAnim(enemy->spr_ENEMY,2);
            SPR_setFrame(enemy->spr_ENEMY,0);
        }

        //------------------------------------------------------//
        //                                                      //
        //                        PUNCH 1                       //
        //                                                      //
        //------------------------------------------------------//
        else if(enemy->counter_ANIM == 8)
        {
            SPR_setFrame(enemy->spr_ENEMY,1);

            // ENEMY IS ON TOP OF PLAYER //
            SPR_setDepth(enemy->spr_ENEMY,1);


            if(player.state != STATE_CROUCH && player.state != STATE_PUNCH_CROUCH && player.state != STATE_KICK_CROUCH)
            {
                // CHECK COLLISION WITH PLAYER //
                if(enemy->axis == AXIS_LEFT)
                {
                    if(player.vulnerable == TRUE)
                    {
                        //------------------------------------------------------//
                        //        CHECK DISTANCE BETWEEN PUNK AND PLAYER        //
                        //------------------------------------------------------//
                        if(player.pos_X <= (enemy->pos_X + 10))
                        {
                            player.counter_ANIM_SPRITE = 0;

                            if(player.state != STATE_GRAB)
                            {
                                player.state = STATE_HIT_UP;

                                //player.vulnerable = FALSE;
                            }

                            player.life -= TABLE_ENEMY_TYPE[enemy->enemy_ID].damages;

                            if(player.life < FIX32(0))
                            {
                                player.life = FIX32(0);
                            }
                            

                            update_LIFE_PLAYER();


                            if(player.armed == TRUE)
                            {
                                hide_NUNCHUCK();
                            }
                        }
                    }
                }


                else if(enemy->axis == AXIS_RIGHT)
                {
                    if(player.vulnerable == TRUE)
                    {
                        //------------------------------------------------------//
                        //        CHECK DISTANCE BETWEEN PUNK AND PLAYER        //
                        //------------------------------------------------------//
                        if(player.pos_X <= (enemy->pos_X + ENEMY_RIGHT_BOUND))//26
                        {
                            player.counter_ANIM_SPRITE = 0;

                            if(player.state != STATE_GRAB)
                            {
                                player.state = STATE_HIT_UP;

                                //player.vulnerable = FALSE;
                            }

                            player.life -= TABLE_ENEMY_TYPE[enemy->enemy_ID].damages;

                            if(player.life < FIX32(0))
                            {
                                player.life = FIX32(0);
                            }


                            update_LIFE_PLAYER();


                            if(player.armed == TRUE)
                            {
                                hide_NUNCHUCK();
                            }                        
                        }
                    }
                }
            }
        }


        else if(enemy->counter_ANIM == 16)
        {
            SPR_setFrame(enemy->spr_ENEMY,2);
        }


        //------------------------------------------------------//
        //                                                      //
        //                        PUNCH 2                       //
        //                                                      //
        //------------------------------------------------------//
        else if(enemy->counter_ANIM == 24)
        {
            SPR_setFrame(enemy->spr_ENEMY,3);

            // ENEMY IS ON TOP OF PLAYER //
            SPR_setDepth(enemy->spr_ENEMY,1);


            if(player.state != STATE_CROUCH && player.state != STATE_PUNCH_CROUCH && player.state != STATE_KICK_CROUCH)
            {
                // CHECK COLLISION WITH PLAYER //
                if(enemy->axis == AXIS_LEFT)
                {
                    if(player.state == STATE_IDLE || player.state == STATE_WALK || player.state == STATE_PUNCH || player.state == STATE_KICK || player.state == STATE_JUMP_H || player.state == STATE_JUMP_V || player.state == STATE_GRAB)
                    {
                        //------------------------------------------------------//
                        //        CHECK DISTANCE BETWEEN PUNK AND PLAYER        //
                        //------------------------------------------------------//
                        if(enemy->pos_X <= (player.pos_X + 10))
                        {
                            player.counter_ANIM_SPRITE = 0;

                            if(player.state != STATE_GRAB)
                            {
                                player.state = STATE_HIT_UP;

                                //player.vulnerable = FALSE;
                            }

                            player.life -= TABLE_ENEMY_TYPE[enemy->enemy_ID].damages;

                            if(player.life < FIX32(0))
                            {
                                player.life = FIX32(0);
                            }
                            

                            update_LIFE_PLAYER();


                            if(player.armed == TRUE)
                            {
                                hide_NUNCHUCK();
                            }
                        }
                    }
                }


                else if(enemy->axis == AXIS_RIGHT)
                {
                    if(player.state == STATE_IDLE || player.state == STATE_WALK || player.state == STATE_PUNCH || player.state == STATE_KICK || player.state == STATE_JUMP_H || player.state == STATE_JUMP_V || player.state == STATE_GRAB)
                    {
                        //------------------------------------------------------//
                        //        CHECK DISTANCE BETWEEN PUNK AND PLAYER        //
                        //------------------------------------------------------//
                        if(player.pos_X <= (enemy->pos_X + ENEMY_RIGHT_BOUND))//26
                        {
                            player.counter_ANIM_SPRITE = 0;

                            if(player.state != STATE_GRAB)
                            {
                                player.state = STATE_HIT_UP;

                                //player.vulnerable = FALSE;
                            }

                            player.life -= TABLE_ENEMY_TYPE[enemy->enemy_ID].damages;

                            if(player.life < FIX32(0))
                            {
                                player.life = FIX32(0);
                            }


                            update_LIFE_PLAYER();


                            if(player.armed == TRUE)
                            {
                                hide_NUNCHUCK();
                            }
                        }
                    }
                }
            }
        }


        else if(enemy->counter_ANIM == 34)
        {
            enemy->counter_ANIM = 0;

            enemy->state = random_NUMBER(4,7); //ENEMY_THREAT_BW

            /*enemy->counter_ANIM = 0;
            
            enemy->state = ENEMY_THREAT_FW;*/

            return;
        }        


        enemy->counter_ANIM += 1;


        SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);
    }


    //****************************************************************//
    //                                                                //
    //                          ATTACK DOWN                           //
    //                                                                //
    //****************************************************************//

    else if(enemy->state == ENEMY_ATTACK_DOWN)
    {
        //----------------------------------------------------------------//
        //                                                                //
        //                          UPDATE FRAME                          //
        //                                                                //
        //----------------------------------------------------------------//

        if(enemy->counter_ANIM == 0)
        {
            SPR_setAnim(enemy->spr_ENEMY,3);
            SPR_setFrame(enemy->spr_ENEMY,0);
        }

        //------------------------------------------------------//
        //                                                      //
        //                        PUNCH 1                       //
        //                                                      //
        //------------------------------------------------------//
        else if(enemy->counter_ANIM == 8)
        {
            SPR_setFrame(enemy->spr_ENEMY,1);

            // ENEMY IS ON TOP OF PLAYER //
            SPR_setDepth(enemy->spr_ENEMY,1);


            if(player.state != STATE_JUMP_V && player.state != STATE_JUMP_H && player.state != STATE_JUMP_KICK && player.state != STATE_JUMP_KICK_BW)
            {
                // CHECK COLLISION WITH PLAYER //
                if(enemy->axis == AXIS_LEFT)
                {
                    if(player.vulnerable == TRUE)
                    {
                        //------------------------------------------------------//
                        //        CHECK DISTANCE BETWEEN PUNK AND PLAYER        //
                        //------------------------------------------------------//
                        if(enemy->pos_X <= (player.pos_X + 10))
                        {
                            if(player.pos_Y == G_GROUND_POSITION)
                            {
                                player.counter_ANIM_SPRITE = 0;

                                if(player.state != STATE_GRAB)
                                {
                                    player.state = STATE_HIT_DOWN;

                                    //player.vulnerable = FALSE;
                                }

                                player.life -= TABLE_ENEMY_TYPE[enemy->enemy_ID].damages;

                                if(player.life < FIX32(0))
                                {
                                    player.life = FIX32(0);
                                }
                                

                                update_LIFE_PLAYER();


                                if(player.armed == TRUE)
                                {
                                    hide_NUNCHUCK();
                                }
                            }
                        }
                    }
                }


                else if(enemy->axis == AXIS_RIGHT)
                {
                    if(player.vulnerable == TRUE)
                    {
                        //------------------------------------------------------//
                        //        CHECK DISTANCE BETWEEN PUNK AND PLAYER        //
                        //------------------------------------------------------//
                        if(player.pos_X <= (enemy->pos_X + ENEMY_RIGHT_BOUND))
                        {
                            if(player.pos_Y == G_GROUND_POSITION)
                            {
                                player.counter_ANIM_SPRITE = 0;
                                
                                if(player.state != STATE_GRAB)
                                {
                                    player.state = STATE_HIT_DOWN;

                                    //player.vulnerable = FALSE;
                                }

                                player.life -= TABLE_ENEMY_TYPE[enemy->enemy_ID].damages;

                                if(player.life < FIX32(0))
                                {
                                    player.life = FIX32(0);
                                }
                                

                                update_LIFE_PLAYER();


                                if(player.armed == TRUE)
                                {
                                    hide_NUNCHUCK();
                                }
                            }
                        }
                    }
                }
            }
        }


        else if(enemy->counter_ANIM == 16)
        {
            SPR_setFrame(enemy->spr_ENEMY,2);
        }


        //------------------------------------------------------//
        //                                                      //
        //                        PUNCH 2                       //
        //                                                      //
        //------------------------------------------------------//
        else if(enemy->counter_ANIM == 24)
        {
            SPR_setFrame(enemy->spr_ENEMY,3);

            // ENEMY IS ON TOP OF PLAYER //
            SPR_setDepth(enemy->spr_ENEMY,1);


            if(player.state != STATE_JUMP_V && player.state != STATE_JUMP_H && player.state != STATE_JUMP_KICK && player.state != STATE_JUMP_KICK_BW)
            {
                // CHECK COLLISION WITH PLAYER //
                if(enemy->axis == AXIS_LEFT)
                {
                    if(player.vulnerable == TRUE)
                    {
                        //------------------------------------------------------//
                        //        CHECK DISTANCE BETWEEN PUNK AND PLAYER        //
                        //------------------------------------------------------//
                        if(enemy->pos_X <= (player.pos_X + 10))
                        {
                            if(player.pos_Y == G_GROUND_POSITION)
                            {
                                player.counter_ANIM_SPRITE = 0;

                                if(player.state != STATE_GRAB)
                                {
                                    player.state = STATE_HIT_DOWN;

                                    //player.vulnerable = FALSE;
                                }

                                player.life -= TABLE_ENEMY_TYPE[enemy->enemy_ID].damages;

                                if(player.life < FIX32(0))
                                {
                                    player.life = FIX32(0);
                                }
                                

                                update_LIFE_PLAYER();


                                if(player.armed == TRUE)
                                {
                                    hide_NUNCHUCK();
                                }
                            }
                        }
                    }
                }


                else if(enemy->axis == AXIS_RIGHT)
                {
                    if(player.vulnerable == TRUE)
                    {
                        //------------------------------------------------------//
                        //        CHECK DISTANCE BETWEEN PUNK AND PLAYER        //
                        //------------------------------------------------------//
                        if(player.pos_X <= (enemy->pos_X + ENEMY_RIGHT_BOUND))
                        {
                            if(player.pos_Y == G_GROUND_POSITION)
                            {
                                player.counter_ANIM_SPRITE = 0;
                                
                                if(player.state != STATE_GRAB)
                                {
                                    player.state = STATE_HIT_DOWN;

                                    //player.vulnerable = FALSE;
                                }

                                player.life -= TABLE_ENEMY_TYPE[enemy->enemy_ID].damages;

                                if(player.life < FIX32(0))
                                {
                                    player.life = FIX32(0);
                                }
                                

                                update_LIFE_PLAYER();


                                if(player.armed == TRUE)
                                {
                                    hide_NUNCHUCK();
                                }
                            }
                        }
                    }
                }
            }
        }


        else if(enemy->counter_ANIM == 34)
        {
            enemy->counter_ANIM = 0;

            enemy->state = random_NUMBER(4,7);

            //enemy->state = ENEMY_THREAT_FW;

            return;
        }        


        enemy->counter_ANIM += 1;


        SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);
    }


    //****************************************************************//
    //                                                                //
    //                       HIT UP & DOWN SLIDE                      //
    //                                                                //
    //****************************************************************//

    else if(enemy->state == ENEMY_HIT_UP_SLIDE || enemy->state == ENEMY_HIT_DOWN_SLIDE)
    {
        if(enemy->counter_ANIM == 0)
        {
            if(enemy->state == ENEMY_HIT_UP_SLIDE)
            {
                SPR_setAnim(enemy->spr_ENEMY,4);
                SPR_setFrame(enemy->spr_ENEMY,0);
            }

            else if(enemy->state == ENEMY_HIT_DOWN_SLIDE)
            {
                SPR_setAnim(enemy->spr_ENEMY,5);
                SPR_setFrame(enemy->spr_ENEMY,0);
            }
        }

        else if(enemy->counter_ANIM == 1)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 3;
            }

            else
            {
                enemy->pos_X -= 3;
            } 
        }

        else if(enemy->counter_ANIM == 2)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 2;
            }

            else
            {
                enemy->pos_X -= 2;
            } 
        }

        else if(enemy->counter_ANIM == 3)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 2;
            }

            else
            {
                enemy->pos_X -= 2;
            } 
        }

        else if(enemy->counter_ANIM == 4)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 3;
            }

            else
            {
                enemy->pos_X -= 3;
            } 
        }

        else if(enemy->counter_ANIM == 5)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            } 
        }

        else if(enemy->counter_ANIM == 6)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 2;
            }

            else
            {
                enemy->pos_X -= 2;
            } 
        }

        else if(enemy->counter_ANIM == 7)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 2;
            }

            else
            {
                enemy->pos_X -= 2;
            } 
        }

        else if(enemy->counter_ANIM == 8)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            } 
        }

        else if(enemy->counter_ANIM == 9)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            } 
        }

        else if(enemy->counter_ANIM == 10)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            } 
        }

        else if(enemy->counter_ANIM == 11)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            } 
        }

        else if(enemy->counter_ANIM == 13)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            } 
        }

        else if(enemy->counter_ANIM == 17)
        {
            enemy->counter_ANIM = 0;

            enemy->vulnerable = TRUE;
            
            enemy->state = ENEMY_WALK;

            SPR_setAnimAndFrame(enemy->spr_ENEMY , 0 , 0);

            //SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);

            return;
        }


        enemy->counter_ANIM += 1;


        SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);
    }


    //****************************************************************//
    //                                                                //
    //                             HIT UP                             //
    //                                                                //
    //****************************************************************//

    else if(enemy->state == ENEMY_HIT_UP)
    {
        //----------------------------------------------------------------//
        //                                                                //
        //                          UPDATE FRAME                          //
        //                                                                //
        //----------------------------------------------------------------//

        if(enemy->counter_ANIM == 0)
        {
            SPR_setAnim(enemy->spr_ENEMY,4);
            SPR_setFrame(enemy->spr_ENEMY,0 + G_REPEAT);
        }

        else if(enemy->counter_ANIM == 6)
        {
            SPR_setFrame(enemy->spr_ENEMY,2);
        }

        else if(enemy->counter_ANIM == 17)
        {
            enemy->counter_ANIM = 0;

            enemy->vulnerable = TRUE;
            
            enemy->state = ENEMY_THREAT_FW;

            return;
        }


        enemy->counter_ANIM += 1;        
    }


    //****************************************************************//
    //                                                                //
    //                            HIT DOWN                            //
    //                                                                //
    //****************************************************************//

    else if(enemy->state == ENEMY_HIT_DOWN)
    {
        //----------------------------------------------------------------//
        //                                                                //
        //                          UPDATE FRAME                          //
        //                                                                //
        //----------------------------------------------------------------//

        if(enemy->counter_ANIM == 0)
        {
            SPR_setAnim(enemy->spr_ENEMY,5);
            SPR_setFrame(enemy->spr_ENEMY,0);
        }

        else if(enemy->counter_ANIM == 17)
        {
            enemy->counter_ANIM = 0;

            enemy->vulnerable = TRUE;
            
            enemy->state = ENEMY_THREAT_FW;

            SPR_setAnimAndFrame(enemy->spr_ENEMY , 0 , 0);

            return;
        }


        enemy->counter_ANIM += 1;  
    }


    //****************************************************************//
    //                                                                //
    //                              DEAD                              //
    //                                                                //
    //****************************************************************//

    else if(enemy->state == ENEMY_DEAD)
    {
        //----------------------------------------------------------------//
        //                                                                //
        //                          UPDATE FRAME                          //
        //                                                                //
        //----------------------------------------------------------------//

        if(enemy->counter_ANIM == 0)
        {
            SPR_setAnimAndFrame(enemy->spr_ENEMY , 6 , 0);
        }

        else if(enemy->counter_ANIM == 11)
        {
            SPR_setAnimAndFrame(enemy->spr_ENEMY , 6 , 1);
        }

        else if(enemy->counter_ANIM == 22)
        {
            SPR_setAnimAndFrame(enemy->spr_ENEMY , 6 , 2);
        }

        enemy->counter_ANIM += 1;


        //----------------------------------------------------------------//
        //                                                                //
        //                         UPDATE POSITION                        //
        //                                                                //
        //----------------------------------------------------------------//

        //----------------------------------------------------------------//
        //                            AXIS LEFT                           //
        //----------------------------------------------------------------//

        if(enemy->axis == AXIS_LEFT)
        {
            enemy->pos_X += 2;
        }


        //----------------------------------------------------------------//
        //                            AXIS RIGHT                          //
        //----------------------------------------------------------------//

        else
        {
            enemy->pos_X -= 2;
        }

        enemy->pos_Y += 3;


        SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);


        if(enemy->pos_Y > 224)
        {
            SPR_releaseSprite(enemy->spr_ENEMY);
            enemy->spr_ENEMY = NULL;

            G_NUMBER_ENEMY -= 1;
        }
    }
}




void update_KNIFE_MAN(struct_ENEMY_ *enemy)
{
    //****************************************************************//
    //                                                                //
    //                              WALK                              //
    //                                                                //
    //****************************************************************//

    if(enemy->state == ENEMY_WALK)
    {
        //----------------------------------------------------------------//
        //                                                                //
        //                     CHECK THREAT DISTANCE                      //
        //                                                                //
        //----------------------------------------------------------------//

        //----------------------------------------------------------------//
        //                            AXIS LEFT                           //
        //----------------------------------------------------------------//

        if(enemy->axis == AXIS_LEFT)
        {
            if((enemy->pos_X - 42) < player.pos_X)
            {
                enemy->state = ENEMY_THREAT_FW;

                enemy->counter_ANIM = 0;

                enemy->vulnerable = TRUE;

                return;
            }
        }

        //----------------------------------------------------------------//
        //                            AXIS RIGHT                          //
        //----------------------------------------------------------------//

        else
        {
            if((enemy->pos_X + 58) > player.pos_X)
            {
                enemy->state = ENEMY_THREAT_FW;

                enemy->counter_ANIM = 0;

                enemy->vulnerable = TRUE;

                return;
            }
        }
        
        
        
        enemy->counter_ANIM += 1;


        //----------------------------------------------------------------//
        //                                                                //
        //                         UPDATE POSITION                        //
        //                                                                //
        //----------------------------------------------------------------//

        //----------------------------------------------------------------//
        //                            AXIS LEFT                           //
        //----------------------------------------------------------------//

        if(enemy->axis == AXIS_LEFT)
        {
            if(enemy->counter_ANIM%2 == TRUE)
            {
                enemy->pos_X -= 2;
            }

            else
            {
                enemy->pos_X -= 1;
            }
        }
        
        //----------------------------------------------------------------//
        //                            AXIS RIGHT                          //
        //----------------------------------------------------------------//

        else
        {
            if(enemy->counter_ANIM%2 == TRUE)
            {
                enemy->pos_X += 2;
            }

            else
            {
                enemy->pos_X += 1;
            }
        }


        SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);




        //----------------------------------------------------------------//
        //                                                                //
        //                          UPDATE FRAME                          //
        //                                                                //
        //----------------------------------------------------------------//

        if(enemy->counter_ANIM == 21)
        {
            enemy->counter_ANIM = 0;
        }




        if(enemy->counter_ANIM == 0)
        {
            SPR_setAnimAndFrame(enemy->spr_ENEMY , 0 , 0);
        }

        else if(enemy->counter_ANIM == 5)
        {
            SPR_setAnimAndFrame(enemy->spr_ENEMY , 0 , 1);
        }

        else if(enemy->counter_ANIM == 11)
        {
            SPR_setAnimAndFrame(enemy->spr_ENEMY , 0 , 2);
        }

        else if(enemy->counter_ANIM == 16)
        {
            SPR_setAnimAndFrame(enemy->spr_ENEMY , 0 , 3);
        }
    }


    //****************************************************************//
    //                                                                //
    //                            THREAT FW                           //
    //                                                                //
    //****************************************************************//

    else if(enemy->state == ENEMY_THREAT_FW)
    {
        //----------------------------------------------------------------//
        //                                                                //
        //                     CHECK ATTACK DISTANCE                      //
        //                                                                //
        //----------------------------------------------------------------//

        //----------------------------------------------------------------//
        //                            AXIS LEFT                           //
        //----------------------------------------------------------------//

        if(enemy->axis == AXIS_LEFT)
        {
            //------------------------------------------------------//
            //             IF PLAYER IS AT PUNCH RANGE              //
            //------------------------------------------------------//
            if(player.state != STATE_DEAD)
            {
                if(enemy->pos_X <= (player.pos_X + 16)) // PLAYER_CENTER
                {
                    enemy->counter_ANIM = 0;

                    enemy->vulnerable = TRUE;

                    //enemy->state = random_NUMBER(6,7);

                    enemy->state = ENEMY_ATTACK_UP;

                    return;
                }
            }
        }

        //----------------------------------------------------------------//
        //                            AXIS RIGHT                          //
        //----------------------------------------------------------------//

        else if(enemy->axis == AXIS_RIGHT)
        {
            //------------------------------------------------------//
            //             IF PLAYER IS AT PUNCH RANGE              //
            //------------------------------------------------------//
            if(player.state != STATE_DEAD)
            {
                if(player.pos_X <= (enemy->pos_X + 32))
                {
                    enemy->counter_ANIM = 0;

                    enemy->vulnerable = TRUE;

                    //enemy->state = random_NUMBER(6,7);

                    enemy->state = ENEMY_ATTACK_UP;

                    return;
                }
            }
        }




        //----------------------------------------------------------------//
        //                                                                //
        //                    UPDATE FRAME AND POSITION                   //
        //                                                                //
        //----------------------------------------------------------------//

        if(enemy->counter_ANIM == 0)
        {
            SPR_setAnim(enemy->spr_ENEMY,1);
            SPR_setFrame(enemy->spr_ENEMY,0);
        }


        else if(enemy->counter_ANIM == 7 || enemy->counter_ANIM == 8 || enemy->counter_ANIM == 9 || enemy->counter_ANIM == 11 || enemy->counter_ANIM == 12 || enemy->counter_ANIM == 13)
        {
            SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X ,  enemy->pos_Y);
            
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X -= 1;
            }

            else
            {
                enemy->pos_X += 1;
            }
        }


        else if(enemy->counter_ANIM == 14)
        {
            SPR_setFrame(enemy->spr_ENEMY,1);
        }


        else if(enemy->counter_ANIM == 15 || enemy->counter_ANIM == 16 || enemy->counter_ANIM == 17 || enemy->counter_ANIM == 19 || enemy->counter_ANIM == 20 || enemy->counter_ANIM == 21)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X -= 1;
            }

            else
            {
                enemy->pos_X += 1;
            }

            SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X ,  enemy->pos_Y);
        }


        else if(enemy->counter_ANIM == 22)
        {
            SPR_setFrame(enemy->spr_ENEMY,2);
        }


        else if(enemy->counter_ANIM == 23 || enemy->counter_ANIM == 24 || enemy->counter_ANIM == 25 || enemy->counter_ANIM == 27 || enemy->counter_ANIM == 28 || enemy->counter_ANIM == 29)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X -= 1;
            }

            else
            {
                enemy->pos_X += 1;
            }

            SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X ,  enemy->pos_Y);
        }


        else if(enemy->counter_ANIM == 30)
        {
            SPR_setFrame(enemy->spr_ENEMY,3);
        }


        else if(enemy->counter_ANIM == 31 || enemy->counter_ANIM == 32 || enemy->counter_ANIM == 33 || enemy->counter_ANIM == 35 || enemy->counter_ANIM == 36 || enemy->counter_ANIM == 37)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X -= 1;
            }

            else
            {
                enemy->pos_X += 1;
            }

            SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X ,  enemy->pos_Y);
        }


        else if(enemy->counter_ANIM == 38)
        {
            // CHECK DISTANCE BETWEEN PUNK AND PLAYER //
            if(enemy->axis == AXIS_LEFT)
            {
                if((enemy->pos_X - 56) < player.pos_X)
                {
                    enemy->state = ENEMY_THREAT_FW;

                    enemy->counter_ANIM = 0;

                    SPR_setFrame(enemy->spr_ENEMY,0);

                    return;
                }

                else
                {
                    enemy->state = ENEMY_WALK;

                    enemy->counter_ANIM = 0;

                    SPR_setAnimAndFrame(enemy->spr_ENEMY,0,0);

                    return;
                }
            }

            else if(enemy->axis == AXIS_RIGHT)
            {
                if((enemy->pos_X + 48) > player.pos_X)
                {
                    enemy->state = ENEMY_THREAT_FW;

                    enemy->counter_ANIM = 0;

                    SPR_setFrame(enemy->spr_ENEMY,0);

                    return;
                }

                else
                {
                    enemy->state = ENEMY_WALK;

                    enemy->counter_ANIM = 0;

                    SPR_setAnimAndFrame(enemy->spr_ENEMY,0,0);

                    return;
                }
            }
        }


        enemy->counter_ANIM += 1;


        SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);
    }


    //****************************************************************//
    //                                                                //
    //                            THREAT BW                           //
    //                                                                //
    //****************************************************************//

    /*else if(enemy->state == ENEMY_THREAT_BW)
    {
        //----------------------------------------------------------------//
        //                                                                //
        //                    UPDATE FRAME AND POSITION                   //
        //                                                                //
        //----------------------------------------------------------------//

        if(enemy->counter_ANIM == 0)
        {
            SPR_setAnim(enemy->spr_ENEMY,1);
            SPR_setFrame(enemy->spr_ENEMY,3);
        }


        else if(enemy->counter_ANIM == 7 || enemy->counter_ANIM == 8 || enemy->counter_ANIM == 9 || enemy->counter_ANIM == 11 || enemy->counter_ANIM == 12 || enemy->counter_ANIM == 13)
        {
            SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X ,  enemy->pos_Y);
            
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            }
        }


        else if(enemy->counter_ANIM == 14)
        {
            SPR_setFrame(enemy->spr_ENEMY,2);
        }


        else if(enemy->counter_ANIM == 15 || enemy->counter_ANIM == 16 || enemy->counter_ANIM == 17 || enemy->counter_ANIM == 19 || enemy->counter_ANIM == 20 || enemy->counter_ANIM == 21)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            }

            SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X ,  enemy->pos_Y);
        }


        else if(enemy->counter_ANIM == 22)
        {
            SPR_setFrame(enemy->spr_ENEMY,1);
        }


        else if(enemy->counter_ANIM == 23 || enemy->counter_ANIM == 24 || enemy->counter_ANIM == 25 || enemy->counter_ANIM == 27 || enemy->counter_ANIM == 28 || enemy->counter_ANIM == 29)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            }

            SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X ,  enemy->pos_Y);
        }


        else if(enemy->counter_ANIM == 30)
        {
            SPR_setFrame(enemy->spr_ENEMY,0);
        }


        else if(enemy->counter_ANIM == 31 || enemy->counter_ANIM == 32 || enemy->counter_ANIM == 33 || enemy->counter_ANIM == 35 || enemy->counter_ANIM == 36 || enemy->counter_ANIM == 37)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            }

            SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X ,  enemy->pos_Y);
        }


        else if(enemy->counter_ANIM == 38)
        {
            enemy->state = ENEMY_THREAT_FW;

            enemy->counter_ANIM = 0;

            SPR_setFrame(enemy->spr_ENEMY,0);

            return;
        }


        enemy->counter_ANIM += 1;


        SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);
    }*/


    //****************************************************************//
    //                                                                //
    //                           ATTACK UP                            //
    //                                                                //
    //****************************************************************//

    else if(enemy->state == ENEMY_ATTACK_UP)
    {
        //----------------------------------------------------------------//
        //                                                                //
        //                          UPDATE FRAME                          //
        //                                                                //
        //----------------------------------------------------------------//

        if(enemy->counter_ANIM == 0)
        {
            SPR_setAnim(enemy->spr_ENEMY,2);
            SPR_setFrame(enemy->spr_ENEMY,0);

            SPR_setDepth(enemy->spr_ENEMY,1);
        }


        else if(enemy->counter_ANIM == 8)
        {
            SPR_setFrame(enemy->spr_ENEMY,1);

            // ENEMY IS ON TOP OF PLAYER //
            //SPR_setDepth(enemy->spr_ENEMY,1);
        }


        else if(enemy->counter_ANIM == 16)
        {
            SPR_setFrame(enemy->spr_ENEMY,2);
        }


        //------------------------------------------------------//
        //                                                      //
        //                        PUNCH 1                       //
        //                                                      //
        //------------------------------------------------------//
        else if(enemy->counter_ANIM == 24)
        {
            SPR_setFrame(enemy->spr_ENEMY,3);

            // ENEMY IS ON TOP OF PLAYER //
            SPR_setDepth(enemy->spr_ENEMY,1);


            if(player.state != STATE_CROUCH && player.state != STATE_PUNCH_CROUCH && player.state != STATE_KICK_CROUCH)
            {
                // CHECK COLLISION WITH PLAYER //
                if(enemy->axis == AXIS_LEFT)
                {
                    if(player.vulnerable == TRUE)
                    {
                        //------------------------------------------------------//
                        //        CHECK DISTANCE BETWEEN PUNK AND PLAYER        //
                        //------------------------------------------------------//
                        if(player.pos_X >= (enemy->pos_X - 40))
                        {
                            player.counter_ANIM_SPRITE = 0;

                            if(player.state != STATE_GRAB)
                            {
                                player.state = STATE_HIT_UP;

                                //player.vulnerable = FALSE;
                            }

                            player.life -= TABLE_ENEMY_TYPE[enemy->enemy_ID].damages;

                            if(player.life < FIX32(0))
                            {
                                player.life = FIX32(0);
                            }
                            

                            update_LIFE_PLAYER();


                            if(player.armed == TRUE)
                            {
                                // LOSE NUNCHUCK //
                                // A FAIRE //
                                
                                hide_NUNCHUCK();
                            }
                        }
                    }
                }


                else if(enemy->axis == AXIS_RIGHT)
                {
                    //if(player.state == STATE_IDLE || player.state == STATE_WALK || player.state == STATE_PUNCH || player.state == STATE_KICK || player.state == STATE_JUMP_H || player.state == STATE_JUMP_V || player.state == STATE_GRAB)
                    if(player.vulnerable == TRUE)
                    {
                        //------------------------------------------------------//
                        //        CHECK DISTANCE BETWEEN PUNK AND PLAYER        //
                        //------------------------------------------------------//
                        if(player.pos_X <= (enemy->pos_X + 56))
                        {
                            player.counter_ANIM_SPRITE = 0;

                            if(player.state != STATE_GRAB)
                            {
                                player.state = STATE_HIT_UP;

                                //player.vulnerable = FALSE;
                            }

                            player.life -= TABLE_ENEMY_TYPE[enemy->enemy_ID].damages;

                            if(player.life < FIX32(0))
                            {
                                player.life = FIX32(0);
                            }


                            update_LIFE_PLAYER();


                            if(player.armed == TRUE)
                            {
                                hide_NUNCHUCK();
                            }                        
                        }
                    }
                }
            }
        }


        else if(enemy->counter_ANIM == 32)
        {
            SPR_setAnimAndFrame(enemy->spr_ENEMY,1,0);
        }


        else if(enemy->counter_ANIM == 40)
        {
            //enemy->state = random_NUMBER(4,6); //ENEMY_THREAT_BW

            enemy->counter_ANIM = 0;

            //enemy->state = random_NUMBER(4,7);

            enemy->state = ENEMY_THREAT_FW;

            return;
        }        


        enemy->counter_ANIM += 1;


        SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);
    }


    //****************************************************************//
    //                                                                //
    //                       HIT UP & DOWN SLIDE                      //
    //                                                                //
    //****************************************************************//

    else if(enemy->state == ENEMY_HIT_UP_SLIDE || enemy->state == ENEMY_HIT_DOWN_SLIDE)
    {
        if(enemy->counter_ANIM == 0)
        {
            if(enemy->state == ENEMY_HIT_UP_SLIDE)
            {
                SPR_setAnim(enemy->spr_ENEMY,4);
                SPR_setFrame(enemy->spr_ENEMY,0);
            }

            else if(enemy->state == ENEMY_HIT_DOWN_SLIDE)
            {
                SPR_setAnim(enemy->spr_ENEMY,5);
                SPR_setFrame(enemy->spr_ENEMY,0);
            }
        }

        else if(enemy->counter_ANIM == 1)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 3;
            }

            else
            {
                enemy->pos_X -= 3;
            } 
        }

        else if(enemy->counter_ANIM == 2)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 2;
            }

            else
            {
                enemy->pos_X -= 2;
            } 
        }

        else if(enemy->counter_ANIM == 3)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 2;
            }

            else
            {
                enemy->pos_X -= 2;
            } 
        }

        else if(enemy->counter_ANIM == 4)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 3;
            }

            else
            {
                enemy->pos_X -= 3;
            } 
        }

        else if(enemy->counter_ANIM == 5)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            } 
        }

        else if(enemy->counter_ANIM == 6)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 2;
            }

            else
            {
                enemy->pos_X -= 2;
            } 
        }

        else if(enemy->counter_ANIM == 7)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 2;
            }

            else
            {
                enemy->pos_X -= 2;
            } 
        }

        else if(enemy->counter_ANIM == 8)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            } 
        }

        else if(enemy->counter_ANIM == 9)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            } 
        }

        else if(enemy->counter_ANIM == 10)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            } 
        }

        else if(enemy->counter_ANIM == 11)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            } 
        }

        else if(enemy->counter_ANIM == 13)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            } 
        }

        else if(enemy->counter_ANIM == 17)
        {
            enemy->counter_ANIM = 0;

            enemy->vulnerable = TRUE;
            
            enemy->state = ENEMY_WALK;

            SPR_setAnimAndFrame(enemy->spr_ENEMY , 0 , 0);

            //SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);

            return;
        }


        enemy->counter_ANIM += 1;


        SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);
    }


    //****************************************************************//
    //                                                                //
    //                             HIT UP                             //
    //                                                                //
    //****************************************************************//

    else if(enemy->state == ENEMY_HIT_UP)
    {
        //----------------------------------------------------------------//
        //                                                                //
        //                          UPDATE FRAME                          //
        //                                                                //
        //----------------------------------------------------------------//

        if(enemy->counter_ANIM == 0)
        {
            SPR_setAnim(enemy->spr_ENEMY,4);
            SPR_setFrame(enemy->spr_ENEMY,0 + G_REPEAT);
        }

        else if(enemy->counter_ANIM == 6)
        {
            SPR_setFrame(enemy->spr_ENEMY,2);
        }

        else if(enemy->counter_ANIM == 17)
        {
            enemy->counter_ANIM = 0;

            enemy->vulnerable = TRUE;
            
            enemy->state = ENEMY_THREAT_FW;

            return;
        }


        enemy->counter_ANIM += 1;        
    }


    //****************************************************************//
    //                                                                //
    //                            HIT DOWN                            //
    //                                                                //
    //****************************************************************//

    else if(enemy->state == ENEMY_HIT_DOWN)
    {
        //----------------------------------------------------------------//
        //                                                                //
        //                          UPDATE FRAME                          //
        //                                                                //
        //----------------------------------------------------------------//

        if(enemy->counter_ANIM == 0)
        {
            SPR_setAnim(enemy->spr_ENEMY,5);
            SPR_setFrame(enemy->spr_ENEMY,0);
        }

        else if(enemy->counter_ANIM == 17)
        {
            enemy->counter_ANIM = 0;

            enemy->vulnerable = TRUE;
            
            enemy->state = ENEMY_THREAT_FW;

            SPR_setAnimAndFrame(enemy->spr_ENEMY , 0 , 0);

            return;
        }


        enemy->counter_ANIM += 1;  
    }


    //****************************************************************//
    //                                                                //
    //                              DEAD                              //
    //                                                                //
    //****************************************************************//

    else if(enemy->state == ENEMY_DEAD)
    {
        //----------------------------------------------------------------//
        //                                                                //
        //                          UPDATE FRAME                          //
        //                                                                //
        //----------------------------------------------------------------//

        if(enemy->counter_ANIM == 0)
        {
            SPR_setAnimAndFrame(enemy->spr_ENEMY , 6 , 0);
        }

        else if(enemy->counter_ANIM == 11)
        {
            SPR_setAnimAndFrame(enemy->spr_ENEMY , 6 , 1);
        }

        else if(enemy->counter_ANIM == 22)
        {
            SPR_setAnimAndFrame(enemy->spr_ENEMY , 6 , 2);
        }

        enemy->counter_ANIM += 1;


        //----------------------------------------------------------------//
        //                                                                //
        //                         UPDATE POSITION                        //
        //                                                                //
        //----------------------------------------------------------------//

        //----------------------------------------------------------------//
        //                            AXIS LEFT                           //
        //----------------------------------------------------------------//

        if(enemy->axis == AXIS_LEFT)
        {
            enemy->pos_X += 2;
        }


        //----------------------------------------------------------------//
        //                            AXIS RIGHT                          //
        //----------------------------------------------------------------//

        else
        {
            enemy->pos_X -= 2;
        }

        enemy->pos_Y += 3;


        SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);


        if(enemy->pos_Y > 224)
        {
            SPR_releaseSprite(enemy->spr_ENEMY);
            enemy->spr_ENEMY = NULL;

            G_NUMBER_ENEMY -= 1;
        }
    }
}




void update_CHAIN_MAN(struct_ENEMY_ *enemy)
{
    //****************************************************************//
    //                                                                //
    //                              WALK                              //
    //                                                                //
    //****************************************************************//

    if(enemy->state == ENEMY_WALK)
    {
        //----------------------------------------------------------------//
        //                                                                //
        //                     CHECK THREAT DISTANCE                      //
        //                                                                //
        //----------------------------------------------------------------//

        //----------------------------------------------------------------//
        //                            AXIS LEFT                           //
        //----------------------------------------------------------------//

        if(enemy->axis == AXIS_LEFT)
        {
            if((enemy->pos_X - 42) < player.pos_X)
            {
                enemy->state = ENEMY_THREAT_FW;

                enemy->counter_ANIM = 0;

                enemy->vulnerable = TRUE;

                return;
            }
        }

        //----------------------------------------------------------------//
        //                            AXIS RIGHT                          //
        //----------------------------------------------------------------//

        else
        {
            if((enemy->pos_X + 58) > player.pos_X)
            {
                enemy->state = ENEMY_THREAT_FW;

                enemy->counter_ANIM = 0;

                enemy->vulnerable = TRUE;

                return;
            }
        }
        
        
        
        enemy->counter_ANIM += 1;


        //----------------------------------------------------------------//
        //                                                                //
        //                         UPDATE POSITION                        //
        //                                                                //
        //----------------------------------------------------------------//

        //----------------------------------------------------------------//
        //                            AXIS LEFT                           //
        //----------------------------------------------------------------//

        if(enemy->axis == AXIS_LEFT)
        {
            if(enemy->counter_ANIM%2 == TRUE)
            {
                enemy->pos_X -= 2;
            }

            else
            {
                enemy->pos_X -= 1;
            }
        }
        
        //----------------------------------------------------------------//
        //                            AXIS RIGHT                          //
        //----------------------------------------------------------------//

        else
        {
            if(enemy->counter_ANIM%2 == TRUE)
            {
                enemy->pos_X += 2;
            }

            else
            {
                enemy->pos_X += 1;
            }
        }


        SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);




        //----------------------------------------------------------------//
        //                                                                //
        //                          UPDATE FRAME                          //
        //                                                                //
        //----------------------------------------------------------------//

        if(enemy->counter_ANIM == 21)
        {
            enemy->counter_ANIM = 0;
        }




        if(enemy->counter_ANIM == 0)
        {
            SPR_setAnimAndFrame(enemy->spr_ENEMY , 0 , 0);
        }

        else if(enemy->counter_ANIM == 5)
        {
            SPR_setAnimAndFrame(enemy->spr_ENEMY , 0 , 1);
        }

        else if(enemy->counter_ANIM == 11)
        {
            SPR_setAnimAndFrame(enemy->spr_ENEMY , 0 , 2);
        }

        else if(enemy->counter_ANIM == 16)
        {
            SPR_setAnimAndFrame(enemy->spr_ENEMY , 0 , 3);
        }
    }


    //****************************************************************//
    //                                                                //
    //                            THREAT FW                           //
    //                                                                //
    //****************************************************************//

    else if(enemy->state == ENEMY_THREAT_FW)
    {
        //----------------------------------------------------------------//
        //                                                                //
        //                     CHECK ATTACK DISTANCE                      //
        //                                                                //
        //----------------------------------------------------------------//

        //----------------------------------------------------------------//
        //                            AXIS LEFT                           //
        //----------------------------------------------------------------//

        if(enemy->axis == AXIS_LEFT)
        {
            //------------------------------------------------------//
            //             IF PLAYER IS AT PUNCH RANGE              //
            //------------------------------------------------------//
            if(player.state != STATE_DEAD)
            {
                if(enemy->pos_X <= (player.pos_X + 16)) // PLAYER_CENTER
                {
                    enemy->counter_ANIM = 0;

                    enemy->vulnerable = TRUE;

                    enemy->state = random_NUMBER(6,7);

                    //enemy->state = ENEMY_ATTACK_UP;

                    return;
                }
            }
        }

        //----------------------------------------------------------------//
        //                            AXIS RIGHT                          //
        //----------------------------------------------------------------//

        else if(enemy->axis == AXIS_RIGHT)
        {
            //------------------------------------------------------//
            //             IF PLAYER IS AT PUNCH RANGE              //
            //------------------------------------------------------//
            if(player.state != STATE_DEAD)
            {
                if(player.pos_X <= (enemy->pos_X + 32))
                {
                    enemy->counter_ANIM = 0;

                    enemy->vulnerable = TRUE;

                    enemy->state = random_NUMBER(6,7);

                    //enemy->state = ENEMY_ATTACK_UP;

                    return;
                }
            }
        }




        //----------------------------------------------------------------//
        //                                                                //
        //                    UPDATE FRAME AND POSITION                   //
        //                                                                //
        //----------------------------------------------------------------//

        if(enemy->counter_ANIM == 0)
        {
            SPR_setAnim(enemy->spr_ENEMY,1);
            SPR_setFrame(enemy->spr_ENEMY,0);
        }


        else if(enemy->counter_ANIM == 7 || enemy->counter_ANIM == 8 || enemy->counter_ANIM == 9 || enemy->counter_ANIM == 11 || enemy->counter_ANIM == 12 || enemy->counter_ANIM == 13)
        {
            SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X ,  enemy->pos_Y);
            
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X -= 1;
            }

            else
            {
                enemy->pos_X += 1;
            }
        }


        else if(enemy->counter_ANIM == 14)
        {
            SPR_setFrame(enemy->spr_ENEMY,1);
        }


        else if(enemy->counter_ANIM == 15 || enemy->counter_ANIM == 16 || enemy->counter_ANIM == 17 || enemy->counter_ANIM == 19 || enemy->counter_ANIM == 20 || enemy->counter_ANIM == 21)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X -= 1;
            }

            else
            {
                enemy->pos_X += 1;
            }

            SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X ,  enemy->pos_Y);
        }


        else if(enemy->counter_ANIM == 22)
        {
            SPR_setFrame(enemy->spr_ENEMY,2);
        }


        else if(enemy->counter_ANIM == 23 || enemy->counter_ANIM == 24 || enemy->counter_ANIM == 25 || enemy->counter_ANIM == 27 || enemy->counter_ANIM == 28 || enemy->counter_ANIM == 29)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X -= 1;
            }

            else
            {
                enemy->pos_X += 1;
            }

            SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X ,  enemy->pos_Y);
        }


        else if(enemy->counter_ANIM == 30)
        {
            SPR_setFrame(enemy->spr_ENEMY,3);
        }


        else if(enemy->counter_ANIM == 31 || enemy->counter_ANIM == 32 || enemy->counter_ANIM == 33 || enemy->counter_ANIM == 35 || enemy->counter_ANIM == 36 || enemy->counter_ANIM == 37)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X -= 1;
            }

            else
            {
                enemy->pos_X += 1;
            }

            SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X ,  enemy->pos_Y);
        }


        else if(enemy->counter_ANIM == 38)
        {
            // CHECK DISTANCE BETWEEN PUNK AND PLAYER //
            if(enemy->axis == AXIS_LEFT)
            {
                if((enemy->pos_X - 56) < player.pos_X)
                {
                    enemy->state = ENEMY_THREAT_FW;

                    enemy->counter_ANIM = 0;

                    SPR_setFrame(enemy->spr_ENEMY,0);

                    return;
                }

                else
                {
                    enemy->state = ENEMY_WALK;

                    enemy->counter_ANIM = 0;

                    SPR_setAnimAndFrame(enemy->spr_ENEMY,0,0);

                    return;
                }
            }

            else if(enemy->axis == AXIS_RIGHT)
            {
                if((enemy->pos_X + 48) > player.pos_X)
                {
                    enemy->state = ENEMY_THREAT_FW;

                    enemy->counter_ANIM = 0;

                    SPR_setFrame(enemy->spr_ENEMY,0);

                    return;
                }

                else
                {
                    enemy->state = ENEMY_WALK;

                    enemy->counter_ANIM = 0;

                    SPR_setAnimAndFrame(enemy->spr_ENEMY,0,0);

                    return;
                }
            }
        }


        enemy->counter_ANIM += 1;


        SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);
    }


    //****************************************************************//
    //                                                                //
    //                            THREAT BW                           //
    //                                                                //
    //****************************************************************//

    else if(enemy->state == ENEMY_THREAT_BW)
    {
        //----------------------------------------------------------------//
        //                                                                //
        //                    UPDATE FRAME AND POSITION                   //
        //                                                                //
        //----------------------------------------------------------------//

        if(enemy->counter_ANIM == 0)
        {
            SPR_setAnim(enemy->spr_ENEMY,1);
            SPR_setFrame(enemy->spr_ENEMY,3);
        }


        else if(enemy->counter_ANIM == 7 || enemy->counter_ANIM == 8 || enemy->counter_ANIM == 9 || enemy->counter_ANIM == 11 || enemy->counter_ANIM == 12 || enemy->counter_ANIM == 13)
        {
            SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X ,  enemy->pos_Y);
            
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            }
        }


        else if(enemy->counter_ANIM == 14)
        {
            SPR_setFrame(enemy->spr_ENEMY,2);
        }


        else if(enemy->counter_ANIM == 15 || enemy->counter_ANIM == 16 || enemy->counter_ANIM == 17 || enemy->counter_ANIM == 19 || enemy->counter_ANIM == 20 || enemy->counter_ANIM == 21)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            }

            SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X ,  enemy->pos_Y);
        }


        else if(enemy->counter_ANIM == 22)
        {
            SPR_setFrame(enemy->spr_ENEMY,1);
        }


        else if(enemy->counter_ANIM == 23 || enemy->counter_ANIM == 24 || enemy->counter_ANIM == 25 || enemy->counter_ANIM == 27 || enemy->counter_ANIM == 28 || enemy->counter_ANIM == 29)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            }

            SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X ,  enemy->pos_Y);
        }


        else if(enemy->counter_ANIM == 30)
        {
            SPR_setFrame(enemy->spr_ENEMY,0);
        }


        else if(enemy->counter_ANIM == 31 || enemy->counter_ANIM == 32 || enemy->counter_ANIM == 33 || enemy->counter_ANIM == 35 || enemy->counter_ANIM == 36 || enemy->counter_ANIM == 37)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            }

            SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X ,  enemy->pos_Y);
        }


        else if(enemy->counter_ANIM == 38)
        {
            enemy->state = ENEMY_THREAT_FW;

            enemy->counter_ANIM = 0;

            SPR_setFrame(enemy->spr_ENEMY,0);

            return;
        }


        enemy->counter_ANIM += 1;


        SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);
    }


    //****************************************************************//
    //                                                                //
    //                           ATTACK UP                            //
    //                                                                //
    //****************************************************************//

    else if(enemy->state == ENEMY_ATTACK_UP)
    {
        //----------------------------------------------------------------//
        //                                                                //
        //                          UPDATE FRAME                          //
        //                                                                //
        //----------------------------------------------------------------//

        if(enemy->counter_ANIM == 0)
        {
            SPR_setAnim(enemy->spr_ENEMY,2);
            SPR_setFrame(enemy->spr_ENEMY,0);
        }


        else if(enemy->counter_ANIM == 8)
        {
            SPR_setFrame(enemy->spr_ENEMY,1);

            // ENEMY IS ON TOP OF PLAYER //
            SPR_setDepth(enemy->spr_ENEMY,1);
        }


        //------------------------------------------------------//
        //                                                      //
        //                        PUNCH 1                       //
        //                                                      //
        //------------------------------------------------------//
        else if(enemy->counter_ANIM == 16)
        {
            SPR_setFrame(enemy->spr_ENEMY,2);

            // ENEMY IS ON TOP OF PLAYER //
            SPR_setDepth(enemy->spr_ENEMY,1);


            if(player.state != STATE_CROUCH && player.state != STATE_PUNCH_CROUCH && player.state != STATE_KICK_CROUCH)
            {
                // CHECK COLLISION WITH PLAYER //
                if(enemy->axis == AXIS_LEFT)
                {
                    if(player.vulnerable == TRUE)
                    {
                        //------------------------------------------------------//
                        //        CHECK DISTANCE BETWEEN PUNK AND PLAYER        //
                        //------------------------------------------------------//
                        if(player.pos_X >= (enemy->pos_X - 40))
                        {
                            player.counter_ANIM_SPRITE = 0;

                            if(player.state != STATE_GRAB)
                            {
                                player.state = STATE_HIT_UP;

                                //player.vulnerable = FALSE;
                            }

                            player.life -= TABLE_ENEMY_TYPE[enemy->enemy_ID].damages;

                            if(player.life < FIX32(0))
                            {
                                player.life = FIX32(0);
                            }
                            

                            update_LIFE_PLAYER();


                            if(player.armed == TRUE)
                            {
                                // LOSE NUNCHUCK //
                                // A FAIRE //
                                
                                hide_NUNCHUCK();
                            }
                        }
                    }
                }


                else if(enemy->axis == AXIS_RIGHT)
                {
                    //if(player.state == STATE_IDLE || player.state == STATE_WALK || player.state == STATE_PUNCH || player.state == STATE_KICK || player.state == STATE_JUMP_H || player.state == STATE_JUMP_V || player.state == STATE_GRAB)
                    if(player.vulnerable == TRUE)
                    {
                        //------------------------------------------------------//
                        //        CHECK DISTANCE BETWEEN PUNK AND PLAYER        //
                        //------------------------------------------------------//
                        if(player.pos_X <= (enemy->pos_X + 56))
                        {
                            player.counter_ANIM_SPRITE = 0;

                            if(player.state != STATE_GRAB)
                            {
                                player.state = STATE_HIT_UP;

                                //player.vulnerable = FALSE;
                            }

                            player.life -= TABLE_ENEMY_TYPE[enemy->enemy_ID].damages;

                            if(player.life < FIX32(0))
                            {
                                player.life = FIX32(0);
                            }


                            update_LIFE_PLAYER();


                            if(player.armed == TRUE)
                            {
                                hide_NUNCHUCK();
                            }                        
                        }
                    }
                }
            }
        }


        else if(enemy->counter_ANIM == 24)
        {
            SPR_setAnimAndFrame(enemy->spr_ENEMY,1,0);
        }


        else if(enemy->counter_ANIM == 32)
        {
            //enemy->state = random_NUMBER(4,6); //ENEMY_THREAT_BW

            enemy->counter_ANIM = 0;

            enemy->state = random_NUMBER(4,7);

            return;
        }        


        enemy->counter_ANIM += 1;


        SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);
    }


    //****************************************************************//
    //                                                                //
    //                          ATTACK DOWN                           //
    //                                                                //
    //****************************************************************//

    else if(enemy->state == ENEMY_ATTACK_DOWN)
    {
        //----------------------------------------------------------------//
        //                                                                //
        //                          UPDATE FRAME                          //
        //                                                                //
        //----------------------------------------------------------------//

        if(enemy->counter_ANIM == 0)
        {
            SPR_setAnim(enemy->spr_ENEMY,3);
            SPR_setFrame(enemy->spr_ENEMY,0);
        }


        else if(enemy->counter_ANIM == 8)
        {
            SPR_setFrame(enemy->spr_ENEMY,1);

            // ENEMY IS ON TOP OF PLAYER //
            SPR_setDepth(enemy->spr_ENEMY,1);
        }


        //------------------------------------------------------//
        //                                                      //
        //                        PUNCH 1                       //
        //                                                      //
        //------------------------------------------------------//
        else if(enemy->counter_ANIM == 16)
        {
            SPR_setFrame(enemy->spr_ENEMY,2);

            // ENEMY IS ON TOP OF PLAYER //
            SPR_setDepth(enemy->spr_ENEMY,1);


            if(player.state != STATE_JUMP_V && player.state != STATE_JUMP_H && player.state != STATE_JUMP_KICK && player.state != STATE_JUMP_KICK_BW)
            {
                // CHECK COLLISION WITH PLAYER //
                if(enemy->axis == AXIS_LEFT)
                {
                    if(player.vulnerable == TRUE)
                    {
                        //------------------------------------------------------//
                        //        CHECK DISTANCE BETWEEN PUNK AND PLAYER        //
                        //------------------------------------------------------//
                        if(player.pos_X >= (enemy->pos_X - 40))
                        {
                            player.counter_ANIM_SPRITE = 0;

                            if(player.state != STATE_GRAB)
                            {
                                player.state = STATE_HIT_DOWN;

                                player.vulnerable = FALSE;
                            }

                            player.life -= TABLE_ENEMY_TYPE[enemy->enemy_ID].damages;

                            if(player.life < FIX32(0))
                            {
                                player.life = FIX32(0);
                            }
                            

                            update_LIFE_PLAYER();


                            if(player.armed == TRUE)
                            {
                                hide_NUNCHUCK();
                            }
                        }
                    }
                }


                else if(enemy->axis == AXIS_RIGHT)
                {
                    if(player.vulnerable == TRUE)
                    {
                        //------------------------------------------------------//
                        //        CHECK DISTANCE BETWEEN PUNK AND PLAYER        //
                        //------------------------------------------------------//
                        if(player.pos_X <= (enemy->pos_X + 56))
                        {
                            player.counter_ANIM_SPRITE = 0;

                            if(player.state != STATE_GRAB)
                            {
                                player.state = STATE_HIT_DOWN;

                                player.vulnerable = FALSE;
                            }

                            player.life -= TABLE_ENEMY_TYPE[enemy->enemy_ID].damages;

                            if(player.life < FIX32(0))
                            {
                                player.life = FIX32(0);
                            }


                            update_LIFE_PLAYER();


                            if(player.armed == TRUE)
                            {
                                hide_NUNCHUCK();
                            }                        
                        }
                    }
                }
            }
        }


        else if(enemy->counter_ANIM == 24)
        {
            SPR_setAnimAndFrame(enemy->spr_ENEMY,1,0);
        }


        else if(enemy->counter_ANIM == 32)
        {
            enemy->counter_ANIM = 0;

            enemy->state = random_NUMBER(4,7);

            return;
        }        


        enemy->counter_ANIM += 1;


        SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);
    }


    //****************************************************************//
    //                                                                //
    //                       HIT UP & DOWN SLIDE                      //
    //                                                                //
    //****************************************************************//

    else if(enemy->state == ENEMY_HIT_UP_SLIDE || enemy->state == ENEMY_HIT_DOWN_SLIDE)
    {
        if(enemy->counter_ANIM == 0)
        {
            if(enemy->state == ENEMY_HIT_UP_SLIDE)
            {
                SPR_setAnim(enemy->spr_ENEMY,4);
                SPR_setFrame(enemy->spr_ENEMY,0);
            }

            else if(enemy->state == ENEMY_HIT_DOWN_SLIDE)
            {
                SPR_setAnim(enemy->spr_ENEMY,5);
                SPR_setFrame(enemy->spr_ENEMY,0);
            }
        }

        else if(enemy->counter_ANIM == 1)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 3;
            }

            else
            {
                enemy->pos_X -= 3;
            } 
        }

        else if(enemy->counter_ANIM == 2)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 2;
            }

            else
            {
                enemy->pos_X -= 2;
            } 
        }

        else if(enemy->counter_ANIM == 3)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 2;
            }

            else
            {
                enemy->pos_X -= 2;
            } 
        }

        else if(enemy->counter_ANIM == 4)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 3;
            }

            else
            {
                enemy->pos_X -= 3;
            } 
        }

        else if(enemy->counter_ANIM == 5)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            } 
        }

        else if(enemy->counter_ANIM == 6)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 2;
            }

            else
            {
                enemy->pos_X -= 2;
            } 
        }

        else if(enemy->counter_ANIM == 7)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 2;
            }

            else
            {
                enemy->pos_X -= 2;
            } 
        }

        else if(enemy->counter_ANIM == 8)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            } 
        }

        else if(enemy->counter_ANIM == 9)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            } 
        }

        else if(enemy->counter_ANIM == 10)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            } 
        }

        else if(enemy->counter_ANIM == 11)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            } 
        }

        else if(enemy->counter_ANIM == 13)
        {
            if(enemy->axis == AXIS_LEFT)
            {
                enemy->pos_X += 1;
            }

            else
            {
                enemy->pos_X -= 1;
            } 
        }

        else if(enemy->counter_ANIM == 17)
        {
            enemy->counter_ANIM = 0;

            enemy->vulnerable = TRUE;
            
            enemy->state = ENEMY_WALK;

            SPR_setAnimAndFrame(enemy->spr_ENEMY , 0 , 0);

            //SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);

            return;
        }


        enemy->counter_ANIM += 1;


        SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);
    }


    //****************************************************************//
    //                                                                //
    //                             HIT UP                             //
    //                                                                //
    //****************************************************************//

    else if(enemy->state == ENEMY_HIT_UP)
    {
        //----------------------------------------------------------------//
        //                                                                //
        //                          UPDATE FRAME                          //
        //                                                                //
        //----------------------------------------------------------------//

        if(enemy->counter_ANIM == 0)
        {
            SPR_setAnim(enemy->spr_ENEMY,4);
            SPR_setFrame(enemy->spr_ENEMY,0 + G_REPEAT);
        }

        else if(enemy->counter_ANIM == 6)
        {
            SPR_setFrame(enemy->spr_ENEMY,2);
        }

        else if(enemy->counter_ANIM == 17)
        {
            enemy->counter_ANIM = 0;

            enemy->vulnerable = TRUE;
            
            enemy->state = ENEMY_THREAT_FW;

            return;
        }


        enemy->counter_ANIM += 1;         
    }


    //****************************************************************//
    //                                                                //
    //                            HIT DOWN                            //
    //                                                                //
    //****************************************************************//

    else if(enemy->state == ENEMY_HIT_DOWN)
    {
        //----------------------------------------------------------------//
        //                                                                //
        //                          UPDATE FRAME                          //
        //                                                                //
        //----------------------------------------------------------------//

        if(enemy->counter_ANIM == 0)
        {
            SPR_setAnim(enemy->spr_ENEMY,5);
            SPR_setFrame(enemy->spr_ENEMY,0);
        }

        else if(enemy->counter_ANIM == 17)
        {
            enemy->counter_ANIM = 0;

            enemy->vulnerable = TRUE;
            
            enemy->state = ENEMY_THREAT_FW;

            SPR_setAnimAndFrame(enemy->spr_ENEMY , 0 , 0);

            return;
        }


        enemy->counter_ANIM += 1;  
    }


    //****************************************************************//
    //                                                                //
    //                              DEAD                              //
    //                                                                //
    //****************************************************************//

    else if(enemy->state == ENEMY_DEAD)
    {
        //----------------------------------------------------------------//
        //                                                                //
        //                          UPDATE FRAME                          //
        //                                                                //
        //----------------------------------------------------------------//

        if(enemy->counter_ANIM == 0)
        {
            SPR_setAnimAndFrame(enemy->spr_ENEMY , 6 , 0);
        }

        else if(enemy->counter_ANIM == 11)
        {
            SPR_setAnimAndFrame(enemy->spr_ENEMY , 6 , 1);
        }

        else if(enemy->counter_ANIM == 22)
        {
            SPR_setAnimAndFrame(enemy->spr_ENEMY , 6 , 2);
        }

        enemy->counter_ANIM += 1;


        //----------------------------------------------------------------//
        //                                                                //
        //                         UPDATE POSITION                        //
        //                                                                //
        //----------------------------------------------------------------//

        //----------------------------------------------------------------//
        //                            AXIS LEFT                           //
        //----------------------------------------------------------------//

        if(enemy->axis == AXIS_LEFT)
        {
            enemy->pos_X += 2;
        }


        //----------------------------------------------------------------//
        //                            AXIS RIGHT                          //
        //----------------------------------------------------------------//

        else
        {
            enemy->pos_X -= 2;
        }

        enemy->pos_Y += 3;


        SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);


        if(enemy->pos_Y > 224)
        {
            SPR_releaseSprite(enemy->spr_ENEMY);
            enemy->spr_ENEMY = NULL;

            G_NUMBER_ENEMY -= 1;
        }
    }
}




void (*TABLE_ENEMY_AI[6])(struct_ENEMY_ *enemy)      =   {
                                                            update_DUDE,
                                                            update_PUNK,
                                                            update_KNIFE_MAN,
                                                            update_CHAIN_MAN,
                                                            NULL,
                                                            update_CHAIN_MAN
                                                        };




inline static void update_ENEMY()
{
    u8 i = 0;

    for(i=0 ; i<4 ; i++)
    {
        if(LIST_ENEMIES[i].spr_ENEMY != NULL)
        {
            // POINTER TO FUNCTION DECLARATION //
            void (*ptr_ENEMY_AI)(struct_ENEMY_ *enemy);

            // GET ENEMY TYPE //
            u8 enemy_ID = LIST_ENEMIES[i].enemy_ID;

            // SETTING FUNCTION POINTER TO AI FUNCTION //
            ptr_ENEMY_AI = TABLE_ENEMY_AI[enemy_ID];

            // SETTING POINTER TO ENEMY //
            struct_ENEMY_ *ptr_ENEMY = &LIST_ENEMIES[i];

            // RUNNING AI FUNCTION //
            (*ptr_ENEMY_AI)(ptr_ENEMY);
        }
    }
}















void sequence_LEVEL_1()
{
    if(G_PHASE_LEVEL == LEVEL_ENTER)
    {
        if(player.pos_X < 73)
        {
            player.state = STATE_WALK;

            player.vulnerable = TRUE;

            player.pos_X += 1;

            SPR_setPosition(player.spr_PLAYER , player.pos_X , player.pos_Y);

            update_PLAYER_SPRITE();
        }


        G_COUNTER += 1;


        if(G_COUNTER == 123)
        {
            XGM_stopPlay();
            
            player.state = STATE_IDLE;

            player.vulnerable = TRUE;

            player.pos_X_RESPAWN = player.pos_X;

            if(player.armed == FALSE)
            {
                SPR_setAnimAndFrame(player.spr_PLAYER,0,0);
            }

            else
            {
                SPR_setAnimAndFrame(player.spr_PLAYER,14,0);
            }

            G_PHASE_LEVEL = LEVEL_PLAY;

            SPR_releaseSprite(sprite_STAGE);
            sprite_STAGE = NULL;

            if(G_COLORS_OPTION == MD_COLORS)
            {
                PAL_setPalette(PAL2,palette_ENEMY_1_MD.data,DMA_QUEUE);
            }

            else
            {
                //PAL_setPalette(PAL2,palette_ENEMY_1_PCE.data,DMA_QUEUE);
                PAL_setPalette(PAL2,palette_ENEMY_1_MD.data,DMA_QUEUE);
            }


            XGM_startPlay(MUSIC_LEVEL_1);
        }
    }


    else if(G_PHASE_LEVEL == LEVEL_PLAY)
    {
        update_TIME();
        
        joypad_PLAYER();
        collision_PLAYER_ATTACK();
        update_PLAYER_SPRITE();

        spawn_ENEMY_LEVEL_1();
        update_ENEMY();


        //spawn_KNIFE_MAN_RIGHT();
        //spawn_PUNK_RIGHT();

        //VDP_drawIntEx_WINDOW_QUEUE_PRIO(player.vulnerable,1,0,0,PAL3);
    }


    else if(G_PHASE_LEVEL == LEVEL_END)
    {
        //
    }
}




void sequence_LEVEL_2()
{
    if(G_PHASE_LEVEL == LEVEL_ENTER)
    {
        if(player.pos_X < 87)
        {
            player.state = STATE_WALK;

            player.vulnerable = TRUE;

            player.pos_X += 1;

            SPR_setPosition(player.spr_PLAYER , player.pos_X , player.pos_Y);

            update_PLAYER_SPRITE();
        }



        G_COUNTER += 1;

        if(G_COUNTER == 123)
        {
            player.state = STATE_IDLE;

            player.vulnerable = TRUE;

            if(player.armed == FALSE)
            {
                SPR_setAnimAndFrame(player.spr_PLAYER,0,0);
            }

            else
            {
                SPR_setAnimAndFrame(player.spr_PLAYER,14,0);
            }

            G_PHASE_LEVEL = LEVEL_PLAY;

            SPR_releaseSprite(sprite_STAGE);
            sprite_STAGE = NULL;

            if(G_COLORS_OPTION == MD_COLORS)
            {
                PAL_setPalette(PAL2,palette_ENEMY_1_MD.data,DMA_QUEUE);
            }

            else
            {
                PAL_setPalette(PAL2,palette_ENEMY_1_PCE.data,DMA_QUEUE);
            }
        }
    }


    else if(G_PHASE_LEVEL == LEVEL_PLAY)
    {
        joypad_PLAYER();

        //collision_PLAYER_ATTACK();

        //spawn_ENEMY_LEVEL_1();
        //update_ENEMY();

        update_PLAYER_SPRITE();
    }


    else if(G_PHASE_LEVEL == LEVEL_END)
    {
        //
    }

}




void sequence_LEVEL_3()
{
    if(G_PHASE_LEVEL == LEVEL_ENTER)
    {
        if(player.pos_X < 87)
        {
            player.state = STATE_WALK;

            player.vulnerable = TRUE;

            player.pos_X += 1;

            SPR_setPosition(player.spr_PLAYER , player.pos_X , player.pos_Y);

            update_PLAYER_SPRITE();
        }



        G_COUNTER += 1;

        if(G_COUNTER == 123)
        {
            player.state = STATE_IDLE;

            player.vulnerable = TRUE;

            if(player.armed == FALSE)
            {
                SPR_setAnimAndFrame(player.spr_PLAYER,0,0);
            }

            else
            {
                SPR_setAnimAndFrame(player.spr_PLAYER,14,0);
            }

            G_PHASE_LEVEL = LEVEL_PLAY;

            SPR_releaseSprite(sprite_STAGE);
            sprite_STAGE = NULL;

            if(G_COLORS_OPTION == MD_COLORS)
            {
                PAL_setPalette(PAL2,palette_ENEMY_1_MD.data,DMA_QUEUE);
            }

            else
            {
                PAL_setPalette(PAL2,palette_ENEMY_1_PCE.data,DMA_QUEUE);
            }
        }
    }


    else if(G_PHASE_LEVEL == LEVEL_PLAY)
    {
        joypad_PLAYER();

        //collision_PLAYER_ATTACK();

        //spawn_ENEMY_LEVEL_1();
        //update_ENEMY();

        update_PLAYER_SPRITE();
    }


    else if(G_PHASE_LEVEL == LEVEL_END)
    {
        //
    }

}




void sequence_LEVEL_4()
{
    if(G_PHASE_LEVEL == LEVEL_ENTER)
    {
        if(player.pos_X < 87)
        {
            player.state = STATE_WALK;

            player.vulnerable = TRUE;

            player.pos_X += 1;

            SPR_setPosition(player.spr_PLAYER , player.pos_X , player.pos_Y);

            update_PLAYER_SPRITE();
        }



        G_COUNTER += 1;

        if(G_COUNTER == 123)
        {
            player.state = STATE_IDLE;

            if(player.armed == FALSE)
            {
                SPR_setAnimAndFrame(player.spr_PLAYER,0,0);
            }

            else
            {
                SPR_setAnimAndFrame(player.spr_PLAYER,14,0);
            }

            G_PHASE_LEVEL = LEVEL_PLAY;

            SPR_releaseSprite(sprite_STAGE);
            sprite_STAGE = NULL;

            if(G_COLORS_OPTION == MD_COLORS)
            {
                PAL_setPalette(PAL2,palette_ENEMY_1_MD.data,DMA_QUEUE);
            }

            else
            {
                PAL_setPalette(PAL2,palette_ENEMY_1_PCE.data,DMA_QUEUE);
            }
        }
    }


    else if(G_PHASE_LEVEL == LEVEL_PLAY)
    {
        joypad_PLAYER();

        //collision_PLAYER_ATTACK();

        //spawn_ENEMY_LEVEL_1();
        //update_ENEMY();

        update_PLAYER_SPRITE();
    }


    else if(G_PHASE_LEVEL == LEVEL_END)
    {
        //
    }

}




void sequence_LEVEL_5()
{
    if(G_PHASE_LEVEL == LEVEL_ENTER)
    {
        if(player.pos_X < 87)
        {
            player.state = STATE_WALK;

            player.vulnerable = TRUE;

            player.pos_X += 1;

            SPR_setPosition(player.spr_PLAYER , player.pos_X , player.pos_Y);

            update_PLAYER_SPRITE();
        }



        G_COUNTER += 1;

        if(G_COUNTER == 123)
        {
            player.state = STATE_IDLE;

            player.vulnerable = TRUE;

            if(player.armed == FALSE)
            {
                SPR_setAnimAndFrame(player.spr_PLAYER,0,0);
            }

            else
            {
                SPR_setAnimAndFrame(player.spr_PLAYER,14,0);
            }

            G_PHASE_LEVEL = LEVEL_PLAY;

            SPR_releaseSprite(sprite_STAGE);
            sprite_STAGE = NULL;

            if(G_COLORS_OPTION == MD_COLORS)
            {
                PAL_setPalette(PAL2,palette_ENEMY_1_MD.data,DMA_QUEUE);
            }

            else
            {
                PAL_setPalette(PAL2,palette_ENEMY_1_PCE.data,DMA_QUEUE);
            }
        }
    }


    else if(G_PHASE_LEVEL == LEVEL_PLAY)
    {
        joypad_PLAYER();

        //collision_PLAYER_ATTACK();

        //spawn_ENEMY_LEVEL_1();
        //update_ENEMY();

        update_PLAYER_SPRITE();
    }


    else if(G_PHASE_LEVEL == LEVEL_END)
    {
        //
    }

}




