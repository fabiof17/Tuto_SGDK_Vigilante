#include <genesis.h>


#include "custom_tools.h"
#include "palettes.h"
#include "variables.h"




#include "maps_GLOBAL.h"
#include "maps_TITLE.h"


#include "musics.h"



#include "sprites_LEVEL.h"



#include "tables_RANKING.h"





void disable_Callback(u16 joy, u16 changed, u16 state)
{
    if(joy == JOY_1)
    {
        //
    }
}




void logo_Callback(u16 joy, u16 changed, u16 state)
{
    if(joy == JOY_1)
    {
        // BOUTON START //
        if( changed & state & BUTTON_START )
        {
            JOY_setEventHandler(disable_Callback);
            
            PAL_setPalette(PAL0,palette_BLACK.data,DMA_QUEUE);

            G_SEQUENCE = SEQUENCE_TITLE;

            G_SEQUENCE_LOADED = FALSE;

            SYS_doVBlankProcess();
        }
    }
}




void title_Callback(u16 joy, u16 changed, u16 state)
{
    if(joy == JOY_1)
    {
        // BUTTON START //
        if( changed & state & BUTTON_START )
        {
            if(G_POS_X_CAMERA < 256)
            {
                G_POS_X_CAMERA = 256;

                VDP_setHorizontalScrollVSync(BG_B,G_POS_X_CAMERA);
                VDP_setHorizontalScrollVSync(BG_A,G_POS_X_CAMERA);

                // DISPLAY PRESS START BUTTON //
                VDP_setTileMapEx(BG_A, image_TITLE_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 39, 19, 39, 28, 18, 1, DMA_QUEUE);

                // DISPLAY LEVEL //
                VDP_setTileMapEx(BG_A, image_TITLE_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 44, 21, 59, 28, 5, 1, DMA_QUEUE);

                // DISPLAY LEVEL NUMBER //
                VDP_drawIntEx_BG_A_QUEUE(G_LEVEL,1,51,21,PAL0);

                // DISPLAY LIVES //
                VDP_setTileMapEx(BG_A, image_TITLE_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 44, 23, 19, 28, 5, 1, DMA_QUEUE);

                // DISPLAY LIVES NUMBER //
                VDP_drawIntEx_BG_A_QUEUE(G_NUMBER_LIVES,1,51,23,PAL0);

                // SELECTION ARROW //
                SPR_setPosition(sprite_ARROW , 72 , 168);

                // PLAY MUSIC //
                u8 music_state = XGM_isPlaying();

                if(music_state != 64)
                {
                    XGM_startPlay(MUSIC_TITLE);
                }
            }

            else
            {
                JOY_setEventHandler(disable_Callback);
                
                PAL_setPalette(PAL0,palette_BLACK.data,DMA_QUEUE);
                PAL_setPalette(PAL1,palette_BLACK.data,DMA_QUEUE);

                // STOP MUSIC //
                XGM_stopPlay();

                SYS_doVBlankProcess();

                // CLEAR PLANES //
                VDP_clearPlane(BG_B,TRUE);
                VDP_clearPlane(BG_A,TRUE);

                // RELEASE ALL SPRITES //
                SPR_reset();

                G_SEQUENCE = SEQUENCE_INTERMEDE;

                G_SEQUENCE_LOADED = FALSE;

                SYS_doVBlankProcess();
            }
        }

        //
        else if( changed & state & BUTTON_RIGHT )
        {
            if(G_OPTIONS == LEVEL_OPTION)
            {
                if(G_LEVEL < 5)
                {
                    G_LEVEL += 1;

                    // DISPLAY LEVEL NUMBER //
                    VDP_drawIntEx_BG_A_QUEUE(G_LEVEL,1,51,21,PAL0);
                }
            }

            else
            {
                if(G_NUMBER_LIVES < 5)
                {
                    G_NUMBER_LIVES += 1;

                    // DISPLAY LIVES NUMBER //
                    VDP_drawIntEx_BG_A_QUEUE(G_NUMBER_LIVES,1,51,23,PAL0);
                }
            }
        }

        //
        else if( changed & state & BUTTON_LEFT )
        {
            if(G_OPTIONS == LEVEL_OPTION)
            {
                if(G_LEVEL > 1)
                {
                    G_LEVEL -= 1;

                    // DISPLAY LEVEL NUMBER //
                    VDP_drawIntEx_BG_A_QUEUE(G_LEVEL,1,51,21,PAL0);
                }
            }

            else
            {
                if(G_NUMBER_LIVES > 2)
                {
                    G_NUMBER_LIVES -= 1;

                    // DISPLAY LIVES NUMBER //
                    VDP_drawIntEx_BG_A_QUEUE(G_NUMBER_LIVES,1,51,23,PAL0);
                }
            }
        }
    
        //
        else if( changed & state & BUTTON_DOWN )
        {
            if(G_OPTIONS == LEVEL_OPTION)
            {
                G_OPTIONS = LIVES_OPTION;

                SPR_setPosition(sprite_ARROW , 72 , 184);
            }
        }

        //
        else if( changed & state & BUTTON_UP )
        {
            if(G_OPTIONS == LIVES_OPTION)
            {
                G_OPTIONS = LEVEL_OPTION;

                SPR_setPosition(sprite_ARROW , 72 , 168);
            }
        }    
    
    }
}




void ranking_Callback(u16 joy, u16 changed, u16 state)
{
    if(joy == JOY_1)
    {
        // BUTTON START //
        if( changed & state & BUTTON_START )
        {
            JOY_setEventHandler(disable_Callback);
            
            PAL_setPalette(PAL0,palette_BLACK.data,DMA_QUEUE);
            PAL_setPalette(PAL1,palette_BLACK.data,DMA_QUEUE);

            // STOP MUSIC //
            //XGM_stopPlay();

            SYS_doVBlankProcess();

            // CLEAR PLANES //
            VDP_clearPlane(BG_B,TRUE);
            VDP_clearPlane(BG_A,TRUE);

            // RELEASE ALL SPRITES //
            SPR_reset();

            G_SEQUENCE = SEQUENCE_TITLE;

            G_SEQUENCE_LOADED = FALSE;

            SYS_doVBlankProcess();
        }
    }
}




void hi_score_Callback(u16 joy, u16 changed, u16 state)
{
    if(joy == JOY_1)
    {
        // BUTTON START //
        if( changed & state & BUTTON_START )
        {
            if(G_INDEX_LETTER == 2)
            {
                JOY_setEventHandler(disable_Callback);

                // UPDATE RANKING TABLE //
                TABLE_RANKING[G_RANK].score = G_SCORE;
                TABLE_RANKING[G_RANK].letter_1 = TABLE_SELECTED_LETTERS[0];
                TABLE_RANKING[G_RANK].letter_2 = TABLE_SELECTED_LETTERS[1];
                TABLE_RANKING[G_RANK].letter_3 = TABLE_SELECTED_LETTERS[2];

                
                PAL_setPalette(PAL0,palette_BLACK.data,DMA_QUEUE);
                PAL_setPalette(PAL1,palette_BLACK.data,DMA_QUEUE);

                // STOP MUSIC //
                XGM_stopPlay();

                SYS_doVBlankProcess();

                // CLEAR PLANES //
                VDP_clearPlane(BG_B,TRUE);
                VDP_clearPlane(BG_A,TRUE);

                // RELEASE ALL SPRITES //
                SPR_reset();

                G_SEQUENCE = SEQUENCE_TITLE;

                G_SEQUENCE_LOADED = FALSE;

                SYS_doVBlankProcess();
            }
        }


        else if( changed & state & BUTTON_RIGHT )
        {
            if(G_INDEX_LETTER < 2)
            {
                // CHANGE CURRENT LETTER COLOR //
                VDP_setTileMapEx(BG_B, image_EMPTY_TILE.tilemap, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, TILE_FONT_INDEX + TABLE_SELECTED_LETTERS[G_INDEX_LETTER]), 22 + G_INDEX_LETTER, 7 + (G_RANK<<1), 0, 0, 1, 1, DMA_QUEUE);

                G_INDEX_LETTER += 1;

                if(TABLE_SELECTED_LETTERS[G_INDEX_LETTER] > 33)
                {
                    TABLE_SELECTED_LETTERS[G_INDEX_LETTER] = 33;
                }

                // HIGHLIGHT NEXT LETTER //
                VDP_setTileMapEx(BG_B, image_EMPTY_TILE.tilemap, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, TILE_FONT_INDEX + TABLE_SELECTED_LETTERS[G_INDEX_LETTER]), 22 + G_INDEX_LETTER, 7 + (G_RANK<<1), 0, 0, 1, 1, DMA_QUEUE);
            }
        }


        else if( changed & state & BUTTON_LEFT )
        {
            if(G_INDEX_LETTER > 0)
            {
                // CHANGE CURRENT LETTER COLOR //
                VDP_setTileMapEx(BG_B, image_EMPTY_TILE.tilemap, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, TILE_FONT_INDEX + TABLE_SELECTED_LETTERS[G_INDEX_LETTER]), 22 + G_INDEX_LETTER, 7 + (G_RANK<<1), 0, 0, 1, 1, DMA_QUEUE);

                G_INDEX_LETTER -= 1;

                // HIGHLIGHT NEXT LETTER //
                VDP_setTileMapEx(BG_B, image_EMPTY_TILE.tilemap, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, TILE_FONT_INDEX + TABLE_SELECTED_LETTERS[G_INDEX_LETTER]), 22 + G_INDEX_LETTER, 7 + (G_RANK<<1), 0, 0, 1, 1, DMA_QUEUE);
            }
        }
    

        else if( changed & state & BUTTON_UP )
        {
            TABLE_SELECTED_LETTERS[G_INDEX_LETTER] += 1;

            if(TABLE_SELECTED_LETTERS[G_INDEX_LETTER] > 60)
            {
                TABLE_SELECTED_LETTERS[G_INDEX_LETTER] = 33;
            }

            VDP_setTileMapEx(BG_B, image_EMPTY_TILE.tilemap, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, TILE_FONT_INDEX + TABLE_SELECTED_LETTERS[G_INDEX_LETTER]), 22 + G_INDEX_LETTER, 7 + (G_RANK<<1), 0, 0, 1, 1, DMA_QUEUE);
        }


        else if( changed & state & BUTTON_DOWN )
        {
            TABLE_SELECTED_LETTERS[G_INDEX_LETTER] -= 1;

            if(TABLE_SELECTED_LETTERS[G_INDEX_LETTER] < 33)
            {
                TABLE_SELECTED_LETTERS[G_INDEX_LETTER] = 60;
            }

            VDP_setTileMapEx(BG_B, image_EMPTY_TILE.tilemap, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, TILE_FONT_INDEX + TABLE_SELECTED_LETTERS[G_INDEX_LETTER]), 22 + G_INDEX_LETTER, 7 + (G_RANK<<1), 0, 0, 1, 1, DMA_QUEUE);
        }
    }
}




void intermede_Callback(u16 joy, u16 changed, u16 state)
{
    if(joy == JOY_1)
    {
        // BOUTON START //
        if( changed & state & BUTTON_START )
        {
            PAL_setPalette(PAL0,palette_BLACK.data,DMA_QUEUE);
            PAL_setPalette(PAL1,palette_BLACK.data,DMA_QUEUE);
            PAL_setPalette(PAL2,palette_BLACK.data,DMA_QUEUE);
            PAL_setPalette(PAL3,palette_BLACK.data,DMA_QUEUE);

            SYS_doVBlankProcess();


            // RESET SCROLLING //
            VDP_setVerticalScroll(BG_B , 0);
            VDP_setVerticalScroll(BG_A , 0);

            // CLEAR PLANES //
            VDP_clearPlane(BG_B,TRUE);
            VDP_clearPlane(BG_A,TRUE);

            // RELEASE ALL SPRITES //
            SPR_reset();


            G_SEQUENCE = SEQUENCE_GAME;

            G_SEQUENCE_LOADED = FALSE;

            // STOP MUSIC //
            XGM_stopPlay();
        }
    }
}




void player_Callback(u16 joy, u16 changed, u16 state)
{
    if(G_PHASE_LEVEL == LEVEL_PLAY)
    {
        if(joy == JOY_1)
        {
            // A BUTTON (PUNCH) //
            if( changed & state & BUTTON_A )
            {
                if(G_PAUSE == FALSE)
                {
                    if(player.state == STATE_IDLE || player.state == STATE_WALK)
                    {                        
                        G_REPEAT = 0;

                        player.counter_ANIM_SPRITE = 0;

                        player.state = STATE_PUNCH;
                    }


                    else if(player.state == STATE_PUNCH)
                    {
                        // IF PLAYER ISN'T EQUIPED WITH NUNCHUK //
                        if(player.armed == FALSE)
                        {
                            // IF PLAYER PRESS A BETWEEN FRAME 17 AND 23 OF THE PUNCH ANIMATION //
                            if(player.counter_ANIM_SPRITE > 15)
                            {
                                // PUNCH WILL REPEAT //
                                G_REPEAT = 1;

                                //SPR_setDepth(player.spr_PLAYER,1);
                                
                                // SECOND SERIE OF PUNCH : RIGHT ARM //
                                if(G_INDEX_ANIM_PUNCH == 1)
                                {
                                    G_INDEX_ANIM_PUNCH = 2;
                                }

                                // FIRST SERIE OF PUNCH : LEFT ARM //
                                else
                                {
                                    G_INDEX_ANIM_PUNCH = 1;
                                }
                            }
                        }
                    }


                    else if(player.state == STATE_CROUCH)
                    {
                        G_REPEAT = 0;

                        player.counter_ANIM_SPRITE = 0;

                        player.state = STATE_PUNCH_CROUCH;
                    }


                    else if(player.state == STATE_PUNCH_CROUCH)
                    {                        
                        // IF PLAYER PRESS A BETWEEN FRAME 17 AND 23 OF THE PUNCH ANIMATION //
                        if(player.counter_ANIM_SPRITE > 16)
                        {
                            // PUNCH WILL REPEAT //
                            G_REPEAT = 1;
                            
                            // SECOND SERIE OF PUNCH : RIGHT ARM //
                            if(G_INDEX_ANIM_PUNCH == 1)
                            {
                                G_INDEX_ANIM_PUNCH = 2;
                            }

                            // FIRST SERIE OF PUNCH : LEFT ARM //
                            else
                            {
                                G_INDEX_ANIM_PUNCH = 1;
                            }
                        }
                    }


                    else if(player.state == STATE_JUMP_V || player.state == STATE_JUMP_H)
                    {
                        G_REPEAT = 0;                    

                        if(player.counter_ANIM_V <= JUMP_HIGH_POINT) // IF BUTTON PRESSED BEFORE PUNCH TRIGGER LIMIT //
                        {
                            if(G_JUMP_KICK == NO_JUMP_KICK)
                            {
                                if(G_JUMP_PUNCH == NO_JUMP_PUNCH)
                                {
                                    G_JUMP_PUNCH = JUMP_PUNCH;
                                }
                            }
                        }
                    }
                }
            }

            // B BUTTON (KICK) //   
            else if( changed & state & BUTTON_B )
            {
                if(G_PAUSE == FALSE)
                {
                    if(player.state == STATE_IDLE || player.state == STATE_WALK)
                    {                        
                        G_REPEAT = 0;

                        player.counter_ANIM_SPRITE = 0;

                        player.state = STATE_KICK;

                        if(player.armed == TRUE)
                        {
                            SPR_setPosition(sprite_NUNCHUK,0,-32);
                        }
                    }


                    else if(player.state == STATE_KICK)
                    {
                        // IF PLAYER PRESS A BETWEEN FRAME 5 AND 23 OF THE KICK ANIMATION //
                        if(player.counter_ANIM_SPRITE > 5)
                        {
                            // KICK WILL REPEAT //
                            G_REPEAT = 1;
                        }
                    }


                    else if(player.state == STATE_CROUCH)
                    {
                        G_REPEAT = 0;                    

                        player.counter_ANIM_SPRITE = 0;

                        player.state = STATE_KICK_CROUCH;
                    }


                    else if(player.state == STATE_JUMP_V || player.state == STATE_JUMP_H)
                    {
                        G_REPEAT = 0;                    

                        if(player.counter_ANIM_V <= JUMP_HIGH_POINT) // IF BUTTON PRESSED BEFORE KICK TRIGGER LIMIT //
                        {
                            if(G_JUMP_PUNCH == NO_JUMP_PUNCH)
                            {
                                if(G_JUMP_KICK == NO_JUMP_KICK)
                                {
                                    G_JUMP_KICK = JUMP_KICK;
                                }
                            }
                        }
                    }
                }
            }

            // C BUTTON (JUMP) //   
            else if( changed & state & BUTTON_C )
            {
                if(G_PAUSE == FALSE)
                {
                    // PLAYER JUMPS VERTICALLY //
                    if(player.state == STATE_IDLE)
                    {
                        //SPR_setDepth(player.spr_PLAYER,1);
                        
                        player.state = STATE_JUMP_V;

                        G_REPEAT = 0;

                        G_JUMP_KICK = NO_JUMP_KICK;
                        G_JUMP_PUNCH = NO_JUMP_PUNCH;

                        G_INDEX_JUMP_V = 0;
                        G_INDEX_JUMP_H = 0;

                        G_GRAVITY = FIX32(4L);
                        
                        player.counter_ANIM_SPRITE = 0;

                        player.counter_ANIM_H = 0;
                        player.counter_ANIM_V = 0;

                        if(player.armed == TRUE)
                        {
                            SPR_setPosition(sprite_NUNCHUK,0,-32);
                        }
                    }

                    // PLAYER JUMPS HORIZONTALLY //
                    else if(player.state == STATE_WALK)
                    {
                        //SPR_setDepth(player.spr_PLAYER,1);
                        
                        player.state = STATE_JUMP_H;
                    
                        G_REPEAT = 0;

                        G_JUMP_KICK = NO_JUMP_KICK;
                        G_JUMP_PUNCH = NO_JUMP_PUNCH;

                        G_INDEX_JUMP_V = 0;
                        G_INDEX_JUMP_H = 0;

                        G_GRAVITY = FIX32(4L);
                        
                        player.counter_ANIM_SPRITE = 0;

                        player.counter_ANIM_H = 0;
                        player.counter_ANIM_V = 0;

                        if(player.armed == TRUE)
                        {
                            SPR_setPosition(sprite_NUNCHUK,0,-32);
                        }
                    }
                }
            }

            // BUTTON START (PAUSE) //
            else if( changed & state & BUTTON_START )
            {
                if(G_PAUSE == FALSE)
                {
                    XGM_pausePlay();
                    
                    G_PAUSE = TRUE;

                    SPR_setPosition(sprite_PAUSE , 200 , 8); // 118 96

                    //SPR_setDepth(sprite_PAUSE,1);
                }

                else
                {
                    XGM_resumePlay();
                    
                    G_PAUSE = FALSE;

                    SPR_setPosition(sprite_PAUSE , 0 , -8);
                }
            }
        
            // LEFT OR RIGHT //
            else if(changed & state & BUTTON_LEFT || changed & state & BUTTON_RIGHT)
            {
                if(player.state == STATE_GRAB)
                {
                    if(player.pos_Y == G_GROUND_POSITION)
                    {
                        if(changed & state & BUTTON_LEFT)
                        {
                            player.axis = AXIS_LEFT;
                            
                            SPR_setHFlip(player.spr_PLAYER,TRUE);
                        }

                        else if(changed & state & BUTTON_RIGHT)
                        {
                            player.axis = AXIS_RIGHT;
                            
                            SPR_setHFlip(player.spr_PLAYER,FALSE);
                        }
                        

                        player.counter_UNGRAB += 1;


                        if(player.counter_UNGRAB == 4)
                        {
                            u8 i;

                            for(i=0 ; i<4 ; i++)
                            {
                                if(LIST_ENEMIES[i].spr_ENEMY != NULL)
                                {
                                    if(LIST_ENEMIES[i].state == ENEMY_GRAB)
                                    {
                                        if(player.axis == AXIS_RIGHT)
                                        {
                                            if(LIST_ENEMIES[i].axis == AXIS_LEFT)
                                            {
                                                LIST_ENEMIES[i].state = ENEMY_DEAD;

                                                LIST_ENEMIES[i].vulnerable = FALSE;

                                                G_NUMBER_GRAB_RIGHT -= 1;

                                                player.counter_UNGRAB -= 1;
                                            }

                                            else
                                            {
                                                player.counter_UNGRAB -= 1;
                                            }
                                        }
                                        
                                        else
                                        {
                                            if(LIST_ENEMIES[i].axis == AXIS_RIGHT)
                                            {
                                                LIST_ENEMIES[i].state = ENEMY_DEAD;

                                                LIST_ENEMIES[i].vulnerable = FALSE;

                                                G_NUMBER_GRAB_LEFT -= 1;

                                                player.counter_UNGRAB -= 1;
                                            }

                                            else
                                            {
                                                player.counter_UNGRAB -= 1;
                                            }
                                        }
                                    }
                                }
                            }


                            if(G_NUMBER_GRAB_LEFT + G_NUMBER_GRAB_RIGHT == 0)
                            {
                                player.state = STATE_IDLE;

                                player.counter_UNGRAB = 0;

                                if(player.armed == FALSE)
                                {
                                    SPR_setAnim(player.spr_PLAYER,0);
                                    SPR_setFrame(player.spr_PLAYER,0);
                                }

                                else
                                {
                                    SPR_setAnim(player.spr_PLAYER,0);
                                    SPR_setFrame(player.spr_PLAYER,4);
                                }
                            }
                        }

                        /*else
                        {

                        }*/
                    }
                }
            }
        
            // DOWN //
            else if(changed & state & BUTTON_DOWN)
            {
                // GRAB NUNCHUCK //
                if(player.invincible == FALSE)
                {
                    if(sprite_WEAPON != NULL)
                    {
                        s16 pos_x_weapon = SPR_getPositionX(sprite_WEAPON);
                        
                        if(player.pos_X >= pos_x_weapon - 36 && player.pos_X <= pos_x_weapon - 20) // -32 -8
                        {
                            player.armed = TRUE;

                            SPR_releaseSprite(sprite_WEAPON);
                            sprite_WEAPON = NULL;

                            G_WEAPON_GRABBED = TRUE;

                            sprite_NUNCHUK = SPR_addSprite(&tiles_SPR_NUNCHUK, 0, -32, TILE_ATTR(PAL3, FALSE, FALSE, FALSE));

                            SPR_setDepth(sprite_NUNCHUK,6);

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
                    }
                }
            }
        }
    }
}

