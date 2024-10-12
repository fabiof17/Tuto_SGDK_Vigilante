#include <genesis.h>



#include "structures.h"
#include "variables.h"




#include "sprites_LEVEL.h"




const struct_ENEMY_TYPE     TABLE_ENEMY_TYPE[6]         =   {
                                                                // DUDE //
                                                                { 1 , 6 , PAL2 , 10 , &tiles_SPR_DUDE },

                                                                // PUNK //
                                                                { 4 , 6 , PAL2 , 20 , &tiles_SPR_PUNK_1 },

                                                                // KNIFE_MAN //
                                                                { NULL , NULL , NULL , NULL , NULL },

                                                                // CHAIN_MAN //
                                                                { NULL , NULL , NULL , NULL , NULL },

                                                                // GUN_MAN //
                                                                { 4 , 6 , PAL3 , NULL , &tiles_SPR_GUN_MAN }
                                                            };




const struct_SPAWN_DATA_    TABLE_SPAWN_LEVEL_1[72]     =   {
                                                                { DUDE , 120 , FALSE }, // 175
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE , 160 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  15 , FALSE },
                                                                { DUDE ,  10 , FALSE },
                                                                { PUNK , 140 , TRUE  },// PUNK

                                                                { DUDE , 120 , FALSE }, // 175
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE , 160 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  15 , FALSE },
                                                                { DUDE ,  10 , FALSE },
                                                                { PUNK , 140 , TRUE  },// PUNK

                                                                { DUDE , 120 , FALSE }, // 175
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE , 160 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  15 , FALSE },
                                                                { DUDE ,  10 , FALSE },
                                                                { PUNK , 140 , TRUE  }, // PUNK

                                                                { DUDE , 120 , FALSE }, // 175
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE , 160 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  15 , FALSE },
                                                                { DUDE ,  10 , FALSE },
                                                                { DUDE , 140 , TRUE  },

                                                                { DUDE , 120 , FALSE }, // 175
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE , 160 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  15 , FALSE },
                                                                { DUDE ,  10 , FALSE },
                                                                { DUDE , 140 , TRUE  },

                                                                { DUDE , 120 , FALSE }, // 175
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE , 160 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  15 , FALSE },
                                                                { DUDE ,  10 , FALSE },
                                                                { DUDE , 140 , TRUE  },

                                                                { DUDE , 120 , FALSE }, // 175
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE , 160 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  15 , FALSE },
                                                                { DUDE ,  10 , FALSE },
                                                                { DUDE , 140 , TRUE  },

                                                                { DUDE , 120 , FALSE }, // 175
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE , 160 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  15 , FALSE },
                                                                { DUDE ,  10 , FALSE },
                                                                { DUDE , 140 , TRUE  },
                                                            };














