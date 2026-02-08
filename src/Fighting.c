#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "story.h"
#include "mechanics.h"
#include "utils.h"
#include "save.h"
#include "menu.h"
#include "fights.h"
#include <unistd.h> 
#include <time.h> 

static bool fight_reloaded = false;

Player fight(Player main_character, NPC enemy, Story *story,int* chapter_npc_ids,bool can_run) {
    fight_reloaded = false; // reset flag at start of fight
    Attributes pre_fight_stats = main_character.stats; // snapshot to clear temporary ability buffs at fight end
    int turn = 1;
    main_character.HUNGER += 5; // Fighting increases hunger
    while(check_alive(&main_character,story,chapter_npc_ids) && !check_win(enemy, &main_character)) {
        main_character.HUNGER += 1; // Each turn increases hunger
        main_character = check_hunger(main_character); // Check if hunger has any effects
        
        printf("\n%s's HP: %d, ", enemy.name, enemy.HP);
        if(main_character.stats.PRECEPTION > enemy.LEVEL){
            printf("MANA: %d", enemy.MANA);
        }
        
        printf("\n\nYour HP: %d, MANA: %d\n", main_character.HP, main_character.MANA);
        sleep(1);

        int priority = priority_calculation(main_character, enemy, turn);

        if(priority >= 1 || (priority == 0 && turn%2!=0)) { // Player goes first, ties favor the player on the odd turns
            printf("\nIt's your turn first!\n");
            main_character = my_turn(main_character,&enemy,story,chapter_npc_ids,can_run);
            sleep(1);
            if(check_win(enemy, &main_character)) {
                printf("You defeated %s!\n", enemy.name);
                break;
            }

            if(priority == 2) {
                printf("\nYour speed advantage lets you act again!\n");
                main_character = my_turn(main_character,&enemy,story,chapter_npc_ids,can_run);
                sleep(1);
                if(check_win(enemy, &main_character)) {
                    printf("You defeated %s!\n", enemy.name);
                    break;
                }
            }

            sleep(2);
            printf("\nIt's %s's turn!\n", enemy.name);
            main_character = enemy_turn(main_character, enemy);
            sleep(1);
        } else { // NPC goes first or ties favor the NPC on even turns
            printf("\n%s is faster and takes the first turn!\n", enemy.name);
            main_character = enemy_turn(main_character, enemy);
            if(!check_alive(&main_character,story,chapter_npc_ids)) {
                printf("You were defeated by %s...\n", enemy.name);
                break;
            }
            sleep(2);
            printf("\nIt's your turn!\n");
            main_character = my_turn(main_character,&enemy,story,chapter_npc_ids,can_run);
            sleep(1);
        }

        turn++;
    }
    main_character.stats = pre_fight_stats; // remove temporary ability effects
    if (main_character.HP > main_character.stats.MAX_HP * 10) {
        main_character.HP = main_character.stats.MAX_HP * 10;
    }
    if (main_character.MANA > main_character.stats.MAX_MANA) {
        main_character.MANA = main_character.stats.MAX_MANA;
    }
    main_character = restore_mana(main_character); // Regenerate some mana after the fight
    return main_character; // Return the updated player state after combat
}

Player my_turn(Player main_character,NPC *enemy,Story *story,int* chapter_npc_ids,bool can_run) {
    char *action = get_input("Choose your action (Attack (D)/Use Ability (A)/Use Item (I)/Charge MANA (C)):\n");
        if (strcmp(action, "D") == 0) {
            int damage = damage_calculation(main_character, *enemy);
            *enemy = damage_npc(*enemy, damage);
            printf("You dealt %d damage to %s!\n", damage, enemy->name);
        } 
        else if (strcmp(action, "A") == 0) {

            int abilityID = open_abilities(&main_character);
            if (abilityID >= 0) {
                main_character = use_ability(main_character, enemy, abilityID);
                printf("You used %s!\n", get_ability_by_id(abilityID)->NAME);
            }
        } 
        else if (strcmp(action, "I") == 0) {
            Player temp_character = main_character; // Create a temporary copy
            printf("You rummage through your inventory...\n");
            open_inventory(&main_character);
            if (temp_character.HP == main_character.HP && temp_character.MANA == main_character.MANA) {
                return my_turn(main_character, enemy, story, chapter_npc_ids, can_run); // No change, ask for input again
            } 
        }
        else if (strcmp(action, "Run") == 0) {
            printf("You attempt to run away...\n");
            // Placeholder for escape logic
        } 
        else if(strcmp(action, "C") == 0) {
            main_character = restore_mana(main_character);
            printf("You focus and restore some MANA!\n");
        }
        else {
            printf("Invalid action. Please choose Attack, Use Ability, Use Item, or Run.\n");
        }
    return main_character;
}

Player enemy_turn(Player main_character, NPC enemy) {
    //TODO: Make enemy AI smarter by choosing between normal attack and abilities based on the situation 
    Abilities *enemy_ability = get_ability_by_id(enemy.Ability_ids[rand() % enemy.abilities_ammount]);
    printf("%s is preparing to attack you!\n", enemy.name);
    int damage = npc_damage_calculation(enemy, main_character);
    
    
    
    main_character = damage_player(main_character, damage);
    printf("%s dealt %d damage to you!\n", enemy.name, damage);
    return main_character;
}

int priority_calculation(Player main_character, NPC npc,int turn) {
    int player_speed = main_character.stats.SPEED;
    int player_stealth = main_character.stats.STEALTH;
    int npc_speed = npc.SPEED;
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

int check_alive(Player *main_character, Story *story,int* chapter_npc_ids) {
    if (main_character->HP <= 0) {
        printf("You have died!\n");
        load_save(story, main_character, chapter_npc_ids);
        fight_reloaded = true; // signal caller that we reloaded a save
        return 0; // Player is dead
    }
    return 1; // Player is alive
}

bool fight_reloaded_from_death(void) {
    return fight_reloaded;
}

int check_win(NPC npc, Player *main_character) {
    if (npc.HP <= 0) {
        main_character->EXP += exp_reward_for_npc(npc);
        return 1; // NPC is defeated
    }
    return 0; // NPC is still alive
}

Player damage_player(Player main_character, int damage_amount) {
    int dodge_chance = main_character.stats.STEALTH;
    if (dodge_chance < 0) dodge_chance = 0;
    if (dodge_chance > 99) dodge_chance = 99;
    int random_value = rand() % 100; // Generate a random number between 0 and 99
    
    if (random_value < dodge_chance) {
        printf("You dodged the attack!\n");
        return main_character; // No damage taken
    }
    
    main_character.HP -= damage_amount;
    return main_character;
}

NPC damage_npc(NPC npc, int damage_amount) { //Always call damage_amount with the damage_calculation functions.
    npc.HP -= damage_amount;
    return npc;
}

int damage_calculation_internal(Player main_character, NPC npc, int ability_damage, int ability_class,int ability_element) {
    int total_damage = ability_damage;
    if (ability_class == -1) { // Basic attack, add weapon damage if applicable
        total_damage += main_character.stats.DAMAGE; // Basic attacks scale with overall damage stat
    }
    if (ability_damage > 0 && ability_class == Magic) { // Only add magic power for magic abilities
        total_damage += main_character.stats.MAGIC_POWER; // Abilities scale with magic power
        }
    if (main_character.weapon >= 0 && ability_class == Melee) { // Only add weapon damage for melee abilities or basic attacks
        total_damage += main_character.stats.WEAPON_DAMAGE;
    }
    if (ability_class == Infused) { // Infused abilities scale with both weapon damage and magic power
        total_damage += main_character.stats.WEAPON_DAMAGE;
        total_damage += main_character.stats.MAGIC_POWER;
    }
    total_damage *= elemental_chart[ability_element][npc.ELEMENTAL_AFFINITY]; // Apply elemental multiplier

    total_damage -= npc.DEFENCE;
    if (total_damage < 0) {
        total_damage = 0;
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
    return npc.DAMAGE-main_character.stats.DEFENCE;
}

int npc_damage_calculation_with_ability(NPC npc, int ability_damage, Player main_character) {
    return npc.DAMAGE + ability_damage - main_character.stats.DEFENCE;
}

int heal_calculation(Player main_character, int heal_amount) {
    heal_amount += main_character.stats.MAGIC_POWER / 2; // Healing scales with magic power
    return heal_amount; // Return integer heal; integer division already floors
}
