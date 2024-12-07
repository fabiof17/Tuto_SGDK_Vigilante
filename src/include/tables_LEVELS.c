#include <genesis.h>



#include "structures.h"
#include "variables.h"




#include "sprites_LEVEL.h"




const struct_ENEMY_TYPE     TABLE_ENEMY_TYPE[6]         =   {
                                                                // DUDE //
                                                                { 1 , 6 , PAL2 , 10 , &tiles_SPR_DUDE , FIX32(0.5) , TRUE },

                                                                // PUNK //
                                                                { 4 , 6 , PAL3 , 20 , &tiles_SPR_PUNK , FIX32(10L) , TRUE },

                                                                // KNIFE_MAN //
                                                                { NULL , NULL , PAL3 , NULL , NULL , FIX32(10L) , TRUE },

                                                                // CHAIN_MAN //
                                                                { 4 , 6 , PAL2 , 20 , &tiles_SPR_CHAIN_MAN , FIX32(10L) , TRUE },

                                                                // GUN_MAN //
                                                                { 4 , 6 , PAL3 , NULL , &tiles_SPR_GUN_MAN , NULL , FALSE },

                                                                // STICK_MAN //
                                                                { 4 , 6 , PAL3 , 20 , &tiles_SPR_STICK_MAN , FIX32(10L) , TRUE }
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
                                                                { STICK_MAN , 140 , TRUE  },// PUNK

                                                                { DUDE , 120 , FALSE }, // 175
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE , 160 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  15 , FALSE },
                                                                { DUDE ,  10 , FALSE },
                                                                { CHAIN_MAN , 140 , TRUE  }, // PUNK

                                                                { DUDE , 120 , FALSE }, // 175
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE , 160 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  15 , FALSE },
                                                                { DUDE ,  10 , FALSE },
                                                                { PUNK , 140 , TRUE  },

                                                                { DUDE , 120 , FALSE }, // 175
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE , 160 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  15 , FALSE },
                                                                { DUDE ,  10 , FALSE },
                                                                { PUNK , 140 , TRUE  },

                                                                { DUDE , 120 , FALSE }, // 175
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE , 160 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  15 , FALSE },
                                                                { DUDE ,  10 , FALSE },
                                                                { CHAIN_MAN , 140 , TRUE  },

                                                                { DUDE , 120 , FALSE }, // 175
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE , 160 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  15 , FALSE },
                                                                { DUDE ,  10 , FALSE },
                                                                { PUNK , 140 , TRUE  },

                                                                { DUDE , 120 , FALSE }, // 175
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE , 160 , FALSE },
                                                                { DUDE ,  30 , FALSE },
                                                                { DUDE ,  15 , FALSE },
                                                                { DUDE ,  10 , FALSE },
                                                                { PUNK , 140 , TRUE  },
                                                            };




const struct_JUMP_          TABLE_JUMP_V[27]            =   {
                                                                {  4 , -3 },
                                                                {  5 , -4 },
                                                                {  6 , -3 },
                                                                {  7 , -3 },
                                                                {  8 , -2 },
                                                                {  9 , -3 },
                                                                { 10 ,  3 },
                                                                { 11 , -2 },
                                                                { 12 , -2 },
                                                                { 13 , -1 },
                                                                { 15 , -1 },
                                                                { 16 , -1 },
                                                                { 18 , -1 },
                                                                { 19 ,  1 },
                                                                { 21 ,  1 },
                                                                { 22 ,  1 },
                                                                { 24 ,  1 },
                                                                { 25 ,  2 },
                                                                { 26 ,  2 },
                                                                { 27 ,  2 },
                                                                { 28 , -2 },
                                                                { 29 ,  2 },
                                                                { 30 ,  3 },
                                                                { 31 ,  3 },
                                                                { 32 ,  4 },
                                                                { 33 ,  3 },
                                                                { 34 ,  4 }
                                                            };




const struct_JUMP_          TABLE_JUMP_H[31]            =   {
                                                                {  0 , -1 },
                                                                {  1 , -2 },
                                                                {  2 , -1 },
                                                                {  3 , -1 },
                                                                {  4 , -1 },
                                                                {  5 , -1 },
                                                                {  6 , -2 },
                                                                {  7 , -1 },
                                                                {  8 , -1 },
                                                                {  9 , -1 },
                                                                { 10 , -1 },
                                                                { 12 , -2 },
                                                                { 13 , -1 },
                                                                { 14 , -1 },
                                                                { 15 , -1 },
                                                                { 16 , -1 },
                                                                { 17 , -2 },
                                                                { 18 , -1 },
                                                                { 19 , -1 },
                                                                { 20 , -1 },
                                                                { 21 , -1 },
                                                                { 22 , -2 },
                                                                { 23 , -1 },
                                                                { 24 , -1 },
                                                                { 25 , -1 },
                                                                { 26 , -1 },
                                                                { 27 , -2 },
                                                                { 28 , -1 },
                                                                { 29 , -1 },
                                                                { 30 , -1 },
                                                                { 31 , -1 }
                                                            };




const struct_JUMP_          TABLE_JUMP_H_BW[27]         =   {
                                                                {  0 , -1 },
                                                                {  1 , -1 },
                                                                {  2 , -1 },
                                                                {  3 , -1 },
                                                                {  4 , -2 },
                                                                {  5 , -1 },
                                                                {  6 , -1 },
                                                                {  7 , -1 },
                                                                {  8 , -1 },
                                                                {  9 , -2 },
                                                                { 10 , -1 },
                                                                { 11 , -1 },
                                                                { 12 , -1 },
                                                                { 13 , -1 },
                                                                { 15 , -2 },
                                                                { 16 , -1 },
                                                                { 17 , -1 },
                                                                { 18 , -1 },
                                                                { 19 , -1 },
                                                                { 20 , -2 },
                                                                { 21 , -1 },
                                                                { 22 , -1 },
                                                                { 23 , -1 },
                                                                { 24 , -1 },
                                                                { 25 , -2 },
                                                                { 26 , -1 },
                                                                { 27 , -1 }
                                                            };



const u16           TABLE_SPAWN_WEAPON_LEVEL_1[2][2]    =   {
                                                                { 216, 168 },
                                                                { NULL , NULL }
                                                            };






































































