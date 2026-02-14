#ifndef FIGHTS_H
#define FIGHTS_H
#include <stdbool.h>
#include "story.h"
#include "mechanics.h"

// Main fight function that handles the entire fight loop and logic, returns the updated player state after the fight concludes
Player fight(Player main_character, NPC enemy, Story *story,int* chapter_npc_ids,bool can_run);

// Individual turn functions for player, team, and enemy actions
Player my_turn(Player main_character,NPC *enemy,Story *story,int* chapter_npc_ids,bool can_run);
Player enemy_turn(Player main_character, NPC enemy);
Player team_turn(Player main_character, NPC *enemy);
NPC team_member_action(NPC member, NPC *enemy);

// Utility functions for combat mechanics
int priority_calculation(Player main_character, NPC npc,int turn);

// Functions to check combat status
int check_alive(Player *main_character);
int check_win(NPC npc, Player *main_character);

// Print current fight status (HP, MANA, team status)
void print_fight_info(Player main_character, NPC enemy);

// Reset player stats after fight to clear temporary buffs/debuffs
Player reset_stats(Player main_character, Attributes base_stats);

// Damage Functions
Player damage_player(Player main_character, int amount);
NPC damage_npc(NPC npc, int damage_amount);

// Damage calculation functions
int damage_calculation(Player main_character, NPC npc);
int damage_calculation_with_ability(Player main_character, NPC npc, int ability_damage, int ability_class,int ability_element);

int npc_damage_calculation(NPC npc, Player main_character);
int npc_damage_calculation_with_ability(NPC npc, int ability_damage, Player main_character);

int damage_calculation_team_member(NPC member, NPC enemy);
int team_damage_calculation_with_ability(NPC member, int ability_damage, NPC enemy);

// Healing calculation function
int heal_calculation(Player main_character, int heal_amount);

// Load last save function to reload player state if they die in combat
int load_last_save(Story *story, Player *player, int *chapter_npc_ids);
Player lost_fight(Player main_character, Story *story, int *chapter_npc_ids);

// Function to check if an ally (NPC) is still alive and handle their defeat if not
int check_ally_alive(NPC ally);
void remove_dead_ally(Player *main_character, NPC ally);

#endif
