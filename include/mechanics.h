#ifndef MECHANICS_H
#define MECHANICS_H
#include <stdbool.h>
#include "story.h"

#define TOTAL_ABILITIES 16
#define TOTAL_MAGIC 9
#define TOTAL_Melle 2
#define TOTAL_ITEMS 21
#define TOTAL_WEAPONS 17
#define TOTAL_CONSUMABLES 3
#define TOTAL_KEY_ITEMS 1
#define TOTAL_SUMMONS 2
#define TOTAL_NPC 10
#define MAX_EQUIPPED_ITEMS 5

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
    //TODO: Implement Freeze, Burn, Poison, Paralises temporary debuffs, and other interesting effects
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
    Learned, // Can be learned by any other characters
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
Player character_creation();
Builds parse_build(const char *s);
void get_attributes(Player *main_character);
const char *gender_to_string(Gender g);

//Inventory Management
Player add_inventory(Player main_character, int itemID, int amount);
Player remove_inventory(Player main_character, int itemID, int amount);

//Abilities 
Player add_ability(Player main_character, int abilityID);
Player remove_ability(Player main_character, int abilityID);
char* get_ability_name(int ability_id);

// Items
Player equip_item(Player main_character, int itemID);
Player unequip_item(Player main_character, int slot);

// Summons
Player add_summon(Player main_character, int summonID);
Player remove_summon(Player main_character, int summonID);

//DNA
Player add_DNA(Player main_character, int DNA_ID);
Player remove_DNA(Player main_character, int DNA_ID);

// Team management
char* team_names(Player main_character);
Player add_team_member(Player main_character, int memberID, bool is_summon_member);
Player remove_team_member(Player main_character, int memberID, bool is_summon_member);
int is_team_member(Player main_character, int memberID);
int is_team_member_summon(Player main_character, int memberID);
int is_summon(int memberID);
void free_team(Player *main_character);

// Active ability effects management
void apply_ability_effect(Player *main_character, Abilities ability, NPC *target_npc);
void apply_copy_ability(Player *main_character, NPC *target_npc);
void register_active_ability(Player *main_character, Abilities ability);
void refresh_active_ability_effects(Player *main_character, Attributes base_stats, NPC *current_enemy);
void clear_active_ability_effects(Player *main_character);

// Inventory and abilities menu functions
void open_inventory(Player *main_character);
void open_abilities(Player *main_character);
int choose_ability(Player *main_character);
int player_stats(Player main_character);
void open_player_menu(Player *main_character);

// Item functions
void use_item(Player *main_character, int item_id);
void use_consumable(Player *main_character, int item_id);
Player apply_weapon_effects(Player main_character, Weapon weapon);
Player remove_weapon_effects(Player main_character, Weapon weapon);
Player sort_items(Player main_character);

int is_consumable_item(int item_id);
int is_key_item(int item_id);
int is_weapon_item(int item_id);

// Ability usage functions
Player use_ability(Player main_character, NPC *target_npc, int abilityID);
NPC npc_apply_ability(NPC npc, int abilityID);

// Mana type functions
Player add_mana_type(Player main_character, int mana_type);
Player remove_mana_type(Player main_character, int mana_type);
int has_mana_type(Player main_character, int mana_type);

//Hunger
Player check_hunger(Player main_character);
Player increase_hunger(Player main_character, int amount);
Player decrease_hunger(Player main_character, int amount);

//Health and Mana management
Player heal_player(Player main_character, int amount);
Player add_Mana(Player main_character, int amount);
Player restore_mana(Player main_character);

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

//Object arrays ND Element chart
extern const Abilities ALL_abilities[TOTAL_ABILITIES];
extern const NPC ALL_summons[TOTAL_SUMMONS];
extern const NPC ALL_npc[TOTAL_NPC];
extern const Items ALL_items[TOTAL_ITEMS];
extern const Weapon ALL_weapons[TOTAL_WEAPONS];
extern const Consumable ALL_consumables[TOTAL_CONSUMABLES];
extern const Key_Item ALL_key_items[TOTAL_KEY_ITEMS];
extern const float elemental_chart[ELEMENTAL_AFFINITY_COUNT][ELEMENTAL_AFFINITY_COUNT];


//Playing Functions
Player play_chapter(Player main_character, Story *story, int *chapter_npc_ids);

#endif
