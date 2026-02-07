#ifndef FIGHTS_H
#define FIGHTS_H
#include <stdbool.h>
#include "story.h"
#include "mechanics.h"

Player fight(Player main_character, NPC enemy, Story *story,int* chapter_npc_ids,bool can_run);
Player my_turn(Player main_character,NPC *enemy,Story *story,int* chapter_npc_ids,bool can_run);
Player enemy_turn(Player main_character, NPC enemy);
Player damage_player(Player main_character, int amount);
int priority_calculation(Player main_character, NPC npc,int turn);
int check_alive(Player *main_character, Story *story,int* chapter_npc_ids);
int check_win(NPC npc, Player *main_character);
NPC damage_npc(NPC npc, int damage_amount);
int damage_calculation(Player main_character, NPC npc);
int damage_calculation_with_ability(Player main_character, NPC npc, int ability_damage);
int npc_damage_calculation(NPC npc, Player main_character);
int npc_damage_calculation_with_ability(NPC npc, int ability_damage, Player main_character);


#endif
