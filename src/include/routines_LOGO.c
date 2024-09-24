#include <genesis.h>



#include "custom_tools.h"
#include "palettes.h"
#include "structures.h"
#include "variables.h"




#include "maps_TITLE.h"







void sequence_LOGO()
{
    G_COUNTER_LOGO += 1;
    
    if(G_COUNTER_LOGO  == 180)
    {
        G_COUNTER_LOGO = 0;

        PAL_setPalette(PAL0,palette_BLACK.data,DMA_QUEUE);

        G_SEQUENCE = SEQUENCE_TITLE;

        G_SEQUENCE_LOADED = FALSE;

        SYS_doVBlankProcess();
    }
}