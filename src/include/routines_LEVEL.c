#include <genesis.h>



#include "custom_tools.h"
#include "palettes.h"
#include "structures.h"
#include "variables.h"




#include "maps_LEVELS.h"




#include "TABLES_LEVELS.h"









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
    
}




void update_PLAYER_SPRITE()
{
    if(player.state == STATE_WALK)
    {        
        if(player.counter_ANIM == 0)
        {
            SPR_setAnimAndFrame(sprite_PLAYER,0,0);
        }
        
        else if(player.counter_ANIM == 8)
        {
            SPR_setAnimAndFrame(sprite_PLAYER,0,1);
        }

        else if(player.counter_ANIM == 16)
        {
            SPR_setAnimAndFrame(sprite_PLAYER,0,2);
        }

        else if(player.counter_ANIM == 24)
        {
            SPR_setAnimAndFrame(sprite_PLAYER,0,3);
        }


        player.counter_ANIM += 1;

        if(player.counter_ANIM == 32)
        {
            player.counter_ANIM = 0;
        }
    }


    else if(player.state == STATE_PUNCH)
    {
        if(player.counter_ANIM == 8)
        {
            SPR_setAnimAndFrame(sprite_PLAYER,G_INDEX_ANIM_PUNCH,1);
        }

        else if(player.counter_ANIM == 16)
        {
            SPR_setAnimAndFrame(sprite_PLAYER,G_INDEX_ANIM_PUNCH,2);

            G_REPEAT = 0;
        }

        // WE RESET THE PUNCH REPEAT, SO PLAYER CAN TRIGGER IT AGAIN //
        /*else if(player.counter_ANIM == 17)
        {
            G_REPEAT = 0;
        }*/


        player.counter_ANIM += 1;

        if(player.counter_ANIM == 24)
        {
            if(G_REPEAT == 0)
            {
                SPR_setAnimAndFrame(sprite_PLAYER,0,4);

                G_INDEX_ANIM_PUNCH = 1;

                player.counter_ANIM = 0;

                player.state = STATE_IDLE;
            }

            else
            {
                SPR_setAnimAndFrame(sprite_PLAYER,G_INDEX_ANIM_PUNCH,0);
                
                player.counter_ANIM = 1;
            } 
        }
    }


    else if(player.state == STATE_PUNCH_CROUCH)
    {
        if(player.counter_ANIM == 8)
        {
            SPR_setAnimAndFrame(sprite_PLAYER,G_INDEX_ANIM_PUNCH + 3,1);
        }

        else if(player.counter_ANIM == 16)
        {
            SPR_setAnimAndFrame(sprite_PLAYER,G_INDEX_ANIM_PUNCH + 3,2);

            G_REPEAT = 0;
        }

        // WE RESET THE PUNCH REPEAT, SO PLAYER CAN TRIGGER IT AGAIN //
        /*else if(player.counter_ANIM == 17)
        {
            G_REPEAT = 0;
        }*/


        player.counter_ANIM += 1;

        if(player.counter_ANIM == 24)
        {
            if(G_REPEAT == 0)
            {
                SPR_setAnimAndFrame(sprite_PLAYER,3,0);

                G_INDEX_ANIM_PUNCH = 1;

                player.counter_ANIM = 0;

                player.state = STATE_CROUCH;
            }

            else
            {
                SPR_setAnimAndFrame(sprite_PLAYER,G_INDEX_ANIM_PUNCH + 3,0);
                
                player.counter_ANIM = 1;
            } 
        }
    }


    else if(player.state == STATE_KICK)
    {
        if(player.counter_ANIM == 5)
        {
            SPR_setAnimAndFrame(sprite_PLAYER,6,1);

            G_REPEAT = 0;
        }

        else if(player.counter_ANIM == 13)
        {
            SPR_setAnimAndFrame(sprite_PLAYER,6,0);
        }



        player.counter_ANIM += 1;

        if(player.counter_ANIM == 24)
        {
            if(G_REPEAT == 0)
            {
                SPR_setAnimAndFrame(sprite_PLAYER,0,4);

                player.counter_ANIM = 0;

                player.state = STATE_IDLE;
            }

            else
            {
                SPR_setAnimAndFrame(sprite_PLAYER,6,1);
                
                player.counter_ANIM = 5;
            } 
        }
    }


    else if(player.state == STATE_KICK_CROUCH)
    {
        player.counter_ANIM += 1;

        if(player.counter_ANIM == 10)
        {
            SPR_setAnimAndFrame(sprite_PLAYER,3,0);

                player.counter_ANIM = 0;

                player.state = STATE_CROUCH;
        }
    }
}







//**************************************************************************************//
//                                                                                      //
//                                      SCROLLING                                       //
//                                                                                      //
//**************************************************************************************//

void scroll_PLANE(s16 increment)
{
    G_POS_X_CAMERA += increment;

    MAP_scrollTo(map_BG_B, G_POS_X_CAMERA , 0);
    MAP_scrollTo(map_BG_A, G_POS_X_CAMERA , 0);
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
        if(G_POS_X_CAMERA%8 == TRUE)
        {
            scrollTable_BG_B[i] = -(G_POS_X_CAMERA >> 3);
        }
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
                                                            scroll_PLANE,
                                                            scroll_PLANE,
                                                            scroll_TILE,
                                                            scroll_PLANE,
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
                
                player.counter_ANIM = 0;

                SPR_setAnimAndFrame(sprite_PLAYER,0,4);

                player.state = STATE_IDLE;
            }
        }


        else if(value & BUTTON_DOWN)
        {
            if(player.state == STATE_IDLE || player.state == STATE_WALK)
            {
                SPR_setAnimAndFrame(sprite_PLAYER,3,0);

                player.state = STATE_CROUCH;
            }

            else if(player.state == STATE_CROUCH)
            {
                if(value & BUTTON_LEFT)
                {
                    if(player.axis != AXIS_LEFT)
                    {
                        player.pos_X -= 16;

                        player.axis = AXIS_LEFT;
                    }

                    SPR_setHFlip(sprite_PLAYER,TRUE);

                    SPR_setPosition(sprite_PLAYER,player.pos_X,player.pos_Y);
                }

                else if(value & BUTTON_RIGHT)
                {
                    if(player.axis != AXIS_RIGHT)
                    {
                        player.pos_X += 16;

                        player.axis = AXIS_RIGHT;
                    }

                    SPR_setHFlip(sprite_PLAYER,FALSE);

                    SPR_setPosition(sprite_PLAYER,player.pos_X,player.pos_Y);
                }
            }
        }


        else if(value & BUTTON_LEFT)
        {
            if(player.state == STATE_IDLE || player.state == STATE_WALK || player.state == STATE_CROUCH)
            {
                if(G_POS_X_CAMERA > 0)
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
                        player.pos_X -= 16;

                        player.axis = AXIS_LEFT;
                    }

                    SPR_setHFlip(sprite_PLAYER,TRUE);

                    SPR_setPosition(sprite_PLAYER,player.pos_X,player.pos_Y);
                }

                else
                {
                    // SCREEN LEFT LIMIT //
                    if(player.pos_X > -18)
                    {
                        player.pos_X -= 1;

                        if(player.axis != AXIS_LEFT)
                        {
                            player.pos_X -= 16;

                            player.axis = AXIS_LEFT;
                        }

                        SPR_setHFlip(sprite_PLAYER,TRUE);

                        SPR_setPosition(sprite_PLAYER,player.pos_X,player.pos_Y);
                    }
                }

                player.state = STATE_WALK;
            }


            else if(player.state == STATE_KICK || player.state == STATE_PUNCH || player.state == STATE_PUNCH_CROUCH)
            {
                if(player.axis != AXIS_LEFT)
                {
                    player.pos_X -= 16;

                    player.axis = AXIS_LEFT;

                    SPR_setHFlip(sprite_PLAYER,TRUE);

                    SPR_setPosition(sprite_PLAYER,player.pos_X,player.pos_Y);
                }
            }
        }


        else if(value & BUTTON_RIGHT)
        {
            if(player.state == STATE_IDLE || player.state == STATE_WALK || player.state == STATE_CROUCH)
            {
                if(G_POS_X_CAMERA == 0)
                {
                    if(player.pos_X < 112)
                    {
                        player.pos_X += 1;


                        if(player.axis != AXIS_RIGHT)
                        {
                            player.pos_X += 16;

                            player.axis = AXIS_RIGHT;
                        }

                        SPR_setHFlip(sprite_PLAYER,FALSE);

                        SPR_setPosition(sprite_PLAYER,player.pos_X,player.pos_Y);

                        //player.state = STATE_WALK;
                    }

                    else
                    {
                        if(G_POS_X_CAMERA < G_LEVEL_LIMIT)
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

                                    //SPR_setPosition(LIST_ENEMIES[i].spr_ENEMY , LIST_ENEMIES[i].pos_X , LIST_ENEMIES[i].pos_Y);
                                }
                            }


                            if(player.axis != AXIS_RIGHT)
                            {
                                player.pos_X += 16;

                                player.axis = AXIS_RIGHT;

                                SPR_setPosition(sprite_PLAYER,player.pos_X,player.pos_Y);
                            }

                            SPR_setHFlip(sprite_PLAYER,FALSE);     
                        }
                    }
                }
                
                else
                {
                    if(G_POS_X_CAMERA < G_LEVEL_LIMIT)
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

                                //SPR_setPosition(LIST_ENEMIES[i].spr_ENEMY , LIST_ENEMIES[i].pos_X , LIST_ENEMIES[i].pos_Y);
                            }
                        }


                        if(player.axis != AXIS_RIGHT)
                        {
                            player.pos_X += 16;

                            player.axis = AXIS_RIGHT;

                            SPR_setPosition(sprite_PLAYER,player.pos_X,player.pos_Y);
                        }

                        SPR_setHFlip(sprite_PLAYER,FALSE);
                    }
                }

                player.state = STATE_WALK;
            }


            else if(player.state == STATE_KICK || player.state == STATE_PUNCH || player.state == STATE_PUNCH_CROUCH)
            {
                if(player.axis != AXIS_RIGHT)
                {
                    player.pos_X += 16;

                    player.axis = AXIS_RIGHT;   

                    SPR_setHFlip(sprite_PLAYER,FALSE);

                    SPR_setPosition(sprite_PLAYER,player.pos_X,player.pos_Y);
                }
            }
        }


        else if(value & BUTTON_UP)
        {
            if(player.state == STATE_CROUCH)
            {
                SPR_setAnimAndFrame(sprite_PLAYER,0,0);

                player.state = STATE_IDLE;
            }
        }
    }
}







//**************************************************************************************//
//                                                                                      //
//                                       ENEMY AI                                       //
//                                                                                      //
//**************************************************************************************//

inline static void spawn_ENEMY_LEVEL_1()
{
    // IF PLAYER HASN'T REACHED THE BOSS, ENEMIES CAN RESPAWN //
    if(G_SPAWN_AUTHORIZED == TRUE)
    {
        // THERE CAN UP TO 4 ENEMIES ON SCREEN //
        // SO IF THERE ARE LESS THAN 4, WE CAN SPAWN A NEW ONE //
        if(G_NUMBER_ENEMY < 4)
        {
            // WE INCREASE THE COUNTER //
            G_SPAWN_COUNTER += 1;
            
            // WE CHECK IF WE HAVE REACHED SPAWN TIME //
            if(G_SPAWN_COUNTER == TABLE_SPAWN_LEVEL_1[G_SPAWN_INDEX].spawn_TIME)
            {
                // WE SEARCH FOR A FREE ENTRY IN THE ENEMIES LIST //
                u8 i;

                for(i=0 ; i<4 ; i++)
                {
                    if(LIST_ENEMIES[i].spr_ENEMY == NULL)
                    {
                        // WE GET ENEMY TYPE //
                        u8 enemy_TYPE = TABLE_SPAWN_LEVEL_1[G_SPAWN_INDEX].enemy_ID;

                        // WE GET ENEMY SPRITE TILES;
                        const SpriteDefinition *ptr_TILE = TABLE_ENEMY_TYPE[enemy_TYPE].tiles_SPRITE;

                        // WE GET ENEMY PALETTE //
                        u8 enemy_PALETTE = TABLE_ENEMY_TYPE[enemy_TYPE].pal;


                        // AFTER SCROLLING REACHED 128, ENEMIES CAN SPAWN ON BOTH SIDES OF THE SCREEN //
                        if(G_POS_X_CAMERA > 127)
                        {
                            // ENEMY SPAWN ON THE RIGHT //
                            if(random_NUMBER(0,1) == 0)
                            {
                                LIST_ENEMIES[i].pos_X = 224;
                                LIST_ENEMIES[i].pos_Y = G_GROUND_POSITION;

                                LIST_ENEMIES[i].axis  = AXIS_LEFT;
                                
                                // WE CREATE ENEMY SPRITE //
                                LIST_ENEMIES[i].spr_ENEMY = SPR_addSprite(ptr_TILE,  LIST_ENEMIES[i].pos_X , LIST_ENEMIES[i].pos_Y , TILE_ATTR(enemy_PALETTE, FALSE, FALSE, TRUE));
                            }

                            // ENEMY SPAWN ON THE LEFT //
                            else
                            {
                                LIST_ENEMIES[i].pos_X = -32;
                                LIST_ENEMIES[i].pos_Y = G_GROUND_POSITION;

                                LIST_ENEMIES[i].axis  = AXIS_RIGHT;
                                
                                // WE CREATE ENEMY SPRITE //
                                LIST_ENEMIES[i].spr_ENEMY = SPR_addSprite(ptr_TILE,  LIST_ENEMIES[i].pos_X , LIST_ENEMIES[i].pos_Y , TILE_ATTR(enemy_PALETTE, FALSE, FALSE, FALSE));
                            }
                        }

                        // BEFORE SCROLLING REACHES 128, ENEMIES CAN ONLY SPAWN ON THE RIGHT //
                        else
                        {
                            //
                            LIST_ENEMIES[i].pos_X = 224;
                            LIST_ENEMIES[i].pos_Y = G_GROUND_POSITION;

                            LIST_ENEMIES[i].axis  = AXIS_LEFT;
                            
                            // WE CREATE ENEMY SPRITE //
                            LIST_ENEMIES[i].spr_ENEMY = SPR_addSprite(ptr_TILE,  LIST_ENEMIES[i].pos_X , LIST_ENEMIES[i].pos_Y , TILE_ATTR(enemy_PALETTE, FALSE, FALSE, TRUE));
                        }


                        // SET ENEMY LIFE POINTS //
                        LIST_ENEMIES[i].life = TABLE_ENEMY_TYPE[enemy_TYPE].life;

                        // SET ENEMY ID //
                        LIST_ENEMIES[i].enemy_ID = enemy_TYPE;

                        // RESET ANIM COUNTER //
                        LIST_ENEMIES[i].counter_ANIM = 0;

                        // SET ENEMY POINTS //
                        LIST_ENEMIES[i].points = TABLE_ENEMY_TYPE[enemy_TYPE].points;

                        // RESET FRAME ANIM //
                        SPR_setAnimAndFrame(LIST_ENEMIES[i].spr_ENEMY , 0 , 0);
                        
                        // SET ENEMY STATE //
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


        // IF THERE ARE ALREADY 4 ENEMIES ON SCREEN //
        else
        {
            // WE KEEP INCREASING THE COUNTER //
            G_SPAWN_COUNTER += 1;

            // IF WE REACH THE NEXT ENEMY SPAWN TIME //
            if(G_SPAWN_COUNTER > TABLE_SPAWN_LEVEL_1[G_SPAWN_INDEX].spawn_TIME)
            {
                // WE BLOCK THE COUNTER //
                // SO IT'S GOING TO RESPAWN AS SOON AS THERE IS A FREE ENTRY IN THE "LIST_ENEMIES[]"" LIST //
                G_SPAWN_COUNTER = TABLE_SPAWN_LEVEL_1[G_SPAWN_INDEX].spawn_TIME;
            }
        }
    }
}








void update_DUDE(struct_ENEMY_ *enemy)
{
    //****************************************************************//
    //                                                                //
    //                              WALK                              //
    //                                                                //
    //****************************************************************//

    if(enemy->state == ENEMY_WALK)
    {
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


        if(enemy->counter_ANIM == 21)
        {
            enemy->counter_ANIM = 0;
        }


        //----------------------------------------------------------------//
        //                                                                //
        //                          UPDATE FRAME                          //
        //                                                                //
        //----------------------------------------------------------------//

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


    //----------------------------------------------------------------//
    //                                                                //
    //                              GRAB                              //
    //                                                                //
    //----------------------------------------------------------------//

    else if(enemy->state == ENEMY_GRAB)
    {
        //
    }


    //----------------------------------------------------------------//
    //                                                                //
    //                              DEAD                              //
    //                                                                //
    //----------------------------------------------------------------//

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


        if(enemy->pos_Y > 224)
        {
            SPR_releaseSprite(enemy->spr_ENEMY);
            enemy->spr_ENEMY = NULL;
        }
    }






    SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);
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


        if(enemy->counter_ANIM == 21)
        {
            enemy->counter_ANIM = 0;
        }


        //----------------------------------------------------------------//
        //                                                                //
        //                          UPDATE FRAME                          //
        //                                                                //
        //----------------------------------------------------------------//

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


    //----------------------------------------------------------------//
    //                                                                //
    //                             THREAT                             //
    //                                                                //
    //----------------------------------------------------------------//

    else if(enemy->state == ENEMY_THREAT)
    {
        //

        enemy->counter_ANIM += 1;
    }


    //----------------------------------------------------------------//
    //                                                                //
    //                             ATTACK                             //
    //                                                                //
    //----------------------------------------------------------------//

    else if(enemy->state == ENEMY_ATTACK)
    {
        //
    }


    //----------------------------------------------------------------//
    //                                                                //
    //                       HIT UP & DOWN SLIDE                      //
    //                                                                //
    //----------------------------------------------------------------//

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
            
            enemy->state = ENEMY_WALK;

            SPR_setAnimAndFrame(enemy->spr_ENEMY , 0 , 0);

            SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);

            return;
        }


        SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);


        enemy->counter_ANIM += 1;
    }


    //----------------------------------------------------------------//
    //                                                                //
    //                             HIT UP                             //
    //                                                                //
    //----------------------------------------------------------------//

    else if(enemy->state == ENEMY_HIT_UP)
    {
        if(enemy->counter_ANIM == 0)
        {
            SPR_setAnim(enemy->spr_ENEMY,4);
            SPR_setFrame(enemy->spr_ENEMY,0);
        }

        else if(enemy->counter_ANIM == 6)
        {
            //SPR_setAnim(enemy->spr_ENEMY,4);
            SPR_setFrame(enemy->spr_ENEMY,1);
        }

        else if(enemy->counter_ANIM == 17)
        {
            enemy->counter_ANIM = 0;
            
            enemy->state = ENEMY_WALK;

            SPR_setAnimAndFrame(enemy->spr_ENEMY , 0 , 0);

            return;
        }


        enemy->counter_ANIM += 1;        
    }


    //----------------------------------------------------------------//
    //                                                                //
    //                            HIT DOWN                            //
    //                                                                //
    //----------------------------------------------------------------//

    else if(enemy->state == ENEMY_HIT_DOWN)
    {
        if(enemy->counter_ANIM == 0)
        {
            SPR_setAnim(enemy->spr_ENEMY,5);
            SPR_setFrame(enemy->spr_ENEMY,0);
        }

        else if(enemy->counter_ANIM == 17)
        {
            enemy->counter_ANIM = 0;
            
            enemy->state = ENEMY_WALK;

            SPR_setAnimAndFrame(enemy->spr_ENEMY , 0 , 0);

            return;
        }


        enemy->counter_ANIM += 1;  
    }


    //----------------------------------------------------------------//
    //                                                                //
    //                              DEAD                              //
    //                                                                //
    //----------------------------------------------------------------//

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


        if(enemy->pos_Y > 224)
        {
            SPR_releaseSprite(enemy->spr_ENEMY);
            enemy->spr_ENEMY = NULL;
        }
    }






    SPR_setPosition(enemy->spr_ENEMY , enemy->pos_X , enemy->pos_Y);
}




void (*TABLE_ENEMY_AI[6])(struct_ENEMY_ *enemy)      =   {
                                                            update_DUDE,
                                                            update_PUNK,
                                                            NULL,
                                                            NULL,
                                                            NULL,
                                                            NULL
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




inline static void collision_PLAYER_TO_ENEMY()
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
                // IF ENEMY IS NOT ALREADY DEAD //
                if(LIST_ENEMIES[i].state != ENEMY_DEAD && LIST_ENEMIES[i].state != ENEMY_HIT_UP_SLIDE && LIST_ENEMIES[i].state != ENEMY_HIT_DOWN_SLIDE && LIST_ENEMIES[i].state != ENEMY_HIT_DOWN && LIST_ENEMIES[i].state != ENEMY_HIT_UP)
                {
                    // IF WE REACHED COLLISION FRAME //
                    if(player.counter_ANIM >= attack_time)
                    {
                        // IF PLAYER IS FACING RIGHT //
                        if(player.axis == AXIS_RIGHT)
                        {
                            // WE CHECK ONLY ENEMIES FACING LEFT //
                            if(LIST_ENEMIES[i].axis == AXIS_LEFT)
                            {
                                if( (player.pos_X + 52) > (LIST_ENEMIES[i].pos_X + 24) )
                                {
                                    LIST_ENEMIES[i].counter_ANIM = 0;


                                    LIST_ENEMIES[i].life -= 1;

                                    // IF ENEMY LIFE REACHES 0, HE'S DEAD //
                                    if(LIST_ENEMIES[i].life == 0)
                                    {
                                        LIST_ENEMIES[i].state = ENEMY_DEAD;

                                        G_POINTS += LIST_ENEMIES[i].points;

                                        update_SCORE();
                                    }

                                    else
                                    {
                                        // ENEMY IS HIT ON HEAD //
                                        if(player.state == STATE_KICK)
                                        {
                                            LIST_ENEMIES[i].state = ENEMY_HIT_UP_SLIDE;
                                        }

                                        // ENEMY IS HIT ON LEGS //
                                        else
                                        {
                                            LIST_ENEMIES[i].state = ENEMY_HIT_DOWN_SLIDE;
                                        }
                                    }

                                    XGM_startPlayPCM(SOUND_HIT_KICK,15,SOUND_PCM_CH2);
                                }
                            }
                        }


                        // IF PLAYER IS FACING LEFT //
                        else
                        {
                            // WE CHECK ONLY ENEMIES FACING RIGHT //
                            if(LIST_ENEMIES[i].axis == AXIS_RIGHT)
                            {
                                if( (player.pos_X + 3) < (LIST_ENEMIES[i].pos_X + 24) )
                                {
                                    LIST_ENEMIES[i].counter_ANIM = 0;


                                    LIST_ENEMIES[i].life -= 1;

                                    // IF ENEMY LIFE REACHES 0, HE'S DEAD //
                                    if(LIST_ENEMIES[i].life == 0)
                                    {
                                        LIST_ENEMIES[i].state = ENEMY_DEAD;

                                        SPR_setAnim(LIST_ENEMIES[i].spr_ENEMY,3);
                                        SPR_setFrame(LIST_ENEMIES[i].spr_ENEMY,0);

                                        G_POINTS += LIST_ENEMIES[i].points;

                                        update_SCORE();
                                    }

                                    else
                                    {
                                        // ENEMY IS HIT ON HEAD //
                                        if(player.state == STATE_KICK)
                                        {
                                            LIST_ENEMIES[i].state = ENEMY_HIT_UP_SLIDE;

                                            SPR_setAnim(LIST_ENEMIES[i].spr_ENEMY,4);
                                            SPR_setFrame(LIST_ENEMIES[i].spr_ENEMY,0);
                                        }

                                        // ENEMY IS HIT ON LEGS //
                                        else
                                        {
                                            LIST_ENEMIES[i].state = ENEMY_HIT_DOWN_SLIDE;

                                            SPR_setAnim(LIST_ENEMIES[i].spr_ENEMY,4);
                                            SPR_setFrame(LIST_ENEMIES[i].spr_ENEMY,1);
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
                if(LIST_ENEMIES[i].state != ENEMY_DEAD && LIST_ENEMIES[i].state != ENEMY_HIT_UP_SLIDE && LIST_ENEMIES[i].state != ENEMY_HIT_DOWN_SLIDE && LIST_ENEMIES[i].state != ENEMY_HIT_DOWN && LIST_ENEMIES[i].state != ENEMY_HIT_UP)
                {
                    // IF WE REACHED COLLISION FRAME //
                    if(player.counter_ANIM > 7 && player.counter_ANIM < 16)
                    {
                        // IF PLAYER IS FACING RIGHT //
                        if(player.axis == AXIS_RIGHT)
                        {
                            // WE CHECK ONLY ENEMIES FACING LEFT //
                            if(LIST_ENEMIES[i].axis == AXIS_LEFT)
                            {
                                if( (player.pos_X + 52) > (LIST_ENEMIES[i].pos_X + 24) )
                                {
                                    LIST_ENEMIES[i].counter_ANIM = 0;


                                    LIST_ENEMIES[i].life -= 1;

                                    // IF ENEMY LIFE REACHES 0, HE'S DEAD //
                                    if(LIST_ENEMIES[i].life == 0)
                                    {
                                        LIST_ENEMIES[i].state = ENEMY_DEAD;

                                        G_POINTS += LIST_ENEMIES[i].points;

                                        update_SCORE();
                                    }

                                    else
                                    {
                                        // ENEMY IS HIT ON HEAD //
                                        if(player.state == STATE_PUNCH)
                                        {
                                            LIST_ENEMIES[i].state = ENEMY_HIT_UP;
                                        }

                                        // ENEMY IS HIT ON LEGS //
                                        else
                                        {
                                            LIST_ENEMIES[i].state = ENEMY_HIT_DOWN;
                                        }
                                        
                                        //XGM_startPlayPCM(SOUND_HIT_KICK,15,SOUND_PCM_CH2);
                                    }
                                }
                            }
                        }


                        // IF PLAYER IS FACING LEFT //
                        else
                        {
                            // WE CHECK ONLY ENEMIES FACING RIGHT //
                            if(LIST_ENEMIES[i].axis == AXIS_RIGHT)
                            {
                                if( (player.pos_X + 3) < (LIST_ENEMIES[i].pos_X + 24) )
                                {
                                    LIST_ENEMIES[i].counter_ANIM = 0;


                                    LIST_ENEMIES[i].life -= 1;

                                    // IF ENEMY LIFE REACHES 0, HE'S DEAD //
                                    if(LIST_ENEMIES[i].life == 0)
                                    {
                                        LIST_ENEMIES[i].state = ENEMY_DEAD;

                                        SPR_setAnim(LIST_ENEMIES[i].spr_ENEMY,3);
                                        SPR_setFrame(LIST_ENEMIES[i].spr_ENEMY,0);

                                        G_POINTS += LIST_ENEMIES[i].points;

                                        update_SCORE();
                                    }

                                    else
                                    {
                                        // ENEMY IS HIT ON HEAD //
                                        if(player.state == STATE_KICK)
                                        {
                                            LIST_ENEMIES[i].state = ENEMY_HIT_UP_SLIDE;

                                            SPR_setAnim(LIST_ENEMIES[i].spr_ENEMY,4);
                                            SPR_setFrame(LIST_ENEMIES[i].spr_ENEMY,0);
                                        }

                                        // ENEMY IS HIT ON LEGS //
                                        else
                                        {
                                            LIST_ENEMIES[i].state = ENEMY_HIT_DOWN_SLIDE;

                                            SPR_setAnim(LIST_ENEMIES[i].spr_ENEMY,4);
                                            SPR_setFrame(LIST_ENEMIES[i].spr_ENEMY,1);
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
}








void sequence_LEVEL_1()
{
    if(G_PHASE_LEVEL == LEVEL_ENTER)
    {
        if(player.pos_X < 87)
        {
            player.state = STATE_WALK;

            player.pos_X += 1;

            SPR_setPosition(sprite_PLAYER , player.pos_X , player.pos_Y);

            update_PLAYER_SPRITE();
        }



        G_COUNTER += 1;

        if(G_COUNTER == 123)
        {
            player.state = STATE_IDLE;

            SPR_setFrame(sprite_PLAYER , 0);

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

        collision_PLAYER_TO_ENEMY();

        spawn_ENEMY_LEVEL_1();
        update_ENEMY();

        update_PLAYER_SPRITE();
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

            player.pos_X += 1;

            SPR_setPosition(sprite_PLAYER , player.pos_X , player.pos_Y);

            update_PLAYER_SPRITE();
        }



        G_COUNTER += 1;

        if(G_COUNTER == 123)
        {
            player.state = STATE_IDLE;

            SPR_setFrame(sprite_PLAYER , 0);

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

        //collision_PLAYER_TO_ENEMY();

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

            player.pos_X += 1;

            SPR_setPosition(sprite_PLAYER , player.pos_X , player.pos_Y);

            update_PLAYER_SPRITE();
        }



        G_COUNTER += 1;

        if(G_COUNTER == 123)
        {
            player.state = STATE_IDLE;

            SPR_setFrame(sprite_PLAYER , 0);

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

        //collision_PLAYER_TO_ENEMY();

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

            player.pos_X += 1;

            SPR_setPosition(sprite_PLAYER , player.pos_X , player.pos_Y);

            update_PLAYER_SPRITE();
        }



        G_COUNTER += 1;

        if(G_COUNTER == 123)
        {
            player.state = STATE_IDLE;

            SPR_setFrame(sprite_PLAYER , 0);

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

        //collision_PLAYER_TO_ENEMY();

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

            player.pos_X += 1;

            SPR_setPosition(sprite_PLAYER , player.pos_X , player.pos_Y);

            update_PLAYER_SPRITE();
        }



        G_COUNTER += 1;

        if(G_COUNTER == 123)
        {
            player.state = STATE_IDLE;

            SPR_setFrame(sprite_PLAYER , 0);

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

        //collision_PLAYER_TO_ENEMY();

        //spawn_ENEMY_LEVEL_1();
        //update_ENEMY();

        update_PLAYER_SPRITE();
    }


    else if(G_PHASE_LEVEL == LEVEL_END)
    {
        //
    }

}




