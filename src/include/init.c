#include <genesis.h>




#include "custom_tools.h"
#include "variables.h"
#include "palettes.h"
#include "structures.h"




#include "maps_GLOBAL.h"
#include "maps_INTERMEDE.h"
#include "maps_LEVELS.h"
#include "maps_LOGO.h"
#include "maps_TITLE.h"




#include "sound.h"




#include "sprites_INTERMEDE.h"
#include "sprites_LEVEL.h"
#include "sprites_TITLE.h"








void init_SYSTEM()
{  
    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                   4 BLACK PALETTES                                   //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    PAL_setColors(0, (u16*) palette_black, 64, CPU);


    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                  H40 MODE : 256*224                                  //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

	VDP_setScreenWidth256();
    VDP_setScreenHeight224();


    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                SCROLLING MODE : PLANE                                //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

}


void init_VARIABLES()
{
    //**************************************************************************************//
    //                                                                                      //
    //                                SEQUENCE INITIALISATION                               //
    //                                                                                      //
    //**************************************************************************************//

    G_SEQUENCE = SEQUENCE_LOGO; // SEQUENCE_LOGO | SEQUENCE_TITLE | SEQUENCE_INTERMEDE | SEQUENCE_GAME 




    //**************************************************************************************//
    //                                                                                      //
    //                                        DEBUG                                         //
    //                                                                                      //
    //**************************************************************************************//




    //**************************************************************************************//
    //                                                                                      //
    //                                      GENERAL                                         //
    //                                                                                      //
    //**************************************************************************************// 

    setRandomSeed(1024);

    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                  GENERAL VARIABLES                                   //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    G_POINTS                    = 0;

    G_HI_SCORE                  = 5000;
    
    G_LEVEL                     = 1;

    G_PAUSE                     = FALSE;

    G_SEQUENCE_LOADED           = FALSE;

    G_PHASE_LEVEL               = LEVEL_PLAY;




    //**************************************************************************************//
    //                                                                                      //
    //                                         AUDIO                                        //
    //                                                                                      //
    //**************************************************************************************//

    XGM_setPCM(SOUND_HIT_KICK, PCM_HIT_KICK, sizeof(PCM_HIT_KICK));
    XGM_setPCM(SOUND_HIT_PUNCH, PCM_HIT_PUNCH, sizeof(PCM_HIT_PUNCH));



}




void init_LOGO()
{
    //**************************************************************************************//
    //                                                                                      //
    //                                    SETUP DISPLAY                                     //
    //                                                                                      //
    //**************************************************************************************//

    VDP_setPlaneSize(64,32,TRUE);
    
    SPR_init();
    
    VDP_setHilightShadow(FALSE);




    //**************************************************************************************//
    //                                                                                      //
    //                                         BG                                           //
    //                                                                                      //
    //**************************************************************************************//

    G_ADR_VRAM_BG_B = TILE_USER_INDEX;

    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                         BG_B                                         //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    VDP_loadTileSet(image_IREM.tileset, G_ADR_VRAM_BG_B, CPU);
    VDP_setTileMapEx(BG_B, image_IREM.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 0, 0, 0, 0, 32, 28, CPU);




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                       PALETTES                                       //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    PAL_setPalette(PAL0,image_IREM.palette->data,DMA_QUEUE);




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                       VARIABLES                                      //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    G_COUNTER_LOGO              = 0;
    
    G_SEQUENCE_LOADED           = TRUE;
}


void init_TITLE()
{
    //**************************************************************************************//
    //                                                                                      //
    //                                    SETUP DISPLAY                                     //
    //                                                                                      //
    //**************************************************************************************//

    VDP_setPlaneSize(64,64,TRUE);
    
    SPR_init();
    
    VDP_setHilightShadow(FALSE);




    //**************************************************************************************//
    //                                                                                      //
    //                                   NUMBERS TILESET                                    //
    //                                                                                      //
    //**************************************************************************************//

    VDP_loadTileSet(image_NUMBERS_TITLE.tileset, TILE_FONT_INDEX + 16, CPU);




    //**************************************************************************************//
    //                                                                                      //
    //                                         BG                                           //
    //                                                                                      //
    //**************************************************************************************//

    G_ADR_VRAM_BG_B = TILE_USER_INDEX;

    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                         BG_B                                         //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    VDP_loadTileSet(image_TITLE_BG_B.tileset, G_ADR_VRAM_BG_B, CPU);
    VDP_setTileMapEx(BG_B, image_TITLE_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 0, 0, 0, 0, 64, 64, CPU);


    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                         BG_A                                         //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    G_ADR_VRAM_BG_A = G_ADR_VRAM_BG_B + image_TITLE_BG_B.tileset->numTile;
    VDP_loadTileSet(image_TITLE_BG_A.tileset, G_ADR_VRAM_BG_A, CPU);
    VDP_setTileMapEx(BG_A, image_TITLE_BG_A.tilemap, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_A), 0, 0, 0, 0, 64, 28, CPU);




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                     INIT SPRITES                                     //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    sprite_ARROW = SPR_addSprite(&tiles_SPR_ARROW, -8, -8, TILE_ATTR(PAL0, FALSE, FALSE, FALSE)); // 72 184

    SPR_update();



    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                       PALETTES                                       //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    PAL_setPalette(PAL0,image_TITLE_BG_B.palette->data,DMA_QUEUE);
    PAL_setPalette(PAL1,palette_TITLE_BG_A_MD.data,DMA_QUEUE);




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                       VARIABLES                                      //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    G_POS_X_CAMERA              = 0;

    G_COUNTER_TITLE             = 1;

    G_OPTIONS                   = LEVEL_OPTION;

    G_COLORS_OPTION             = MD_COLORS;

    G_SEQUENCE_LOADED           = TRUE;
}




void init_INTERMEDE_1()
{
    //**************************************************************************************//
    //                                                                                      //
    //                                    SETUP DISPLAY                                     //
    //                                                                                      //
    //**************************************************************************************//

    VDP_setPlaneSize(64,32,TRUE);
    
    SPR_init();
    
    VDP_setHilightShadow(FALSE);

    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);




    //**************************************************************************************//
    //                                                                                      //
    //                                   NUMBERS TILESET                                    //
    //                                                                                      //
    //**************************************************************************************//

    //VDP_loadTileSet(image_NUMBERS_TITLE.tileset, TILE_FONT_INDEX + 16, CPU);




    //**************************************************************************************//
    //                                                                                      //
    //                                         BG                                           //
    //                                                                                      //
    //**************************************************************************************//

    G_ADR_VRAM_BG_B = TILE_USER_INDEX;

    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                         BG_B                                         //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    VDP_loadTileSet(image_INTERMEDE_BG_B.tileset, G_ADR_VRAM_BG_B, CPU);
    VDP_setTileMapEx(BG_B, image_INTERMEDE_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 0, 0, 0, 0, 64, 28, CPU);


    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                         BG_A                                         //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    G_ADR_VRAM_BG_A = G_ADR_VRAM_BG_B + image_INTERMEDE_BG_B.tileset->numTile;
    VDP_loadTileSet(image_INTERMEDE_BG_A.tileset, G_ADR_VRAM_BG_A, CPU);
    VDP_setTileMapEx(BG_A, image_INTERMEDE_BG_A.tilemap, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_A), 0, 0, 0, 0, 32, 28, CPU);




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                SETUP PLANES POSITION                                 //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    VDP_setHorizontalScroll(BG_B , 0);
    VDP_setHorizontalScroll(BG_A , 0);

    VDP_setVerticalScroll(BG_B , 0);
    VDP_setVerticalScroll(BG_A , 0);




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                         TEXT                                         //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    G_ADR_VRAM_TEXT = G_ADR_VRAM_BG_A + image_INTERMEDE_BG_A.tileset->numTile;
    VDP_loadTileSet(image_INTERMEDE_1_TEXT.tileset, G_ADR_VRAM_TEXT, CPU);




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                     INIT SPRITES                                     //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    //--------------------------------------------------------------------------------------//
    //                                       MADONNA                                        //
    //--------------------------------------------------------------------------------------//

    sprite_MADONNA = SPR_addSprite(&tiles_SPR_MADONNA, -64, -64, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));


    //--------------------------------------------------------------------------------------//
    //                                      WOODEN BOX                                      //
    //--------------------------------------------------------------------------------------//

    sprite_BOX = SPR_addSprite(&tiles_SPR_BOX, 122, 104, TILE_ATTR(PAL3, FALSE, FALSE, FALSE));


    SPR_update();
    SYS_doVBlankProcess();




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                       PALETTES                                       //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    PAL_setPalette(PAL0,image_INTERMEDE_BG_B.palette->data,DMA_QUEUE);
    PAL_setPalette(PAL1,image_INTERMEDE_BG_A.palette->data,DMA_QUEUE);

    if(G_COLORS_OPTION == MD_COLORS)
    {
        PAL_setPalette(PAL2,palette_MADONNA_INTERMEDE_MD.data,DMA_QUEUE);
    }

    else
    {
        PAL_setPalette(PAL2,palette_MADONNA_INTERMEDE_PCE.data,DMA_QUEUE);
    }
    
    PAL_setPalette(PAL3,palette_BOX.data,DMA_QUEUE);


    SYS_doVBlankProcess();




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                       VARIABLES                                      //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    G_TEXT_MAX_LINES            = 4;

    G_LINE_INDEX                = 0;

    G_LETTER_INDEX              = 0;

    G_POS_X_CAMERA              = 0;

    G_COUNTER_INTERMEDE         = 0;

    G_SEQUENCE_LOADED           = TRUE;
}


void init_INTERMEDE_2()
{
    //**************************************************************************************//
    //                                                                                      //
    //                                    SETUP DISPLAY                                     //
    //                                                                                      //
    //**************************************************************************************//

    VDP_setPlaneSize(64,32,TRUE);
    
    SPR_init();
    
    VDP_setHilightShadow(FALSE);

    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);




    //**************************************************************************************//
    //                                                                                      //
    //                                      CLEAN VRAM                                      //
    //                                                                                      //
    //**************************************************************************************//

    u16 i = 0;

    for(i=16 ; i<1440 ; i++)
    {
        VDP_loadTileSet(image_EMPTY_TILE.tileset , i , CPU);
    }




    //**************************************************************************************//
    //                                                                                      //
    //                                         BG                                           //
    //                                                                                      //
    //**************************************************************************************//

    G_ADR_VRAM_BG_B = TILE_USER_INDEX;

    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                         BG_B                                         //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    VDP_loadTileSet(image_INTERMEDE_BG_B.tileset, G_ADR_VRAM_BG_B, CPU);
    VDP_setTileMapEx(BG_B, image_INTERMEDE_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 0, 0, 0, 0, 64, 28, CPU);


    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                         BG_A                                         //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    G_ADR_VRAM_BG_A = G_ADR_VRAM_BG_B + image_INTERMEDE_BG_B.tileset->numTile;
    VDP_loadTileSet(image_INTERMEDE_BG_A.tileset, G_ADR_VRAM_BG_A, CPU);
    VDP_setTileMapEx(BG_A, image_INTERMEDE_BG_A.tilemap, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_A), 0, 0, 0, 0, 32, 28, CPU);
    VDP_setTileMapEx(BG_A, image_INTERMEDE_BG_A.tilemap, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_A), 8, 8, 32, 0, 6, 10, CPU);




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                SETUP PLANES POSITION                                 //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    VDP_setHorizontalScroll(BG_B , 0);
    VDP_setHorizontalScroll(BG_A , 0);

    VDP_setVerticalScroll(BG_B , 0);
    VDP_setVerticalScroll(BG_A , 0);




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                         TEXT                                         //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    G_ADR_VRAM_TEXT = G_ADR_VRAM_BG_A + image_INTERMEDE_BG_A.tileset->numTile;
    VDP_loadTileSet(image_INTERMEDE_2_TEXT.tileset, G_ADR_VRAM_TEXT, CPU);




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                     INIT SPRITES                                     //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    //--------------------------------------------------------------------------------------//
    //                                       MADONNA                                        //
    //--------------------------------------------------------------------------------------//

    sprite_MADONNA = SPR_addSprite(&tiles_SPR_MADONNA, 91, 123, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));

    SPR_setFrame(sprite_MADONNA,3);


    //--------------------------------------------------------------------------------------//
    //                                      WOODEN BOX                                      //
    //--------------------------------------------------------------------------------------//

    sprite_BOX = SPR_addSprite(&tiles_SPR_BOX, 122, 104, TILE_ATTR(PAL3, FALSE, FALSE, FALSE));


    SPR_update();
    SYS_doVBlankProcess();




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                       PALETTES                                       //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    PAL_setPalette(PAL0,image_INTERMEDE_BG_B.palette->data,DMA_QUEUE);
    PAL_setPalette(PAL1,image_INTERMEDE_BG_A.palette->data,DMA_QUEUE);

    if(G_COLORS_OPTION == MD_COLORS)
    {
        PAL_setPalette(PAL2,palette_MADONNA_INTERMEDE_MD.data,DMA_QUEUE);
    }

    else
    {
        PAL_setPalette(PAL2,palette_MADONNA_INTERMEDE_PCE.data,DMA_QUEUE);
    }

    PAL_setPalette(PAL3,palette_BOX.data,DMA_QUEUE);


    SYS_doVBlankProcess();




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                       VARIABLES                                      //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    G_TEXT_MAX_LINES            = 3;

    G_LINE_INDEX                = 0;

    G_LETTER_INDEX              = 0;

    G_POS_X_CAMERA              = 0;

    G_COUNTER_INTERMEDE         = 0;

    G_SEQUENCE_LOADED           = TRUE;
}


void init_INTERMEDE_3()
{
    //**************************************************************************************//
    //                                                                                      //
    //                                    SETUP DISPLAY                                     //
    //                                                                                      //
    //**************************************************************************************//

    VDP_setPlaneSize(64,32,TRUE);
    
    SPR_init();
    
    VDP_setHilightShadow(FALSE);

    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);




    //**************************************************************************************//
    //                                                                                      //
    //                                      CLEAN VRAM                                      //
    //                                                                                      //
    //**************************************************************************************//

    u16 i = 0;

    for(i=16 ; i<1440 ; i++)
    {
        VDP_loadTileSet(image_EMPTY_TILE.tileset , i , CPU);
    }




    //**************************************************************************************//
    //                                                                                      //
    //                                         BG                                           //
    //                                                                                      //
    //**************************************************************************************//

    G_ADR_VRAM_BG_B = TILE_USER_INDEX;

    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                         BG_B                                         //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    VDP_loadTileSet(image_INTERMEDE_BG_B.tileset, G_ADR_VRAM_BG_B, CPU);
    VDP_setTileMapEx(BG_B, image_INTERMEDE_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 0, 0, 0, 0, 64, 28, CPU);


    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                         BG_A                                         //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    G_ADR_VRAM_BG_A = G_ADR_VRAM_BG_B + image_INTERMEDE_BG_B.tileset->numTile;
    VDP_loadTileSet(image_INTERMEDE_BG_A.tileset, G_ADR_VRAM_BG_A, CPU);
    VDP_setTileMapEx(BG_A, image_INTERMEDE_BG_A.tilemap, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_A), 0, 0, 0, 0, 32, 28, CPU);
    VDP_setTileMapEx(BG_A, image_INTERMEDE_BG_A.tilemap, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_A), 8, 8, 32, 0, 6, 10, CPU);




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                SETUP PLANES POSITION                                 //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    VDP_setHorizontalScroll(BG_B , 0);
    VDP_setHorizontalScroll(BG_A , 0);

    VDP_setVerticalScroll(BG_B , 0);
    VDP_setVerticalScroll(BG_A , 0);




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                         TEXT                                         //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    G_ADR_VRAM_TEXT = G_ADR_VRAM_BG_A + image_INTERMEDE_BG_A.tileset->numTile;
    VDP_loadTileSet(image_INTERMEDE_3_TEXT.tileset, G_ADR_VRAM_TEXT, CPU);




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                     INIT SPRITES                                     //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//
    //--------------------------------------------------------------------------------------//
    //                                       MADONNA                                        //
    //--------------------------------------------------------------------------------------//

    sprite_MADONNA = SPR_addSprite(&tiles_SPR_MADONNA, 91, 123, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));

    SPR_setFrame(sprite_MADONNA,3);


    //--------------------------------------------------------------------------------------//
    //                                      WOODEN BOX                                      //
    //--------------------------------------------------------------------------------------//

    sprite_BOX = SPR_addSprite(&tiles_SPR_BOX, 122, 104, TILE_ATTR(PAL3, FALSE, FALSE, FALSE));


    SPR_update();
    SYS_doVBlankProcess();




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                       PALETTES                                       //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    PAL_setPalette(PAL0,image_INTERMEDE_BG_B.palette->data,DMA_QUEUE);
    PAL_setPalette(PAL1,image_INTERMEDE_BG_A.palette->data,DMA_QUEUE);
    
    if(G_COLORS_OPTION == MD_COLORS)
    {
        PAL_setPalette(PAL2,palette_MADONNA_INTERMEDE_MD.data,DMA_QUEUE);
    }

    else
    {
        PAL_setPalette(PAL2,palette_MADONNA_INTERMEDE_PCE.data,DMA_QUEUE);
    }

    PAL_setPalette(PAL3,palette_BOX.data,DMA_QUEUE);


    SYS_doVBlankProcess();




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                       VARIABLES                                      //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    G_TEXT_MAX_LINES            = 3;

    G_LINE_INDEX                = 0;

    G_LETTER_INDEX              = 0;

    G_POS_X_CAMERA              = 0;

    G_COUNTER_INTERMEDE         = 0;

    G_SEQUENCE_LOADED           = TRUE;
}


void init_INTERMEDE_4()
{
    //**************************************************************************************//
    //                                                                                      //
    //                                    SETUP DISPLAY                                     //
    //                                                                                      //
    //**************************************************************************************//

    VDP_setPlaneSize(64,32,TRUE);
    
    SPR_init();
    
    VDP_setHilightShadow(FALSE);

    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);




    //**************************************************************************************//
    //                                                                                      //
    //                                      CLEAN VRAM                                      //
    //                                                                                      //
    //**************************************************************************************//

    u16 i = 0;

    for(i=16 ; i<1440 ; i++)
    {
        VDP_loadTileSet(image_EMPTY_TILE.tileset , i , CPU);
    }




    //**************************************************************************************//
    //                                                                                      //
    //                                         BG                                           //
    //                                                                                      //
    //**************************************************************************************//

    G_ADR_VRAM_BG_B = TILE_USER_INDEX;

    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                         BG_B                                         //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    VDP_loadTileSet(image_INTERMEDE_BG_B.tileset, G_ADR_VRAM_BG_B, CPU);
    VDP_setTileMapEx(BG_B, image_INTERMEDE_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 0, 0, 0, 0, 64, 28, CPU);


    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                         BG_A                                         //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    G_ADR_VRAM_BG_A = G_ADR_VRAM_BG_B + image_INTERMEDE_BG_B.tileset->numTile;
    VDP_loadTileSet(image_INTERMEDE_BG_A.tileset, G_ADR_VRAM_BG_A, CPU);
    VDP_setTileMapEx(BG_A, image_INTERMEDE_BG_A.tilemap, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_A), 0, 0, 0, 0, 32, 28, CPU);
    VDP_setTileMapEx(BG_A, image_INTERMEDE_BG_A.tilemap, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_A), 8, 8, 32, 0, 6, 10, CPU);




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                SETUP PLANES POSITION                                 //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    VDP_setHorizontalScroll(BG_B , 0);
    VDP_setHorizontalScroll(BG_A , 0);

    VDP_setVerticalScroll(BG_B , 0);
    VDP_setVerticalScroll(BG_A , 0);




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                         TEXT                                         //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    G_ADR_VRAM_TEXT = G_ADR_VRAM_BG_A + image_INTERMEDE_BG_A.tileset->numTile;
    VDP_loadTileSet(image_INTERMEDE_4_TEXT.tileset, G_ADR_VRAM_TEXT, CPU);




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                     INIT SPRITES                                     //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//
    //--------------------------------------------------------------------------------------//
    //                                       MADONNA                                        //
    //--------------------------------------------------------------------------------------//

    sprite_MADONNA = SPR_addSprite(&tiles_SPR_MADONNA, 91, 123, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));

    SPR_setFrame(sprite_MADONNA,3);


    //--------------------------------------------------------------------------------------//
    //                                      WOODEN BOX                                      //
    //--------------------------------------------------------------------------------------//

    sprite_BOX = SPR_addSprite(&tiles_SPR_BOX, 122, 104, TILE_ATTR(PAL3, FALSE, FALSE, FALSE));


    SPR_update();
    SYS_doVBlankProcess();




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                       PALETTES                                       //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    PAL_setPalette(PAL0,image_INTERMEDE_BG_B.palette->data,DMA_QUEUE);
    PAL_setPalette(PAL1,image_INTERMEDE_BG_A.palette->data,DMA_QUEUE);
    
    if(G_COLORS_OPTION == MD_COLORS)
    {
        PAL_setPalette(PAL2,palette_MADONNA_INTERMEDE_MD.data,DMA_QUEUE);
    }

    else
    {
        PAL_setPalette(PAL2,palette_MADONNA_INTERMEDE_PCE.data,DMA_QUEUE);
    }

    PAL_setPalette(PAL3,palette_BOX.data,DMA_QUEUE);


    SYS_doVBlankProcess();




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                       VARIABLES                                      //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    G_TEXT_MAX_LINES            = 4;

    G_LINE_INDEX                = 0;

    G_LETTER_INDEX              = 0;

    G_POS_X_CAMERA              = 0;

    G_COUNTER_INTERMEDE         = 0;

    G_SEQUENCE_LOADED           = TRUE;
}


void init_INTERMEDE_5()
{
    //**************************************************************************************//
    //                                                                                      //
    //                                    SETUP DISPLAY                                     //
    //                                                                                      //
    //**************************************************************************************//

    VDP_setPlaneSize(64,32,TRUE);
    
    SPR_init();
    
    VDP_setHilightShadow(FALSE);

    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);




    //**************************************************************************************//
    //                                                                                      //
    //                                      CLEAN VRAM                                      //
    //                                                                                      //
    //**************************************************************************************//

    u16 i = 0;

    for(i=16 ; i<1440 ; i++)
    {
        VDP_loadTileSet(image_EMPTY_TILE.tileset , i , CPU);
    }




    //**************************************************************************************//
    //                                                                                      //
    //                                         BG                                           //
    //                                                                                      //
    //**************************************************************************************//

    G_ADR_VRAM_BG_B = TILE_USER_INDEX;

    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                         BG_B                                         //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    VDP_loadTileSet(image_INTERMEDE_5_BG_B.tileset, G_ADR_VRAM_BG_B, CPU);
    VDP_setTileMapEx(BG_B, image_INTERMEDE_5_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 0, 0, 0, 0, 32, 28, CPU);


    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                         BG_A                                         //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    G_ADR_VRAM_BG_A = G_ADR_VRAM_BG_B + image_INTERMEDE_5_BG_B.tileset->numTile;
    VDP_loadTileSet(image_INTERMEDE_5_BG_A.tileset, G_ADR_VRAM_BG_A, CPU);
    VDP_setTileMapEx(BG_A, image_INTERMEDE_5_BG_A.tilemap, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_A), 0, 0, 0, 0, 32, 28, CPU);




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                SETUP PLANES POSITION                                 //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//
    
    VDP_setHorizontalScroll(BG_B , 0);
    VDP_setHorizontalScroll(BG_A , 0);

    VDP_setVerticalScroll(BG_B , 0);
    VDP_setVerticalScroll(BG_A , 0);




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                         TEXT                                         //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    G_ADR_VRAM_TEXT = G_ADR_VRAM_BG_A + image_INTERMEDE_5_BG_A.tileset->numTile;
    VDP_loadTileSet(image_INTERMEDE_5_TEXT.tileset, G_ADR_VRAM_TEXT, CPU);




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                     INIT SPRITES                                     //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    //--------------------------------------------------------------------------------------//
    //                                       MADONNA                                        //
    //--------------------------------------------------------------------------------------//

    sprite_MADONNA = SPR_addSprite(&tiles_SPR_MADONNA_2, 82, 68, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));


    //--------------------------------------------------------------------------------------//
    //                                        CHAIN                                         //
    //--------------------------------------------------------------------------------------//

    sprite_CHAIN = SPR_addSprite(&tiles_SPR_CHAIN, 97, -32, TILE_ATTR(PAL3, FALSE, FALSE, FALSE));


    SPR_update();
    SYS_doVBlankProcess();




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                       PALETTES                                       //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    PAL_setPalette(PAL0,image_INTERMEDE_5_BG_B.palette->data,DMA_QUEUE);
    PAL_setPalette(PAL1,image_INTERMEDE_5_BG_A.palette->data,DMA_QUEUE);
    
    if(G_COLORS_OPTION == MD_COLORS)
    {
        PAL_setPalette(PAL2,palette_MADONNA_INTERMEDE_MD.data,DMA_QUEUE);
    }

    else
    {
        PAL_setPalette(PAL2,palette_MADONNA_INTERMEDE_PCE.data,DMA_QUEUE);
    }

    PAL_setPalette(PAL3,palette_CHAIN_INTERMEDE.data,DMA_QUEUE);


    SYS_doVBlankProcess();




    //--------------------------------------------------------------------------------------//
    //                                                                                      //
    //                                       VARIABLES                                      //
    //                                                                                      //
    //--------------------------------------------------------------------------------------//

    G_INDEX_MADONNA             = 0;

    G_TEXT_MAX_LINES            = 3;

    G_LINE_INDEX                = 0;

    G_LETTER_INDEX              = 0;

    G_POS_X_CAMERA              = 0;

    G_COUNTER_INTERMEDE         = 0;

    G_SEQUENCE_LOADED           = TRUE;
}




void init_LEVEL()
{
    if(G_LEVEL == 1)
    {
        //**************************************************************************************//
        //                                                                                      //
        //                                      CLEAN VRAM                                      //
        //                                                                                      //
        //**************************************************************************************//

        u16 i = 0;

        for(i=16 ; i<1440 ; i++)
        {
            VDP_loadTileSet(image_EMPTY_TILE.tileset , i , CPU);
        }




        //**************************************************************************************//
        //                                                                                      //
        //                                    SETUP DISPLAY                                     //
        //                                                                                      //
        //**************************************************************************************//

        VDP_setPlaneSize(64,32,TRUE);
        
        SPR_initEx(300);
        
        VDP_setHilightShadow(FALSE);

        VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);




        //**************************************************************************************//
        //                                                                                      //
        //                                   NUMBERS TILESET                                    //
        //                                                                                      //
        //**************************************************************************************//

        VDP_loadTileSet(image_NUMBERS.tileset, TILE_FONT_INDEX + 16, CPU);




        //**************************************************************************************//
        //                                                                                      //
        //                                         BG                                           //
        //                                                                                      //
        //**************************************************************************************//

        G_ADR_VRAM_BG_B = VRAM_START_ADRESS; //VRAM_START_ADRESS

        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                         BG_B                                         //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        VDP_loadTileSet(&tileset_LEVEL_1_BG_B, G_ADR_VRAM_BG_B, CPU);


        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                         BG_A                                         //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        G_ADR_VRAM_BG_A = G_ADR_VRAM_BG_B + tileset_LEVEL_1_BG_B.numTile;
        VDP_loadTileSet(&tileset_LEVEL_1_BG_A, G_ADR_VRAM_BG_A, CPU);




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                    CREATE MAP BG_B                                   //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        map_BG_B = MAP_create(&map_LEVEL_1_BG_B, BG_B, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B));
        SYS_doVBlankProcess();


        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                    CREATE MAP BG_A                                   //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        map_BG_A = MAP_create(&map_LEVEL_1_BG_A, BG_A, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_A));
        SYS_doVBlankProcess();




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                      INIT MAPS                                       //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        G_POS_X_CAMERA = 0;


        MAP_scrollTo(map_BG_B, G_POS_X_CAMERA , 0);
        SYS_doVBlankProcess();

        MAP_scrollTo(map_BG_A, G_POS_X_CAMERA , 0);
        SYS_doVBlankProcess();




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                         HUB                                          //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        VDP_setWindowHPos(0, 0);
        VDP_setWindowVPos(0, 5);


        G_ADR_VRAM_HUB = G_ADR_VRAM_BG_A + tileset_LEVEL_1_BG_A.numTile;
        VDP_loadTileSet(image_HUB.tileset, G_ADR_VRAM_HUB, CPU);
        VDP_setTileMapEx(WINDOW, image_HUB.tilemap, TILE_ATTR_FULL(PAL3, TRUE, FALSE, FALSE, G_ADR_VRAM_HUB), 0, 0, 0, 0, 32, 5, CPU);




        //--------------------------------------------------------------------------------------//
        //                                       HI SCORE                                       //
        //--------------------------------------------------------------------------------------//
        VDP_drawIntEx_WINDOW_CPU_PRIO(G_HI_SCORE,4,15,2,PAL3);

        //--------------------------------------------------------------------------------------//
        //                                        SCORE                                         //
        //--------------------------------------------------------------------------------------//
        VDP_drawIntEx_WINDOW_CPU_PRIO(G_POINTS,1,7,2,PAL3);




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                   PLAYER LIFE BAR                                    //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        G_ADR_VRAM_LIFE_PLAYER = G_ADR_VRAM_HUB + image_HUB.tileset->numTile;
        VDP_loadTileSet(image_LIFE_PLAYER.tileset, G_ADR_VRAM_LIFE_PLAYER, CPU);




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                    BOSS LIFE BAR                                     //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        G_ADR_VRAM_LIFE_BOSS = G_ADR_VRAM_LIFE_PLAYER + image_LIFE_PLAYER.tileset->numTile;
        VDP_loadTileSet(image_LIFE_BOSS.tileset, G_ADR_VRAM_LIFE_BOSS, CPU);




        //**************************************************************************************//
        //                                                                                      //
        //                                     INIT SPRITES                                     //
        //                                                                                      //
        //**************************************************************************************//

        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                        PAUSE                                         //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        sprite_PAUSE = SPR_addSprite(&tiles_SPR_PAUSE, 0,-8, TILE_ATTR(PAL3, FALSE, FALSE, FALSE));


        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                      VIGILANTE                                       //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        G_GROUND_POSITION   = 113;

        player.pos_X        = -8; //87
        player.pos_Y        = G_GROUND_POSITION;

        player.counter_ANIM = 4;
        player.axis         = AXIS_RIGHT;

        player.state        = STATE_IDLE;


        sprite_PLAYER = SPR_addSprite(&tiles_SPR_VIGILANTE_MD, player.pos_X,player.pos_Y, TILE_ATTR(PAL3, FALSE, FALSE, FALSE));


        SPR_setAnimAndFrame(sprite_PLAYER,0,4);




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                    STAGE 1 READY                                     //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        sprite_STAGE = SPR_addSprite(&tiles_SPR_STAGE_1, 72, 87, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));



        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                       ENEMIES                                        //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        for(i=0 ; i<4 ; i++)
        {
            LIST_ENEMIES[i].pos_X           = 0;
            LIST_ENEMIES[i].pos_Y           = 0;
            
            LIST_ENEMIES[i].counter_ANIM    = 0;

            LIST_ENEMIES[i].spr_ENEMY       = NULL;
        }




        SPR_update();
        SYS_doVBlankProcess();




        //**************************************************************************************//
        //                                                                                      //
        //                                       PALETTES                                       //
        //                                                                                      //
        //**************************************************************************************//

        PAL_setPalette(PAL0,image_LEVEL_1_BG_B.palette->data,DMA_QUEUE);
        PAL_setPalette(PAL1,image_LEVEL_1_BG_A.palette->data,DMA_QUEUE);
        PAL_setPalette(PAL2,palette_STAGE.data,DMA_QUEUE);

        if(G_COLORS_OPTION == MD_COLORS)
        {
            PAL_setPalette(PAL3,palette_VIGILANTE_MD.data,DMA_QUEUE);
        }

        else
        {
            PAL_setPalette(PAL3,palette_VIGILANTE_PCE.data,DMA_QUEUE);
        }
        
        




        //**************************************************************************************//
        //                                                                                      //
        //                                       VARIABLES                                      //
        //                                                                                      //
        //**************************************************************************************//

        G_LEVEL_LIMIT           = 1536;

        G_SPAWN_MAX_INDEX       = 72;
    }
    

    else if(G_LEVEL == 2)
    {
        //**************************************************************************************//
        //                                                                                      //
        //                                      CLEAN VRAM                                      //
        //                                                                                      //
        //**************************************************************************************//

        u16 i = 0;

        for(i=16 ; i<1440 ; i++)
        {
            VDP_loadTileSet(image_EMPTY_TILE.tileset , i , CPU);
        }




        //**************************************************************************************//
        //                                                                                      //
        //                                    SETUP DISPLAY                                     //
        //                                                                                      //
        //**************************************************************************************//

        VDP_setPlaneSize(64,32,TRUE);
        
        SPR_initEx(300);
        
        VDP_setHilightShadow(FALSE);

        VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);




        //**************************************************************************************//
        //                                                                                      //
        //                                   NUMBERS TILESET                                    //
        //                                                                                      //
        //**************************************************************************************//

        VDP_loadTileSet(image_NUMBERS.tileset, TILE_FONT_INDEX + 16, CPU);




        //**************************************************************************************//
        //                                                                                      //
        //                                         BG                                           //
        //                                                                                      //
        //**************************************************************************************//

        G_ADR_VRAM_BG_B = VRAM_START_ADRESS;

        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                         BG_B                                         //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        VDP_loadTileSet(&tileset_LEVEL_2_BG_B, G_ADR_VRAM_BG_B, CPU);


        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                         BG_A                                         //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        G_ADR_VRAM_BG_A = G_ADR_VRAM_BG_B + tileset_LEVEL_2_BG_B.numTile;
        VDP_loadTileSet(&tileset_LEVEL_2_BG_A, G_ADR_VRAM_BG_A, CPU);




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                    CREATE MAP BG_B                                   //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        map_BG_B = MAP_create(&map_LEVEL_2_BG_B, BG_B, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B));
        SYS_doVBlankProcess();


        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                    CREATE MAP BG_A                                   //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        map_BG_A = MAP_create(&map_LEVEL_2_BG_A, BG_A, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_A));
        SYS_doVBlankProcess();




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                      INIT MAPS                                       //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        G_POS_X_CAMERA = 0;


        MAP_scrollTo(map_BG_B, G_POS_X_CAMERA , 0);
        SYS_doVBlankProcess();

        MAP_scrollTo(map_BG_A, G_POS_X_CAMERA , 0);
        SYS_doVBlankProcess();




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                         HUB                                          //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        VDP_setWindowHPos(0, 0);
        VDP_setWindowVPos(0, 5);


        G_ADR_VRAM_HUB = G_ADR_VRAM_BG_A + tileset_LEVEL_2_BG_A.numTile;
        VDP_loadTileSet(image_HUB.tileset, G_ADR_VRAM_HUB, CPU);
        VDP_setTileMapEx(WINDOW, image_HUB.tilemap, TILE_ATTR_FULL(PAL3, TRUE, FALSE, FALSE, G_ADR_VRAM_HUB), 0, 0, 0, 0, 32, 5, CPU);




        //--------------------------------------------------------------------------------------//
        //                                       HI SCORE                                       //
        //--------------------------------------------------------------------------------------//
        VDP_drawIntEx_WINDOW_CPU_PRIO(G_HI_SCORE,4,15,2,PAL3);

        //--------------------------------------------------------------------------------------//
        //                                        SCORE                                         //
        //--------------------------------------------------------------------------------------//
        VDP_drawIntEx_WINDOW_CPU_PRIO(G_POINTS,1,7,2,PAL3);




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                   PLAYER LIFE BAR                                    //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        G_ADR_VRAM_LIFE_PLAYER = G_ADR_VRAM_HUB + image_HUB.tileset->numTile;
        VDP_loadTileSet(image_LIFE_PLAYER.tileset, G_ADR_VRAM_LIFE_PLAYER, CPU);




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                    BOSS LIFE BAR                                     //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        G_ADR_VRAM_LIFE_BOSS = G_ADR_VRAM_LIFE_PLAYER + image_LIFE_PLAYER.tileset->numTile;
        VDP_loadTileSet(image_LIFE_BOSS.tileset, G_ADR_VRAM_LIFE_BOSS, CPU);




        //**************************************************************************************//
        //                                                                                      //
        //                                     INIT SPRITES                                     //
        //                                                                                      //
        //**************************************************************************************//

        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                        PAUSE                                         //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        sprite_PAUSE = SPR_addSprite(&tiles_SPR_PAUSE, 0,-8, TILE_ATTR(PAL3, FALSE, FALSE, FALSE));




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                      VIGILANTE                                       //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        G_GROUND_POSITION   = 104;

        player.pos_X        = -8; //87
        player.pos_Y        = G_GROUND_POSITION;

        player.counter_ANIM = 4;
        player.axis         = AXIS_RIGHT;

        player.state        = STATE_IDLE;


        sprite_PLAYER = SPR_addSprite(&tiles_SPR_VIGILANTE_MD, player.pos_X,player.pos_Y, TILE_ATTR(PAL3, FALSE, FALSE, FALSE));

        
        SPR_setAnimAndFrame(sprite_PLAYER,0,4);



        
        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                    STAGE 2 READY                                     //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        sprite_STAGE = SPR_addSprite(&tiles_SPR_STAGE_2, 72, 87, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                       ENEMIES                                        //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        for(i=0 ; i<4 ; i++)
        {
            LIST_ENEMIES[i].pos_X           = 0;
            LIST_ENEMIES[i].pos_Y           = 0;
            
            LIST_ENEMIES[i].counter_ANIM    = 0;

            LIST_ENEMIES[i].spr_ENEMY       = NULL;
        }



        SPR_update();
        SYS_doVBlankProcess();




        //**************************************************************************************//
        //                                                                                      //
        //                                       PALETTES                                       //
        //                                                                                      //
        //**************************************************************************************//

        PAL_setPalette(PAL0,image_LEVEL_2_BG_B.palette->data,DMA_QUEUE);
        PAL_setPalette(PAL1,image_LEVEL_2_BG_A.palette->data,DMA_QUEUE);
        PAL_setPalette(PAL2,palette_STAGE.data,DMA_QUEUE);

        if(G_COLORS_OPTION == MD_COLORS)
        {
            PAL_setPalette(PAL3,palette_VIGILANTE_MD.data,DMA_QUEUE);
        }

        else
        {
            PAL_setPalette(PAL3,palette_VIGILANTE_PCE.data,DMA_QUEUE);
        }




        //**************************************************************************************//
        //                                                                                      //
        //                                       VARIABLES                                      //
        //                                                                                      //
        //**************************************************************************************//

        G_LEVEL_LIMIT           = 1152;

        G_SPAWN_MAX_INDEX       = 72;
    }


    else if(G_LEVEL == 3)
    {
        //**************************************************************************************//
        //                                                                                      //
        //                                      CLEAN VRAM                                      //
        //                                                                                      //
        //**************************************************************************************//

        u16 i = 0;

        for(i=16 ; i<1440 ; i++)
        {
            VDP_loadTileSet(image_EMPTY_TILE.tileset , i , CPU);
        }




        //**************************************************************************************//
        //                                                                                      //
        //                                    SETUP DISPLAY                                     //
        //                                                                                      //
        //**************************************************************************************//

        VDP_setPlaneSize(64,32,TRUE);
        
        SPR_initEx(300);
        
        VDP_setHilightShadow(FALSE);

        VDP_setScrollingMode(HSCROLL_TILE, VSCROLL_PLANE);




        //**************************************************************************************//
        //                                                                                      //
        //                                   NUMBERS TILESET                                    //
        //                                                                                      //
        //**************************************************************************************//

        VDP_loadTileSet(image_NUMBERS.tileset, TILE_FONT_INDEX + 16, CPU);




        //**************************************************************************************//
        //                                                                                      //
        //                                         BG                                           //
        //                                                                                      //
        //**************************************************************************************//

        G_ADR_VRAM_BG_B = VRAM_START_ADRESS;

        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                         BG_B                                         //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        VDP_loadTileSet(image_LEVEL_3_BG_B.tileset, G_ADR_VRAM_BG_B, CPU);
        VDP_setTileMapEx(BG_B, image_LEVEL_3_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 0, 0, 0, 0, 64, 28, CPU);


        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                         BG_A                                         //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        G_ADR_VRAM_BG_A = G_ADR_VRAM_BG_B + image_LEVEL_3_BG_B.tileset->numTile;
        VDP_loadTileSet(image_LEVEL_3_BG_A.tileset, G_ADR_VRAM_BG_A, CPU);
        VDP_setTileMapEx(BG_A, image_LEVEL_3_BG_A.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_A), 0, 0, 0, 0, 64, 28, CPU);




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                         HUB                                          //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        VDP_setWindowHPos(0, 0);
        VDP_setWindowVPos(0, 5);


        G_ADR_VRAM_HUB = G_ADR_VRAM_BG_A + image_LEVEL_3_BG_A.tileset->numTile;
        VDP_loadTileSet(image_HUB.tileset, G_ADR_VRAM_HUB, CPU);
        VDP_setTileMapEx(WINDOW, image_HUB.tilemap, TILE_ATTR_FULL(PAL3, TRUE, FALSE, FALSE, G_ADR_VRAM_HUB), 0, 0, 0, 0, 32, 5, CPU);




        //--------------------------------------------------------------------------------------//
        //                                       HI SCORE                                       //
        //--------------------------------------------------------------------------------------//
        VDP_drawIntEx_WINDOW_CPU_PRIO(G_HI_SCORE,4,15,2,PAL3);

        //--------------------------------------------------------------------------------------//
        //                                        SCORE                                         //
        //--------------------------------------------------------------------------------------//
        VDP_drawIntEx_WINDOW_CPU_PRIO(G_POINTS,1,7,2,PAL3);




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                   PLAYER LIFE BAR                                    //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        G_ADR_VRAM_LIFE_PLAYER = G_ADR_VRAM_HUB + image_HUB.tileset->numTile;
        VDP_loadTileSet(image_LIFE_PLAYER.tileset, G_ADR_VRAM_LIFE_PLAYER, CPU);




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                    BOSS LIFE BAR                                     //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        G_ADR_VRAM_LIFE_BOSS = G_ADR_VRAM_LIFE_PLAYER + image_LIFE_PLAYER.tileset->numTile;
        VDP_loadTileSet(image_LIFE_BOSS.tileset, G_ADR_VRAM_LIFE_BOSS, CPU);




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                SETUP PLANES POSITION                                 //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        G_POS_X_CAMERA = 0;



        for (i=0; i<23; i++)
        {
            scrollTable_BG_B[i] = 0;
            scrollTable_BG_A[i] = 0; 
        }




        //**************************************************************************************//
        //                                                                                      //
        //                                     INIT SPRITES                                     //
        //                                                                                      //
        //**************************************************************************************//

        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                        PAUSE                                         //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        sprite_PAUSE = SPR_addSprite(&tiles_SPR_PAUSE, 0,-8, TILE_ATTR(PAL3, FALSE, FALSE, FALSE));


        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                      VIGILANTE                                       //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        G_GROUND_POSITION   = 112;

        player.pos_X        = -8;
        player.pos_Y        = G_GROUND_POSITION;

        player.counter_ANIM = 4;
        player.axis         = AXIS_RIGHT;

        player.state        = STATE_IDLE;


        sprite_PLAYER = SPR_addSprite(&tiles_SPR_VIGILANTE_MD, player.pos_X,player.pos_Y, TILE_ATTR(PAL3, FALSE, FALSE, FALSE));


        SPR_setAnimAndFrame(sprite_PLAYER,0,4);




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                    STAGE 3 READY                                     //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        sprite_STAGE = SPR_addSprite(&tiles_SPR_STAGE_3, 72, 87, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));



        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                       ENEMIES                                        //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        for(i=0 ; i<4 ; i++)
        {
            LIST_ENEMIES[i].pos_X           = 0;
            LIST_ENEMIES[i].pos_Y           = 0;
            
            LIST_ENEMIES[i].counter_ANIM    = 0;

            LIST_ENEMIES[i].spr_ENEMY       = NULL;
        }




        SPR_update();
        SYS_doVBlankProcess();




        //**************************************************************************************//
        //                                                                                      //
        //                                       PALETTES                                       //
        //                                                                                      //
        //**************************************************************************************//

        PAL_setColors(0,image_LEVEL_3_BG_B.palette->data,32,DMA_QUEUE); // PAL0 & PAL1 ARE IN "image_LEVEL_3_BG_B" //
        
        PAL_setPalette(PAL2,palette_STAGE.data,DMA_QUEUE);
        
        if(G_COLORS_OPTION == MD_COLORS)
        {
            PAL_setPalette(PAL3,palette_VIGILANTE_MD.data,DMA_QUEUE);
        }

        else
        {
            PAL_setPalette(PAL3,palette_VIGILANTE_PCE.data,DMA_QUEUE);
        }




        //**************************************************************************************//
        //                                                                                      //
        //                                       VARIABLES                                      //
        //                                                                                      //
        //**************************************************************************************//

        G_LEVEL_LIMIT           = 1280;

        G_SPAWN_MAX_INDEX       = 72;
    }


    else if(G_LEVEL == 4)
    {
        //**************************************************************************************//
        //                                                                                      //
        //                                      CLEAN VRAM                                      //
        //                                                                                      //
        //**************************************************************************************//

        u16 i = 0;

        for(i=16 ; i<1440 ; i++)
        {
            VDP_loadTileSet(image_EMPTY_TILE.tileset , i , CPU);
        }




        //**************************************************************************************//
        //                                                                                      //
        //                                    SETUP DISPLAY                                     //
        //                                                                                      //
        //**************************************************************************************//

        VDP_setPlaneSize(64,32,TRUE);
        
        SPR_initEx(300);
        
        VDP_setHilightShadow(FALSE);

        VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);




        //**************************************************************************************//
        //                                                                                      //
        //                                   NUMBERS TILESET                                    //
        //                                                                                      //
        //**************************************************************************************//

        VDP_loadTileSet(image_NUMBERS.tileset, TILE_FONT_INDEX + 16, CPU);




        //**************************************************************************************//
        //                                                                                      //
        //                                         BG                                           //
        //                                                                                      //
        //**************************************************************************************//

        G_ADR_VRAM_BG_B = VRAM_START_ADRESS;

        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                         BG_B                                         //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        VDP_loadTileSet(&tileset_LEVEL_4_BG_B, G_ADR_VRAM_BG_B, CPU);


        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                         BG_A                                         //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        G_ADR_VRAM_BG_A = G_ADR_VRAM_BG_B + tileset_LEVEL_4_BG_B.numTile;
        VDP_loadTileSet(&tileset_LEVEL_4_BG_A, G_ADR_VRAM_BG_A, CPU);




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                    CREATE MAP BG_B                                   //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        map_BG_B = MAP_create(&map_LEVEL_4_BG_B, BG_B, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B));
        SYS_doVBlankProcess();


        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                    CREATE MAP BG_A                                   //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        map_BG_A = MAP_create(&map_LEVEL_4_BG_A, BG_A, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_A));
        SYS_doVBlankProcess();




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                      INIT MAPS                                       //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        G_POS_X_CAMERA = 0;


        MAP_scrollTo(map_BG_B, G_POS_X_CAMERA , 0);
        SYS_doVBlankProcess();

        MAP_scrollTo(map_BG_A, G_POS_X_CAMERA , 0);
        SYS_doVBlankProcess();




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                         HUB                                          //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        VDP_setWindowHPos(0, 0);
        VDP_setWindowVPos(0, 5);


        G_ADR_VRAM_HUB = G_ADR_VRAM_BG_A + tileset_LEVEL_4_BG_A.numTile;
        VDP_loadTileSet(image_HUB.tileset, G_ADR_VRAM_HUB, CPU);
        VDP_setTileMapEx(WINDOW, image_HUB.tilemap, TILE_ATTR_FULL(PAL3, TRUE, FALSE, FALSE, G_ADR_VRAM_HUB), 0, 0, 0, 0, 32, 5, CPU);




        //--------------------------------------------------------------------------------------//
        //                                       HI SCORE                                       //
        //--------------------------------------------------------------------------------------//
        VDP_drawIntEx_WINDOW_CPU_PRIO(G_HI_SCORE,4,15,2,PAL3);

        //--------------------------------------------------------------------------------------//
        //                                        SCORE                                         //
        //--------------------------------------------------------------------------------------//
        VDP_drawIntEx_WINDOW_CPU_PRIO(G_POINTS,1,7,2,PAL3);




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                   PLAYER LIFE BAR                                    //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        G_ADR_VRAM_LIFE_PLAYER = G_ADR_VRAM_HUB + image_HUB.tileset->numTile;
        VDP_loadTileSet(image_LIFE_PLAYER.tileset, G_ADR_VRAM_LIFE_PLAYER, CPU);




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                    BOSS LIFE BAR                                     //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        G_ADR_VRAM_LIFE_BOSS = G_ADR_VRAM_LIFE_PLAYER + image_LIFE_PLAYER.tileset->numTile;
        VDP_loadTileSet(image_LIFE_BOSS.tileset, G_ADR_VRAM_LIFE_BOSS, CPU);




        //**************************************************************************************//
        //                                                                                      //
        //                                     INIT SPRITES                                     //
        //                                                                                      //
        //**************************************************************************************//

        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                        PAUSE                                         //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        sprite_PAUSE = SPR_addSprite(&tiles_SPR_PAUSE, 0,-8, TILE_ATTR(PAL3, FALSE, FALSE, FALSE));


        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                      VIGILANTE                                       //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        G_GROUND_POSITION   = 113;

        player.pos_X        = -8;
        player.pos_Y        = G_GROUND_POSITION;

        player.counter_ANIM = 4;
        player.axis         = AXIS_RIGHT;

        player.state        = STATE_IDLE;


        sprite_PLAYER = SPR_addSprite(&tiles_SPR_VIGILANTE_MD, player.pos_X,player.pos_Y, TILE_ATTR(PAL3, FALSE, FALSE, FALSE));


        SPR_setAnimAndFrame(sprite_PLAYER,0,4);




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                    STAGE 4 READY                                     //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        sprite_STAGE = SPR_addSprite(&tiles_SPR_STAGE_4, 72, 87, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));



        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                       ENEMIES                                        //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        for(i=0 ; i<4 ; i++)
        {
            LIST_ENEMIES[i].pos_X           = 0;
            LIST_ENEMIES[i].pos_Y           = 0;
            
            LIST_ENEMIES[i].counter_ANIM    = 0;

            LIST_ENEMIES[i].spr_ENEMY       = NULL;
        }




        SPR_update();
        SYS_doVBlankProcess();




        //**************************************************************************************//
        //                                                                                      //
        //                                       PALETTES                                       //
        //                                                                                      //
        //**************************************************************************************//

        PAL_setPalette(PAL0,image_LEVEL_4_BG_B.palette->data,DMA_QUEUE);
        PAL_setPalette(PAL1,image_LEVEL_4_BG_A.palette->data,DMA_QUEUE);
        PAL_setPalette(PAL2,palette_STAGE.data,DMA_QUEUE);

        if(G_COLORS_OPTION == MD_COLORS)
        {
            PAL_setPalette(PAL3,palette_VIGILANTE_MD.data,DMA_QUEUE);
        }

        else
        {
            PAL_setPalette(PAL3,palette_VIGILANTE_PCE.data,DMA_QUEUE);
        }
        




        //**************************************************************************************//
        //                                                                                      //
        //                                       VARIABLES                                      //
        //                                                                                      //
        //**************************************************************************************//

        G_LEVEL_LIMIT           = 1536;

        G_SPAWN_MAX_INDEX       = 72;
    }


    else if(G_LEVEL == 5)
    {
        //**************************************************************************************//
        //                                                                                      //
        //                                      CLEAN VRAM                                      //
        //                                                                                      //
        //**************************************************************************************//

        u16 i = 0;

        for(i=16 ; i<1440 ; i++)
        {
            VDP_loadTileSet(image_EMPTY_TILE.tileset , i , CPU);
        }




        //**************************************************************************************//
        //                                                                                      //
        //                                    SETUP DISPLAY                                     //
        //                                                                                      //
        //**************************************************************************************//

        VDP_setPlaneSize(64,32,TRUE);
        
        SPR_initEx(300);
        
        VDP_setHilightShadow(FALSE);

        VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);




        //**************************************************************************************//
        //                                                                                      //
        //                                   NUMBERS TILESET                                    //
        //                                                                                      //
        //**************************************************************************************//

        VDP_loadTileSet(image_NUMBERS.tileset, TILE_FONT_INDEX + 16, CPU);




        //**************************************************************************************//
        //                                                                                      //
        //                                         BG                                           //
        //                                                                                      //
        //**************************************************************************************//

        G_ADR_VRAM_BG_B = VRAM_START_ADRESS;

        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                         BG_B                                         //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        VDP_loadTileSet(&tileset_LEVEL_5_BG_B, G_ADR_VRAM_BG_B, CPU);


        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                         BG_A                                         //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        G_ADR_VRAM_BG_A = G_ADR_VRAM_BG_B + tileset_LEVEL_5_BG_B.numTile;
        VDP_loadTileSet(&tileset_LEVEL_5_BG_A, G_ADR_VRAM_BG_A, CPU);




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                    CREATE MAP BG_B                                   //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        map_BG_B = MAP_create(&map_LEVEL_5_BG_B, BG_B, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B));
        SYS_doVBlankProcess();


        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                    CREATE MAP BG_A                                   //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        map_BG_A = MAP_create(&map_LEVEL_5_BG_A, BG_A, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_A));
        SYS_doVBlankProcess();




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                      INIT MAPS                                       //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        G_POS_X_CAMERA = 0;


        MAP_scrollTo(map_BG_B, G_POS_X_CAMERA , 0);
        SYS_doVBlankProcess();

        MAP_scrollTo(map_BG_A, G_POS_X_CAMERA , 0);
        SYS_doVBlankProcess();




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                         HUB                                          //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        VDP_setWindowHPos(0, 0);
        VDP_setWindowVPos(0, 5);


        G_ADR_VRAM_HUB = G_ADR_VRAM_BG_A + tileset_LEVEL_5_BG_A.numTile;
        VDP_loadTileSet(image_HUB.tileset, G_ADR_VRAM_HUB, CPU);
        VDP_setTileMapEx(WINDOW, image_HUB.tilemap, TILE_ATTR_FULL(PAL3, TRUE, FALSE, FALSE, G_ADR_VRAM_HUB), 0, 0, 0, 0, 32, 5, CPU);




        //--------------------------------------------------------------------------------------//
        //                                       HI SCORE                                       //
        //--------------------------------------------------------------------------------------//
        VDP_drawIntEx_WINDOW_CPU_PRIO(G_HI_SCORE,4,15,2,PAL3);

        //--------------------------------------------------------------------------------------//
        //                                        SCORE                                         //
        //--------------------------------------------------------------------------------------//
        VDP_drawIntEx_WINDOW_CPU_PRIO(G_POINTS,1,7,2,PAL3);




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                   PLAYER LIFE BAR                                    //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        G_ADR_VRAM_LIFE_PLAYER = G_ADR_VRAM_HUB + image_HUB.tileset->numTile;
        VDP_loadTileSet(image_LIFE_PLAYER.tileset, G_ADR_VRAM_LIFE_PLAYER, CPU);




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                    BOSS LIFE BAR                                     //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        G_ADR_VRAM_LIFE_BOSS = G_ADR_VRAM_LIFE_PLAYER + image_LIFE_PLAYER.tileset->numTile;
        VDP_loadTileSet(image_LIFE_BOSS.tileset, G_ADR_VRAM_LIFE_BOSS, CPU);




        //**************************************************************************************//
        //                                                                                      //
        //                                     INIT SPRITES                                     //
        //                                                                                      //
        //**************************************************************************************//

        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                        PAUSE                                         //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        sprite_PAUSE = SPR_addSprite(&tiles_SPR_PAUSE, 0,-8, TILE_ATTR(PAL3, FALSE, FALSE, FALSE));


        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                      VIGILANTE                                       //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        G_GROUND_POSITION   = 105;
        
        player.pos_X        = -8;
        player.pos_Y        = G_GROUND_POSITION;

        player.counter_ANIM = 4;
        player.axis         = AXIS_RIGHT;

        player.state        = STATE_IDLE;


        sprite_PLAYER = SPR_addSprite(&tiles_SPR_VIGILANTE_MD, player.pos_X,player.pos_Y, TILE_ATTR(PAL3, FALSE, FALSE, FALSE));


        SPR_setAnimAndFrame(sprite_PLAYER,0,4);




        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                    STAGE 5 READY                                     //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        sprite_STAGE = SPR_addSprite(&tiles_SPR_STAGE_5, 72, 87, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));



        //--------------------------------------------------------------------------------------//
        //                                                                                      //
        //                                       ENEMIES                                        //
        //                                                                                      //
        //--------------------------------------------------------------------------------------//

        for(i=0 ; i<4 ; i++)
        {
            LIST_ENEMIES[i].pos_X           = 0;
            LIST_ENEMIES[i].pos_Y           = 0;
            
            LIST_ENEMIES[i].counter_ANIM    = 0;

            LIST_ENEMIES[i].spr_ENEMY       = NULL;
        }




        SPR_update();
        SYS_doVBlankProcess();




        //**************************************************************************************//
        //                                                                                      //
        //                                       PALETTES                                       //
        //                                                                                      //
        //**************************************************************************************//

        PAL_setPalette(PAL0,image_LEVEL_5_BG_B.palette->data,DMA_QUEUE);
        PAL_setPalette(PAL1,image_LEVEL_5_BG_A.palette->data,DMA_QUEUE);
        PAL_setPalette(PAL2,palette_STAGE.data,DMA_QUEUE);

        if(G_COLORS_OPTION == MD_COLORS)
        {
            PAL_setPalette(PAL3,palette_VIGILANTE_MD.data,DMA_QUEUE);
        }

        else
        {
            PAL_setPalette(PAL3,palette_VIGILANTE_PCE.data,DMA_QUEUE);
        }
        




        //**************************************************************************************//
        //                                                                                      //
        //                                       VARIABLES                                      //
        //                                                                                      //
        //**************************************************************************************//

        G_LEVEL_LIMIT           = 1568;

        G_SPAWN_MAX_INDEX       = 72;
    }


        
    G_REPEAT                = 0;

    G_INDEX_ANIM_PUNCH      = 1;

    G_NUMBER_ENEMY          = 0;

    G_INDEX_LIFE_PLAYER     = 13;

    G_STEP_LIFE_PLAYER      = 0;

    G_SPAWN_AUTHORIZED      = TRUE;

    G_PHASE_LEVEL           = LEVEL_ENTER;// LEVEL_PLAY

    G_SEQUENCE_LOADED       = TRUE;
}

