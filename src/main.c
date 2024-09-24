#include "genesis.h"




#include "include/custom_tools.h"




#include "include/joypad_BUTTONS.h"
#include "include/init.h"




#include "include/routines_LEVEL.h"
#include "include/routines_LOGO.h"
#include "include/routines_TITLE.h"


#include "include/variables.h"









int main(bool hardReset)
{
    init_SYSTEM();

    init_VARIABLES();

    JOY_init();
    
    while(TRUE)
    {
        //**************************************************************************************//
        //                                                                                      //
        //                                      LOGO                                            //
        //                                                                                      //
        //**************************************************************************************//

        if(G_SEQUENCE == SEQUENCE_LOGO)
        {
            // LOADING LOGO SCREEN //
            if(G_SEQUENCE_LOADED == FALSE)
            {
                init_LOGO();
            }

            else
            {                
                JOY_setEventHandler(logo_Callback);

                sequence_LOGO();
                
                SPR_update();
                SYS_doVBlankProcess();
            }            
        }




        //**************************************************************************************//
        //                                                                                      //
        //                                      TITLE                                           //
        //                                                                                      //
        //**************************************************************************************//

        else if(G_SEQUENCE == SEQUENCE_TITLE)
        {
            // LOADING TITLE SCREEN //
            if(G_SEQUENCE_LOADED == FALSE)
            {
                init_TITLE();
            }

            else
            {                
                JOY_setEventHandler(title_Callback);
                
                sequence_TITLE();
                
                SPR_update();
                SYS_doVBlankProcess();
            } 
        }




        //**************************************************************************************//
        //                                                                                      //
        //                                    INTERMEDE                                         //
        //                                                                                      //
        //**************************************************************************************//

        else if(G_SEQUENCE == SEQUENCE_INTERMEDE)
        {
            
        }




        //**************************************************************************************//
        //                                                                                      //
        //                                     LEVEL                                            //
        //                                                                                      //
        //**************************************************************************************//

        else if(G_SEQUENCE == SEQUENCE_GAME)
        {
            // LOADING LEVEL //
            if(G_SEQUENCE_LOADED == FALSE)
            {
                init_LEVEL();
            }

            else
            {
                JOY_setEventHandler(player_Callback);
                joypad_PLAYER();

                update_PLAYER_SPRITE();
                
                SPR_update();
                SYS_doVBlankProcess();
            }
        }
    }

	return 0;
}
