#ifndef MECHANICS_H
#define MECHANICS_H
#include <stdbool.h>
#include "menu.h"

#define TOTAL_ABILITIES 21
#define TOTAL_MAGIC 14
#define TOTAL_Melle 2
#define TOTAL_ITEMS 21
#define TOTAL_WEAPONS 17
#define TOTAL_CONSUMABLES 3
#define TOTAL_KEY_ITEMS 1
#define TOTAL_SUMMONS 2
#define TOTAL_NPC 10
#define MAX_EQUIPPED_ITEMS 5
#define MAX_START_ITEMS    8
#define MAX_START_ABILITIES 4
#define MAX_START_SUMMONS  2

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

typedef enum{
    Assassin,
    Tank,
    Monk,
    Ninja,
    Mage,
    Healer,
    Summoner,
    Balanced,
    BUILD_COUNT, // Keep this as the last element to track the count of builds
}Builds;

typedef enum{
    WEAPON,
    CONSUMABLE,
    KEY,
}Item_Types;

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
    ELEMENTAL_AFFINITY_COUNT, // Keep this as the last element to track the count of affinities
}Elemental_Affinity;

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
    COPY, 
    REVEAL,
    POISON,
    BURN,
    FREEZE,
    PARALYSE,
}EFFECT_TYPE;

typedef struct initial_build_attributes{
    int DEFENCE;
    int MAX_HP;
    int MAX_MANA;
    int SUMMONS_STORAGE;
    int MAGIC_POWER;
    int WEAPON_DAMAGE;
    int DAMAGE;
    int SPEED;
    int STEALTH;
    int PERCEPTION;
    bool WEAPON_USER;
    bool DUAL_WILDING;
    bool MAGIC_USER;
}Attributes;

typedef struct {
    Attributes stats;
    int items[MAX_START_ITEMS];      // item IDs, -1 terminated
    int abilities[MAX_START_ABILITIES]; // ability IDs, -1 terminated
    int summons[MAX_START_SUMMONS];  // summon IDs, -1 terminated
} BuildDef;

typedef struct {
    int *stat;
    int hp_bonus;
    int mana_bonus;
} StatUpgrade;


typedef struct player_abilities{
    int ID;
    char *NAME;
    int MANA_COST;
    int RANK;
    int DNA;
    char *DESCRIPTION;
    int turns_remaining; // For temporary effects, track remaining turns DEFAULT 0
    char *EFFECT; 
    int EFFECT_TYPE;
}Abilities;

typedef struct active_ability_effect{
    int ability_id;
    int turns_remaining;
}ActiveAbilityEffect;

typedef struct melee{
    int ability_id;
    int damage;
    int mana_type;
}Melee;

typedef struct magic{
    int ability_id;
    int damage;
    int mana_type;
}Magic;

typedef struct infused{
    int ability_id;
    int damage;
    int mana_type;
}Infused;

typedef struct summon{
    int ability_id;
    int damage;
    int mana_type;
}Summon;

typedef struct support{
    int ability_id;
    int healing;
    int mana_restoration;
    bool team_effect;
}Support;

typedef enum{
    Inate, // Unique to the character no one else can learn it
    All, // Can be learned by any other characters
    Minamoto, // Only learned by Minamoto Clan members (Shadow Dog)
    Sharingan, // Only learned by Sharingan users 
    MS_1,//(Amaterasu)
    MS_2,//(Tsukuyomi)
}DNA_Neded;

typedef enum{
    AbilityClass_Melee,
    AbilityClass_Magic,
    AbilityClass_Infused,
    AbilityClass_Summon,
    AbilityClass_Support,
}Ability_Class;

typedef struct items{
    int ID;
    char *name; 
    const char *description;
    int item_type;
}Items;

typedef struct weapon{
    int item_id;
    int equip_slot; // MAIN_HAND, OFF_HAND, HEAD, CHEST, LEGS, SHOES
    const char *effect;
}Weapon;

typedef struct consumable{
    int item_id;
    int healling;
    int mana_restoration;
    int hunger_restoration;
}Consumable;

typedef struct key_item{
    int item_id;
    const char *use_description;
}Key_Item;

typedef struct other_characters{
    // Basic info
    int ID;
    int age;
    char *name;
    // Lists
    int* Ability_ids;
    int* summonIDs;
    // Amounts
    int abilities_ammount;
    int summons_ammount;
    // Combat attributes
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
    int ELEMENTAL_AFFINITY;
}NPC;

typedef struct player {
    // Basic info
    char *name;
    char *hair_colour;
    int age;
    int gender;
    // Game attributes
    int money;
    int build;
    // Lists
    int* summonIDs;
    int* abilitiesIDs;
    int* inventoryIDs;
    int* equipped_items; // Array to track equipped items (size 4 for armor slots + 1 for weapon)
    int* mana_elements;
    int* DNA;
    // Amounts
    int DNA_ammount;
    int mana_elements_ammount;
    int item_ammount;
    int abilities_ammount;
    int summons_ammount;
    // Combat attributes
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
    // Team info
    int *team_memberIDs; // IDs of NPCs in the player's team
    int team_size;
    int *team_member_hp;   // Current HP per team member
    int *team_member_mana; // Current MANA per team member
    // Active ability effects
    ActiveAbilityEffect active_effects[TOTAL_ABILITIES];
    int active_effect_count;
} Player;

//Build Character Functions
Player character_creation(void);
Player set_mc_build(Player main_character,int build_id);
Player set_mc_stats(Player main_character, Attributes new_stats);
void get_attributes(Player *main_character);
const char *gender_to_string(Gender g);

//Getters for player attributes
int get_mc_build(Player main_character);
int get_mc_max_hp(Player main_character);
int get_mc_max_mana(Player main_character);
int get_mc_summons_storage(Player main_character);
int get_mc_speed(Player main_character);
int get_mc_stealth(Player main_character);
int get_mc_weapon_damage(Player main_character);
bool is_weapon_user(Player main_character);
bool is_dual_wielding(Player main_character);
bool is_magic_user(Player main_character);
char *get_mc_name(Player main_character);
char *get_mc_hair_colour(Player main_character);
int get_mc_age(Player main_character);
int get_mc_gender(Player main_character);
int get_mc_money(Player main_character);
int get_mc_hp(Player main_character);
int get_mc_mana(Player main_character);
int get_mc_hunger(Player main_character);
int get_mc_skill_points(Player main_character);
int get_mc_level(Player main_character);
int get_mc_exp(Player main_character);
int get_mc_goodness(Player main_character);
int get_mc_rank(Player main_character);
int get_mc_team_size(Player main_character);
int* get_mc_team_memberIDs(Player main_character);
int* get_mc_team_member_hp(Player main_character);
int* get_mc_team_member_mana(Player main_character);
int* get_mc_inventoryIDs(Player main_character);
int* get_mc_abilitiesIDs(Player main_character);
int* get_mc_summonIDs(Player main_character);
int *get_mc_equipped_items(Player main_character);
int* get_mc_mana_elements(Player main_character);
int get_mc_mana_elements_ammount(Player main_character);
int* get_mc_DNA(Player main_character);
int get_mc_DNA_ammount(Player main_character);
int get_mc_summons_ammount(Player main_character);
int get_mc_item_ammount(Player main_character);
int get_mc_abilities_ammount(Player main_character);
Attributes get_mc_attributes(Player main_character);

//Setters/increasers for player attributes
Player increase_mc_stealth(Player main_character, int amount);
Player increase_mc_speed(Player main_character, int amount);
Player increase_mc_summons_storage(Player main_character, int amount);
Player increase_mc_magic_power(Player main_character, int amount);
Player increase_mc_weapon_damage(Player main_character, int amount);
Player increase_mc_defence(Player main_character, int amount);
Player increase_mc_damage(Player main_character, int amount);
Player increase_mc_perception(Player main_character, int amount);
Player set_mc_stats(Player main_character, Attributes new_stats);
Player set_mc_build(Player main_character, int build_id);
Player set_mc_level(Player main_character, int new_level);
Player set_mc_exp(Player main_character, int new_exp);
Player set_mc_skill_points(Player main_character, int sp);
Player set_mc_stats(Player main_character, Attributes new_stats);

//DNA
Player add_DNA(Player main_character, int DNA_ID);
Player remove_DNA(Player main_character, int DNA_ID);

// Mana type functions
Player add_mana_type(Player main_character, int mana_type);
Player remove_mana_type(Player main_character, int mana_type);
int has_mana_type(Player main_character, int mana_type);

//Hunger
Player increase_hunger(Player main_character, int amount);
Player decrease_hunger(Player main_character, int amount);

//Health and Mana management
Player heal_player(Player main_character, int amount);
Player add_Mana(Player main_character, int amount);
Player restore_mana(Player main_character);
Player change_mc_goodness(Player main_character, int change);

//Leveling and experience
int exp_reward_for_npc(NPC npc);
float rank_exp_multiplier(int rank);
Player level_up(Player main_character);
NPC level_up_rival(NPC rival, int target_level);

//Utilitie Functions
Abilities get_ability_by_id(int id);
NPC get_npc_by_id(int id);
Items get_items_by_id(int id);
NPC get_summon_by_id(int id);
Weapon get_weapon(int id);
Consumable get_consumable(int id);
char* get_ability_name(int ability_id);
int get_ability_id(Abilities ability);
int get_ability_effect_duration(int ability_id);

//Getters for ability attributes
int get_ability_by_summon(int summonID);
int get_ability_damage_value(int ability_id);
int get_ability_healing_value(int ability_id);
int get_ability_mana_type(int ability_id);
Ability_Class get_ability_class(int ability_id);
EFFECT_TYPE get_ability_effect_type(int ability_id);
const char *get_ability_effects(int ability_id);
int get_ability_mana_cost(int ability_id);
int get_ability_rank(int ability_id);
int get_ability_by_summon_id(int summon_id);
int get_ability_dna(int ability_id);

//Object arrays and Element chart
extern const Abilities ALL_abilities[TOTAL_ABILITIES];
extern const NPC ALL_summons[TOTAL_SUMMONS];
extern const NPC ALL_npc[TOTAL_NPC];
extern const Items ALL_items[TOTAL_ITEMS];
extern const Weapon ALL_weapons[TOTAL_WEAPONS];
extern const Consumable ALL_consumables[TOTAL_CONSUMABLES];
extern const Key_Item ALL_key_items[TOTAL_KEY_ITEMS];
extern const float elemental_chart[ELEMENTAL_AFFINITY_COUNT][ELEMENTAL_AFFINITY_COUNT];

//Player menu and stats
Player player_stats(Player main_character);
void open_player_menu(Player *main_character);

//Playing Functions
Player play_chapter(Player main_character, Story *story, int *chapter_npc_ids);

#endif
