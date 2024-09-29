#include "genesis.h"




#include "include/custom_tools.h"




#include "include/joypad_BUTTONS.h"
#include "include/init.h"




#include "include/routines_INTERMEDE.h"
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
            JOY_setEventHandler(disable_Callback);
            
            // LOADING INTERMEDE SCREEN //
            if(G_SEQUENCE_LOADED == FALSE)
            {
                if(G_LEVEL == 1)
                {
                    init_INTERMEDE_1();
                }

                else if(G_LEVEL == 2)
                {                    
                    init_INTERMEDE_2();
                }

                else if(G_LEVEL == 3)
                {                    
                    init_INTERMEDE_3();
                }

                else if(G_LEVEL == 4)
                {                    
                    init_INTERMEDE_4();
                }

                else if(G_LEVEL == 5)
                {                    
                    init_INTERMEDE_5();
                }
            }

            else
            {                                
                if(G_LEVEL == 1)
                {    
                    sequence_INTERMEDE_1();
                }

                else if(G_LEVEL == 2)
                {       
                    sequence_INTERMEDE_2();
                }

                else if(G_LEVEL == 3)
                {    
                    sequence_INTERMEDE_3();
                }

                else if(G_LEVEL == 4)
                {    
                    sequence_INTERMEDE_4();
                }

                else if(G_LEVEL == 5)
                {    
                    sequence_INTERMEDE_5();
                }

                SPR_update();
                SYS_doVBlankProcess();
            } 
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
                JOY_setEventHandler(disable_Callback);
                
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
