#include <genesis.h>



#include "custom_tools.h"
#include "structures.h"
#include "variables.h"




#include "maps_TITLE.h"







void sequence_TITLE()
{
    // TITLE SCROLLING //
    if(G_POS_X_CAMERA < 256)
    {
        G_POS_X_CAMERA += 1;

        VDP_setHorizontalScrollVSync(BG_B,G_POS_X_CAMERA);
        VDP_setHorizontalScrollVSync(BG_A,G_POS_X_CAMERA);

        
        if(G_POS_X_CAMERA == 256)
        {
            // DISPLAY PRESS START BUTTON //
            VDP_setTileMapEx(BG_A, image_TITLE_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 39, 19, 39, 28, 18, 1, DMA_QUEUE);

            // DISPLAY LEVEL //
            VDP_setTileMapEx(BG_A, image_TITLE_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 44, 21, 59, 28, 5, 1, DMA_QUEUE);

            // DISPLAY LEVEL NUMBER //
            VDP_drawIntEx_BG_A_QUEUE(G_LEVEL,1,51,21,PAL0);

            // DISPLAY COLORS //
            VDP_setTileMapEx(BG_A, image_TITLE_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 43, 23, 25, 28, 6, 1, DMA_QUEUE);

            // DISPLAY MD //
            VDP_setTileMapEx(BG_A, image_TITLE_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 51, 23, 32, 28, 2, 1, DMA_QUEUE);

            SPR_setPosition(sprite_ARROW , 72 , 168);
        }
    }

    // PRESS START BUTTON BLINKING //
    else
    {        
        if(G_COUNTER_TITLE == 0)
        {
            VDP_setTileMapEx(BG_A, image_TITLE_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 39, 19, 39, 28, 18, 1, DMA_QUEUE);
        }

        else if(G_COUNTER_TITLE == 15)
        {
            VDP_setTileMapEx(BG_A, image_TITLE_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 39, 19, 39, 21, 18, 1, DMA_QUEUE);
        }

        else if(G_COUNTER_TITLE == 30)
        {
            VDP_setTileMapEx(BG_A, image_TITLE_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 39, 19, 39, 28, 18, 1, DMA_QUEUE);
        }

        else if(G_COUNTER_TITLE == 45)
        {
            VDP_setTileMapEx(BG_A, image_TITLE_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 39, 19, 39, 21, 18, 1, DMA_QUEUE);
        }

        else if(G_COUNTER_TITLE == 60)
        {
            VDP_setTileMapEx(BG_A, image_TITLE_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 39, 19, 39, 28, 18, 1, DMA_QUEUE);
        }

        else if(G_COUNTER_TITLE == 75)
        {
            VDP_setTileMapEx(BG_A, image_TITLE_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 39, 19, 39, 21, 18, 1, DMA_QUEUE);
        }

        G_COUNTER_TITLE += 1;

        if(G_COUNTER_TITLE == 89)
        {
            G_COUNTER_TITLE = 0;
        }
    }
}