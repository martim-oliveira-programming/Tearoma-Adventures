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

void get_attributes(Player *main_character) {
    if (main_character->build == Assassin) {
        *main_character = add_inventory(*main_character,2,1); //Basic Dagger
        *main_character = add_inventory(*main_character,3,1); //Secondary Dagger
        *main_character = add_ability(*main_character,1); //Speed Boost
        *main_character = add_ability(*main_character,4); //Disguise
        
        main_character->stats = (Attributes){
            .DEFENCE = 4,
            .DAMAGE = 10,
            .MAGIC_POWER = 2,
            .MAX_HP = 8,
            .MAX_MANA = 10,
            .SUMMONS_STORAGE = 0,
            .SPEED = 18,
            .STEALTH = 12,
            .WEAPON_DAMAGE = 6,
            .WEAPON_USER = true,
            .DUAL_WILDING = true,
            .MAGIC_USER = true,
        };//Total:70
    }
    else if (main_character->build == Tank) {
        *main_character = add_inventory(*main_character,4,1); //Basic Sword
        *main_character = add_inventory(*main_character,5,1); //Basic Shield
        *main_character = add_ability(*main_character,2);     //Shield Bash
        
        *main_character = add_inventory(*main_character,6,1); //Headband
        *main_character = add_inventory(*main_character,7,1); //Leather Chestplate
        *main_character = add_inventory(*main_character,8,1); //Leather Pants
        *main_character = add_inventory(*main_character,9,1); //Leather Boots
        
        main_character->stats = (Attributes){
            .DEFENCE = 16,
            .DAMAGE = 6,
            .MAGIC_POWER = 2,
            .MAX_HP = 16,
            .MAX_MANA = 6,
            .SUMMONS_STORAGE = 0,
            .SPEED = 6,
            .STEALTH = 4,
            .WEAPON_DAMAGE = 14,
            .WEAPON_USER = true,
            .DUAL_WILDING = false,
            .MAGIC_USER = true,
        };//Total:70
    }
    else if (main_character->build == Monk) {

        *main_character = add_ability(*main_character,3); //Lethal Punch Barrage 

        *main_character = add_inventory(*main_character,6,1);//Headband
        
        main_character->stats = (Attributes){
            .DEFENCE = 6,
            .DAMAGE = 20,
            .MAGIC_POWER = 0,
            .MAX_HP = 14,
            .MAX_MANA = 0,
            .SUMMONS_STORAGE = 0,
            .SPEED = 18,
            .STEALTH = 12,
            .WEAPON_DAMAGE = 0,
            .WEAPON_USER = false,
            .DUAL_WILDING = false,
            .MAGIC_USER = false,
        };//Total:70, balanced for unarmed focus.
    }
    else if (main_character->build == Ninja) {
        *main_character = add_inventory(*main_character,14,1); //Katana
        *main_character = add_inventory(*main_character,15,1); //Shuriken
        *main_character = add_ability(*main_character,4); //Disguise
        *main_character = add_ability(*main_character,1); //Speed Boost
        
        // Initialize armor slots
        *main_character = add_inventory(*main_character,6,1);//Headband
        *main_character = add_inventory(*main_character,16,1);//Ninja chestplate
        *main_character = add_inventory(*main_character,17,1);//Ninja pants
        *main_character = add_inventory(*main_character,18,1);//Soundless sandals
        
        main_character->stats = (Attributes){
            .DEFENCE = 6,
            .DAMAGE = 8,
            .MAGIC_POWER = 6,
            .MAX_HP = 8,
            .MAX_MANA = 10,
            .SUMMONS_STORAGE = 0,
            .SPEED = 16,
            .STEALTH = 16,
            .WEAPON_DAMAGE = 10,
            .WEAPON_USER = true,
            .DUAL_WILDING = false,
            .MAGIC_USER = true,
        };//Total:70
    }
    else if (main_character->build == Mage) {
        *main_character = add_inventory(*main_character,11,1); //Basic Grimoire
        *main_character = add_inventory(*main_character,13,1); //Mage Robe

        *main_character = add_ability(*main_character,5); //Fire Bolt
        *main_character = add_ability(*main_character,6); //Basic Healing
        
        main_character->stats = (Attributes){
            .DEFENCE = 4,
            .DAMAGE = 4,
            .MAGIC_POWER = 20,
            .MAX_HP = 6,
            .MAX_MANA = 16,
            .SUMMONS_STORAGE = 0,
            .SPEED = 6,
            .STEALTH = 4,
            .WEAPON_DAMAGE = 10,
            .WEAPON_USER = true,
            .DUAL_WILDING = false,
            .MAGIC_USER = true,
        };//Total:70
    }
    else if (main_character->build == Healer) {
        *main_character = add_inventory(*main_character,6,1); //Headband
        *main_character = add_inventory(*main_character,12,1); //Healer's Glove

        *main_character = add_ability(*main_character,6); //Basic Healing
        *main_character = add_ability(*main_character,7); //Group Healing
          
        main_character->stats = (Attributes){
            .DEFENCE = 6,
            .DAMAGE = 2,
            .MAGIC_POWER = 14,
            .MAX_HP = 8,         
            .MAX_MANA = 18,
            .SUMMONS_STORAGE = 0,
            .SPEED = 6,
            .STEALTH = 10,
            .WEAPON_DAMAGE = 6,
            .WEAPON_USER = true,
            .DUAL_WILDING = false,
            .MAGIC_USER = true,
        };//Total:70
    }
    else if (main_character->build == Summoner) {
        *main_character = add_inventory(*main_character,6,1); //Headband
        *main_character = add_inventory(*main_character,11,1); //Basic Grimoire

        *main_character = add_ability(*main_character,6); //Basic Healing
        *main_character = add_ability(*main_character,11); //Fire Spirit Summon
        *main_character = add_summon(*main_character, 0); //Fire Spirit
        
        main_character->stats = (Attributes){
            .DEFENCE = 6,
            .DAMAGE = 6,
            .MAGIC_POWER = 12,
            .MAX_HP = 10,          
            .MAX_MANA = 18,
            .SUMMONS_STORAGE = 3,
            .SPEED = 6,
            .STEALTH = 8,
            .WEAPON_DAMAGE = 4,
            .WEAPON_USER = true,
            .DUAL_WILDING = false,
            .MAGIC_USER = true,
        };//Total:70
    }

    else if (main_character->build == Balanced) {
        *main_character = add_inventory(*main_character,4,1);
        *main_character = add_inventory(*main_character,6,1);
        *main_character = add_ability(*main_character,5);
        *main_character = add_ability(*main_character,9);
        
        *main_character = add_inventory(*main_character,7,1);
        *main_character = add_inventory(*main_character,8,1);
        
        main_character->stats = (Attributes){
            .DEFENCE = 8,
            .DAMAGE = 8,
            .MAGIC_POWER = 8,
            .MAX_HP = 8,       
            .MAX_MANA = 8,
            .SUMMONS_STORAGE = 2,
            .SPEED = 8,
            .STEALTH = 8,
            .WEAPON_DAMAGE = 8,
            .WEAPON_USER = true,
            .DUAL_WILDING = true,
            .MAGIC_USER = true,
        };//Total:72
    }
}

static void apply_boost_effect(Player *main_character, const char *first, const char *second) {
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

static void apply_summon_effect(Player *main_character, const char *first) {
    int summon_id = first ? atoi(first) : -1;
    // Allow summoning if the ability is known; storage and duplicates are handled by add_team_member
    if (summon_id == -1) {
        printf("Invalid summon id.\n");
        return;
    }
    *main_character = add_team_member(*main_character, summon_id, true);
}

static void apply_plus_effect(Player *main_character, const char *first, const char *second, NPC *target_npc) {
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
            main_character->HP += delta;
            int max_hp_cap = main_character->stats.MAX_HP * 10;
            if (main_character->HP > max_hp_cap) {
                main_character->HP = max_hp_cap;
            }
            if (main_character->HP < 0) {
                main_character->HP = 0;
            }
        }
    }
}

static void apply_group_effect(Player *main_character, const char *first, const char *second) {
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

static void apply_heal_effect(Player *main_character, int ability_id) {
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
                printf("Not enough MAGIC_POWER to summon this creature.\n");
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
        case NONE:
        default:
            break;
    }
    if (copy) free(copy);
}

void apply_copy_ability(Player *main_character, NPC *target_npc) {
    if (!target_npc) {
        printf("No target to copy ability from.\n");
        return;
    }
    Abilities copied_ability = get_ability_by_id(target_npc->Ability_ids[target_npc->abilities_ammount - 1]); // Get the last ability used by the target
    if (copied_ability.ID == -1) {
        printf("No ability to copy.\n");
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

void refresh_active_ability_effects(Player *main_character, Attributes base_stats, NPC *current_enemy) {
    if (main_character->active_effect_count < 0 || main_character->active_effect_count > TOTAL_ABILITIES) {
        clear_active_ability_effects(main_character);
    }
    main_character->stats = base_stats; // Reset to baseline before reapplying temporary effects
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

NPC get_summon_by_id(int id){
    for(int i = 0;i<TOTAL_SUMMONS;i++){
        if (ALL_summons[i].ID == id){
            return ALL_summons[i];
        }
    }
    return (NPC){ .ID = -1 }; // Return an empty NPC if not found
}

Abilities get_ability_by_id(int id) {
    for (int i = 0; i < TOTAL_ABILITIES; i++) {
        if (ALL_abilities[i].ID == id) {
            return ALL_abilities[i];
        }
    }
    return (Abilities){ .ID = -1 }; // Return an empty Abilities struct if not found
}

NPC get_npc_by_id(int id){
    for(int i = 0;i<TOTAL_NPC;i++){
        if (ALL_npc[i].ID == id){
            return ALL_npc[i];
        }
    }
    return (NPC){ .ID = -1 }; // Return an empty NPC if not found
}

Items get_items_by_id(int id){
    for(int i = 0;i<TOTAL_ITEMS;i++){
        if (ALL_items[i].ID == id){
            return ALL_items[i];
        }
    }
    return (Items){ .ID = -1 };
}

Weapon get_weapon(int id){
    for(int i = 0;i<TOTAL_WEAPONS;i++){
        if (ALL_weapons[i].item_id == id){
            return ALL_weapons[i];
        }
    }
    return (Weapon){ .item_id = -1 };
}

Consumable get_consumable(int id){
    for (int i = 0; i < TOTAL_CONSUMABLES; i++) {
        if (ALL_consumables[i].item_id == id) {
            return ALL_consumables[i];
        }
    }
    return (Consumable){ .item_id = -1 };
}

Player sort_items(Player main_character){
    // Simple bubble sort for demonstration
    for (int i = 0; i < main_character.item_ammount - 1; i++) {
        for (int j = 0; j < main_character.item_ammount - i - 1; j++) {
            if (main_character.inventoryIDs[j] > main_character.inventoryIDs[j + 1]) {
                // Swap
                int temp = main_character.inventoryIDs[j];
                main_character.inventoryIDs[j] = main_character.inventoryIDs[j + 1];
                main_character.inventoryIDs[j + 1] = temp;
            }
        }
    }
    return main_character;
}

Player add_inventory(Player main_character, int itemID, int amount){
    main_character.inventoryIDs = realloc(main_character.inventoryIDs,(main_character.item_ammount + amount) * sizeof(int));
    for(int i=0; i< amount; i++){
    main_character.inventoryIDs[main_character.item_ammount] = itemID;
    main_character.item_ammount +=1;
    }
    main_character = sort_items(main_character);
    return main_character;
}

Player remove_inventory(Player main_character, int itemID, int amount){
    if (not_in(itemID,main_character.inventoryIDs,main_character.item_ammount)) {
        printf("Item not found in inventory.\n");
        return main_character;
    }
    int removed = 0;
    for (int j = 0; j < amount && removed < amount; j++) {
        for (int i = 0; i < main_character.item_ammount; i++) {
            if (main_character.inventoryIDs[i] == itemID) {
                // Shift elements left
                for (int k = i; k < main_character.item_ammount - 1; k++) {
                    main_character.inventoryIDs[k] = main_character.inventoryIDs[k + 1];
                }
                main_character.item_ammount -= 1;
                removed += 1;
                // Realloc to shrink array
                main_character.inventoryIDs = realloc(main_character.inventoryIDs, (main_character.item_ammount) * sizeof(int));
                break; // Only remove one per loop
            }
        }
    }
    main_character = sort_items(main_character);
    return main_character;
}

Player add_ability(Player main_character, int abilityID){
    Abilities ability = get_ability_by_id(abilityID);
    if (ability.ID == -1) {
        printf("Ability with ID %d not found.\n", abilityID);
        return main_character;
    }
    if(not_in(ability.DNA,main_character.DNA,main_character.DNA_ammount)) {
        printf("Ability %s cannot be added due to DNA incompatibility.\n", get_ability_name(abilityID));
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
        printf("Ability not found in player's abilities.\n");
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

int is_consumable_item(int item_id) {
    Items item = get_items_by_id(item_id);
    return (item.item_type == CONSUMABLE);
}

int is_key_item(int item_id) {
    Items item = get_items_by_id(item_id);
    return item.item_type == KEY;
}

int is_weapon_item(int item_id) {
    Items item = get_items_by_id(item_id);
    return item.item_type == WEAPON;
}

Player equip_item(Player main_character, int itemID) {
    Weapon weapon = get_weapon(itemID);
    if (weapon.item_id == -1) {
        printf("Item cannot be equipped.\n");
        return main_character;
    }
    if(!is_weapon_item(itemID)) {
        printf("Item is not a weapon and cannot be equipped.\n");
        return main_character;
    }

    int slot = weapon.equip_slot;
    if (slot == MAIN_HAND) {
        if (main_character.weapon != -1) {
            main_character = unequip_item(main_character, MAIN_HAND);
        }
        main_character.weapon = itemID;
    } else if (slot == OFF_HAND) {
        if (main_character.weapon_OFF_Hand != -1) {
            main_character = unequip_item(main_character, OFF_HAND);
        }
        main_character.weapon_OFF_Hand = itemID;
    } else if (slot >= HEAD && slot <= SHOES) {
        int armor_index = slot - HEAD; // map enum to 0-3 indices
        if (armor_index < 0 || armor_index >= 4) {
            printf("Invalid armor slot.\n");
            return main_character;
        }
        if (main_character.armor[armor_index] != -1) {
            main_character = unequip_item(main_character, slot);
        }
        main_character.armor[armor_index] = itemID;
    } else {
        printf("Invalid equip slot.\n");
        return main_character;
    }
    main_character = apply_weapon_effects(main_character, weapon);
    main_character = remove_inventory(main_character, itemID, 1);
    return main_character;
}

Player unequip_item(Player main_character, int slot) {
    if (slot == MAIN_HAND) {
        if (main_character.weapon == -1) {
            printf("No weapon equipped in main hand.\n");
            return main_character;
        }
        const Weapon w = get_weapon(main_character.weapon);
        main_character = remove_weapon_effects(main_character, w);
        main_character = add_inventory(main_character, main_character.weapon, 1);
        main_character.weapon = -1;
    } else if (slot == OFF_HAND) {
        if (main_character.weapon_OFF_Hand == -1) {
            printf("No weapon equipped in off hand.\n");
            return main_character;
        }
        const Weapon w = get_weapon(main_character.weapon_OFF_Hand);
        main_character = remove_weapon_effects(main_character, w);
        main_character = add_inventory(main_character, main_character.weapon_OFF_Hand, 1);
        main_character.weapon_OFF_Hand = -1;
    } else if (slot >= HEAD && slot <= SHOES) {
        int armor_index = slot - HEAD; // map enum to 0-3 indices
        if (armor_index < 0 || armor_index >= 4) {
            printf("Invalid armor slot.\n");
            return main_character;
        }
        if (main_character.armor[armor_index] == -1) {
            printf("No armor equipped in this slot.\n");
            return main_character;
        }
        Weapon w = get_weapon(main_character.armor[armor_index]);
        main_character = remove_weapon_effects(main_character, w);
        main_character = add_inventory(main_character, main_character.armor[armor_index], 1);
        main_character.armor[armor_index] = -1;
    } else {
        printf("Invalid equip slot.\n");
        return main_character;
    }
    return main_character;
}

Player add_summon(Player main_character, int summonID){
    if (main_character.summons_ammount == main_character.stats.SUMMONS_STORAGE) {
        printf("Cannot add more abilities, storage full.\n");
        return main_character;
    }

    for (int i = 0; i < main_character.summons_ammount; i++) {
        if (main_character.summonIDs[i] == summonID) {
            return main_character; // Already present, do nothing
        }
    }
    // Add new summon
    main_character.summonIDs = realloc(main_character.summonIDs, (main_character.summons_ammount + 1) * sizeof(int));
    main_character.summonIDs[main_character.summons_ammount] = summonID;
    main_character.summons_ammount += 1;
    return main_character;
}

Player remove_summon(Player main_character, int summonID){
    if(not_in(summonID,main_character.summonIDs,main_character.summons_ammount)) {
        printf("Summon not found in player's summons.\n");
        return main_character;
    }
    for (int i = 0; i < main_character.summons_ammount; i++) {
        if (main_character.summonIDs[i] == summonID) {
            // Shift left
            for (int k = i; k < main_character.summons_ammount - 1; k++) {
                main_character.summonIDs[k] = main_character.summonIDs[k + 1];
            }
            main_character.summons_ammount -= 1;
            main_character.summonIDs = realloc(main_character.summonIDs, main_character.summons_ammount * sizeof(int));
            break;
        }
    }
    main_character.stats.MAGIC_POWER += 10;//If a summoner's summon is destrouyed, they loose the ability to even summon it again, but they also gain a boost
    return main_character;
}

Builds parse_build(const char *s) {
    if (!s) return Balanced;
    if (strcasecmp(s, "Assassin") == 0) return Assassin;
    if (strcasecmp(s, "Tank") == 0) return Tank;
    if (strcasecmp(s, "Monk") == 0) return Monk;
    if (strcasecmp(s, "Ninja") == 0) return Ninja;
    if (strcasecmp(s, "Mage") == 0) return Mage;
    if (strcasecmp(s, "Healer") == 0) return Healer;
    if (strcasecmp(s, "Summoner") == 0) return Summoner;
    if (strcasecmp(s, "Balanced") == 0) return Balanced;
    // default
    return Balanced;
}

const char *gender_to_string(Gender g){
    switch(g){
        case Boy:  return "Boy";
        case Girl: return "Girl";
        default:   return "Unknown";
    }
}

Player add_team_member(Player main_character, int memberID, bool is_summon_member) {
    // Prevent duplicates
    if (is_team_member(main_character, memberID)) {
        return main_character;
    }

    // Enforce summon storage if applicable
    if (is_summon_member && main_character.stats.SUMMONS_STORAGE > 0) {
        int summon_count = 0;
        for (int i = 0; i < main_character.team_size; i++) {
            if (is_summon(main_character.team_memberIDs[i])) {
                summon_count++;
            }
        }
        if (summon_count >= main_character.stats.SUMMONS_STORAGE) {
            printf("Summon storage full. Cannot add more summons.\n");
            return main_character;
        }
    }

    int new_size = main_character.team_size + 1;
    int *new_ids = realloc(main_character.team_memberIDs, new_size * sizeof(int));
    int *new_hp = realloc(main_character.team_member_hp, new_size * sizeof(int));
    int *new_mana = realloc(main_character.team_member_mana, new_size * sizeof(int));
    if (!new_ids || !new_hp || !new_mana) {
        free(new_ids);
        free(new_hp);
        free(new_mana);
        return main_character;
    }
    main_character.team_memberIDs = new_ids;
    main_character.team_member_hp = new_hp;
    main_character.team_member_mana = new_mana;
    main_character.team_memberIDs[main_character.team_size] = memberID;
    NPC member = is_summon(memberID) ? get_summon_by_id(memberID) : get_npc_by_id(memberID);
    main_character.team_member_hp[main_character.team_size] = member.HP > 0 ? member.HP : member.MAX_HP;
    main_character.team_member_mana[main_character.team_size] = member.MANA > 0 ? member.MANA : member.MAX_MANA;
    main_character.team_size = new_size;
    return main_character;
}

Player remove_team_member(Player main_character, int memberID, bool is_summon_member) {
    (void)is_summon_member;
    int removed = 0;
    for (int i = 0; i < main_character.team_size; i++) {
        if (main_character.team_memberIDs[i] == memberID) {
            for (int k = i; k < main_character.team_size - 1; k++) {
                main_character.team_memberIDs[k] = main_character.team_memberIDs[k + 1];
                main_character.team_member_hp[k] = main_character.team_member_hp[k + 1];
                main_character.team_member_mana[k] = main_character.team_member_mana[k + 1];
            }
            main_character.team_size -= 1;
            if (main_character.team_size == 0) {
                free(main_character.team_memberIDs);
                free(main_character.team_member_hp);
                free(main_character.team_member_mana);
                main_character.team_memberIDs = NULL;
                main_character.team_member_hp = NULL;
                main_character.team_member_mana = NULL;
            } else {
                int *shrunk = realloc(main_character.team_memberIDs, main_character.team_size * sizeof(int));
                if (shrunk) {
                    main_character.team_memberIDs = shrunk;
                }
                int *shrunk_hp = realloc(main_character.team_member_hp, main_character.team_size * sizeof(int));
                if (shrunk_hp) {
                    main_character.team_member_hp = shrunk_hp;
                }
                int *shrunk_mana = realloc(main_character.team_member_mana, main_character.team_size * sizeof(int));
                if (shrunk_mana) {
                    main_character.team_member_mana = shrunk_mana;
                }
            }
            removed = 1;
            break;
        }
    }
    (void)removed; // silence unused warning if not used later
    return main_character;
}

int is_team_member_summon(Player main_character, int memberID) {
    if(is_team_member(main_character, memberID) && is_summon(memberID)){
        return 1;
    }
    return 0;
}

int is_team_member(Player main_character, int memberID) {
    for (int i = 0; i < main_character.team_size; i++) {
        if (main_character.team_memberIDs[i] == memberID) {
            return 1;
        }
    }
    return 0;
}

int is_summon(int memberID) {
    return memberID >= 100 && memberID < 100 + TOTAL_SUMMONS;
}

void free_team(Player *main_character) {
    if (!main_character) return;
    if (main_character->team_memberIDs) {
        free(main_character->team_memberIDs);
        main_character->team_memberIDs = NULL;
    }
    if (main_character->team_member_hp) {
        free(main_character->team_member_hp);
        main_character->team_member_hp = NULL;
    }
    if (main_character->team_member_mana) {
        free(main_character->team_member_mana);
        main_character->team_member_mana = NULL;
    }
    main_character->team_size = 0;
}

char* team_names(Player main_character) {
    if (main_character.team_size == 0) {
        return strdup("No team members.");
    }
    size_t buffer_size = 256;
    char *buffer = malloc(buffer_size);
    if (!buffer) return NULL;
    buffer[0] = '\0';
    for (int i = 0; i < main_character.team_size; i++) {
        int member_id = main_character.team_memberIDs[i];
        NPC member = get_npc_by_id(member_id);
        const char *name = member.ID >= 0 ? member.name : "Unknown";
        size_t needed = strlen(name) + 3; // for ", " or null terminator
        if (strlen(buffer) + needed >= buffer_size) {
            buffer_size *= 2;
            char *new_buffer = realloc(buffer, buffer_size);
            if (!new_buffer) {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
        }
        strcat(buffer, name);
        if (i < main_character.team_size - 1) {
            strcat(buffer, ", ");
        }
    }
    return buffer;
}

static const char *item_type_to_string(int type) {
    switch (type) {
        case 0: return "Consumable";
        case 1: return "Key";
        case 2: return "Weapon";
        default: return "Unknown";
    }
}

static const char *equipped_item_name(int item_id) {
    if (item_id == -1) return "Empty";
    Items item = get_items_by_id(item_id);
    return item.ID >= 0 ? item.name : "Unknown";
}

void open_inventory(Player *main_character) {
    while (1) {
    printf("---- Inventory ----\n");
    if (main_character->item_ammount == 0) {
        printf("Inventory is empty.\n");
    } else {
        int index = 0;
        int printed = 0;
        while (index < main_character->item_ammount) {
            int current_id = main_character->inventoryIDs[index];
            int count = 1;
            while (index + count < main_character->item_ammount && main_character->inventoryIDs[index + count] == current_id) {
                count++;
            }
            Items item = get_items_by_id(current_id);
            if (item.ID >= 0) {
                int type_code = -1;
                if (is_consumable_item(current_id)) {
                    type_code = 0;
                } else if (is_key_item(current_id)) {
                    type_code = 1;
                } else {
                    Weapon weapon = get_weapon(current_id);
                    if (weapon.item_id != -1) {
                        type_code = 2;
                    }
                }
                printf("%d. %dx %s (%s) ID(%d)\n", ++printed, count, item.name, item_type_to_string(type_code), item.ID);
            } else {
                printf("%d. %dx Unknown Item (ID: %d)\n", ++printed, count, current_id);
            }
            index += count;
        }
    }

        printf("---- Equipped ----\n");
        printf("1. Main Hand: %s\n", equipped_item_name(main_character->weapon));
        printf("2. Off Hand: %s\n", equipped_item_name(main_character->weapon_OFF_Hand));
        printf("3. Head: %s\n", equipped_item_name(main_character->armor[0]));
        printf("4. Chest: %s\n", equipped_item_name(main_character->armor[1]));
        printf("5. Legs: %s\n", equipped_item_name(main_character->armor[2]));
        printf("6. Shoes: %s\n", equipped_item_name(main_character->armor[3]));

        if (main_character->item_ammount == 0) {
            return;
        }

        char *choice = get_input("ID to use item, 'q' to exit: ");
        if (!choice) {
            break;
        }
        if (choice[0] == 'q' && choice[1] == '\0') {
            free(choice);
            break;
        }
        int id_to_use = atoi(choice);
        free(choice);
        use_item(main_character, id_to_use);
    }
}

void use_item(Player *main_character, int item_id){
    if (not_in(item_id,main_character->inventoryIDs,main_character->item_ammount)) {
        printf("Item not found in inventory.\n");
        return;
    }
    Items item = get_items_by_id(item_id);
    if (item.ID < 0) {
        printf("Invalid item.\n");
        return;
    }
    if (is_consumable_item(item_id)) {
        use_consumable(main_character, item_id);
        return;
    } else if (is_weapon_item(item_id)) {
        *main_character = equip_item(*main_character, item_id);
        printf("You equipped %s.\n", item.name);
        return;
    } else if (is_key_item(item_id)) {
        printf("You can't use %s right now!!.\n", item.name);
        return;
    } else {
        printf("Item type not usable.\n");
        return;
    }
}

void use_consumable(Player *main_character, int item_id) {
    Consumable consumable = get_consumable(item_id);
    if (consumable.item_id == -1) {
        printf("Invalid consumable.\n");
        return;
    }
    Items item = get_items_by_id(item_id);
    const char *item_name = item.ID >= 0 ? item.name : "Unknown consumable";
    int temp_hp = main_character->HP;
    int temp_hunger = main_character->HUNGER;
    int temp_mana = main_character->MANA;
    int hp_heal = consumable.healling;
    int hunger_restore = consumable.hunger_restoration;
    int mana_restore = consumable.mana_restoration;
    if (hp_heal > 0) {
        if (main_character->HP == (main_character->stats.MAX_HP*10)) {
            printf("You are already at full health. Cannot use %s.\n", item_name);
            return;
        }
        *main_character = heal_player(*main_character, hp_heal);
        printf("You consumed %s and restored %d health.\n", item_name, main_character->HP - temp_hp);
        *main_character = remove_inventory(*main_character, item_id, 1);
        return;
    }
    if (hunger_restore > 0) {
        if (main_character->HUNGER == 0) {
            printf("You are not hungry. Cannot use %s.\n", item_name);
            return;
        }
        *main_character = decrease_hunger(*main_character, hunger_restore);
        printf("You consumed %s and restored %d hunger.\n", item_name, temp_hunger - main_character->HUNGER);
        *main_character = remove_inventory(*main_character, item_id, 1);
        return;
    }
    if(mana_restore >0){
        if (main_character->MANA == (main_character->stats.MAX_MANA*10)){
            printf("You are already at full mana. Cannot use %s.\n", item_name);
            return;
        }
        *main_character = add_Mana(*main_character, mana_restore);
        printf("You consumed %s and restored %d mana.\n", item_name, main_character->MANA - temp_mana);
        *main_character = remove_inventory(*main_character, item_id, 1);
        return;
    }

    printf("This consumable has no effect right now.\n");
    return;
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
            printf("Ability not found.\n");
            continue;
        }
        return ability_id;
    }
    return -1; // Safety net if loop exits unexpectedly
}

void open_abilities(Player *main_character) {
    printf("---- Abilities ----\n");
        if (main_character->abilities_ammount == 0) {
            printf("No abilities learned yet.\n");
            return;
        }
        for (int i = 0; i < main_character->abilities_ammount; i++) {
            Abilities ability = get_ability_by_id(main_character->abilitiesIDs[i]);
            if (ability.ID >= 0) {
                int ability_damage = get_ability_damage_value(ability.ID);
                int ability_heal = get_ability_healing_value(ability.ID);
                printf("%d. ID: %d - %s - %d MANA - dmg:%d heal:%d - %s\n", i + 1, ability.ID, ability.NAME, ability.MANA_COST, ability_damage, ability_heal, ability.DESCRIPTION);
            } else {
                printf("%d. Unknown Ability (ID: %d)\n", i + 1, main_character->abilitiesIDs[i]);
            }
        }
}

void open_player_menu(Player *main_character) {
    while (1) {
        printf("---- Player Menu ----\n");
        printf("1. View Stats\n");
        printf("2. Open Inventory\n");
        printf("3. See Abilities\n");
        printf("4. Exit Menu\n");

        char *choice = get_input("Enter your choice: ");
        if (!choice) {
            break;
        }
        if (choice[0] == '4' && choice[1] == '\0') {
            free(choice);
            break;
        }
        int option = atoi(choice);
        free(choice);

        switch (option) {
            case 1:
                player_stats(*main_character);
                break;
            case 2:
                open_inventory(main_character);
                break;
            case 3: {
                open_abilities(main_character);
                break;
            }
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    }
}

void print_player_info(Player main_character) {
    printf("You have %d€.\n", main_character.money);
    printf("Hunger: %d/100\n\n", main_character.HUNGER);
    printf("You have %d Skill Points to use.\n", main_character.Skill_Points);
    
    printf("---- Player Stats ----\n");
    printf("1. HP: %d/%d\n", main_character.HP, main_character.stats.MAX_HP);
    printf("2. Mana: %d/%d\n", main_character.MANA, main_character.stats.MAX_MANA);
    printf("3. Damage: %d\n", main_character.stats.DAMAGE);
    printf("4. Magic Power: %d\n", main_character.stats.MAGIC_POWER);
    printf("5. Defence: %d\n", main_character.stats.DEFENCE);
    printf("6. Speed: %d\n", main_character.stats.SPEED);
    printf("7. Stealth: %d\n", main_character.stats.STEALTH);
    printf("8. Weapon Damage: %d\n", main_character.stats.WEAPON_DAMAGE);
    printf("9. Preception: %d\n", main_character.stats.PERCEPTION);
    printf("Press 'q' to exit stats menu.\n");
}

int player_stats(Player main_character) {
    int Sp = main_character.Skill_Points;
    char* choice;
    print_player_info(main_character);  
    while (Sp > 0) {
        print_player_info(main_character);
        choice = get_input("Enter the number of the stat you want to increase (or 'q' to exit): ");
        if (!choice) {
            return 0;
        }
        if (choice[0] == 'q' && choice[1] == '\0') {
            free(choice);
            return 0;
        }
        int stat_choice = atoi(choice);
        free(choice);
        if (stat_choice < 1 || stat_choice > 8) {
            printf("Invalid choice.\n");
        }
        switch (stat_choice)
        {
        case 1:
            main_character.stats.MAX_HP += 1;
            main_character.HP += 10;
            Sp -= 1;
            break;
        
        case 2:
            main_character.stats.MAX_MANA += 1;
            main_character.MANA += 10;
            Sp -= 1;
            break;
        case 3:
            main_character.stats.DAMAGE += 1;
            Sp -= 1;
            break;
        case 4:
            main_character.stats.MAGIC_POWER += 1;
            Sp -= 1;
            break;
        case 5:
            main_character.stats.DEFENCE += 1;
            Sp -= 1;
            break;
        case 6:
            main_character.stats.SPEED += 1;
            Sp -= 1;
            break;
        case 7:
            main_character.stats.STEALTH += 1;
            Sp -= 1;
            break;
        case 8:           
            main_character.stats.WEAPON_DAMAGE += 1;
            Sp -= 1;
            break;
        
        default:
            break;
        }
    }
    return 0;
}

Player apply_weapon_effects(Player main_character, Weapon weapon) {
    const char *src = weapon.effect ? weapon.effect : "";
    char *copy = strdup(src);
    if (!copy) return main_character;

    char *saveptr = NULL;
    char *first = strtok_r(copy, " ", &saveptr);
    char *second = strtok_r(NULL, " ", &saveptr);

    int boost = first ? atoi(first) : 0;
    const char *Attribute = second;
    if (Attribute) {
        if (strcmp(Attribute,"DEFENCE")==0) main_character.stats.DEFENCE += boost;
        else if (strcmp(Attribute,"MAX_HP")==0) main_character.stats.MAX_HP += boost;
        else if (strcmp(Attribute,"MAX_MANA")==0) main_character.stats.MAX_MANA += boost;
        else if (strcmp(Attribute,"MAGIC_POWER")==0) main_character.stats.MAGIC_POWER += boost;
        else if (strcmp(Attribute,"WEAPON_DAMAGE")==0) main_character.stats.WEAPON_DAMAGE += boost;
        else if (strcmp(Attribute,"DAMAGE")==0) main_character.stats.DAMAGE += boost;
        else if (strcmp(Attribute,"SPEED")==0) main_character.stats.SPEED += boost;
        else if (strcmp(Attribute,"STEALTH")==0) main_character.stats.STEALTH += boost;
    }
    if(copy)free(copy);
    return main_character;
}

Player remove_weapon_effects(Player main_character, Weapon weapon) {
    const char *src = weapon.effect ? weapon.effect : "";
    char *copy = strdup(src);
    if (!copy) return main_character;

    char *saveptr = NULL;
    char *first = strtok_r(copy, " ", &saveptr);
    char *second = strtok_r(NULL, " ", &saveptr);

    int boost = first ? atoi(first) : 0;
    const char *Attribute = second;
    if (Attribute) {
        if (strcmp(Attribute,"DEFENCE")==0) main_character.stats.DEFENCE -= boost;
        else if (strcmp(Attribute,"MAX_HP")==0) main_character.stats.MAX_HP -= boost;
        else if (strcmp(Attribute,"MAX_MANA")==0) main_character.stats.MAX_MANA -= boost;
        else if (strcmp(Attribute,"MAGIC_POWER")==0) main_character.stats.MAGIC_POWER -= boost;
        else if (strcmp(Attribute,"WEAPON_DAMAGE")==0) main_character.stats.WEAPON_DAMAGE -= boost;
        else if (strcmp(Attribute,"DAMAGE")==0) main_character.stats.DAMAGE -= boost;
        else if (strcmp(Attribute,"SPEED")==0) main_character.stats.SPEED -= boost;
        else if (strcmp(Attribute,"STEALTH")==0) main_character.stats.STEALTH -= boost;
    }
    if(copy)free(copy);
    return main_character;
}

Player check_hunger(Player main_character) {
    if (main_character.HUNGER >= 100) {
        printf("You are starving! Find food quickly!\n");
        main_character.HP -= 10; // Lose health due to starvation
    } else if (main_character.HUNGER >= 75) {
        printf("You are very hungry.\n");
    } else if (main_character.HUNGER >= 50) {
        printf("You are getting hungry.\n");
    } else if (main_character.HUNGER >= 25) {
        printf("You feel a bit hungry.\n");
    } else {
        printf("You are well fed.\n");
    }
    return main_character;
    }

Player check_MANA(Player main_character) {
    if (main_character.MANA <= 0) {
        printf("You are out of mana! You cannot use abilities until you restore it. It hurts!!\n");
        main_character.HP -= 5; // Lose health due to mana depletion
        main_character.MANA = 0; // Ensure mana doesn't go negative
    } else if (main_character.MANA <= main_character.stats.MAX_MANA * 0.25) {
        printf("Your mana is low.\n");
    } else if (main_character.MANA <= main_character.stats.MAX_MANA * 0.5) {
        printf("Your mana is getting low.\n");
    } else if (main_character.MANA <= main_character.stats.MAX_MANA * 0.75) {
        printf("Your mana is at a decent level.\n");
    } else {
        printf("Your mana is full.\n");
    }
    return main_character;
}

Player increase_hunger(Player main_character, int amount) {
    main_character.HUNGER += amount;
    if (main_character.HUNGER > 100) {
        main_character.HUNGER = 100;
    }
    check_hunger(main_character);
    return main_character;
}

Player decrease_hunger(Player main_character, int amount) {
    main_character.HUNGER -= amount;
    if (main_character.HUNGER < 0) {
        main_character.HUNGER = 0;
    }
    check_hunger(main_character);
    return main_character;
}

Player heal_player(Player main_character, int heal_amount) {
    heal_amount = heal_calculation(main_character, heal_amount);
    main_character.HP += heal_amount;
    if (main_character.HP > main_character.stats.MAX_HP*10) {
        main_character.HP = (main_character.stats.MAX_HP * 10);
    }
    return main_character;
}

Player add_Mana(Player main_character, int mana_ammount){
    if(main_character.MANA == main_character.stats.MAX_MANA*10){
        printf("Your mana is already full.\n");
        return main_character;
    }
    main_character.MANA += mana_ammount;
    if (main_character.MANA > main_character.stats.MAX_MANA*10) {
        main_character.MANA = main_character.stats.MAX_MANA*10;
    }
    return main_character;
}

Player restore_mana(Player main_character) {
    int mana_amount = main_character.stats.MAX_MANA * 2; // Example: restore based on MAGIC_POWER
    main_character.MANA += mana_amount;
    if (main_character.MANA > main_character.stats.MAX_MANA*10) {
        main_character.MANA = main_character.stats.MAX_MANA*10;
    }
    return main_character;
}

float rank_exp_multiplier(int rank) {
    switch (rank) {
        case E: return 1.0f;
        case D: return 1.2f;
        case C: return 1.5f;
        case B: return 1.9f;
        case A: return 2.4f;
        case S: return 3.0f;
        default: return 1.0f;
    }
}

int exp_reward_for_npc(NPC npc) {
    int lvl = npc.LEVEL > 0 ? npc.LEVEL : 1;
    int base = 5 * (lvl * lvl + 5 * lvl); // not grindy: ~30 exp at level 1
    int reward = (int)(base * rank_exp_multiplier(npc.RANK));
    if (reward < 10) reward = 10; // floor to keep progress moving
    // Allow manual override if EXP_GIVEN is higher
    if (npc.EXP_GIVEN > reward) {
        reward = npc.EXP_GIVEN;
    }
    return reward;
}

NPC heal_npc(NPC npc, int heal_amount) {
    npc.HP += heal_amount;
    if (npc.HP > npc.MAX_HP) {
        npc.HP = npc.MAX_HP;
    }
    return npc;
}

Player use_ability(Player main_character, NPC *target_npc, int abilityID) {
    if (not_in(abilityID, main_character.abilitiesIDs, main_character.abilities_ammount)) {
        printf("Ability not found in player's abilities.\n");
        return main_character;
    }

    Abilities ability = get_ability_by_id(abilityID);
    if (ability.ID < 0) {
        printf("Invalid ability.\n");
        return main_character;
    }

    int mana_type = get_ability_mana_type(ability.ID);
    if (mana_type != BASE && not_in(mana_type, main_character.mana_elements, main_character.mana_elements_ammount)) {
        printf("You can't mold your MANA into that element yet.\n");
        return main_character;
    }

    if (main_character.MANA < ability.MANA_COST) {
        printf("Not enough mana to use %s.\n", ability.NAME);
        return main_character;
    }
    main_character.MANA -= ability.MANA_COST;

    int ability_damage = get_ability_damage_value(ability.ID);
    int ability_heal = get_ability_healing_value(ability.ID);
    Ability_Class ability_class = get_ability_class(ability.ID);
    EFFECT_TYPE effect_type = get_ability_effect_type(ability.ID);

    apply_ability_effect(&main_character, ability, target_npc);
    register_active_ability(&main_character, ability);
    printf("You used %s.\n", ability.NAME);
    
    if (target_npc && ability_damage > 0) {
        int damage = damage_calculation_with_ability(main_character, *target_npc, ability_damage, ability_class, mana_type);
        *target_npc = damage_npc(*target_npc, damage);
        printf("You dealt %d damage to %s.\n", damage, target_npc->name);
    }
    if (ability_heal > 0 && effect_type != HEAL && effect_type != GROUP) {
        main_character = heal_player(main_character, ability_heal);
        printf("You healed yourself for %d HP.\n", ability_heal);
    }

    return main_character;
}

Player npc_use_ability(Player main_character, NPC target_npc, int abilityID) {
    Abilities ability = get_ability_by_id(abilityID);
    if (ability.ID < 0) {
        printf("Invalid ability.\n");
        return main_character;
    }
    int ability_id = ability.ID;
    target_npc = npc_apply_ability(target_npc, ability_id);
    printf("%s used %s.\n", target_npc.name, ability.NAME);
    int ability_damage = get_ability_damage_value(ability_id);
    if(ability_damage > 0){
        int damage = npc_damage_calculation_with_ability(target_npc, ability_damage, main_character);
        main_character = damage_player(main_character, damage);
        printf("%s dealt %d damage to you.\n", target_npc.name, damage);
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

static int exp_required_for_next_level(int current_level) {
    int next_level = current_level + 1;
    return 25 * next_level * next_level + 75 * next_level; // gentle early, ramps later
}

Player level_up(Player main_character) {
    // Loop to handle multiple level-ups if a big reward comes in
    while (1) {
        int required_exp = exp_required_for_next_level(main_character.LEVEL);
        if (main_character.EXP < required_exp) {
            break;
        }
        main_character.EXP -= required_exp;
        main_character.LEVEL += 1;

        // Stat growth: steady, not grindy
        main_character.stats.MAX_HP += 2;
        main_character.stats.MAX_MANA += 1;
        main_character.stats.DAMAGE += 1;
        if (main_character.LEVEL % 2 == 0) {
            main_character.stats.SPEED += 1;
        }
        if (main_character.LEVEL % 5 == 0) {
            main_character.stats.MAX_HP += 1;
            main_character.stats.DAMAGE += 1;
            main_character.Skill_Points += 1; // bonus at milestones
        }

        main_character.Skill_Points += 1;

        // Refill resources
        main_character.HP = main_character.stats.MAX_HP * 10;
        main_character.MANA = main_character.stats.MAX_MANA;

        printf("Congratulations! You've reached level %d!\n", main_character.LEVEL);
    }
    return main_character;
}

NPC level_up_rival(NPC rival, int target_level) {
    if (target_level <= rival.LEVEL) {
        rival.LEVEL = target_level;
        rival.HP = rival.MAX_HP;
        rival.MANA = rival.MAX_MANA;
        return rival;
    }

    for (int next = rival.LEVEL + 1; next <= target_level; ++next) {
        rival.MAX_HP += 8;       // keep HP growth chunky so rival stays threatening
        rival.MAX_MANA += 6;     // rivals lean on abilities too
        rival.DAMAGE += 2;
        rival.DEFENCE += 1;
        if (next % 2 == 0) {
            rival.SPEED += 1;
        }
        rival.EXP_GIVEN += 5;    // scale rewards with power
    }

    rival.LEVEL = target_level;
    rival.HP = rival.MAX_HP;
    rival.MANA = rival.MAX_MANA;
    return rival;
}

Player add_mana_type(Player main_character, int mana_type) {
    if (not_in(mana_type, main_character.mana_elements, main_character.mana_elements_ammount) && mana_type >= 0) {
        main_character.mana_elements = realloc(main_character.mana_elements, (main_character.mana_elements_ammount + 1) * sizeof(int));
        main_character.mana_elements[main_character.mana_elements_ammount] = mana_type;
        main_character.mana_elements_ammount += 1;
    }
    return main_character;
}

Player remove_mana_type(Player main_character, int mana_type) {
    if (not_in(mana_type, main_character.mana_elements, main_character.mana_elements_ammount)) {
        printf("Mana type not found in player's mana types.\n");
        return main_character;
    }
    for (int i = 0; i < main_character.mana_elements_ammount; i++) {
        if (main_character.mana_elements[i] == mana_type) {
            for (int k = i; k < main_character.mana_elements_ammount - 1; k++) {
                main_character.mana_elements[k] = main_character.mana_elements[k + 1];
            }
            main_character.mana_elements_ammount -= 1;
            main_character.mana_elements = realloc(main_character.mana_elements, main_character.mana_elements_ammount * sizeof(int));
            break;
        }
    }
    return main_character;
}

int has_mana_type(Player main_character, int mana_type) { return !not_in(mana_type, main_character.mana_elements, main_character.mana_elements_ammount); }

int get_ability_by_summon(int summonID) { 
    Abilities ability;
    for (int i = 0; i < TOTAL_ABILITIES; i++) { 
        if (ability.EFFECT_TYPE == SUMMON && atoi(ability.EFFECT) == summonID) {
            return ability.ID;

        }
    } 
    return -1; // No ability found for this summon

}

Player add_DNA(Player main_character, int dna_id) {
    if (not_in(dna_id, main_character.DNA, main_character.DNA_ammount)) {
        main_character.DNA = realloc(main_character.DNA, (main_character.DNA_ammount + 1) * sizeof(int));
        main_character.DNA[main_character.DNA_ammount] = dna_id;
        main_character.DNA_ammount += 1;
    }
    return main_character;
}

Player remove_DNA(Player main_character, int dna_id) {
    if (not_in(dna_id, main_character.DNA, main_character.DNA_ammount)) {
        printf("DNA not found in player's DNA.\n");
        return main_character;
    }
    for (int i = 0; i < main_character.DNA_ammount; i++) {
        if (main_character.DNA[i] == dna_id) {
            for (int k = i; k < main_character.DNA_ammount - 1; k++) {
                main_character.DNA[k] = main_character.DNA[k + 1];
            }
            main_character.DNA_ammount -= 1;
            main_character.DNA = realloc(main_character.DNA, main_character.DNA_ammount * sizeof(int));
            break;
        }
    }
    return main_character;
}
