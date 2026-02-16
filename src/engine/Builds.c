#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "story.h"
#include "mechanics.h"
#include "items.h"
#include "abilities.h"
#include "npc.h"
#include "utils.h"
#include "save.h"
#include "menu.h"
#include "fights.h"
#include "dialogue.h"
#include <unistd.h> 

//TODO: Balance builds
static const BuildDef build_table[BUILD_COUNT] = {
    [Assassin] = {
        .stats = { .DEFENCE=4, .DAMAGE=10, .MAGIC_POWER=2, .MAX_HP=8, .MAX_MANA=10,
                    .SUMMONS_STORAGE=0, .SPEED=18, .STEALTH=12, .WEAPON_DAMAGE=6,
                    .WEAPON_USER=true, .DUAL_WILDING=true, .MAGIC_USER=true }, //Total:70
        .items     = { 2, 3, -1 },         // Basic Dagger, Secondary Dagger
        .abilities = { 1, 4, -1 },         // Speed Boost, Disguise
        .summons   = { -1 },
    },
    [Tank] = {
        .stats = { .DEFENCE=16, .DAMAGE=6, .MAGIC_POWER=2, .MAX_HP=16, .MAX_MANA=6,
                    .SUMMONS_STORAGE=0, .SPEED=6, .STEALTH=4, .WEAPON_DAMAGE=14,
                    .WEAPON_USER=true, .DUAL_WILDING=false, .MAGIC_USER=true }, //Total:70
        .items     = { 4, 5, 6, 7, 8, 9, -1 }, // Sword, Shield, Headband, Leather set
        .abilities = { 2, -1 },             // Shield Bash
        .summons   = { -1 },
    },
    [Monk] = {
        .stats = { .DEFENCE=6, .DAMAGE=20, .MAGIC_POWER=0, .MAX_HP=14, .MAX_MANA=0,
                    .SUMMONS_STORAGE=0, .SPEED=18, .STEALTH=12, .WEAPON_DAMAGE=0,
                    .WEAPON_USER=false, .DUAL_WILDING=false, .MAGIC_USER=false }, //Total:70
        .items     = { 6, -1 },             // Headband
        .abilities = { 3, -1 },             // Lethal Punch Barrage
        .summons   = { -1 },
    },
    [Ninja] = {
        .stats = { .DEFENCE=6, .DAMAGE=8, .MAGIC_POWER=6, .MAX_HP=8, .MAX_MANA=10,
                    .SUMMONS_STORAGE=0, .SPEED=16, .STEALTH=16, .WEAPON_DAMAGE=10,
                    .WEAPON_USER=true, .DUAL_WILDING=false, .MAGIC_USER=true }, //Total:70
        .items     = { 14, 15, 6, 16, 17, 18, -1 }, // Katana, Shuriken, Headband, Ninja armor
        .abilities = { 4, 1, -1 },          // Disguise, Speed Boost
        .summons   = { -1 },
    },
    [Mage] = {
        .stats = { .DEFENCE=4, .DAMAGE=4, .MAGIC_POWER=20, .MAX_HP=6, .MAX_MANA=16,
                    .SUMMONS_STORAGE=0, .SPEED=6, .STEALTH=4, .WEAPON_DAMAGE=10,
                    .WEAPON_USER=true, .DUAL_WILDING=false, .MAGIC_USER=true }, //Total:70
        .items     = { 11, 13, -1 },        // Basic Grimoire, Mage Robe
        .abilities = { 5, 6, -1 },          // Fire Bolt, Basic Healing
        .summons   = { -1 },
    },
    [Healer] = {
        .stats = { .DEFENCE=6, .DAMAGE=2, .MAGIC_POWER=14, .MAX_HP=8, .MAX_MANA=18,
                    .SUMMONS_STORAGE=0, .SPEED=6, .STEALTH=10, .WEAPON_DAMAGE=6,
                    .WEAPON_USER=true, .DUAL_WILDING=false, .MAGIC_USER=true }, //Total:70
        .items     = { 6, 12, -1 },         // Headband, Healer's Glove
        .abilities = { 6, 7, -1 },          // Basic Healing, Group Healing
        .summons   = { -1 },
    },
    [Summoner] = {
        .stats = { .DEFENCE=6, .DAMAGE=6, .MAGIC_POWER=12, .MAX_HP=10, .MAX_MANA=18,
                    .SUMMONS_STORAGE=3, .SPEED=6, .STEALTH=8, .WEAPON_DAMAGE=4,
                    .WEAPON_USER=true, .DUAL_WILDING=false, .MAGIC_USER=true }, //Total:70
        .items     = { 6, 11, -1 },         // Headband, Basic Grimoire
        .abilities = { 6, 11, -1 },         // Basic Healing, Fire Spirit Summon
        .summons   = { 0, -1 },             // Fire Spirit
    },
    [Balanced] = {
        .stats = { .DEFENCE=8, .DAMAGE=8, .MAGIC_POWER=8, .MAX_HP=8, .MAX_MANA=8,
                    .SUMMONS_STORAGE=2, .SPEED=8, .STEALTH=8, .WEAPON_DAMAGE=8,
                    .WEAPON_USER=true, .DUAL_WILDING=true, .MAGIC_USER=true }, //Total:72
        .items     = { 4, 6, 7, 8, -1 },    // Sword, Headband, Leather Chest, Leather Pants
        .abilities = { 5, 9, -1 },          // Fire Bolt, ???
        .summons   = { -1 },
    },
};

void get_attributes(Player *main_character) {
    int build = get_mc_build(*main_character);
    if (build < 0 || build >= BUILD_COUNT) return;

    const BuildDef *def = &build_table[build];

    // Apply stats
    *main_character = set_mc_stats(*main_character, def->stats);

    // Add starting items
    for (int i = 0; i < MAX_START_ITEMS && def->items[i] != -1; i++) {
        *main_character = add_inventory(*main_character, def->items[i], 1);
    }

    // Add starting abilities
    for (int i = 0; i < MAX_START_ABILITIES && def->abilities[i] != -1; i++) {
        *main_character = add_ability(*main_character, def->abilities[i]);
    }

    // Add starting summons
    for (int i = 0; i < MAX_START_SUMMONS && def->summons[i] != -1; i++) {
        *main_character = add_summon(*main_character, def->summons[i]);
    }
}

int get_mc_build(Player main_character) {
    return main_character.build;
}
int get_mc_defence(Player main_character) {
    return main_character.stats.DEFENCE;
}
int get_mc_damage(Player main_character) {
    return main_character.stats.DAMAGE;
}
int get_mc_magic_power(Player main_character) {
    return main_character.stats.MAGIC_POWER;
}
int get_mc_max_hp(Player main_character) {
    return main_character.stats.MAX_HP;
}
int get_mc_max_mana(Player main_character) {
    return main_character.stats.MAX_MANA;
}
int get_mc_summons_storage(Player main_character) {
    return main_character.stats.SUMMONS_STORAGE;
}
int get_mc_speed(Player main_character) {
    return main_character.stats.SPEED;
}
int get_mc_stealth(Player main_character) {
    return main_character.stats.STEALTH;
}
int get_mc_weapon_damage(Player main_character) {
    return main_character.stats.WEAPON_DAMAGE;
}
bool is_weapon_user(Player main_character) {
    return main_character.stats.WEAPON_USER;
}
bool is_dual_wielding(Player main_character) {
    return main_character.stats.DUAL_WILDING;
}
bool is_magic_user(Player main_character) {
    return main_character.stats.MAGIC_USER;
}
char *get_mc_name(Player main_character) {
    return main_character.name;
}
char *get_mc_hair_colour(Player main_character) {
    return main_character.hair_colour;
}
int get_mc_age(Player main_character) {
    return main_character.age;
}
int get_mc_gender(Player main_character) {
    return main_character.gender;
}
int get_mc_money(Player main_character) {
    return main_character.money;
}
int get_mc_hp(Player main_character) {
    return main_character.HP;
}
int get_mc_mana(Player main_character) {
    return main_character.MANA;
}
int get_mc_hunger(Player main_character) {
    return main_character.HUNGER;
}
int get_mc_skill_points(Player main_character) {
    return main_character.Skill_Points;
}
int get_mc_level(Player main_character) {
    return main_character.LEVEL;
}
int get_mc_exp(Player main_character) {
    return main_character.EXP;
}
int get_mc_goodness(Player main_character) {
    return main_character.GOODNESS;
}
int get_mc_rank(Player main_character) {
    return main_character.RANK;
}
int get_mc_team_size(Player main_character) {
    return main_character.team_size;
}
int* get_mc_team_memberIDs(Player main_character) {
    return main_character.team_memberIDs;
}
int* get_mc_team_member_hp(Player main_character) {
    return main_character.team_member_hp;
}
int* get_mc_team_member_mana(Player main_character) {
    return main_character.team_member_mana;
}
int* get_mc_summonIDs(Player main_character) {
    return main_character.summonIDs;
}
int get_mc_summons_ammount(Player main_character) {
    return main_character.summons_ammount;
}
int* get_mc_abilitiesIDs(Player main_character) {
    return main_character.abilitiesIDs;
}
int get_mc_abilities_ammount(Player main_character) {
    return main_character.abilities_ammount;
}
int* get_mc_inventoryIDs(Player main_character) {
    return main_character.inventoryIDs;
}
int get_mc_item_ammount(Player main_character) {
    return main_character.item_ammount;
}
int* get_mc_equipped_items(Player main_character) {
    return main_character.equipped_items;
}
int* get_mc_mana_elements(Player main_character) {
    return main_character.mana_elements;
}
int get_mc_mana_elements_ammount(Player main_character) {
    return main_character.mana_elements_ammount;
}
int* get_mc_DNA(Player main_character) {
    return main_character.DNA;
}
int get_mc_DNA_ammount(Player main_character) {
    return main_character.DNA_ammount;
}

Attributes get_mc_attributes(Player main_character) {
    return main_character.stats;
}

Player increase_mc_stealth(Player main_character, int amount) {
    main_character.stats.STEALTH += amount;
    return main_character;
}

Player increase_mc_speed(Player main_character, int amount) {
    main_character.stats.SPEED += amount;
    return main_character;
}

Player increase_mc_summons_storage(Player main_character, int amount) {
    main_character.stats.SUMMONS_STORAGE += amount;
    return main_character;
}

Player increase_mc_magic_power(Player main_character, int amount) {
    main_character.stats.MAGIC_POWER += amount;
    return main_character;
}

Player increase_mc_weapon_damage(Player main_character, int amount) {
    main_character.stats.WEAPON_DAMAGE += amount;
    return main_character;
}

Player increase_mc_defence(Player main_character, int amount) {
    main_character.stats.DEFENCE += amount;
    return main_character;
}

Player increase_mc_damage(Player main_character, int amount) {
    main_character.stats.DAMAGE += amount;
    return main_character;
}

Player increase_mc_perception(Player main_character, int amount) {
    main_character.stats.PERCEPTION += amount;
    return main_character;
}

Player set_mc_build(Player main_character, int build_id) {
    if (build_id >= 0 && build_id < BUILD_COUNT) {
        main_character.build = (Builds)build_id;
    } else {
        say(0, "Invalid build ID. No changes made.\n");
    }

    return main_character;
}

NPC get_summon_by_id(int id){
    for(int i = 0;i<TOTAL_SUMMONS;i++){
        if (ALL_summons[i].ID == id){
            return ALL_summons[i];
        }
    }
    return (NPC){ .ID = -1 }; // Return an empty NPC if not found
}

Abilities get_ability_by_id(int id) {
    for (int i = 0; i < TOTAL_ABILITIES; i++) {
        if (ALL_abilities[i].ID == id) {
            return ALL_abilities[i];
        }
    }
    return (Abilities){ .ID = -1 }; // Return an empty Abilities struct if not found
}

NPC get_npc_by_id(int id){
    for(int i = 0;i<TOTAL_NPC;i++){
        if (ALL_npc[i].ID == id){
            return ALL_npc[i];
        }
    }
    return (NPC){ .ID = -1 }; // Return an empty NPC if not found
}

Items get_items_by_id(int id){
    for(int i = 0;i<TOTAL_ITEMS;i++){
        if (ALL_items[i].ID == id){
            return ALL_items[i];
        }
    }
    return (Items){ .ID = -1 };
}

Weapon get_weapon(int id){
    for(int i = 0;i<TOTAL_WEAPONS;i++){
        if (ALL_weapons[i].item_id == id){
            return ALL_weapons[i];
        }
    }
    return (Weapon){ .item_id = -1 };
}

Consumable get_consumable(int id){
    for (int i = 0; i < TOTAL_CONSUMABLES; i++) {
        if (ALL_consumables[i].item_id == id) {
            return ALL_consumables[i];
        }
    }
    return (Consumable){ .item_id = -1 };
}

int get_ability_by_summon(int summonID) { 
    Abilities ability;
    for (int i = 0; i < TOTAL_ABILITIES; i++) { 
        if (ability.EFFECT_TYPE == SUMMON && atoi(ability.EFFECT) == summonID) {
            return ability.ID;

        }
    } 
    return -1; // No ability found for this summon
}

const char *gender_to_string(Gender g){
    switch(g){
        case Boy:  return "Boy";
        case Girl: return "Girl";
        default:   return "Unknown";
    }
}

const char *item_type_to_string(int type) {
    switch (type) {
        case 0: return "Consumable";
        case 1: return "Key";
        case 2: return "Weapon";
        default: return "Unknown";
    }
}

const char *equipped_item_name(int item_id) {
    if (item_id == -1) return "Empty";
    Items item = get_items_by_id(item_id);
    return item.ID >= 0 ? item.name : "Unknown";
}

Player check_MANA(Player main_character) {
    if (main_character.MANA <= 0) {
        say(0,"You are out of mana! You cannot use abilities until you restore it. It hurts!!\n");
        main_character.HP -= 5; // Lose health due to mana depletion
        main_character.MANA = 0; // Ensure mana doesn't go negative
    } else if (main_character.MANA <= main_character.stats.MAX_MANA * 0.25) {
        say(0,"Your mana is low.\n");
    } else if (main_character.MANA <= main_character.stats.MAX_MANA * 0.5) {
        say(0,"Your mana is getting low.\n");
    } else if (main_character.MANA <= main_character.stats.MAX_MANA * 0.75) {
        say(0,"Your mana is at a decent level.\n");
    } else {
        say(0,"Your mana is full.\n");
    }
    return main_character;
}

Player increase_hunger(Player main_character, int amount) {
    main_character.HUNGER += amount;
    if (main_character.HUNGER > 100) {
        main_character.HUNGER = 100;
    }
    return main_character;
}

Player decrease_hunger(Player main_character, int amount) {
    main_character.HUNGER -= amount;
    if (main_character.HUNGER < 0) {
        main_character.HUNGER = 0;
    }
    return main_character;
}

Player heal_player(Player main_character, int heal_amount) {
    heal_amount = heal_calculation(main_character, heal_amount);
    main_character.HP += heal_amount;
    if (main_character.HP > main_character.stats.MAX_HP*10) {
        main_character.HP = (main_character.stats.MAX_HP * 10);
    }
    return main_character;
}

Player add_Mana(Player main_character, int mana_ammount){
    if(main_character.MANA == main_character.stats.MAX_MANA*10){
        say(0,"Your mana is already full.\n");
        return main_character;
    }
    main_character.MANA += mana_ammount;
    if (main_character.MANA > main_character.stats.MAX_MANA*10) {
        main_character.MANA = main_character.stats.MAX_MANA*10;
    }
    return main_character;
}

Player restore_mana(Player main_character) {
    int mana_amount = main_character.stats.MAX_MANA * 2; // Example: restore based on MAGIC_POWER
    main_character.MANA += mana_amount;
    if (main_character.MANA > main_character.stats.MAX_MANA*10) {
        main_character.MANA = main_character.stats.MAX_MANA*10;
    }
    return main_character;
}

int has_mana_type(Player main_character, int mana_type) { return !not_in(mana_type, main_character.mana_elements, main_character.mana_elements_ammount); }

Player add_mana_type(Player main_character, int mana_type) {
    if (not_in(mana_type, main_character.mana_elements, main_character.mana_elements_ammount) && mana_type >= 0) {
        main_character.mana_elements = realloc(main_character.mana_elements, (main_character.mana_elements_ammount + 1) * sizeof(int));
        main_character.mana_elements[main_character.mana_elements_ammount] = mana_type;
        main_character.mana_elements_ammount += 1;
    }
    return main_character;
}

Player remove_mana_type(Player main_character, int mana_type) {
    if (not_in(mana_type, main_character.mana_elements, main_character.mana_elements_ammount)) {
        say(0,"Mana type not found in player's mana types.\n");
        return main_character;
    }
    for (int i = 0; i < main_character.mana_elements_ammount; i++) {
        if (main_character.mana_elements[i] == mana_type) {
            for (int k = i; k < main_character.mana_elements_ammount - 1; k++) {
                main_character.mana_elements[k] = main_character.mana_elements[k + 1];
            }
            main_character.mana_elements_ammount -= 1;
            main_character.mana_elements = realloc(main_character.mana_elements, main_character.mana_elements_ammount * sizeof(int));
            break;
        }
    }
    return main_character;
}

Player add_DNA(Player main_character, int dna_id) {
    if (not_in(dna_id, main_character.DNA, main_character.DNA_ammount)) {
        main_character.DNA = realloc(main_character.DNA, (main_character.DNA_ammount + 1) * sizeof(int));
        main_character.DNA[main_character.DNA_ammount] = dna_id;
        main_character.DNA_ammount += 1;
    }
    return main_character;
}

Player remove_DNA(Player main_character, int dna_id) {
    if (not_in(dna_id, main_character.DNA, main_character.DNA_ammount)) {
        say(0,"DNA not found in player's DNA.\n");
        return main_character;
    }
    for (int i = 0; i < main_character.DNA_ammount; i++) {
        if (main_character.DNA[i] == dna_id) {
            for (int k = i; k < main_character.DNA_ammount - 1; k++) {
                main_character.DNA[k] = main_character.DNA[k + 1];
            }
            main_character.DNA_ammount -= 1;
            main_character.DNA = realloc(main_character.DNA, main_character.DNA_ammount * sizeof(int));
            break;
        }
    }
    return main_character;
}

Player change_mc_goodness(Player main_character, int change) {
    main_character.GOODNESS += change;
    if (main_character.GOODNESS > 100) {
        main_character.GOODNESS = 100;
    } else if (main_character.GOODNESS < -100) {
        main_character.GOODNESS = -100;
    }
    return main_character;
}

Player add_mc_money(Player main_character, int amount) {
    main_character.money += amount;
    if (main_character.money < 0) {
        main_character.money = 0;
    }
    return main_character;
}

Player add_mc_exp(Player main_character, int exp) {
    int mc_exp = get_mc_exp(main_character);
    int mc_level = get_mc_level(main_character);
    int sp = get_mc_skill_points(main_character);
    mc_exp += exp;
    while (mc_exp >= mc_level * 100) {
        mc_exp -= mc_level * 100;
        mc_level += 1;
        sp += 1; 
        say(0,"You leveled up! You are now level %d.\n", main_character.LEVEL);
    }
    main_character = set_mc_exp(main_character, mc_exp);
    main_character = set_mc_level(main_character, mc_level);
    main_character = set_mc_skill_points(main_character, sp);
    return main_character;
}

Player set_mc_level(Player main_character, int level) {
    if (level < 1) {
        say(0,"Level cannot be set below 1.\n");
        return main_character;
    }
    main_character.LEVEL = level;
    return main_character;
}

Player set_mc_exp(Player main_character, int exp) {
    if (exp < 0) {
        say(0,"EXP cannot be negative.\n");
        return main_character;
    }
    main_character.EXP = exp;
    return main_character;
}

Player set_mc_skill_points(Player main_character, int sp) {
    if (sp < 0) {
        say(0,"Skill points cannot be negative.\n");
        return main_character;
    }
    main_character.Skill_Points = sp;
    return main_character;
}

Player set_mc_stats(Player main_character, Attributes new_stats) {
    main_character.stats = new_stats;
    return main_character;
}
