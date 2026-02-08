#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "story.h"
#include "mechanics.h"
#include <unistd.h> 

//Abilities {Id,Name,Healing,Damage,Mana Cost,Effects,Effect Type,Rank,Ability_Active,Ability_Type}
Abilities ALL_abilities[TOTAL_ABILITIES] = {
    {0,"NO Abilitie",0,0,0,"",NONE,E,BASE,Melee,Learned,"Does nothing."},
    {1,"Speed Boost",0,0,30,"2 SPEED",BOOST,D,BASE,Magic,Learned,"Temporarily doubles your speed for the duration of the fight."},
    {2,"Shield Bash",0,20,10,"1.1 DEFENCE",BOOST,D,BASE,Melee,Learned,"Deals damage and slightly increases your defence."},
    {3,"Lethal Punch Barrage",0,30,25,"0.75 DAMAGE",BOOST,C,BASE,Melee,Learned,"Deals heavy damage but reduces your damage."},
    {4,"Disguise",0,0,30,"3 STEALTH",PLUS,C,BASE,Magic,Learned,"Increases your stealth, making it harder for enemies to hit you."},
    {5,"Fire Bolt",0,15,15,"",NONE,D,FIRE,Magic,Learned,"Deals fire damage."},
    {6,"Basic Healing",20,0,20,"",NONE,D,BASE,Magic,Learned,"Heals a small amount of HP."},
    {7,"Group Healing",15,0,30,"15 0",GROUP,B,BASE,Support,Learned,"Heals you and your allies."},
    {8,"Shadow Dog Summon",0,0,40,"100",SUMMON,C,DARK,Summon,Hereditary,"Summons a Shadow Dog to fight alongside you."},
    {9,"Strength Boost",0,0,30,"2 DAMAGE",BOOST,D,BASE,Magic,Learned,"Temporarily doubles your damage for the duration of the fight."},
    {10,"Invisibility",0,0,200,"7 STEALTH",BOOST,S,BASE,Magic,Learned,"Grants invisibility, greatly increasing your stealth."},
    {11,"Fire Spirit Summon",0,0,50,"101",SUMMON,E,BASE,Summon,Learned,"Summons a Fire Spirit to fight alongside you."},
    {12,"Mana Infusion",0,0,30,"",NONE,D,BASE,Infused,Learned,"Infuses your weapon or hands with mana, increasing its damage based on your magic power."},
};


//TODO Balance the Rival
//NPC {ID,age,name,Ability_ids*,summonIDs*,abilities_ammount,summons_ammount,RANK,LEVEL,EXP_GIVEN,HP,MAX_HP,MANA,MAX_MANA,DAMAGE,DEFENCE,SPEED,ELEMENTAL_AFFINITY}
NPC ALL_npc[TOTAL_NPC] = {//TODO Change these Random NPC
    {0,15,"Sofia",  (int[]){6,11}, (int[]){0,1}, 2, 2, E, 1, 20, 20, 20, 100, 100, 3, 2, 6, LIGHT},
    {1,15,"Nathan", (int[]){6,11}, (int[]){0,1}, 2, 2, E, 1, 20, 20, 20, 100, 100, 3, 2, 6, LIGHT},
    {2,0, "",       NULL, NULL, 0, 0, D, 1,10, 20, 20, 0, 0, 5, 1, 3, BASE},
    {3,0, "",       NULL, NULL, 0, 0, C, 1,15, 15, 15, 0, 0, 3, 1, 2, BASE},
    {4,0, "",       NULL, NULL, 0, 0, B, 1,20, 30, 30, 0, 0, 7, 2, 5, BASE},
    {5,0, "",       NULL, NULL, 0, 0, C, 1,15, 25, 25, 0, 0, 6, 2, 4, BASE},
    {6,0, "",       NULL, NULL, 0, 0, A, 1,30, 40, 40, 0, 0, 8, 3, 6, BASE},
    {7,0, "",       NULL, NULL, 0, 0, B, 1,20, 30, 30, 0, 0, 5, 2, 4, BASE},
    {8,0, "",       NULL, NULL, 0, 0, C, 1,15, 25, 25, 0, 0, 6, 2, 4, BASE},
    {9,0, "",       NULL, NULL, 0, 0, S, 1,50, 60, 60, 0, 0,10, 4, 8, BASE},
};
NPC ALL_summons[TOTAL_SUMMONS] = {
    {100,100,"Shadow Dog", NULL, NULL, 0, 0, D, 1, 1000, 30, 30, 30, 30, 4, 2, 5, DARK},
    {101,4,  "Fire Spirit", NULL, NULL, 0, 0, E, 1, 100, 10, 10, 10, 10, 7, 1, 3, FIRE},
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

const float elemental_chart[ELEMENTAL_AFFINITY_COUNT][ELEMENTAL_AFFINITY_COUNT] = { // Advantage multiplier chart: [Attacker][Defender]
/* ATK \ DEF */
/*            BA    FI    WA    EA    AI    EL    IC    LA    ST    LI    DA */
/* BASE */  {1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0},
/* FIRE */  {1.0,  1.0,  0.75, 1.5,  1.0,  1.0,  1.5,  1.0,  0.75, 1.0,  1.0},
/* WATER */ {1.0,  1.5,  1.0,  1.0,  1.0,  0.75, 0.75, 1.5,  1.0,  1.0,  1.0},
/* EARTH */ {1.0,  1.0,  0.75, 1.0,  1.5,  1.5,  1.0,  0.75, 1.0,  1.0,  1.0},
/* AIR */   {1.0,  1.0,  1.0,  0.75, 1.0,  0.75, 1.5,  1.0,  0.75, 1.0,  1.0},
/* ELECT */ {1.0,  1.0,  1.5,  0.75, 1.5,  1.0,  0.75, 1.0,  1.0,  1.0,  1.0},
/* ICE */   {1.0,  0.75, 1.5,  1.0,  1.5,  1.5,  1.0,  0.75, 0.75, 1.0,  1.0},
/* LAVA */  {1.0,  1.0,  0.75, 1.5,  1.0,  1.0,  1.5,  1.0,  1.0,  1.0,  1.0},
/* STORM */ {1.0,  1.5,  1.5,  0.75, 1.5,  1.0,  0.75, 1.0,  1.0,  0.75, 1.0},
/* LIGHT */ {1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.5},
/* DARK */  {1.0,  0.75, 1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.5,  1.0}
};
