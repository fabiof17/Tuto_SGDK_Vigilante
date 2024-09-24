#include <genesis.h>



#include "custom_tools.h"
#include "structures.h"
#include "variables.h"







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




void joypad_PLAYER()
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
                G_POS_X_CAMERA -= 1;

                MAP_scrollTo(map_BG_B, G_POS_X_CAMERA , 0);
                MAP_scrollTo(map_BG_A, G_POS_X_CAMERA , 0);

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
                    if(G_POS_X_CAMERA < 1536)
                    {
                        G_POS_X_CAMERA += 1;

                        MAP_scrollTo(map_BG_B, G_POS_X_CAMERA , 0);
                        MAP_scrollTo(map_BG_A, G_POS_X_CAMERA , 0);

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
                if(G_POS_X_CAMERA < 1536)
                {
                    G_POS_X_CAMERA += 1;

                    MAP_scrollTo(map_BG_B, G_POS_X_CAMERA , 0);
                    MAP_scrollTo(map_BG_A, G_POS_X_CAMERA , 0);

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

