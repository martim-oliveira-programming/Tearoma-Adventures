#ifndef MECHANICS_H
#define MECHANICS_H
#include <stdbool.h>
#include "story.h"

#define TOTAL_ABILITIES 11
#define TOTAL_ITEMS 19
#define TOTAL_SUMMONS 1
#define TOTAL_NPC 10

typedef enum{
    Assassin,
    Tank,
    Monk,
    Ninja,
    Mage,
    Healer,
    Summoner,
    Balanced,
}Builds;

typedef enum{
    NO,
    MAIN_HAND,
    OFF_HAND,
    HEAD,
    CHEST,
    LEGS,
    SHOES,
}Equipable;

typedef enum{
    NONE,
    BOOST,
    SUMMON,
    GROUP,
    PLUS,
}EFFECT_TYPE;

typedef enum{
    CONSUMABLE,
    KEY,
    WEAPON,
}ITEM_TYPE;

typedef struct initial_build_attributes{
    char *MOUNT;
    int DEFENCE;
    int MAX_HP;
    int MAX_MANA;
    int SUMMONS_STORAGE;
    int MAGIC_POWER;
    int WEAPON_DAMAGE;
    int DAMAGE;
    int SPEED;
    int STEALTH;
    bool WEAPON_USER;
    bool DUAL_WILDING;
    bool MAGIC_USER;
}Attributes;

typedef struct player_abilities{
    int ID;
    char *NAME;
    int HEALING;
    int DAMAGE;
    int MANA_COST;
    char *EFFECTS;
    int EFFECT_TYPE;
}Abilities;

typedef struct items{
    int ID;
    char *name;
    const char *effect;
    int effect_type;
    int item_type;
    int healling;
    int equipable;
}Items;

typedef enum gender{
    Boy,
    Girl,
}Gender;

typedef enum Rank{
    E,
    D,
    C,
    B,
    A,
    S,
}Rank;

typedef struct other_characters{
    int ID;
    char *name;
    int Ability_id;
    int EFFECT_TYPE;
    int RANK;
    int LEVEL;
    int EXP_GIVVEN;
    int HP;
    int MAX_HP;
    int DAMAGE;
    int SPEED;
}NPC;

typedef struct summoning_contracts{
    NPC stats;
}SUMMONS;

typedef struct team {
    int *memberIDs;
    int *summonIDs;
    int size;
}NPC_Team;

typedef struct player {
    // Basic info
    char *name;
    char *hair_colour;
    int age;
    int gender;
    // Game attributes
    int money;
    int build;
    int* summonIDs;
    int* abilitiesIDs;
    int* inventoryIDs;
    int item_ammount;
    int abilities_ammount;
    int summons_ammount;
    int armor[4];  // Array for armor slots (head, chest, legs, boots)
    int weapon;
    int weapon_OFF_Hand;
    int RANK;
    int HUNGER;
    int Skill_Points;
    int LEVEL;
    int EXP;
    int HP;
    int MANA;
    int GOODNESS;
    Attributes stats;  // Contains all build-specific attributes
    NPC_Team *team;
} Player;

//Build Character Functions
Player character_creation();
Builds parse_build(const char *s);
void get_attributes(Player *main_character);
const char *gender_to_string(Gender g);
const char *build_to_string(Builds b);

//Inventory Management
Player add_inventory(Player main_character, int itemID, int amount);
Player remove_inventory(Player main_character, int itemID, int amount);


Player add_ability(Player main_character, int abilityID);
Player remove_ability(Player main_character, int abilityID);
Player equip_armor(Player main_character, int itemID);
Player unequip_armor(Player main_character, int slot);
Player equip_weapon(Player main_character, int itemID);
Player unequip_weapon(Player main_character, int slot);
Player add_summon(Player main_character, int summonID);
Player remove_summon(Player main_character, int summonID);
NPC_Team add_team_member(NPC_Team team, int memberID, bool is_summon);
NPC_Team remove_team_member(NPC_Team team, int memberID, bool is_summon);
int is_team_member(NPC_Team team, int memberID, bool is_summon);
void apply_ability_effect(Player *main_character ,Abilities player_ability);

//Utilitie Functions
Abilities* get_ability_by_id(int id);
NPC* get_npc_by_id(int id);
Items* get_items_by_id(int id);
NPC *get_summon_by_id(int id);

extern Abilities ALL_abilities[TOTAL_ABILITIES];
extern NPC ALL_summons[TOTAL_SUMMONS];
extern Items ALL_items[TOTAL_ITEMS];

//Playing Functions
Player play_chapter(Player main_character, Story *story);

#endif
