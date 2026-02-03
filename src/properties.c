#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "story.h"
#include "mechanics.h"
#include <unistd.h> 

//Abilities {Id,Name,Healing,Damage,Mana Cost,Effects,Effect Type}
Abilities ALL_abilities[TOTAL_ABILITIES] = {
    {0,"NO Abilitie",0,0,0,"",NONE},
    {1,"Speed Boost",0,0,30,"2 SPEED",BOOST},
    {2,"Shield Bash",0,20,10,"",NONE},
    {3,"Lethal Punch Barrage",0,30,25,"0.75 DAMAGE",BOOST},
    {4,"Disguise",0,0,30,"3 STEALTH",BOOST},
    {5,"Fire Bolt",0,15,15,"",NONE},
    {6,"Basic Healing",20,0,20,"",NONE},
    {7,"Group Healing",15,0,30,"15 0",GROUP},
    {8,"Shadow Dog Summon",0,0,40,"1 Shadow Dog",SUMMON},
    {9,"Strength Boost",0,0,30,"2 DAMAGE",BOOST},
    {10,"Invisibility",0,0,5,"10 STEALTH",BOOST},
};

//NPC {ID,Name,Ability_id,Effect Type,Rank,Level,Exp_Givven,HP,Max_HP,Damage,Speed}
NPC ALL_summons[TOTAL_SUMMONS] = {
    {0,"Shadow Dog",0,NONE,D,1,0,3,3,4,5},
    {1,"Fire Sprite",0,NONE,D,1,0,1,1,7,3},
};

//NPC {ID,Name,Ability_id,Effect Type,Rank,Level,Exp_Givven,HP,Max_HP,Damage,Speed}
NPC ALL_npc[TOTAL_NPC] = {//TODO Change these Random NPC
    {0,"Mom",0,NONE,E,1,0,10,10,1,1},
    {1,"Dad",0,NONE,E,1,0,10,10,1,1},
    {2,"Security Guard",0,NONE,D,1,10,20,20,5,3},
    {3,"Old Lady",0,NONE,C,1,15,15,15,3,2},
    {4,"Mysterious Stranger",0,NONE,B,1,20,30,30,7,5},
    {5,"Gang Member",0,NONE,C,1,15,25,25,6,4},
    {6,"Police Officer",0,NONE,A,1,30,40,40,8,6},
    {7,"Company Executive",0,NONE,B,1,20,30,30,5,4},
    {8,"Mine Foreman",0,NONE,C,1,15,25,25,6,4},
    {9,"Underground Creature",0,NONE,S,1,50,60,60,10,8},
};

//Items {ID,Name,Effect,Effect Type,Item Type,Healling,Equipable}
Items ALL_items[TOTAL_ITEMS] = {
    {0,"Chicken Sandwich","",NONE,CONSUMABLE,10,NO},
    {1,"Flashlight","0.3 Stealth",BOOST,KEY,0,OFF_HAND},
    {2,"Basic Dagger","3 WEAPON_DAMAGE",PLUS,WEAPON,0,MAIN_HAND},
    {3,"Secondary Dagger","2 WEAPON_DAMAGE",PLUS,WEAPON,0,OFF_HAND},
    {4,"Basic Sword","4 WEAPON_DAMAGE",PLUS,WEAPON,0,MAIN_HAND},
    {5,"Basic Shield","3 DEFENCE",PLUS,WEAPON,0,OFF_HAND},
    {6,"Leather Helmet","1 DEFENCE",PLUS,WEAPON,0,HEAD},
    {7,"Leather Chestplate","3 DEFENCE",PLUS,WEAPON,0,CHEST},
    {8,"Leather Pants","2 DEFENCE",PLUS,WEAPON,0,LEGS},
    {9,"Leather Boots","1 DEFENCE",PLUS,WEAPON,0,SHOES},
    {10,"Headband","3 DEFENCE",PLUS,WEAPON,0,HEAD},
    {11,"Basic Grimoire","3 MAGIC_POWER",PLUS,WEAPON,0,MAIN_HAND},
    {12,"Healer's Glove","2 MAX_MANA",PLUS,WEAPON,0,MAIN_HAND},
    {13,"Mage's Robe","3 MAGIC_POWER",PLUS,WEAPON,0,CHEST},
    {14,"Basic Katana","5 WEAPON_DAMAGE",PLUS,WEAPON,0,MAIN_HAND},
    {15,"Shuriken","3 WEAPON_DAMAGE",PLUS,WEAPON,0,OFF_HAND},
    {16,"Ninja chestplate","4 DEFENCE",PLUS,WEAPON,0,CHEST},
    {17,"Ninja pants","3 DEFENCE",PLUS,WEAPON,0,LEGS},
    {18,"Soundless sandals","2 DEFENCE",PLUS,WEAPON,0,SHOES},
};


