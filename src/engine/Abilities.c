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

void apply_boost_effect(Player *main_character, const char *first, const char *second) {
    float multiplier = first ? atof(first) : 1.0f;
    const char *attr = second;
    if (!attr) return;
    if (strcmp(attr,"DEFENCE")==0) main_character->stats.DEFENCE *= multiplier;
    else if (strcmp(attr,"MAX_HP")==0) main_character->stats.MAX_HP *= multiplier;
    else if (strcmp(attr,"MAX_MANA")==0) main_character->stats.MAX_MANA *= multiplier;
    else if (strcmp(attr,"MAGIC_POWER")==0) main_character->stats.MAGIC_POWER *= multiplier;
    else if (strcmp(attr,"WEAPON_DAMAGE")==0) main_character->stats.WEAPON_DAMAGE *= multiplier;
    else if (strcmp(attr,"DAMAGE")==0) main_character->stats.DAMAGE *= multiplier;
    else if (strcmp(attr,"SPEED")==0) main_character->stats.SPEED *= multiplier;
    else if (strcmp(attr,"STEALTH")==0) main_character->stats.STEALTH *= multiplier;
}

void apply_summon_effect(Player *main_character, const char *first) {
    int summon_id = first ? atoi(first) : -1;
    // Allow summoning if the ability is known; storage and duplicates are handled by add_team_member
    if (summon_id == -1) {
        say(0,"Invalid summon id.\n");
        return;
    }
    *main_character = add_team_member(*main_character, summon_id, true);
}

void apply_reveal_effect(Player *main_character, const char *first) {
    int mana_restore = first ? atoi(first) : 0;
    if (mana_restore > 0) {
        main_character->MANA += mana_restore;
        if (main_character->MANA > main_character->stats.MAX_MANA) {
            main_character->MANA = main_character->stats.MAX_MANA;
        }
    }
    int magic_boost = first ? atoi(first) : 0;
    if (magic_boost > 0) {
        *main_character = increase_mc_magic_power(*main_character, magic_boost);
    }
}

void apply_plus_effect(Player *main_character, const char *first, const char *second, NPC *target_npc) {
    int boost = first ? atoi(first) : 0;
    const char *attr = second;
    if (!attr) return;
    if (strcmp(attr,"DEFENCE")==0) main_character->stats.DEFENCE += boost;
    else if (strcmp(attr,"MAX_HP")==0) main_character->stats.MAX_HP += boost;
    else if (strcmp(attr,"MAX_MANA")==0) main_character->stats.MAX_MANA += boost;
    else if (strcmp(attr,"MAGIC_POWER")==0) main_character->stats.MAGIC_POWER += boost;
    else if (strcmp(attr,"WEAPON_DAMAGE")==0) main_character->stats.WEAPON_DAMAGE += boost;
    else if (strcmp(attr,"DAMAGE")==0) main_character->stats.DAMAGE += boost;
    else if (strcmp(attr,"SPEED")==0) main_character->stats.SPEED += boost;
    else if (strcmp(attr,"STEALTH")==0) main_character->stats.STEALTH += boost;
    else if (strcmp(attr,"HP")==0) {
        int delta = boost;
        if (target_npc) {
            if (delta < 0) {
                *target_npc = damage_npc(*target_npc, -delta);
            } else {
                target_npc->HP += delta;
                if (target_npc->HP > target_npc->MAX_HP) {
                    target_npc->HP = target_npc->MAX_HP;
                }
            }
        } else {
            *main_character = heal_player(*main_character, delta);
        }
    }
}

void apply_group_effect(Player *main_character, const char *first, const char *second) {
    int team_heal = first ? atoi(first) : 0;
    int team_boost = second ? atoi(second) : 0;
    if (team_heal > 0) {
        main_character->HP += team_heal;
        if (main_character->HP > main_character->stats.MAX_HP) {
            main_character->HP = main_character->stats.MAX_HP;
        }
        for (int i = 0; i < main_character->team_size; i++) {
            NPC member = get_npc_by_id(main_character->team_memberIDs[i]);
            if (member.ID >= 0) {
                member.HP += team_heal;
                if (member.HP > member.MAX_HP) {
                    member.HP = member.MAX_HP;
                }
            }
        }
    }
    if (team_boost > 0) {
        main_character->stats.DAMAGE += team_boost;
        for (int i = 0; i < main_character->team_size; i++) {
            NPC member = get_npc_by_id(main_character->team_memberIDs[i]);
            if (member.ID >= 100) { // Only boost summons, not NPC allies
                member.DAMAGE += team_boost;
            }
        }
    }
}

void apply_heal_effect(Player *main_character, int ability_id) {
    int heal_amount = get_ability_healing_value(ability_id);
    if (heal_amount > 0) {
        *main_character = heal_player(*main_character, heal_amount);
    }
}

void apply_ability_effect(Player *main_character, Abilities ability, NPC *target_npc){
    if (ability.ID == 15) { // Copy Ability special handling
        apply_copy_ability(main_character, target_npc);
        return;
    }

    EFFECT_TYPE effect_type = ability.EFFECT_TYPE ? ability.EFFECT_TYPE : get_ability_effect_type(ability.ID);
    if (effect_type == NONE) {
        return;
    }

    const char *src = get_ability_effects(ability.ID);
    char *copy = strdup(src ? src : "");
    if (!copy) return;

    char *saveptr = NULL;
    char *first = strtok_r(copy, " ", &saveptr);
    char *second = strtok_r(NULL, " ", &saveptr);

    switch (effect_type) {
        case BOOST:
            apply_boost_effect(main_character, first, second);
            break;
        case SUMMON:
            if(main_character->stats.MAGIC_POWER < ability.MANA_COST/10) {
                say(0,"Not enough MAGIC_POWER to summon this creature.\n");
                break;
            }

            apply_summon_effect(main_character, first);
            break;
        case PLUS:
            apply_plus_effect(main_character, first, second, target_npc);
            break;
        case GROUP:
            apply_group_effect(main_character, first, second);
            break;
        case HEAL:
            apply_heal_effect(main_character, ability.ID);
            break;
        case REVEAL:
            apply_reveal_effect(main_character, first);
            break;
        case POISON:
            apply_poison_effect(target_npc);
            break;
        case BURN:
            apply_burn_effect(main_character, target_npc, ability.ID);
            break;
        case FREEZE:
            apply_freeze_effect(target_npc);
            break;
        case PARALYSE:
            apply_paralysis_effect(target_npc);
            break;
        case NONE:
            break;
        default:
            break;
    }
    if (copy) free(copy);
}

void apply_poison_effect(NPC *target_npc) {
    int damage_per_turn = target_npc->MAX_HP / 8; // Poison deals 12.5% of max HP as damage each turn
    *target_npc = damage_npc(*target_npc, damage_per_turn);
    say(0,"The enemy is poisoned and takes %d damage.\n", damage_per_turn);
}

void apply_burn_effect(Player *main_character,NPC *target_npc ,int ability_id) {
    int damage_per_turn = target_npc->MAX_HP / 12; // Burn deals ~8.3% of max HP as damage each turn
    *target_npc = damage_npc(*target_npc, damage_per_turn);

    bool already_active = false;
    for (int i = 0; i < main_character->active_effect_count; i++) {
        if (main_character->active_effects[i].ability_id == ability_id) {
            already_active = true;
            break;
        }
    }
    if (!already_active) {
        target_npc->DAMAGE -= target_npc->DAMAGE / 3; // Burn reduces damage output by 33% on first tick
        say(0,"The enemy is burned! Damage reduced by 33%%.\n");
    }

    say(0,"The enemy burns and takes %d damage.\n", damage_per_turn);
}

void apply_paralysis_effect(NPC *target_npc) {
        target_npc->SPEED /= 2;
        say(0,"The enemy is paralysed and its speed is greatly reduced.\n");
}

void apply_freeze_effect(NPC *target_npc) {
        target_npc->SPEED = 0;
        say(0,"The enemy is frozen and can't move.\n");
}

void apply_copy_ability(Player *main_character, NPC *target_npc) {
    if (!target_npc) {
        say(0,"No target to copy ability from.\n");
        return;
    }
    Abilities copied_ability = get_ability_by_id(target_npc->Ability_ids[target_npc->abilities_ammount - 1]); // Get the last ability used by the target
    if (copied_ability.ID == -1) {
        say(0,"No ability to copy.\n");
        return;
    }
    *main_character = add_ability(*main_character, copied_ability.ID);
}

void clear_active_ability_effects(Player *main_character) {
    main_character->active_effect_count = 0;
    memset(main_character->active_effects, 0, sizeof(main_character->active_effects));
}

void register_active_ability(Player *main_character, Abilities ability) {
    if (ability.turns_remaining <= 0) {
        return;
    }
    if (main_character->active_effect_count < 0 || main_character->active_effect_count > TOTAL_ABILITIES) {
        clear_active_ability_effects(main_character);
    }
    for (int i = 0; i < main_character->active_effect_count; i++) {
        if (main_character->active_effects[i].ability_id == ability.ID) {
            main_character->active_effects[i].turns_remaining = ability.turns_remaining;
            return;
        }
    }
    if (main_character->active_effect_count < TOTAL_ABILITIES) {
        main_character->active_effects[main_character->active_effect_count].ability_id = ability.ID;
        main_character->active_effects[main_character->active_effect_count].turns_remaining = ability.turns_remaining;
        main_character->active_effect_count++;
    }
}

void refresh_active_ability_effects(Player *main_character, Attributes base_stats, NPC *current_enemy, NPC enemy_base) {
    if (main_character->active_effect_count < 0 || main_character->active_effect_count > TOTAL_ABILITIES) {
        clear_active_ability_effects(main_character);
    }
    main_character->stats = base_stats; // Reset to baseline before reapplying temporary effects
    // Reset enemy combat stats to baseline before reapplying active debuffs
    current_enemy->DAMAGE = enemy_base.DAMAGE;
    current_enemy->SPEED = enemy_base.SPEED;
    current_enemy->DEFENCE = enemy_base.DEFENCE;
    int write_index = 0;
    for (int i = 0; i < main_character->active_effect_count; i++) {
        ActiveAbilityEffect effect = main_character->active_effects[i];
        if (effect.turns_remaining <= 0) {
            continue;
        }
        Abilities ability = get_ability_by_id(effect.ability_id);
        apply_ability_effect(main_character, ability, current_enemy);
        effect.turns_remaining -= 1;
        if (effect.turns_remaining > 0 && write_index < TOTAL_ABILITIES) {
            main_character->active_effects[write_index++] = effect;
        }
    }
    main_character->active_effect_count = write_index;
}

Player add_ability(Player main_character, int abilityID){
    Abilities ability = get_ability_by_id(abilityID);
    if (ability.ID == -1) {
        say(0,"Ability with ID %d not found.\n", abilityID);
        return main_character;
    }
    if(not_in(ability.DNA,main_character.DNA,main_character.DNA_ammount)) {
        say(0,"Ability %s cannot be added due to DNA incompatibility.\n", get_ability_name(abilityID));
        return main_character;
    }

    // Check if ability already exists
    for (int i = 0; i < main_character.abilities_ammount; i++) {
        if (main_character.abilitiesIDs[i] == abilityID) {
            return main_character; // Already present, do nothing
        }
    }
    // Add new ability
    main_character.abilitiesIDs = realloc(main_character.abilitiesIDs, (main_character.abilities_ammount + 1) * sizeof(int));
    main_character.abilitiesIDs[main_character.abilities_ammount] = abilityID;
    main_character.abilities_ammount += 1;
    return main_character;
}

Player remove_ability(Player main_character, int abilityID){
    if(not_in(abilityID,main_character.abilitiesIDs,main_character.abilities_ammount)) {
        say(0,"Ability not found in player's abilities.\n");
        return main_character;
    }
    for (int i = 0; i < main_character.abilities_ammount; i++) {
        if (main_character.abilitiesIDs[i] == abilityID) {
            // Shift left
            for (int k = i; k < main_character.abilities_ammount - 1; k++) {
                main_character.abilitiesIDs[k] = main_character.abilitiesIDs[k + 1];
            }
            main_character.abilities_ammount -= 1;
            main_character.abilitiesIDs = realloc(main_character.abilitiesIDs, main_character.abilities_ammount * sizeof(int));
            break;
        }
    }
    return main_character;
}

int choose_ability(Player *main_character) {
    while (1) {
        open_abilities(main_character);
        char *choice = get_input("Enter ability's ID to use, 'q' to exit: ");
        if (!choice) {
            break;
        }
        if (choice[0] == 'q' && choice[1] == '\0') {
            free(choice);
            return -2; // Special code for user exit
        }
        int ability_id = atoi(choice);
        free(choice);

        if (not_in(ability_id, main_character->abilitiesIDs, main_character->abilities_ammount)) {
            say(0,"Ability not found.\n");
            continue;
        }
        return ability_id;
    }
    return -1; // Safety net if loop exits unexpectedly
}

void open_abilities(Player *main_character) {
    say(0,"---- Abilities ----\n");
        if (main_character->abilities_ammount == 0) {
            say(0,"No abilities All yet.\n");
            return;
        }
        for (int i = 0; i < main_character->abilities_ammount; i++) {
            Abilities ability = get_ability_by_id(main_character->abilitiesIDs[i]);
            if (ability.ID >= 0) {
                int ability_damage = get_ability_damage_value(ability.ID);
                int ability_heal = get_ability_healing_value(ability.ID);
                say(0,"%d. ID: %d - %s - %d MANA - dmg:%d heal:%d - %s\n", i + 1, ability.ID, ability.NAME, ability.MANA_COST, ability_damage, ability_heal, ability.DESCRIPTION);
            } else {
                say(0,"%d. Unknown Ability (ID: %d)\n", i + 1, main_character->abilitiesIDs[i]);
            }
        }
}

Player use_ability(Player main_character, NPC *target_npc, int abilityID) {
    if (not_in(abilityID, main_character.abilitiesIDs, main_character.abilities_ammount)) {
        say(0,"Ability not found in player's abilities.\n");
        return main_character;
    }

    Abilities ability = get_ability_by_id(abilityID);
    if (ability.ID < 0) {
        say(0,"Invalid ability.\n");
        return main_character;
    }

    int mana_type = get_ability_mana_type(ability.ID);
    if (mana_type != BASE && not_in(mana_type, main_character.mana_elements, main_character.mana_elements_ammount)) {
        say(0,"You can't mold your MANA into that element yet.\n");
        return main_character;
    }

    if (main_character.MANA < ability.MANA_COST) {
        say(0,"Not enough mana to use %s.\n", ability.NAME);
        return main_character;
    }
    main_character.MANA -= ability.MANA_COST;

    int ability_damage = get_ability_damage_value(ability.ID);
    int ability_heal = get_ability_healing_value(ability.ID);
    Ability_Class ability_class = get_ability_class(ability.ID);
    EFFECT_TYPE effect_type = get_ability_effect_type(ability.ID);

    apply_ability_effect(&main_character, ability, target_npc);
    register_active_ability(&main_character, ability);
    say(0,"You used %s.\n", ability.NAME);
    
    if (target_npc && ability_damage > 0) {
        int damage = damage_calculation_with_ability(main_character, *target_npc, ability_damage, ability_class, mana_type);
        *target_npc = damage_npc(*target_npc, damage);
        say(0,"You dealt %d damage to %s.\n", damage, target_npc->name);
    }
    if (ability_heal > 0 && effect_type != HEAL && effect_type != GROUP) {
        main_character = heal_player(main_character, ability_heal);
        say(0,"You healed yourself for %d HP.\n", ability_heal);
    }

    return main_character;
}

Player npc_use_ability(Player main_character, NPC target_npc, int abilityID) {
    Abilities ability = get_ability_by_id(abilityID);
    if (ability.ID < 0) {
        say(0,"Invalid ability.\n");
        return main_character;
    }
    int ability_id = ability.ID;
    target_npc = npc_apply_ability(target_npc, ability_id);
    say(0,"%s used %s.\n", target_npc.name, ability.NAME);
    int ability_damage = get_ability_damage_value(ability_id);
    if(ability_damage > 0){
        int damage = npc_damage_calculation_with_ability(target_npc, ability_damage, main_character);
        main_character = damage_player(main_character, damage);
        say(0,"%s dealt %d damage to you.\n", target_npc.name, damage);
    }
    return main_character;
}

NPC npc_apply_ability(NPC npc, int abilityID) {
    EFFECT_TYPE effect_type = get_ability_effect_type(abilityID);
    const char *src = get_ability_effects(abilityID);
    char *copy = strdup(src ? src : "");
    char *saveptr = NULL;
    char *first = copy ? strtok_r(copy, " ", &saveptr) : NULL;
    char *second = copy ? strtok_r(NULL, " ", &saveptr) : NULL;

    if (effect_type == BOOST) {
        float multiplier = first ? atof(first) : 1.0f;
        const char *Attribute = second;
        if (Attribute) {
            if (strcmp(Attribute, "MAX_HP") == 0) npc.MAX_HP = (int)(npc.MAX_HP * multiplier);
            else if (strcmp(Attribute, "MAX_MANA") == 0) npc.MAX_MANA = (int)(npc.MAX_MANA * multiplier);
            else if (strcmp(Attribute, "DAMAGE") == 0) npc.DAMAGE = (int)(npc.DAMAGE * multiplier);
            else if (strcmp(Attribute, "SPEED") == 0) npc.SPEED = (int)(npc.SPEED * multiplier);
        }
    }
    else if (effect_type == PLUS) {
        int boost = first ? atoi(first) : 0;
        const char *Attribute = second;
        if (Attribute) {
            if (strcmp(Attribute, "MAX_HP") == 0) npc.MAX_HP += boost;
            else if (strcmp(Attribute, "MAX_MANA") == 0) npc.MAX_MANA += boost;
            else if (strcmp(Attribute, "DAMAGE") == 0) npc.DAMAGE += boost;
            else if (strcmp(Attribute, "SPEED") == 0) npc.SPEED += boost;
        }
    }
    else if (effect_type == GROUP) {
        int heal_amount = first ? atoi(first) : 0;
        int damage_boost = second ? atoi(second) : 0;
        if (heal_amount > 0) {
            npc = heal_npc(npc, heal_amount);
        }
        if (damage_boost > 0) {
            npc.DAMAGE += damage_boost;
        }
    }
    else if (effect_type == HEAL) {
        int heal_amount = get_ability_healing_value(abilityID);
        npc = heal_npc(npc, heal_amount);
    }
    // SUMMON and NONE are ignored for NPC self-application

    if (npc.HP > npc.MAX_HP) {
        npc.HP = npc.MAX_HP;
    }
    if (copy) free(copy);

    return npc;
}
int inate_ability(Player main_character){
    int mc_ability_ammount = get_mc_abilities_ammount(main_character);
    int* ability_ids = get_mc_abilitiesIDs(main_character);
    for(int i = 0;i<mc_ability_ammount;i++){
        int ability_id = ability_ids[i];
        int ability_dna = get_ability_dna(ability_id);
        if(ability_dna == Inate){return ability_id;}
    } 
    return -1;
}
