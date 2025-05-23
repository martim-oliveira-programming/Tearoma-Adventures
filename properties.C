#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"
#include <unistd.h> 

Abilities ALL_abilities[TOTAL_ABILITIES]{
    {1,"Speed Boost",0,0,30,"2 SPEED",BOOST},
    {2,"Shield Bash",0,20,10,"",NONE},
    {3,"Lethal Punch Barrage",0,30,25,"0.75 DAMAGE",BOOST},
    {4,"Disguise",0,0,30,"3 STEALTH",BOOST},
    {5,"Fire Bolt",0,15,15,"",NONE},
    {6,"Basic Healing",20,0,20,""},
    {7,"Group Healing",15,0,30,"15 NONE 0",Group},
    {8,"Shadow Dog Summon",0,0,40,"1 Shadow Dog",SUMMON},
    {9,"Strength Boost",0,0,30,"2 DAMAGE",BOOST}
};
