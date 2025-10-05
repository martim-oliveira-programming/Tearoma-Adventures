#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"
#include <unistd.h> 

void get_attributes(Player *main_character) {
    if (main_character->build == Assassin) {
        add_inventory(*main_character,2,1); //Basic Dagger
        add_inventory(*main_character,3,1); //Secondary Dagger
        add_ability(*main_character,10); //Invisibility
        
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
        add_inventory(*main_character,4,1); //Basic Sword
        add_inventory(*main_character,5,1); //Basic Shield
        add_ability(*main_character,2);     //Shield Bash
        
        add_inventory(*main_character,6,1); //Headband
        add_inventory(*main_character,7,1); //Leather Chestplate
        add_inventory(*main_character,8,1); //Leather Pants
        add_inventory(*main_character,9,1); //Leather Boots
        
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

        add_ability(*main_character,3); //Lethal Punch Barrage 

        add_inventory(*main_character,6,1);//Headband
        
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
        add_inventory(*main_character,14,1); //Katana
        add_inventory(*main_character,15,1); //Shuriken
        add_ability(*main_character,4); //Disguise
        add_ability(*main_character,1); //Speed Boost
        
        // Initialize armor slots
        add_inventory(*main_character,6,1);//Headband
        add_inventory(*main_character,16,1);//Ninja chestplate
        add_inventory(*main_character,17,1);//Ninja pants
        add_inventory(*main_character,18,1);//Soundless sandals
        
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
        add_inventory(*main_character,11,1); //Basic Grimoire
        add_inventory(*main_character,13,1); //Mage Robe

        add_ability(*main_character,5); //Fire Bolt
        add_ability(*main_character,6); //Basic Healing
        
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
        add_inventory(*main_character,6,1); //Headband
        add_inventory(*main_character,12,1); //Healer's Glove

        add_ability(*main_character,6); //Basic Healing
        add_ability(*main_character,7); //Group Healing
          
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
        add_inventory(*main_character,6,1); //Headband
        add_inventory(*main_character,11,1); //Basic Grimoire

        add_ability(*main_character,6); //Basic Healing
        add_ability(*main_character,8); //Shadow Dog Summon
        
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
        add_inventory(*main_character,4,1);
        add_inventory(*main_character,6,1);
        add_ability(*main_character,5);
        add_ability(*main_character,9);
        
        add_inventory(*main_character,7,1);
        add_inventory(*main_character,8,1);
        
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
    if (player_ability.EFFECT_TYPE == NONE){
    }
    else if(player_ability.EFFECT_TYPE == BOOST){
        char *effect = player_ability.EFFECTS;
        char *multiplier_str = strtok(effect," ");
        char *Attribute = strtok(NULL,"");
        float multiplier = atof(multiplier_str);

        if (strcmp(Attribute,"DEFENCE")==0){
            main_character->stats.DEFENCE *= multiplier;
        }else if (strcmp(Attribute,"MAX_HP")==0){
            main_character->stats.MAX_HP *= multiplier;
        }else if (strcmp(Attribute,"MAX_MANA")==0){
            main_character->stats.MAX_MANA *= multiplier;
        }else if (strcmp(Attribute,"MAGIC_POWER")==0){
            main_character->stats.MAGIC_POWER *= multiplier;
        }else if (strcmp(Attribute,"WEAPON_DAMAGE")==0){
            main_character->stats.WEAPON_DAMAGE *= multiplier;
        }else if (strcmp(Attribute,"DAMAGE")==0){
            main_character->stats.DAMAGE *= multiplier;
        }else if (strcmp(Attribute,"SPEED")==0){
            main_character->stats.SPEED *= multiplier;
        }else if (strcmp(Attribute,"STEALTH")==0){
            main_character->stats.STEALTH *= multiplier;
        }
    }
    else if(player_ability.EFFECT_TYPE == SUMMON){ //TODO How will summons work
        char *effect = player_ability.EFFECTS;
        char *ammount_str = strtok(effect," ");
        char *SUMMON = strtok(NULL,"");
        int ammount = atoi(ammount_str);
        int summon_id = atoi(SUMMON);
        

    }
    else if(player_ability.EFFECT_TYPE == PLUS){
        char *effect = player_ability.EFFECTS;
        char *plus_boost = strtok(effect," ");
        char *Attribute = strtok(NULL,"");
        int boost = atoi(plus_boost);


        if (strcmp(Attribute,"DEFENCE")==0){
            main_character->stats.DEFENCE += boost;
        }else if (strcmp(Attribute,"MAX_HP")==0){
            main_character->stats.MAX_HP += boost;
        }else if (strcmp(Attribute,"MAX_MANA")==0){
            main_character->stats.MAX_MANA += boost;
        }else if (strcmp(Attribute,"MAGIC_POWER")==0){
            main_character->stats.MAGIC_POWER += boost;
        }else if (strcmp(Attribute,"WEAPON_DAMAGE")==0){
            main_character->stats.WEAPON_DAMAGE += boost;
        }else if (strcmp(Attribute,"DAMAGE")==0){
            main_character->stats.DAMAGE += boost;
        }else if (strcmp(Attribute,"SPEED")==0){
            main_character->stats.SPEED += boost;
        }else if (strcmp(Attribute,"STEALTH")==0){
            main_character->stats.STEALTH += boost;
    }
}
    else if(player_ability.EFFECT_TYPE == GROUP){
        char *effect = player_ability.EFFECTS;
        char *team_boost_str = strtok(effect," ");
        char *NONE = strtok(NULL," ");
        char *zero_str = strtok(NULL," ");
        int team_boost = atoi(team_boost_str);
        //TODO Group Healling function
    }
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

Player add_inventory(Player main_character, int itemID, int amount){
    main_character.inventoryIDs = realloc(main_character.inventoryIDs,(main_character.item_ammount + amount) * sizeof(int));
    for(int i=0; i< amount; i++){
    main_character.inventoryIDs[main_character.item_ammount] = itemID;
    main_character.item_ammount +=1;
    }
    return main_character;
}

Player remove_inventory(Player main_character, int itemID, int amount){
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

Player equip_armor(Player main_character, int itemID){
    Items *item = get_items_by_id(itemID);
    if (item == NULL || item->item_type != WEAPON || item->equipable == MAIN_HAND || item->equipable == OFF_HAND){
        printf("Item cannot be equipped as armor.\n");
        return main_character;
    }
    int slot = item->equipable;
    if (slot < HEAD || slot > SHOES){
        printf("Invalid armor slot.\n");
        return main_character;
    }
    // Unequip current armor in the slot if any
    if (main_character.armor[slot] != -1) {
        main_character = add_inventory(main_character, main_character.armor[slot], 1);
    }
    // Equip new armor
    main_character.armor[slot] = itemID;
    // Remove from inventory
    main_character = remove_inventory(main_character, itemID, 1);
    return main_character;
}

Player unequip_armor(Player main_character, int slot){
    if (slot < HEAD || slot > SHOES){
        printf("Invalid armor slot.\n");
        return main_character;
    }
    if (main_character.armor[slot] == -1) {
        printf("No armor equipped in this slot.\n");
        return main_character;
    }
    // Add armor back to inventory
    main_character = add_inventory(main_character, main_character.armor[slot], 1);
    // Unequip armor
    main_character.armor[slot] = -1;
    return main_character;
}

Player equip_weapon(Player main_character, int itemID){
    Items *item = get_items_by_id(itemID);
    if (item == NULL || item->item_type != WEAPON){
        printf("Item cannot be equipped as a weapon.\n");
        return main_character;
    }
    int slot = item->equipable;
    if (slot != MAIN_HAND && slot != OFF_HAND){
        printf("Invalid weapon slot.\n");
        return main_character;
    }
    // Unequip current weapon in the slot if any
    if (slot == MAIN_HAND && main_character.weapon != -1) {
        main_character = add_inventory(main_character, main_character.weapon, 1);
    } else if (slot == OFF_HAND && main_character.weapon_OFF_Hand != -1) {
        main_character = add_inventory(main_character, main_character.weapon_OFF_Hand, 1);
    }
    // Equip new weapon
    if (slot == MAIN_HAND) {
        main_character.weapon = itemID;
    } else {
        main_character.weapon_OFF_Hand = itemID;
    }
    // Remove from inventory
    main_character = remove_inventory(main_character, itemID, 1);
    return main_character;
}

Player unequip_weapon(Player main_character, int slot){
    if (slot != MAIN_HAND && slot != OFF_HAND){
        printf("Invalid weapon slot.\n");
        return main_character;
    }
    if (slot == MAIN_HAND && main_character.weapon == -1) {
        printf("No weapon equipped in main hand.\n");
        return main_character;
    } else if (slot == OFF_HAND && main_character.weapon_OFF_Hand == -1) {
        printf("No weapon equipped in off hand.\n");
        return main_character;
    }
    // Add weapon back to inventory
    if (slot == MAIN_HAND) {
        main_character = add_inventory(main_character, main_character.weapon, 1);
        main_character.weapon = -1;
    } else {
        main_character = add_inventory(main_character, main_character.weapon_OFF_Hand, 1);
        main_character.weapon_OFF_Hand = -1;
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
