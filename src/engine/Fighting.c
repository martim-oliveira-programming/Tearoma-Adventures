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
#include <time.h> 

void ensure_team_arrays(Player *player) {
    if (!player) return;
    if (player->team_size <= 0) return;
    if (!player->team_member_hp) {
        player->team_member_hp = calloc(player->team_size, sizeof(int));
    }
    if (!player->team_member_mana) {
        player->team_member_mana = calloc(player->team_size, sizeof(int));
    }
    for (int i = 0; i < player->team_size; i++) {
        int member_id = player->team_memberIDs[i];
        NPC member = (member_id >= 100) ? get_summon_by_id(member_id) : get_npc_by_id(member_id);
        if (player->team_member_hp) {
            if (player->team_member_hp[i] <= 0) {
                player->team_member_hp[i] = member.HP > 0 ? member.HP : member.MAX_HP;
            }
        }
        if (player->team_member_mana) {
            if (player->team_member_mana[i] <= 0) {
                player->team_member_mana[i] = member.MANA > 0 ? member.MANA : member.MAX_MANA;
            }
        }
    }
}

Player fight(Player main_character, NPC enemy, Story *story,int* chapter_npc_ids,bool can_run) {
    int npc_ids_size = chapter_npc_ids ? 1 : 0; // chapter_npc_ids is always a single-element array from main.c
    Attributes pre_fight_stats = main_character.stats; // snapshot to clear temporary ability buffs at fight end
    NPC enemy_base = enemy; // snapshot to restore enemy stats when debuffs expire
    clear_active_ability_effects(&main_character);
    ensure_team_arrays(&main_character);
    int turn = 1;
    int mc_hp = get_mc_hp(main_character);
    if (mc_hp <= 0) {
        say(0,"You don't have enough HP to fight %s...\n", enemy.name);
        return lost_fight(main_character,story, chapter_npc_ids);
    }
    main_character = increase_hunger(main_character, 5);
    while(main_character.HP > 0 && !check_win(enemy, &main_character)) {

        main_character = increase_hunger(main_character, 2);
        refresh_active_ability_effects(&main_character, pre_fight_stats, &enemy, enemy_base);
        
        print_fight_info(main_character, enemy);

        int priority = priority_calculation(main_character, enemy, turn);

        if(priority >= 1 || (priority == 0 && turn%2!=0)) { // Player goes first, ties favor the player on the odd turns
            say(0,"\nIt's your turn first!\n");
            print_fight_info(main_character, enemy);
            main_character = my_turn(main_character,&enemy,story,chapter_npc_ids,can_run);
            if (check_win(enemy, &main_character)) {
                say(1,"You defeated %s!\n", enemy.name);
                break;
            }
            main_character = team_turn(main_character, &enemy); // Allow team to act if player has speed advantage
            if (check_win(enemy, &main_character)) {
                say(2,"You and your team defeated %s!\n", enemy.name);
                break;
            }

            if(priority == 2) {
                say(1,"\nYour speed advantage lets you act again!\n");
                print_fight_info(main_character, enemy);
                main_character = my_turn(main_character,&enemy,story,chapter_npc_ids,can_run);
                if(check_win(enemy, &main_character)) {
                    say(0,"You defeated %s!\n", enemy.name);
                    break;
                }
                main_character = team_turn(main_character, &enemy); // Allow team to act again if player has very high speed
                if (check_win(enemy, &main_character)) {
                    say(1,"You and your team defeated %s!\n", enemy.name);
                    break;
            }

            say(1,"\nIt's %s's turn!\n", enemy.name);
            
            if(priority != 3){
            main_character = enemy_turn(main_character, enemy);
            }else{
                say(1,"%s's is frozen and can't move!\n", enemy.name);
            }
        } 
    } else { // NPC goes first or ties favor the NPC on even turns
            say(1,"\n%s is faster and takes the first turn!\n", enemy.name);
            main_character = enemy_turn(main_character, enemy);
            if (main_character.HP <= 0) {
                say(1,"You were defeated by %s...\n", enemy.name);
                break;
            }
            sleep(2);
            print_fight_info(main_character, enemy);
            say(1,"\nIt's your turn!\n");
            main_character = my_turn(main_character,&enemy,story,chapter_npc_ids,can_run);
            main_character = team_turn(main_character, &enemy);
            if (check_win(enemy, &main_character)) {
                say(0,"You and your team defeated %s!\n", enemy.name);
                break;
            }
        }
        turn++;
    }
    main_character = reset_stats(main_character, pre_fight_stats); // Clear any temporary buffs/debuffs after the fight
    main_character = restore_mana(main_character); // Regenerate some mana after the fight
    clear_active_ability_effects(&main_character); // Clear any remaining active effects
    free_team(&main_character); // Free team member arrays to clear any defeated members and reset for next fight
    main_character = build_team(main_character, chapter_npc_ids, npc_ids_size); // Rebuild team based on current chapter's NPCs (some may have been defeated and removed)
    return main_character; // Return the updated player state after combat
}

int load_last_save(Story *story, Player *player, int *chapter_npc_ids) {
    int status = load_save(story, player, chapter_npc_ids);
    if (!status) {
        say(0,"No save file found or failed to load.\n");
        return 0;
    }
    return 1;
}

void print_fight_info(Player main_character, NPC enemy) {
    say(0,"\n%s's HP: %d, ", enemy.name, enemy.HP);
        if(main_character.stats.PERCEPTION > enemy.LEVEL){
            say(0,"MANA: %d", enemy.MANA);
        }
        
        say(0,"\n\nYour HP: %d, MANA: %d\n", main_character.HP, main_character.MANA);
        if (main_character.team_size > 0) {
            say(0,"Team Status:\n");
            for (int i = 0; i < main_character.team_size; i++) {
                int member_id = main_character.team_memberIDs[i];
                NPC member = (member_id >= 100) ? get_summon_by_id(member_id) : get_npc_by_id(member_id);
                int cur_hp = main_character.team_member_hp ? main_character.team_member_hp[i] : member.HP;
                int cur_mana = main_character.team_member_mana ? main_character.team_member_mana[i] : member.MANA;
                if (member.ID >= 0) {
                    say(0,"  %s - HP: %d/%d", member.name, cur_hp, member.MAX_HP);
                    if (member.MAX_MANA > 0) {
                        say(0,", MANA: %d/%d", cur_mana, member.MAX_MANA);
                    }
                    say(0,"\n");
                }
            }
        }
        sleep(1);
}

Player reset_stats(Player main_character, Attributes base_stats) {
    main_character = set_mc_stats(main_character, base_stats);
    return main_character;
}

Player my_turn(Player main_character,NPC *enemy,Story *story,int* chapter_npc_ids,bool can_run) {
    char *action = get_input("Choose your action (Attack (D)/Use Ability (A)/Use Item (I)/Charge MANA (C)):\n");
        if (strcmp(action, "D") == 0) {
            int damage = damage_calculation(main_character, *enemy);
            *enemy = damage_npc(*enemy, damage);
            say(0,"You dealt %d damage to %s!\n", damage, enemy->name);
        } 
        else if (strcmp(action, "A") == 0) {
            int abilityID = choose_ability(&main_character);
            if (abilityID >= 0) {
                main_character = use_ability(main_character, enemy, abilityID);
                Abilities used = get_ability_by_id(abilityID);
                if (used.ID >= 0) {
                    say(0,"You used %s!\n", used.NAME);
                }
            }else if (abilityID == -2) {
                say(0,"You exited the abilities menu.\n");
                return my_turn(main_character, enemy, story, chapter_npc_ids, can_run); // Ask for input again
            }
        } 
        else if (strcmp(action, "I") == 0) {
            Player temp_character = main_character; // Create a temporary copy
            say(0,"You rummage through your inventory...\n");
            open_inventory(&main_character);
            if (temp_character.HP == main_character.HP && temp_character.MANA == main_character.MANA) {
                return my_turn(main_character, enemy, story, chapter_npc_ids, can_run); // No change, ask for input again
            } 
        }
        else if (strcmp(action, "Run") == 0) {
            say(0,"You attempt to run away...\n");
            // Placeholder for escape logic
        } 
        else if(strcmp(action, "C") == 0) {
            main_character = restore_mana(main_character);
            say(0,"You focus and restore some MANA!\n");
        }
        else {
            say(0,"Invalid action. Please choose Attack, Use Ability, Use Item, or Run.\n");
        }
    free(action);


    return main_character;
}

Player team_turn(Player main_character, NPC *enemy) {
    if(main_character.team_size == 0){
        return main_character; // No team members to act
    }
    say(0,"\nYour team members take their actions!\n");
    for(int i = 0; i < main_character.team_size; i++){
        int memberID = main_character.team_memberIDs[i];
        if(is_team_member_summon(main_character,memberID)){ // Check if it's a summon
            NPC summon = get_summon_by_id(memberID);
            const char *name = (summon.ID >= 0 && summon.name) ? summon.name : "Unknown summon";
            say(0,"%s the summon attacks!\n", name);
            summon = team_member_action(summon, enemy);
            if(check_win(*enemy, &main_character)) {
                say(0,"Your summon %s defeated %s!\n", name, enemy->name);
                break;
            }
        } 
        else if (is_team_member_summon(main_character,memberID)==0 && is_team_member(main_character,memberID)){ // Check if it's an NPC ally
            NPC ally = get_npc_by_id(memberID);
            const char *name = (ally.ID >= 0 && ally.name) ? ally.name : "Unknown ally";
            say(0,"%s the ally attacks!\n", name);
            ally = team_member_action(ally, enemy);
            if(check_win(*enemy, &main_character)) {
                say(0,"Your ally %s defeated %s!\n", name, enemy->name);
                break;
            }
        }
    }
    return main_character;
}

NPC team_member_action(NPC member, NPC *enemy) {
    const char *member_name = (member.ID >= 0 && member.name) ? member.name : "Unknown";
    const char *enemy_name = (enemy && enemy->name) ? enemy->name : "the enemy";
    say(0,"%s is taking action against %s!\n", member_name, enemy_name);
    if (!enemy) {
        return member;
    }
    int damage = damage_calculation_team_member(member, *enemy);
    *enemy = damage_npc(*enemy, damage);
    say(0,"%s dealt %d damage to %s!\n", member_name, damage, enemy_name);
    return member; // Return updated member state if needed
}

Player enemy_turn(Player main_character, NPC enemy) {
    ensure_team_arrays(&main_character);
    int random_value = rand() % 100; // Random number between 0 and 99 for decision making
    int attack_member = rand() % (main_character.team_size + 1); // Randomly decide to attack player or a team member
    say(0,"%s is preparing to attack you!\n", enemy.name);
    int damage = npc_damage_calculation(enemy, main_character);
    for (int i = 0; i < enemy.abilities_ammount; i++) {
        Abilities ability = get_ability_by_id(enemy.Ability_ids[i]);
        int ability_damage = get_ability_damage_value(ability.ID);
        if (ability.ID >= 0 && ability_damage > 0) {
            int potential_damage = npc_damage_calculation_with_ability(enemy, ability_damage, main_character);
            if (potential_damage > damage) {
                damage = potential_damage;
            }
        }
    }  
    if (random_value % 2 ==0 || main_character.team_size == 0 ){
    main_character = damage_player(main_character, damage);
    }else{ // Attack a team member instead
        if (attack_member > 0 && attack_member <= main_character.team_size) {
            int memberID = main_character.team_memberIDs[attack_member - 1];
            if (is_team_member_summon(main_character,memberID)) { // Summon
                NPC summon = get_summon_by_id(memberID);
                int team_damage = damage_calculation_team_member(enemy, summon);
                int idx = attack_member - 1;
                int current_hp = (main_character.team_member_hp && main_character.team_member_hp[idx] > 0)
                                  ? main_character.team_member_hp[idx]
                                  : summon.HP;
                int remaining_hp = current_hp - team_damage;
                if (main_character.team_member_hp) {
                    main_character.team_member_hp[idx] = remaining_hp;
                }
                say(0,"%s attacked your summon %s for %d damage!\n", enemy.name, summon.name, team_damage);
                if (remaining_hp <= 0) {
                    say(0,"Your summon %s has been defeated!\n", summon.name);
                    remove_dead_ally(&main_character, summon); // Handle summon defeat
                }
            } 
            else if (is_team_member(main_character, memberID) && is_team_member_summon(main_character,memberID) == 0) { // NPC ally
                NPC ally = get_npc_by_id(memberID);
                int team_damage = damage_calculation_team_member(enemy, ally);
                int idx = attack_member - 1;
                int current_hp = (main_character.team_member_hp && main_character.team_member_hp[idx] > 0)
                                  ? main_character.team_member_hp[idx]
                                  : ally.HP;
                int remaining_hp = current_hp - team_damage;
                if (main_character.team_member_hp) {
                    main_character.team_member_hp[idx] = remaining_hp;
                }
                say(0,"%s attacked your ally %s for %d damage!\n", enemy.name, ally.name, team_damage);
                if (remaining_hp <= 0) {
                    say(0,"Your ally %s has been defeated!\n", ally.name);
                    main_character = remove_team_member(main_character, ally.ID, false);
                }
            }
        } else {
            main_character = damage_player(main_character, damage);
            say(0,"%s dealt %d damage to you!\n", enemy.name, damage);
        }
    }
    return main_character;
}

int priority_calculation(Player main_character, NPC npc,int turn) {
    int player_speed = get_mc_speed(main_character);
    int player_stealth = get_mc_stealth(main_character);
    int npc_speed = npc.SPEED;
    if (npc_speed == 0){return 3;} // NPC is frozen and can't move, player automatically goes first without needing to check speed
    
    if (turn == 1){
        player_speed += player_stealth / 1.5; // Stealth gives a significant boost to speed on the first turn
    }
    if (player_speed/2 > npc_speed){
        return 2; //Player moves twice before NPC
    }
    else if (player_speed > npc_speed) {
        return 1; // Player goes first
    } else if (npc_speed > player_speed) {
        return -1; // NPC goes first
    } else {
        return 0; // Tie, decide randomly
    }
}

int check_alive(Player *main_character) {
    if (main_character->HP <= 0) {
        return 0; // Player is dead
    }
    return 1; // Player is alive
}

int check_win(NPC npc, Player *main_character) {
    if (npc.HP <= 0) {
        main_character->EXP += exp_reward_for_npc(npc);
        return 1; // NPC is defeated
    }
    return 0; // NPC is still alive
}

int check_ally_alive(NPC ally) {
    if (ally.HP <= 0) {
        return 0; // Ally is dead
    }
    return 1; // Ally is alive
}

void remove_dead_ally(Player *main_character, NPC ally) {
    if (!check_ally_alive(ally) && is_team_member(*main_character, ally.ID)&& ally.ID!= 101) { // Check if it's an NPC ally (not a summon) and is in the team. Fire Spirit summon (ID 101) is a special case that doesn't get removed on defeat
        if (is_team_member_summon(*main_character, ally.ID)) {
            *main_character = remove_summon(*main_character, ally.ID);
            *main_character = remove_ability(*main_character, get_ability_by_summon_id(ally.ID)); // Remove associated ability when summon is defeated
        }
        say(0,"Your ally %s has been defeated!\n", ally.name);
        *main_character = remove_team_member(*main_character, ally.ID, false);
    }
}

Player damage_player(Player main_character, int damage_amount) {
    int dodge_chance = main_character.stats.STEALTH;
    if (dodge_chance < 0) dodge_chance = 0;
    if (dodge_chance > 99) dodge_chance = 99;
    int random_value = rand() % 100; // Generate a random number between 0 and 99
    
    if (random_value < dodge_chance) {
        say(0,"You dodged the attack!\n");
        return main_character; // No damage taken
    }
    
    main_character.HP -= damage_amount;
    return main_character;
}

NPC damage_npc(NPC npc, int damage_amount) { //Always call damage_amount with the damage_calculation functions.
    npc.HP -= damage_amount;
    return npc;
}

int damage_calculation_team_member(NPC member, NPC enemy) {
    int damage = member.DAMAGE - enemy.DEFENCE;
    if (damage < 1) {
        damage = 1; // Ensure allies/summons chip away at tough foes
    }
    damage *= 5;
    return damage;
}

int team_damage_calculation_with_ability(NPC member, int ability_damage, NPC enemy) {
    int damage = member.DAMAGE + ability_damage - enemy.DEFENCE;
    if (damage < 1) {
        damage = 1;
    }
    damage *= 5;
    return damage;
}

int damage_calculation_internal(Player main_character, NPC npc, int ability_damage, int ability_class,int ability_element) {
    int total_damage = ability_damage;
    
    if (ability_class == -1) { // Basic attack, add weapon damage if applicable
        total_damage += main_character.stats.DAMAGE * 5; // Basic attacks scale with overall damage stat
    }
    if (ability_damage > 0 && ability_class == AbilityClass_Magic) { // Only add magic power for magic abilities
        total_damage += main_character.stats.MAGIC_POWER; // Abilities scale with magic power
        }
    if (main_character.weapon >= 0 && (ability_class == AbilityClass_Melee || ability_class == -1)) { // Only add weapon damage for melee abilities or basic attacks
        total_damage += main_character.stats.WEAPON_DAMAGE;
    }
    if (ability_class == AbilityClass_Infused) { // Infused abilities scale with both weapon damage and magic power
        total_damage += main_character.stats.WEAPON_DAMAGE;
        total_damage += main_character.stats.MAGIC_POWER;
    }
    total_damage *= elemental_chart[ability_element][npc.ELEMENTAL_AFFINITY]; // Apply elemental multiplier

    total_damage -= npc.DEFENCE;
    if (total_damage < 1) {
        total_damage = 1;
    }
    return total_damage;
}

int damage_calculation(Player main_character, NPC npc) {
    return damage_calculation_internal(main_character, npc, 0,-1,0);
}

int damage_calculation_with_ability(Player main_character, NPC npc, int ability_damage, int ability_class,int ability_element) {
    return damage_calculation_internal(main_character, npc, ability_damage, ability_class, ability_element);
}

int npc_damage_calculation(NPC npc, Player main_character) {
    int damage = (npc.DAMAGE-main_character.stats.DEFENCE)*5;
    if (damage < 1) {
        damage = 1; // Ensure NPCs always deal at least some damage
    }
    return damage;
}

int npc_damage_calculation_with_ability(NPC npc, int ability_damage, Player main_character) {
    int damage = (npc.DAMAGE - main_character.stats.DEFENCE) * 5;
    damage += ability_damage; // Add ability damage on top of NPC's base damage
    if (damage < 1) {
        damage = 1; // Ensure NPCs always deal at least some damage
    }
    return damage;
}

int heal_calculation(Player main_character, int heal_amount) {
    heal_amount += main_character.stats.MAGIC_POWER; 
    return heal_amount; // Return integer heal; integer division already floors
}

Player lost_fight(Player main_character, Story *story, int *chapter_npc_ids) {
    if(!check_alive(&main_character)){
            load_last_save(story, &main_character, chapter_npc_ids); // Reload last save if player died
            return play_chapter(main_character, story, chapter_npc_ids); // Restart chapter if player dies
        }
    return main_character; // Player is still alive, return current state
}
