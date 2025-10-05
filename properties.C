#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"
#include <unistd.h> 


Abilities ALL_abilities[TOTAL_ABILITIES] = {
    {0,"NO Abilitie",0,0,0,"",NONE},
    {1,"Speed Boost",0,0,30,"2 SPEED",BOOST},
    {2,"Shield Bash",0,20,10,"",NONE},
    {3,"Lethal Punch Barrage",0,30,25,"0.75 DAMAGE",BOOST},
    {4,"Disguise",0,0,30,"3 STEALTH",BOOST},
    {5,"Fire Bolt",0,15,15,"",NONE},
    {6,"Basic Healing",20,0,20,"",NONE},
    {7,"Group Healing",15,0,30,"15 NONE 0",GROUP},
    {8,"Shadow Dog Summon",0,0,40,"1 Shadow Dog",SUMMON},
    {9,"Strength Boost",0,0,30,"2 DAMAGE",BOOST},
    {10,"Invisibility",0,0,5,"10 STEALTH",BOOST},
};

NPC ALL_summons[TOTAL_SUMMONS] = {
    {0,"Shadow Dog",0,NONE,E,1,0,2,2,4,4},
};

Items ALL_items[TOTAL_ITEMS] = {
    {0,"Chicken Sandwich","",NONE,CONSUMABLE,10,NO},
    {1,"Flashlight","0.3 Stealth",BOOST,KEY,0,OFF_HAND},
    {2,"Basic Dagger","3 WEAPON_DAMAGE",PLUS,WEAPON,MAIN_HAND},
    {3,"Secondary Dagger","2 WEAPON_DAMAGE",PLUS,WEAPON,OFF_HAND},
    {4,"Basic Sword","4 WEAPON_DAMAGE",PLUS,WEAPON,MAIN_HAND},
    {5,"Basic Shield","3 DEFENCE",PLUS,WEAPON,OFF_HAND},
    {6,"Leather Helmet","1 DEFENCE",PLUS,WEAPON,HEAD},
    {7,"Leather Chestplate","3 DEFENCE",PLUS,WEAPON,CHEST},
    {8,"Leather Pants","2 DEFENCE",PLUS,WEAPON,LEGS},
    {9,"Leather Boots","1 DEFENCE",PLUS,WEAPON,SHOES},
    {10,"Headband","3 DEFENCE",PLUS,WEAPON,HEAD},
    {11,"Basic Grimoire","3 MAGIC_POWER",PLUS,WEAPON,MAIN_HAND},
    {12,"Healer's Glove","2 MAX_MANA",PLUS,WEAPON,MAIN_HAND},
    {13,"Mage's Robe","3 MAGIC_POWER",PLUS,WEAPON,CHEST},
    {14,"Basic Katana","5 WEAPON_DAMAGE",PLUS,WEAPON,MAIN_HAND},
    {15,"Shuriken","3 WEAPON_DAMAGE",PLUS,WEAPON,OFF_HAND},
    {16,"Ninja chestplate","4 DEFENCE",PLUS,WEAPON,CHEST},
    {17,"Ninja pants","3 DEFENCE",PLUS,WEAPON,LEGS},
    {18,"Soundless sandals","2 DEFENCE",PLUS,WEAPON,SHOES},
};


