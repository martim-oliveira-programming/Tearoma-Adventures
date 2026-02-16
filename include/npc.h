#ifndef NPC_H
#define NPC_H
#include "mechanics.h"

//Summons
Player add_summon(Player main_character, int summonID);
Player remove_summon(Player main_character, int summonID);

//Team management
char* team_names(Player main_character);
Player add_team_member(Player main_character, int memberID, bool is_summon_member);
Player remove_team_member(Player main_character, int memberID, bool is_summon_member);
int is_team_member(Player main_character, int memberID);
int is_team_member_summon(Player main_character, int memberID);
int is_summon(int memberID);
void free_team(Player *main_character);

//NPC helpers
NPC heal_npc(NPC npc, int heal_amount);

#endif
