#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "story.h"
#include "mechanics.h"
#include <unistd.h> 

//Abilities {Id,Name,Healing,Damage,Mana Cost,Effects,Effect Type,Rank,Ability_Active,Ability_Type}
Abilities ALL_abilities[TOTAL_ABILITIES] = {
    {0,"NO Abilitie",0,0,0,"",NONE,E,BASE,Passive,Learned},
    {1,"Speed Boost",0,0,30,"2 SPEED",BOOST,D,BASE,Active,Learned},
    {2,"Shield Bash",0,20,10,"",NONE,D,BASE,Active,Learned},
    {3,"Lethal Punch Barrage",0,30,25,"0.75 DAMAGE",BOOST,C,BASE,Active,Learned},
    {4,"Disguise",0,0,30,"3 STEALTH",BOOST,D,BASE,Active,Learned},
    {5,"Fire Bolt",0,15,15,"",NONE,D,FIRE,Active,Learned},
    {6,"Basic Healing",20,0,20,"",NONE,D,BASE,Active,Learned},
    {7,"Group Healing",15,0,30,"15 0",GROUP,B,BASE,Active,Learned},
    {8,"Shadow Dog Summon",0,0,40,"0",SUMMON,C,DARK,Active,Hereditary},
    {9,"Strength Boost",0,0,30,"2 DAMAGE",BOOST,D,BASE,Active,Learned},
    {10,"Invisibility",0,0,5,"10 STEALTH",BOOST,C,BASE,Active,Learned},
    {11,"Fire Spirit Summon",0,0,50,"1",SUMMON,E,BASE,Active,Learned},
};

//NPC {ID,age,name,Ability_ids*,summonIDs*,abilities_ammount,summons_ammount,RANK,LEVEL,EXP_GIVEN,HP,MAX_HP,MANA,MAX_MANA,DAMAGE,DEFENCE,SPEED}
NPC ALL_summons[TOTAL_SUMMONS] = {
    {0,100,"Shadow Dog", NULL, NULL, 0, 0, D, 1, 1000, 30, 30, 30, 30, 4, 2, 5},
    {1,4,  "Fire Spirit", NULL, NULL, 0, 0, E, 1, 100, 10, 10, 10, 10, 7, 1, 3},
};

//TODO Balance the Rival
//NPC {ID,age,name,Ability_ids*,summonIDs*,abilities_ammount,summons_ammount,RANK,LEVEL,EXP_GIVEN,HP,MAX_HP,MANA,MAX_MANA,DAMAGE,DEFENCE,SPEED}
NPC ALL_npc[TOTAL_NPC] = {//TODO Change these Random NPC
    {0,15,"Sofia",  (int[]){6,11}, (int[]){0,1}, 2, 2, E, 1, 20, 20, 20, 100, 100, 3, 2, 6},
    {1,15,"Nathan", (int[]){6,11}, (int[]){0,1}, 2, 2, E, 1, 20, 20, 20, 100, 100, 3, 2, 6},
    {2,0, "",       NULL, NULL, 0, 0, D, 1,10, 20, 20, 0, 0, 5, 1, 3},
    {3,0, "",       NULL, NULL, 0, 0, C, 1,15, 15, 15, 0, 0, 3, 1, 2},
    {4,0, "",       NULL, NULL, 0, 0, B, 1,20, 30, 30, 0, 0, 7, 2, 5},
    {5,0, "",       NULL, NULL, 0, 0, C, 1,15, 25, 25, 0, 0, 6, 2, 4},
    {6,0, "",       NULL, NULL, 0, 0, A, 1,30, 40, 40, 0, 0, 8, 3, 6},
    {7,0, "",       NULL, NULL, 0, 0, B, 1,20, 30, 30, 0, 0, 5, 2, 4},
    {8,0, "",       NULL, NULL, 0, 0, C, 1,15, 25, 25, 0, 0, 6, 2, 4},
    {9,0, "",       NULL, NULL, 0, 0, S, 1,50, 60, 60, 0, 0,10, 4, 8},
};

//Items {ID,Name,Effect,Effect Type,Item Type,Healling,Equipable}
Items ALL_items[TOTAL_ITEMS] = {
    {0,"Chicken Sandwich","",NONE,CONSUMABLE,10,NO},
    {1,"Flashlight","",NONE,KEY,0,OFF_HAND},
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
    {19,"Potion of Healing","",HEAL,CONSUMABLE,20,NO},
};


//TODO: Binding Vows, MANA bottle, Summons (and teams) actually working.
