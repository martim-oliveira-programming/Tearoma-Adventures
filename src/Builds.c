#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "story.h"
#include "mechanics.h"
#include "utils.h"
#include "save.h"
#include "menu.h"
#include <unistd.h> 

void get_attributes(Player *main_character) {
    if (main_character->build == Assassin) {
        *main_character = add_inventory(*main_character,2,1); //Basic Dagger
        *main_character = add_inventory(*main_character,3,1); //Secondary Dagger
        *main_character = add_ability(*main_character,10); //Invisibility
        
        main_character->stats = (Attributes){
            .DEFENCE = 0,
            .DAMAGE = 4,
            .MAGIC_POWER = 1,
            .MAX_HP = 3,
            .MOUNT = NULL,
            .MAX_MANA = 10,
            .SUMMONS_STORAGE = 0,
            .SPEED = 20,
            .STEALTH = 10,
            .WEAPON_DAMAGE = 12,
            .WEAPON_USER = true,
            .DUAL_WILDING = true,
            .MAGIC_USER = true,
        };//Total:60
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
            .DEFENCE = 10,
            .DAMAGE = 4,
            .MAGIC_POWER = 1,
            .MAX_HP = 20,
            .MOUNT = NULL,
            .MAX_MANA = 4,
            .SUMMONS_STORAGE = 0,
            .SPEED = 5,
            .STEALTH = 4,
            .WEAPON_DAMAGE = 12,
            .WEAPON_USER = true,
            .DUAL_WILDING = false,
            .MAGIC_USER = true,
        };//Total:60
    }
    else if (main_character->build == Monk) {

        *main_character = add_ability(*main_character,3); //Lethal Punch Barrage 

        *main_character = add_inventory(*main_character,6,1);//Headband
        
        main_character->stats = (Attributes){
            .DEFENCE = 0,
            .DAMAGE = 30,
            .MAGIC_POWER = 0,
            .MAX_HP = 10,
            .MOUNT = NULL,
            .MAX_MANA = 10,
            .SUMMONS_STORAGE = 0,
            .SPEED = 20,
            .STEALTH = 9,
            .WEAPON_DAMAGE = 0,
            .WEAPON_USER = false,
            .DUAL_WILDING = false,
            .MAGIC_USER = false,
        };//Total:80. Higher because the player will never be able to use magic or weapons.
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
            .DEFENCE = 0,
            .DAMAGE = 2,
            .MAGIC_POWER = 8,
            .MAX_HP = 2,
            .MOUNT = NULL,
            .MAX_MANA = 8,
            .SUMMONS_STORAGE = 0,
            .SPEED = 13,
            .STEALTH = 15,
            .WEAPON_DAMAGE = 12,
            .WEAPON_USER = true,
            .DUAL_WILDING = false,
            .MAGIC_USER = true,
        };//Total:60
    }
    else if (main_character->build == Mage) {
        *main_character = add_inventory(*main_character,11,1); //Basic Grimoire
        *main_character = add_inventory(*main_character,13,1); //Mage Robe

        *main_character = add_ability(*main_character,5); //Fire Bolt
        *main_character = add_ability(*main_character,6); //Basic Healing
        
        main_character->stats = (Attributes){
            .DEFENCE = 0,
            .DAMAGE = 4,
            .MAGIC_POWER = 20,
            .MAX_HP = 4,
            .MOUNT = NULL,
            .MAX_MANA = 13,
            .SUMMONS_STORAGE = 0,
            .SPEED = 5,
            .STEALTH = 4,
            .WEAPON_DAMAGE = 10,
            .WEAPON_USER = true,
            .DUAL_WILDING = false,
            .MAGIC_USER = true,
        };//Total:60
    }
    else if (main_character->build == Healer) {
        *main_character = add_inventory(*main_character,6,1); //Headband
        *main_character = add_inventory(*main_character,12,1); //Healer's Glove

        *main_character = add_ability(*main_character,6); //Basic Healing
        *main_character = add_ability(*main_character,7); //Group Healing
          
        main_character->stats = (Attributes){
            .DEFENCE = 0,
            .DAMAGE = 0,
            .MAGIC_POWER = 10,
            .MAX_HP = 5,
            .MOUNT = NULL,
            .MAX_MANA = 17,
            .SUMMONS_STORAGE = 0,
            .SPEED = 6,
            .STEALTH = 12,
            .WEAPON_DAMAGE = 10,
            .WEAPON_USER = true,
            .DUAL_WILDING = false,
            .MAGIC_USER = true,
        };//Total:60
    }
    else if (main_character->build == Summoner) {
        *main_character = add_inventory(*main_character,6,1); //Headband
        *main_character = add_inventory(*main_character,11,1); //Basic Grimoire

        *main_character = add_ability(*main_character,6); //Basic Healing
        *main_character = add_ability(*main_character,8); //Shadow Dog Summon
        
        main_character->stats = (Attributes){
            .DEFENCE = 0,
            .DAMAGE = 0,
            .MAGIC_POWER = 11,
            .MAX_HP = 7,
            .MOUNT = NULL,
            .MAX_MANA = 18,
            .SUMMONS_STORAGE = 2,
            .SPEED = 6,
            .STEALTH = 12,
            .WEAPON_DAMAGE = 2,
            .WEAPON_USER = true,
            .DUAL_WILDING = false,
            .MAGIC_USER = true,
        };//Total:60
    }

    else if (main_character->build == Balanced) {
        *main_character = add_inventory(*main_character,4,1);
        *main_character = add_inventory(*main_character,6,1);
        *main_character = add_ability(*main_character,5);
        *main_character = add_ability(*main_character,9);
        
        *main_character = add_inventory(*main_character,7,1);
        *main_character = add_inventory(*main_character,8,1);
        
        main_character->stats = (Attributes){
            .DEFENCE = 6,
            .DAMAGE = 6,
            .MAGIC_POWER = 6,
            .MAX_HP = 6,
            .MOUNT = NULL,
            .MAX_MANA = 6,
            .SUMMONS_STORAGE = 6,
            .SPEED = 6,
            .STEALTH = 6,
            .WEAPON_DAMAGE = 6,
            .WEAPON_USER = true,
            .DUAL_WILDING = true,
            .MAGIC_USER = true,
        };//Total:60
    }
}

void apply_ability_effect(Player *main_character ,Abilities player_ability){
    if (player_ability.EFFECT_TYPE == NONE) {
        return;
    }

    const char *src = player_ability.EFFECTS ? player_ability.EFFECTS : "";
    char *copy = strdup(src);
    if (!copy) return;

    char *saveptr = NULL;
    char *first = strtok_r(copy, " ", &saveptr);
    char *second = strtok_r(NULL, " ", &saveptr);

    if (player_ability.EFFECT_TYPE == BOOST) {
        float multiplier = first ? atof(first) : 1.0f;
        const char *Attribute = second;
        if (Attribute) {
            if (strcmp(Attribute,"DEFENCE")==0) main_character->stats.DEFENCE *= multiplier;
            else if (strcmp(Attribute,"MAX_HP")==0) main_character->stats.MAX_HP *= multiplier;
            else if (strcmp(Attribute,"MAX_MANA")==0) main_character->stats.MAX_MANA *= multiplier;
            else if (strcmp(Attribute,"MAGIC_POWER")==0) main_character->stats.MAGIC_POWER *= multiplier;
            else if (strcmp(Attribute,"WEAPON_DAMAGE")==0) main_character->stats.WEAPON_DAMAGE *= multiplier;
            else if (strcmp(Attribute,"DAMAGE")==0) main_character->stats.DAMAGE *= multiplier;
            else if (strcmp(Attribute,"SPEED")==0) main_character->stats.SPEED *= multiplier;
            else if (strcmp(Attribute,"STEALTH")==0) main_character->stats.STEALTH *= multiplier;
        }
    }
    else if (player_ability.EFFECT_TYPE == SUMMON) {
        int summon_id = first ? atoi(first) : -1;
        if (summon_id != -1) {
            *main_character->team = add_team_member(*(main_character->team), summon_id, true);
        
        }
    }

    else if (player_ability.EFFECT_TYPE == PLUS) {
        int boost = first ? atoi(first) : 0;
        const char *Attribute = second;
        if (Attribute) {
            if (strcmp(Attribute,"DEFENCE")==0) main_character->stats.DEFENCE += boost;
            else if (strcmp(Attribute,"MAX_HP")==0) main_character->stats.MAX_HP += boost;
            else if (strcmp(Attribute,"MAX_MANA")==0) main_character->stats.MAX_MANA += boost;
            else if (strcmp(Attribute,"MAGIC_POWER")==0) main_character->stats.MAGIC_POWER += boost;
            else if (strcmp(Attribute,"WEAPON_DAMAGE")==0) main_character->stats.WEAPON_DAMAGE += boost;
            else if (strcmp(Attribute,"DAMAGE")==0) main_character->stats.DAMAGE += boost;
            else if (strcmp(Attribute,"SPEED")==0) main_character->stats.SPEED += boost;
            else if (strcmp(Attribute,"STEALTH")==0) main_character->stats.STEALTH += boost;
        }
    }
    else if (player_ability.EFFECT_TYPE == GROUP) {
        int team_heal = first ? atoi(first) : 0;
        int team_boost = second ? atoi(second) : 0;
        if (team_heal > 0) {
            main_character->HP += team_heal;
            if (main_character->HP > main_character->stats.MAX_HP) {
                main_character->HP = main_character->stats.MAX_HP;
            }
            for (int i = 0; i < main_character->team->size; i++) {
                NPC *member = get_npc_by_id(main_character->team->memberIDs[i]);
                if (member) {
                    member->HP += team_heal;
                    if (member->HP > member->MAX_HP) {
                        member->HP = member->MAX_HP;
                    }
                }
            }
    }
        if (team_boost > 0) {
            main_character->stats.DAMAGE += team_boost;
            for (int i = 0; i < main_character->team->size; i++) {
                NPC *member = get_npc_by_id(main_character->team->memberIDs[i]);
                if (member) {
                    member->DAMAGE += team_boost;
                }
            }
        }
    }
    if (copy)free(copy);
}

NPC *get_summon_by_id(int id){
    for(int i = 0;i<TOTAL_SUMMONS;i++){
        if (ALL_summons[i].ID == id){
            return &ALL_summons[i];
        }
    }
    return NULL;
}

Abilities* get_ability_by_id(int id) {
    for (int i = 0; i < TOTAL_ABILITIES; i++) {
        if (ALL_abilities[i].ID == id) {
            return &ALL_abilities[i];
        }
    }
    return NULL; // Not found
}

NPC* get_npc_by_id(int id){
    for(int i = 0;i<TOTAL_SUMMONS;i++){
        if (ALL_summons[i].ID == id){
            return &ALL_summons[i];
        }
    }
    return NULL;
}

Items* get_items_by_id(int id){
    for(int i = 0;i<TOTAL_ITEMS;i++){
        if (ALL_items[i].ID == id){
            return &ALL_items[i];
        }
    }
    return NULL;
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

Player equip_item(Player main_character, int itemID) {
    Items *item = get_items_by_id(itemID);
    if (item == NULL || item->item_type != WEAPON) {
        printf("Item cannot be equipped.\n");
        return main_character;
    }

    int slot = item->equipable;
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
        if (main_character.armor[slot] != -1) {
            main_character = unequip_item(main_character, slot);
        }
        main_character.armor[slot] = itemID;
    } else {
        printf("Invalid equip slot.\n");
        return main_character;
    }
    main_character = apply_item_effects(main_character, *item);
    main_character = remove_inventory(main_character, itemID, 1);
    return main_character;
}

Player unequip_item(Player main_character, int slot) {
    if (slot == MAIN_HAND) {
        if (main_character.weapon == -1) {
            printf("No weapon equipped in main hand.\n");
            return main_character;
        }
        main_character = apply_item_effects(main_character, *get_items_by_id(main_character.weapon));
        main_character = add_inventory(main_character, main_character.weapon, 1);
        main_character.weapon = -1;
    } else if (slot == OFF_HAND) {
        if (main_character.weapon_OFF_Hand == -1) {
            printf("No weapon equipped in off hand.\n");
            return main_character;
        }
        main_character = apply_item_effects(main_character, *get_items_by_id(main_character.weapon_OFF_Hand));
        main_character = add_inventory(main_character, main_character.weapon_OFF_Hand, 1);
        main_character.weapon_OFF_Hand = -1;
    } else if (slot >= HEAD && slot <= SHOES) {
        if (main_character.armor[slot] == -1) {
            printf("No armor equipped in this slot.\n");
            return main_character;
        }
        main_character = apply_item_effects(main_character, *get_items_by_id(main_character.armor[slot]));
        main_character = add_inventory(main_character, main_character.armor[slot], 1);
        main_character.armor[slot] = -1;
    } else {
        printf("Invalid equip slot.\n");
        return main_character;
    }
    return main_character;
}

Player add_summon(Player main_character, int summonID){
    // Check if summon already exists
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

NPC_Team add_team_member(NPC_Team team, int memberID, bool is_summon) {
    if (is_summon) {
        team.summonIDs = realloc(team.summonIDs, (team.size + 1) * sizeof(int));
        team.summonIDs[team.size] = memberID;

    } else {
    team.memberIDs = realloc(team.memberIDs, (team.size + 1) * sizeof(int));
    team.memberIDs[team.size] = memberID;
    }
    team.size += 1;
    return team;
}

NPC_Team remove_team_member(NPC_Team team, int memberID, bool is_summon) {
    if (is_summon) {
        for (int i = 0; i < team.size; i++) {
            if (team.summonIDs[i] == memberID) {
                // Shift left
                for (int k = i; k < team.size - 1; k++) {
                    team.summonIDs[k] = team.summonIDs[k + 1];
                }
                team.size -= 1;
                team.summonIDs = realloc(team.summonIDs, team.size * sizeof(int));
                break;
            }
        }
    } else {
    for (int i = 0; i < team.size; i++) {
        if (team.memberIDs[i] == memberID) {
            // Shift left
            for (int k = i; k < team.size - 1; k++) {
                team.memberIDs[k] = team.memberIDs[k + 1];
            }
            team.size -= 1;
            team.memberIDs = realloc(team.memberIDs, team.size * sizeof(int));
            break;
        }
    }
}
    team.size -= 1;
    return team;
}

int is_team_member(NPC_Team team, int memberID, bool is_summon) {
    if (is_summon) {
        for (int i = 0; i < team.size; i++) {
            if (team.summonIDs[i] == memberID) {
                return 1; // Found
            }
        }
    } else {
    for (int i = 0; i < team.size; i++) {
        if (team.memberIDs[i] == memberID) {
            return 1; // Found
        }
    }
}
    return 0; // Not found
}

void free_team(NPC_Team *team) {
    if (team->memberIDs) {
        free(team->memberIDs);
        team->memberIDs = NULL;
    }
    if (team->summonIDs) {
        free(team->summonIDs);
        team->summonIDs = NULL;
    }
    team->size = 0;
}

static const char *item_type_to_string(int type) {
    switch (type) {
        case CONSUMABLE: return "Consumable";
        case KEY:        return "Key";
        case WEAPON:     return "Weapon";
        default:         return "Unknown";
    }
}

void open_inventory(Player *main_character) {
    printf("---- Inventory ----\n");
    if (main_character->item_ammount == 0) {
        printf("Inventory is empty.\n");
        return;
    }

    int index = 0;
    int printed = 0;
    while (index < main_character->item_ammount) {
        int current_id = main_character->inventoryIDs[index];
        int count = 1;
        while (index + count < main_character->item_ammount && main_character->inventoryIDs[index + count] == current_id) {
            count++;
        }
        Items *item = get_items_by_id(current_id);
        if (item) {
            printf("%d. %dx %s (%s) ID(%d)\n", ++printed, count, item->name, item_type_to_string(item->item_type), item->ID);
        } else {
            printf("%d. %dx Unknown Item (ID: %d)\n", ++printed, count, current_id);
        }
        index += count;
    }

    while (1) {
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
    Items *item = get_items_by_id(item_id);
    if (item == NULL) {
        printf("Invalid item.\n");
        return;
    }
    if (item->item_type == CONSUMABLE) {
        *main_character = decrease_hunger(*main_character, item->healling);
        *main_character = remove_inventory(*main_character, item_id, 1);
        printf("You used %s and restored %d hunger.\n", item->name, item->healling);
        
        return;
    }
    else if (item->item_type == WEAPON) {
        *main_character = equip_item(*main_character, item_id);
        printf("You equipped %s.\n", item->name);
        return;
    }
    else if (item->item_type == KEY) {
        printf("You can't use %s right now!!.\n", item->name);
        return;
    }
    else {
        printf("Item type not usable.\n");
        return;
    }    
}

Player apply_item_effects(Player main_character, Items item) {
    if (item.effect_type == NONE) {
        return main_character;
    }

    const char *src = item.effect ? item.effect : "";
    char *copy = strdup(src);
    if (!copy) return main_character;

    char *saveptr = NULL;
    char *first = strtok_r(copy, " ", &saveptr);
    char *second = strtok_r(NULL, " ", &saveptr);

    if (item.effect_type == BOOST) {
        float multiplier = first ? strtof(first, NULL) : 1.0f;
        const char *Attribute = second;
        if (Attribute) {
            if (strcmp(Attribute,"DEFENCE")==0) main_character.stats.DEFENCE *= multiplier;
            else if (strcmp(Attribute,"MAX_HP")==0) main_character.stats.MAX_HP *= multiplier;
            else if (strcmp(Attribute,"MAX_MANA")==0) main_character.stats.MAX_MANA *= multiplier;
            else if (strcmp(Attribute,"MAGIC_POWER")==0) main_character.stats.MAGIC_POWER *= multiplier;
            else if (strcmp(Attribute,"WEAPON_DAMAGE")==0) main_character.stats.WEAPON_DAMAGE *= multiplier;
            else if (strcmp(Attribute,"DAMAGE")==0) main_character.stats.DAMAGE *= multiplier;
            else if (strcmp(Attribute,"SPEED")==0) main_character.stats.SPEED *= multiplier;
            else if (strcmp(Attribute,"STEALTH")==0) main_character.stats.STEALTH *= multiplier;
        }
    }
    else if (item.effect_type == PLUS) {
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
    }

    if(copy)free(copy);
    return main_character;
}

Player remove_item_effects(Player main_character, Items item) {
    if (item.effect_type == NONE) {
        return main_character;
    }

    const char *src = item.effect ? item.effect : "";
    char *copy = strdup(src);
    if (!copy) return main_character;

    char *saveptr = NULL;
    char *first = strtok_r(copy, " ", &saveptr);
    char *second = strtok_r(NULL, " ", &saveptr);

    if (item.effect_type == BOOST) {
        float multiplier = first ? strtof(first, NULL) : 1.0f;
        const char *Attribute = second;
        if (Attribute) {
            if (strcmp(Attribute,"DEFENCE")==0) main_character.stats.DEFENCE /= multiplier;
            else if (strcmp(Attribute,"MAX_HP")==0) main_character.stats.MAX_HP /= multiplier;
            else if (strcmp(Attribute,"MAX_MANA")==0) main_character.stats.MAX_MANA /= multiplier;
            else if (strcmp(Attribute,"MAGIC_POWER")==0) main_character.stats.MAGIC_POWER /= multiplier;
            else if (strcmp(Attribute,"WEAPON_DAMAGE")==0) main_character.stats.WEAPON_DAMAGE /= multiplier;
            else if (strcmp(Attribute,"DAMAGE")==0) main_character.stats.DAMAGE /= multiplier;
            else if (strcmp(Attribute,"SPEED")==0) main_character.stats.SPEED /= multiplier;
            else if (strcmp(Attribute,"STEALTH")==0) main_character.stats.STEALTH /= multiplier;
        }
    }
    else if (item.effect_type == PLUS) {
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

void check_hp(Player *main_character, Story *story,NPC* npcs) {
    if (main_character->HP <= 0) {
        printf("You have died!\n");
        load_save(story, main_character, npcs);
    }
}

Player heal_player(Player main_character, int heal_amount) {
    main_character.HP += heal_amount;
    if (main_character.HP > main_character.stats.MAX_HP) {
        main_character.HP = main_character.stats.MAX_HP;
    }
    return main_character;
}

Player damage_player(Player main_character, int damage_amount, Story *story,NPC* npcs) {
    main_character.HP -= damage_amount;
    check_hp(&main_character, story, npcs);
    return main_character;
}
