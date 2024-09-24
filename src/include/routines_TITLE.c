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

        // DISPLAY PRESS START BUTTON //
        if(G_POS_X_CAMERA == 256)
        {
            VDP_setTileMapEx(BG_B, image_TITLE_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 39, 21, 39, 28, 18, 1, DMA_QUEUE);
        }
    }

    // PRESS START BUTTON BLINKING //
    else
    {        
        if(G_COUNTER_TITLE == 0)
        {
            VDP_setTileMapEx(BG_B, image_TITLE_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 39, 21, 39, 28, 18, 1, DMA_QUEUE);
        }

        else if(G_COUNTER_TITLE == 15)
        {
            VDP_setTileMapEx(BG_B, image_TITLE_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 39, 21, 39, 21, 18, 1, DMA_QUEUE);
        }

        else if(G_COUNTER_TITLE == 30)
        {
            VDP_setTileMapEx(BG_B, image_TITLE_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 39, 21, 39, 28, 18, 1, DMA_QUEUE);
        }

        else if(G_COUNTER_TITLE == 45)
        {
            VDP_setTileMapEx(BG_B, image_TITLE_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 39, 21, 39, 21, 18, 1, DMA_QUEUE);
        }

        else if(G_COUNTER_TITLE == 60)
        {
            VDP_setTileMapEx(BG_B, image_TITLE_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 39, 21, 39, 28, 18, 1, DMA_QUEUE);
        }

        else if(G_COUNTER_TITLE == 75)
        {
            VDP_setTileMapEx(BG_B, image_TITLE_BG_B.tilemap, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, G_ADR_VRAM_BG_B), 39, 21, 39, 21, 18, 1, DMA_QUEUE);
        }

        G_COUNTER_TITLE += 1;

        if(G_COUNTER_TITLE == 89)
        {
            G_COUNTER_TITLE = 0;
        }
    }
}