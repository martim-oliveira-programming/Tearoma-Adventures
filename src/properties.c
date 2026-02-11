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


//Items {ID, Name, Description}
Items ALL_items[TOTAL_ITEMS] = {
    {0,  "Chicken Sandwich", "A filling sandwich that restores some health."},
    {1,  "Flashlight",        "A handy light source for dark places."},
    {2,  "Basic Dagger",      "A light dagger favored by rogues."},
    {3,  "Secondary Dagger",  "A small off-hand dagger."},
    {4,  "Basic Sword",       "A simple but reliable sword."},
    {5,  "Basic Shield",      "A wooden shield that offers modest protection."},
    {6,  "Leather Helmet",    "Light head protection made of leather."},
    {7,  "Leather Chestplate","Sturdy leather armor for the torso."},
    {8,  "Leather Pants",     "Leather leg guards for basic defense."},
    {9,  "Leather Boots",     "Boots that offer grip and slight protection."},
    {10, "Headband",          "A headband that bolsters focus."},
    {11, "Basic Grimoire",    "A beginner's spellbook containing simple incantations."},
    {12, "Healer's Glove",    "A glove imbued to aid restorative magic."},
    {13, "Mage's Robe",       "Robes that enhance magical aptitude."},
    {14, "Basic Katana",      "A sharp katana suited for swift strikes."},
    {15, "Shuriken",          "Throwing stars for quick, precise attacks."},
    {16, "Ninja chestplate",  "Light armor tailored for agility."},
    {17, "Ninja pants",       "Flexible pants aiding silent movement."},
    {18, "Soundless sandals", "Sandals that muffle footsteps."},
    {19, "Potion of Healing", "A potion that restores 30 health when consumed."},
    {20, "Mana Bottle",       "A bottle that restores 30 mana when consumed."},
};

Weapon ALL_weapons[TOTAL_WEAPONS] = {
    {ALL_items[2], MAIN_HAND, "3 WEAPON_DAMAGE"},
    {ALL_items[3], OFF_HAND, "2 WEAPON_DAMAGE"},
    {ALL_items[4], MAIN_HAND, "4 WEAPON_DAMAGE"},
    {ALL_items[5], OFF_HAND, "3 DEFENCE"},
    {ALL_items[6], HEAD, "1 DEFENCE"},
    {ALL_items[7], CHEST, "3 DEFENCE"},
    {ALL_items[8], LEGS, "2 DEFENCE"},
    {ALL_items[9], SHOES, "1 DEFENCE"},
    {ALL_items[10], HEAD, "3 DEFENCE"},
    {ALL_items[11], MAIN_HAND, "3 MAGIC_POWER"},
    {ALL_items[12], MAIN_HAND, "2 MAX_MANA"},
    {ALL_items[13], CHEST, "3 MAGIC_POWER"},
    {ALL_items[14], MAIN_HAND, "5 WEAPON_DAMAGE"},
    {ALL_items[15], OFF_HAND, "3 WEAPON_DAMAGE"},
    {ALL_items[16], CHEST, "4 DEFENCE"},
    {ALL_items[17], LEGS, "3 DEFENCE"},
    {ALL_items[18], SHOES, "2 DEFENCE"},
};

Consumable ALL_consumables[TOTAL_CONSUMABLES] = {
    {ALL_items[0], 5, 0, 20},
    {ALL_items[19], 30, 0,0}, 
    {ALL_items[20], 0, 30,0},
};

Key_Item ALL_key_items[TOTAL_KEY_ITEMS] = {
    {ALL_items[1], "Can be used to light up dark areas."},
};


//TODO: Binding Vows, Summons (and teams) actually working.

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
