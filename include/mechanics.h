#ifndef MECHANICS_H
#define MECHANICS_H
#include <stdbool.h>
#include "story.h"

#define TOTAL_ABILITIES 12
#define TOTAL_ITEMS 20
#define TOTAL_SUMMONS 2
#define TOTAL_NPC 10
#define MAX_EQUIPPED_ITEMS 5


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
    BASE,
    FIRE,
    WATER,
    EARTH,
    AIR,
    ELECTIC,
    ICE,
    LAVA,
    STORM,
    LIGHT,
    DARK,
}Mana_Types;

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
    HEAL,
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
    int PRECEPTION;
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
    int RANK;
    int MANA_TYPE;
    int ABILITY_ACTIVE;
    int ABILITY_TYPE;
}Abilities;

typedef enum{
    Inate,
    Learned,
    Hereditary,
}Ability_Types;

typedef enum{
    Active,
    Passive,
}Ability_Active;

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
    int age;
    char *name;
    int* Ability_ids;
    int* summonIDs;
    int abilities_ammount;
    int summons_ammount;
    int RANK;
    int LEVEL;
    int EXP_GIVEN;
    int HP;
    int MAX_HP;
    int MANA;
    int MAX_MANA;
    int DAMAGE;
    int DEFENCE;
    int SPEED;
}NPC;

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
    int* equipped_items; // Array to track equipped items (size 4 for armor slots + 1 for weapon)
    int* mana_types;
    int mana_types_ammount;
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

//Inventory Management
Player add_inventory(Player main_character, int itemID, int amount);
Player remove_inventory(Player main_character, int itemID, int amount);

//Abilities and Summons Management
Player add_ability(Player main_character, int abilityID);
Player remove_ability(Player main_character, int abilityID);
Player equip_item(Player main_character, int itemID);
Player unequip_item(Player main_character, int slot);
Player add_summon(Player main_character, int summonID);
Player remove_summon(Player main_character, int summonID);
NPC_Team add_team_member(NPC_Team team, int memberID, bool is_summon);
NPC_Team remove_team_member(NPC_Team team, int memberID, bool is_summon);
int is_team_member(NPC_Team team, int memberID, bool is_summon);
void apply_ability_effect(Player *main_character ,Abilities player_ability);
void free_team(NPC_Team *team);
void open_inventory(Player *main_character);
int open_abilities(Player *main_character);
void use_item(Player *main_character, int item_id);
Player use_ability(Player main_character, NPC *target_npc, int abilityID);
NPC npc_apply_ability(NPC npc, int abilityID);
Player apply_item_effects(Player main_character, Items item);
Player remove_item_effects(Player main_character, Items item);
Player sort_items(Player main_character);
Player check_hunger(Player main_character);
Player increase_hunger(Player main_character, int amount);
Player decrease_hunger(Player main_character, int amount);
Player heal_player(Player main_character, int amount);
Player restore_mana(Player main_character);
Player add_mana_type(Player main_character, int mana_type);
Player remove_mana_type(Player main_character, int mana_type);
int exp_reward_for_npc(NPC npc);
float rank_exp_multiplier(int rank);
//Utilitie Functions
Abilities* get_ability_by_id(int id);
NPC* get_npc_by_id(int id);
Items* get_items_by_id(int id);
NPC *get_summon_by_id(int id);

extern Abilities ALL_abilities[TOTAL_ABILITIES];
extern NPC ALL_summons[TOTAL_SUMMONS];
extern NPC ALL_npc[TOTAL_NPC];
extern Items ALL_items[TOTAL_ITEMS];


//Playing Functions
Player play_chapter(Player main_character, Story *story, int *chapter_npc_ids);

#endif
