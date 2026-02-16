#ifndef ABILITIES_H
#define ABILITIES_H
#include "mechanics.h"

//Ability management
Player add_ability(Player main_character, int abilityID);
Player remove_ability(Player main_character, int abilityID);

//Active ability effects management
void apply_ability_effect(Player *main_character, Abilities ability, NPC *target_npc);
void apply_copy_ability(Player *main_character, NPC *target_npc);
void register_active_ability(Player *main_character, Abilities ability);
void refresh_active_ability_effects(Player *main_character, Attributes base_stats, NPC *current_enemy);
void clear_active_ability_effects(Player *main_character);

//Abilities menu
void open_abilities(Player *main_character);
int choose_ability(Player *main_character);

//Ability usage
Player use_ability(Player main_character, NPC *target_npc, int abilityID);
NPC npc_apply_ability(NPC npc, int abilityID);

#endif
