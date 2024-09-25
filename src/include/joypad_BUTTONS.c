#include <genesis.h>


#include "custom_tools.h"
#include "palettes.h"
#include "variables.h"




#include "maps_TITLE.h"





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
        // BOUTON START //
        if( changed & state & BUTTON_START )
        {
            if(G_POS_X_CAMERA < 256)
            {
                G_POS_X_CAMERA = 256;

                VDP_setHorizontalScrollVSync(BG_B,G_POS_X_CAMERA);
                VDP_setHorizontalScrollVSync(BG_A,G_POS_X_CAMERA);

                // DISPLAY PRESS START BUTTON //
                VDP_setTileMapEx(BG_B, image_TITLE_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 39, 21, 39, 28, 18, 1, DMA_QUEUE);

                // DISPLAY LEVEL //
                VDP_setTileMapEx(BG_B, image_TITLE_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 44, 23, 59, 28, 5, 1, DMA_QUEUE);

                // DISPLAY LEVEL NUMBER //
                VDP_drawIntEx_BG_A_QUEUE(G_LEVEL,1,51,23,PAL0);
            }

            else
            {
                PAL_setPalette(PAL0,palette_BLACK.data,DMA_QUEUE);
                PAL_setPalette(PAL1,palette_BLACK.data,DMA_QUEUE);

                G_SEQUENCE = SEQUENCE_GAME;

                G_SEQUENCE_LOADED = FALSE;

                SYS_doVBlankProcess();
            }
        }

        //
        else if( changed & state & BUTTON_RIGHT )
        {
            if(G_LEVEL < 2)
            {
                G_LEVEL = 2;

                // DISPLAY LEVEL NUMBER //
                VDP_drawIntEx_BG_A_QUEUE(G_LEVEL,1,51,23,PAL0);
            }
        }

        //
        else if( changed & state & BUTTON_LEFT )
        {
            if(G_LEVEL > 1)
            {
                G_LEVEL = 1;

                // DISPLAY LEVEL NUMBER //
                VDP_drawIntEx_BG_A_QUEUE(G_LEVEL,1,51,23,PAL0);
            }
        }
    }
}




void player_Callback(u16 joy, u16 changed, u16 state)
{
    if(joy == JOY_1)
    {
        // BOUTON A //
        if( changed & state & BUTTON_A )
        {
            if(player.state == STATE_IDLE || player.state == STATE_WALK)
            {
                G_REPEAT = 0;
                
                SPR_setAnimAndFrame(sprite_PLAYER,1,0);

                player.counter_ANIM = 1;

                player.state = STATE_PUNCH;
            }


            else if(player.state == STATE_PUNCH)
            {
                // IF PLAYER PRESS A BETWEEN FRAME 17 AND 23 OF THE PUNCH ANIMATION //
                if(player.counter_ANIM > 16)
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


            else if(player.state == STATE_CROUCH)
            {
                G_REPEAT = 0;
                
                SPR_setAnimAndFrame(sprite_PLAYER,3,0);

                player.counter_ANIM = 1;

                player.state = STATE_PUNCH_CROUCH;
            }


            else if(player.state == STATE_PUNCH_CROUCH)
            {
                // IF PLAYER PRESS A BETWEEN FRAME 17 AND 23 OF THE PUNCH ANIMATION //
                if(player.counter_ANIM > 16)
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
        }

        // BOUTON B //   
        else if( changed & state & BUTTON_B )
        {
            if(player.state == STATE_IDLE || player.state == STATE_WALK)
            {
                G_REPEAT = 0;
                
                SPR_setAnimAndFrame(sprite_PLAYER,6,0);

                player.counter_ANIM = 1;

                player.state = STATE_KICK;
            }


            else if(player.state == STATE_KICK)
            {
                // IF PLAYER PRESS A BETWEEN FRAME 5 AND 23 OF THE KICK ANIMATION //
                if(player.counter_ANIM > 5)
                {
                    // KICK WILL REPEAT //
                    G_REPEAT = 1;
                }
            }


            else if(player.state == STATE_CROUCH)
            {
                G_REPEAT = 0;
                
                SPR_setAnimAndFrame(sprite_PLAYER,7,0);

                player.counter_ANIM = 0;

                player.state = STATE_KICK_CROUCH;
            }
        }
    }
}

