#include <genesis.h>



#include "custom_tools.h"
#include "palettes.h"
#include "structures.h"
#include "variables.h"




#include "maps_INTERMEDE.h"







void sequence_INTERMEDE_1()
{
    if(G_COUNTER_INTERMEDE == 3)
    {
        SPR_setPosition(sprite_MADONNA,87,78);
    }

    else if(G_COUNTER_INTERMEDE == 11)
    {
        SPR_setPosition(sprite_MADONNA,95,86);
    }

    else if(G_COUNTER_INTERMEDE == 20)
    {
        SPR_setFrame(sprite_MADONNA,1);
        
        SPR_setPosition(sprite_MADONNA,95,118);
    }

    // CLOSE DOORS //
    else if(G_COUNTER_INTERMEDE == 27)
    {
        VDP_setTileMapEx(BG_A, image_INTERMEDE_BG_A.tilemap, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_A), 8, 8, 32, 0, 6, 10, DMA_QUEUE);
    }

    else if(G_COUNTER_INTERMEDE == 29)
    {
        SPR_setFrame(sprite_MADONNA,2);
        
        SPR_setPosition(sprite_MADONNA,101,129);
    }

    // SCROLLING //
    if(G_COUNTER_INTERMEDE > 29)
    {
        G_POS_X_CAMERA -= 1;

        VDP_setHorizontalScrollVSync(BG_B,G_POS_X_CAMERA);
    }

    if(G_COUNTER_INTERMEDE == 804)
    {
        PAL_setPalette(PAL0,palette_BLACK.data,DMA_QUEUE);
        PAL_setPalette(PAL1,palette_BLACK.data,DMA_QUEUE);
        PAL_setPalette(PAL2,palette_BLACK.data,DMA_QUEUE);
        PAL_setPalette(PAL3,palette_BLACK.data,DMA_QUEUE);


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

        SYS_doVBlankProcess();
    }


    G_COUNTER_INTERMEDE += 1;
}


void sequence_INTERMEDE_2()
{
    G_POS_X_CAMERA -= 1;

    VDP_setHorizontalScrollVSync(BG_B,G_POS_X_CAMERA);
    

    if(G_COUNTER_INTERMEDE == 665)
    {
        PAL_setPalette(PAL0,palette_BLACK.data,DMA_QUEUE);
        PAL_setPalette(PAL1,palette_BLACK.data,DMA_QUEUE);
        PAL_setPalette(PAL2,palette_BLACK.data,DMA_QUEUE);
        PAL_setPalette(PAL3,palette_BLACK.data,DMA_QUEUE);

        G_SEQUENCE = SEQUENCE_GAME;

        G_SEQUENCE_LOADED = FALSE;

        SYS_doVBlankProcess();
    }


    G_COUNTER_INTERMEDE += 1;
}


void sequence_INTERMEDE_3()
{
    G_POS_X_CAMERA -= 1;

    VDP_setHorizontalScrollVSync(BG_B,G_POS_X_CAMERA);
    

    if(G_COUNTER_INTERMEDE == 665)
    {
        PAL_setPalette(PAL0,palette_BLACK.data,DMA_QUEUE);
        PAL_setPalette(PAL1,palette_BLACK.data,DMA_QUEUE);
        PAL_setPalette(PAL2,palette_BLACK.data,DMA_QUEUE);
        PAL_setPalette(PAL3,palette_BLACK.data,DMA_QUEUE);

        G_SEQUENCE = SEQUENCE_GAME;

        G_SEQUENCE_LOADED = FALSE;

        SYS_doVBlankProcess();
    }


    G_COUNTER_INTERMEDE += 1;
}