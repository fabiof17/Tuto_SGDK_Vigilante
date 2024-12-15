#include <genesis.h>


#include "variables.h"


#include "palettes.h"







void sequence_RANKING()
{
    if(G_TIMER == 300)
    {
        G_TIMER = 0;

        PAL_setPalette(PAL0,palette_BLACK.data,DMA_QUEUE);
        PAL_setPalette(PAL1,palette_BLACK.data,DMA_QUEUE);

        SYS_doVBlankProcess();

        // CLEAR PLANES //
        VDP_clearPlane(BG_B,TRUE);
        VDP_clearPlane(BG_A,TRUE);

        // RELEASE ALL SPRITES //
        SPR_reset();

        G_SEQUENCE = SEQUENCE_TITLE;

        G_SEQUENCE_LOADED = FALSE;

        SYS_doVBlankProcess();

        return;
    }

    G_TIMER += 1;
}