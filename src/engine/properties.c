#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "story.h"
#include "mechanics.h"
#include <unistd.h> 

//Abilities {ID, NAME, MANA_COST, RANK, DNA, DESCRIPTION, turns_remaining, EFFECT, EFFECT_TYPE}
const Abilities ALL_abilities[TOTAL_ABILITIES] = {
    {0, "Fire Punch", 20, D, All, "A fire attack that deals damage based on your magic power.", 0, "-5 HP", PLUS},
    {1, "Speed Boost", 30, D, All, "Temporarily doubles your speed for the duration of the fight.", 0, "2 SPEED", BOOST},
    {2, "Shield Bash", 10, D, All, "Deals damage and slightly increases your defence.", 0, "1.1 DEFENCE", BOOST},
    {3, "Lethal Punch Barrage", 25, C, All, "Deals heavy damage but reduces your damage.", 0, "0.75 DAMAGE", BOOST},
    {4, "Disguise", 30, C, All, "Increases your stealth, making it harder for enemies to hit you.", 0, "1.5 STEALTH", BOOST},
    {5, "Fire Bolt", 15, D, All, "Deals fire damage.", 0, "", NONE},
    {6, "Basic Healing", 20, D, All, "Heals a small amount of HP.", 0, "", HEAL},
    {7, "Group Healing", 30, B, All, "Heals you and your allies.", 0, "15 0", GROUP},
    {8, "Shadow Dog Summon", 80, C, Minamoto, "Summons a Shadow Dog to fight alongside you.", 0, "100", SUMMON},
    {9, "Strength Boost", 30, D, All, "Temporarily increases your damage for the duration of the fight.", 0, "1.5 DAMAGE", BOOST},
    {10, "Invisibility", 200, S, All, "Grants invisibility, greatly increasing your stealth.", 0, "7 STEALTH", BOOST},
    {11, "Fire Spirit Summon", 50, E, All, "Summons a Fire Spirit to fight alongside you.", 0, "101", SUMMON},
    {12, "Mana Infusion", 30, D, All, "Infuses your weapon or hands with mana, increasing its damage based on your magic power.", 0, "", NONE},
    {13, "Amaterasu", 100, S, MS_1, "Engulfs the enemy in black flames that deal heavy damage over time.", 100, "-20 HP", PLUS},
    {14, "Tsukuyomi", 80, S, MS_2, "Traps the enemy in a powerful illusion, stunning them for several turns.", 0, "", NONE},
    {15, "Copy Ability", 20, B, Sharingan, "Copies an ability used by the enemy and allows you to use it if you share its mana type and DNA.", 0, "", COPY},
    {16, "Reveal One's Hand", 0, C, All, "In exchange for revealing how your inate ability works to the enemy, you gain Mana and Magic Power.", 0, "30 5", REVEAL}, // Effect "30 5" means "restore 30 mana and increase magic power by 5"
    {17, "Poison Needles", 50, C, All, "Poisons the enemy, dealing damage over time.", 5, "", POISON},
    {18, "Flame Slash", 40, C, All, "Deals fire damage and has a chance to burn the enemy.", 5, "", BURN},
    {19, "Ice Shard", 40, C, All, "Deals ice damage and has a chance to freeze the enemy.", 3, "", FREEZE},
    {20, "Thunder Strike", 40, C, All, "Deals lightning damage and has a chance to paralyse the enemy.", 5, "", PARALYSE},
};

//Magic abilities {ability_id, damage, mana_type}
const Magic ALL_magic[TOTAL_MAGIC] = {
    {5, 15, FIRE},   // Fire Bolt
    {6, 0, BASE},    // Basic Healing (handled as HEAL)
    {7, 0, BASE},    // Group Healing (handled as GROUP)
    {9, 0, BASE},    // Strength Boost (buff only)
    {10, 0, BASE},   // Invisibility (buff only)
    {12, 0, BASE},   // Mana Infusion (buff only)
    {13, 50, FIRE},  // Amaterasu
    {14, 0, DARK},   // Tsukuyomi (control effect)
    {15, 0, BASE},   // Copy Ability (special)
    {16, 0, BASE},   // Reveal One's Hand (buff/debuff)
    {17, 10, POISON}, // Poison Needles (damage over time)
    {18, 30, FIRE},  // Flame Slash (damage with burn)
    {19, 20, ICE},   // Ice Shard (damage with freeze)
    {20, 25, ELECTIC}, // Thunder Strike (damage with paralysis)
};

//Melee abilities {ability_id, damage, mana_type}
const Melee ALL_melee[TOTAL_Melle] = {
    {2, 20, BASE}, // Shield Bash
    {3, 30, BASE}, // Lethal Punch Barrage
};

//Infused abilities {ability_id, damage, mana_type}
const Infused ALL_infused[] = {
    {0, 0, FIRE},   // Fire Punch (damage calculated from magic power)
    {12, 0, BASE},
};

//Summon abilities {ability_id, damage, mana_type}
const Summon ALL_summon_abilities[] = {
    {8, 0, DARK},
    {11, 0, BASE},
};

//Support abilities {ability_id, healing, mana_restoration, team_effect}
const Support ALL_support[] = {
    {6, 20, 0, false}, // Basic Healing
    {7, 15, 0, true},  // Group Healing
};


//NPC {ID,age,name,Ability_ids*,summonIDs*,abilities_ammount,summons_ammount,RANK,LEVEL,EXP_GIVEN,HP,MAX_HP,MANA,MAX_MANA,DAMAGE,DEFENCE,SPEED,ELEMENTAL_AFFINITY}
const NPC ALL_npc[TOTAL_NPC] = {//.               exp.hp,maxhp.mana.maxm.dmg,df,speed,element
    {0,15,"Sofia",  (int[]){5,9}, NULL, 2, 0, D, 1, 25, 90, 90, 60, 60, 10, 5, 8, BASE},
    {1,15,"Nathan", (int[]){5,9}, NULL, 2, 0, D, 1, 25, 90, 90, 60, 60, 10, 5, 8, BASE},
    {2,0, "",       NULL, NULL, 0, 0, D, 1,10, 20, 20, 0, 0, 5, 1, 3, BASE},
    {3,0, "",       NULL, NULL, 0, 0, C, 1,15, 15, 15, 0, 0, 3, 1, 2, BASE},
    {4,0, "",       NULL, NULL, 0, 0, B, 1,20, 30, 30, 0, 0, 7, 2, 5, BASE},
    {5,0, "",       NULL, NULL, 0, 0, C, 1,15, 25, 25, 0, 0, 6, 2, 4, BASE},
    {6,0, "",       NULL, NULL, 0, 0, A, 1,30, 40, 40, 0, 0, 8, 3, 6, BASE},
    {7,0, "",       NULL, NULL, 0, 0, B, 1,20, 30, 30, 0, 0, 5, 2, 4, BASE},
    {8,0, "",       NULL, NULL, 0, 0, C, 1,15, 25, 25, 0, 0, 6, 2, 4, BASE},
    {9,0, "",       NULL, NULL, 0, 0, S, 1,50, 60, 60, 0, 0,10, 4, 8, BASE},
};
const NPC ALL_summons[TOTAL_SUMMONS] = {
    {100,100,"Shadow Dog", NULL, NULL, 0, 0, D, 1, 1000, 30, 30, 30, 30, 4, 2, 5, DARK},
    {101,4,  "Fire Spirit", NULL, NULL, 0, 0, E, 1, 100, 10, 10, 10, 10, 7, 1, 3, BASE},
};


//Items {ID, Name, Description}
const Items ALL_items[TOTAL_ITEMS] = {
    {0,  "Chicken Sandwich", "A filling sandwich that restores some health.",CONSUMABLE},
    {1,  "Flashlight",        "A handy light source for dark places.",KEY},
    {2,  "Basic Dagger",      "A light dagger favored by rogues.",WEAPON},
    {3,  "Secondary Dagger",  "A small off-hand dagger.",WEAPON},
    {4,  "Basic Sword",       "A simple but reliable sword.",WEAPON},
    {5,  "Basic Shield",      "A wooden shield that offers modest protection.",WEAPON},
    {6,  "Leather Helmet",    "Light head protection made of leather.",WEAPON},
    {7,  "Leather Chestplate","Sturdy leather armor for the torso.",WEAPON},
    {8,  "Leather Pants",     "Leather leg guards for basic defense.",WEAPON},
    {9,  "Leather Boots",     "Boots that offer grip and slight protection.",WEAPON},
    {10, "Headband",          "A headband that bolsters focus.",WEAPON},
    {11, "Basic Grimoire",    "A beginner's spellbook containing simple incantations.",WEAPON},
    {12, "Healer's Glove",    "A glove imbued to aid restorative magic.",WEAPON},
    {13, "Mage's Robe",       "Robes that enhance magical aptitude.",WEAPON},
    {14, "Basic Katana",      "A sharp katana suited for swift strikes.",WEAPON},
    {15, "Shuriken",          "Throwing stars for quick, precise attacks.",WEAPON},
    {16, "Ninja chestplate",  "Light armor tailored for agility.",WEAPON},
    {17, "Ninja pants",       "Flexible pants aiding silent movement.",WEAPON},
    {18, "Soundless sandals", "Sandals that muffle footsteps.",WEAPON},
    {19, "Potion of Healing", "A potion that restores 30 health when consumed.",CONSUMABLE},
    {20, "Mana Bottle",       "A bottle that restores 30 mana when consumed.",CONSUMABLE},
};

//Weapons {item_id, equip_slot, effect}
const Weapon ALL_weapons[TOTAL_WEAPONS] = {
    {2, MAIN_HAND, "3 WEAPON_DAMAGE"},
    {3, OFF_HAND, "2 WEAPON_DAMAGE"},
    {4, MAIN_HAND, "4 WEAPON_DAMAGE"},
    {5, OFF_HAND, "3 DEFENCE"},
    {6, HEAD, "1 DEFENCE"},
    {7, CHEST, "3 DEFENCE"},
    {8, LEGS, "2 DEFENCE"},
    {9, SHOES, "1 DEFENCE"},
    {10, HEAD, "3 DEFENCE"},
    {11, MAIN_HAND, "3 MAGIC_POWER"},
    {12, MAIN_HAND, "2 MAX_MANA"},
    {13, CHEST, "3 MAGIC_POWER"},
    {14, MAIN_HAND, "5 WEAPON_DAMAGE"},
    {15, OFF_HAND, "3 WEAPON_DAMAGE"},
    {16, CHEST, "4 DEFENCE"},
    {17, LEGS, "3 DEFENCE"},
    {18, SHOES, "2 DEFENCE"},
};
//Consumables {item_id,healling,mana_restoration,hunger_restoration}
const Consumable ALL_consumables[TOTAL_CONSUMABLES] = {
    {0, 0, 0, 20},
    {19, 30, 0, 0},
    {20, 0, 30, 0},
};

//Key Items {item_id, use_description}
const Key_Item ALL_key_items[TOTAL_KEY_ITEMS] = {
    {1, "Can be used to light up dark areas."},
};

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

int get_ability_damage_value(int ability_id) {
    switch (ability_id) {
        case 2: return 20; // Shield Bash
        case 3: return 30; // Lethal Punch Barrage
        case 5: return 15; // Fire Bolt
        case 13: return 50; // Amaterasu
        default: return 0;
    }
}

int get_ability_healing_value(int ability_id) {
    switch (ability_id) {
        case 6: return 20; // Basic Healing
        case 7: return 15; // Group Healing (per target)
        default: return 0;
    }
}

int get_ability_mana_type(int ability_id) {
    for (int i = 0; i < TOTAL_MAGIC; i++)
        if (ALL_magic[i].ability_id == ability_id) return ALL_magic[i].mana_type;
    for (int i = 0; i < TOTAL_Melle; i++)
        if (ALL_melee[i].ability_id == ability_id) return ALL_melee[i].mana_type;
    for (int i = 0; i < (int)(sizeof(ALL_infused)/sizeof(ALL_infused[0])); i++)
        if (ALL_infused[i].ability_id == ability_id) return ALL_infused[i].mana_type;
    for (int i = 0; i < (int)(sizeof(ALL_summon_abilities)/sizeof(ALL_summon_abilities[0])); i++)
        if (ALL_summon_abilities[i].ability_id == ability_id) return ALL_summon_abilities[i].mana_type;
    return BASE;
}

Ability_Class get_ability_class(int ability_id) {
    for (int i = 0; i < TOTAL_Melle; i++)
        if (ALL_melee[i].ability_id == ability_id) return AbilityClass_Melee;
    for (int i = 0; i < (int)(sizeof(ALL_infused)/sizeof(ALL_infused[0])); i++)
        if (ALL_infused[i].ability_id == ability_id) return AbilityClass_Infused;
    for (int i = 0; i < (int)(sizeof(ALL_summon_abilities)/sizeof(ALL_summon_abilities[0])); i++)
        if (ALL_summon_abilities[i].ability_id == ability_id) return AbilityClass_Summon;
    for (int i = 0; i < (int)(sizeof(ALL_support)/sizeof(ALL_support[0])); i++)
        if (ALL_support[i].ability_id == ability_id) return AbilityClass_Support;
    return AbilityClass_Magic;
}

EFFECT_TYPE get_ability_effect_type(int ability_id) {
    for (int i = 0; i < TOTAL_ABILITIES; i++) {
        if (ALL_abilities[i].ID == ability_id) {
            return (EFFECT_TYPE)ALL_abilities[i].EFFECT_TYPE;
        }
    }
    return NONE;
}

int get_ability_id(Abilities ability) {
    for (int i = 0; i < TOTAL_ABILITIES; i++) {
        if (ALL_abilities[i].ID == ability.ID) {
            return ALL_abilities[i].ID;
        }
    }
    return -1; // Not found
}

const char *get_ability_effects(int ability_id) {
    switch (ability_id) {
        case 1: return "2 SPEED";
        case 2: return "1.1 DEFENCE";
        case 3: return "0.75 DAMAGE";
        case 4: return "1.5 STEALTH";
        case 7: return "15 0";
        case 8: return "100";
        case 9: return "2 DAMAGE";
        case 10: return "7 STEALTH";
        case 11: return "101";
        default: return "";
    }
}

char* get_ability_name(int ability_id) {
    for (int i = 0; i < TOTAL_ABILITIES; i++) {
        if (ALL_abilities[i].ID == ability_id) {
            return ALL_abilities[i].NAME;
        }
    }
    return "Unknown Ability";
}

int get_ability_mana_cost(int ability_id) {
    for (int i = 0; i < TOTAL_ABILITIES; i++) {
        if (ALL_abilities[i].ID == ability_id) {
            return ALL_abilities[i].MANA_COST;
        }
    }
    return -1;
}

int get_ability_rank(int ability_id) {
    for (int i = 0; i < TOTAL_ABILITIES; i++) {
        if (ALL_abilities[i].ID == ability_id) {
            return ALL_abilities[i].RANK;
        }
    }
    return D; // Default to lowest rank if not found
}

int get_ability_by_summon_id(int summon_id) {
    for (int i = 0; i < TOTAL_ABILITIES; i++) {
        if(ALL_abilities[i].EFFECT_TYPE != SUMMON) continue; // Skip non-summon abilities because their EFFECT field won't correspond to a summon ID and doesnt work with atoi()
        if (atoi(ALL_abilities[i].EFFECT) == summon_id) {
            return ALL_abilities[i].ID;
        }
    }
    return -1; // Not found
}

int get_ability_dna(int ability_id){
    for (int i = 0; i < TOTAL_ABILITIES; i++) {
        if (ALL_abilities[i].ID == ability_id) {
            return ALL_abilities[i].DNA;
        }
    }
    return -1;
}

int get_ability_effect_duration(int ability_id) {
    for (int i = 0; i < TOTAL_ABILITIES; i++) {
        if (ALL_abilities[i].ID == ability_id) {
            return ALL_abilities[i].turns_remaining;
        }
    }
    return 0; // Default to 0 for non-temporary effects
}
