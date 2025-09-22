#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"
#include <unistd.h> 

void get_attributes(Player *main_character) {
    if (main_character->build == Assassin) {
        add_inventory(*main_character,2,1);
        add_inventory(*main_character,3,1);
        add_ability(*main_character,10);
        
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
        add_inventory(*main_character,4,1);
        add_inventory(*main_character,5,1);
        add_ability(*main_character,2);
        
        add_inventory(*main_character,6,1);
        add_inventory(*main_character,7,1);
        add_inventory(*main_character,8,1);
        add_inventory(*main_character,9,1);
        
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
    else if (main_character->build == "Monk") {

        add_ability(*main_character,3);  

        // Initialize armor

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
        main_character->weapon = "Basic Katana";
        main_character->weapon_OFF_Hand = "Shuriken";
        add_ability(*main_character,4);
        
        // Initialize armor slots
        add_inventory(*main_character,6,1);//Headband
        strcpy(main_character->armor[1], "Ninja chestplate");
        strcpy(main_character->armor[2], "Ninja pants");
        strcpy(main_character->armor[3], "Soundless sandals");
        
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
        add_inventory(*main_character,11,1);

        add_ability(*main_character,5); 
        add_ability(*main_character,6); 
        
        // Initialize armor
        //TODO Armors to items transform in ints
        add_inventory(*main_character,13,1);

        
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
        add_inventory(*main_character,6,1);
        add_ability(*main_character,6);
        add_ability(*main_character,7); 
        
        add_inventory(*main_character,12,1);

        
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
        add_inventory(*main_character,6,1);

        add_ability(*main_character,6);
        add_ability(*main_character,8);
        
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

//TODO PLUS abilities
void apply_ability_effect(Player *main_character ,Abilities player_ability){
    if (player_ability.EFFECT_TYPE == NONE){
    }
    else if(player_ability.EFFECT_TYPE == BOOST){
        char *effect = player_ability.EFFECTS;
        char *multiplier_str = strtok(effect," ");
        char *Attribute = strtok(NULL,"");
        float multiplier = atof(multiplier_str);
        free(effect);
        free(multiplier_str);

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
        free(Attribute);
    }
    else if(player_ability.EFFECT_TYPE == SUMMON){
        char *effect = player_ability.EFFECTS;
        char *ammount_str = strtok(effect," ");
        char *SUMMON = strtok(NULL,"");
        int ammount = atoi(ammount_str);
        int summon_id = atoi(SUMMON);
        free(effect);
        free(ammount_str);
        free(SUMMON);


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
    main_character.inventoryIDs = realloc(main_character.inventoryIDs,main_character.item_ammount + amount * sizeof(int));
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
                main_character.inventoryIDs = realloc(main_character.inventoryIDs, main_character.item_ammount * sizeof(int));
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

//TODO equip_weapons()
