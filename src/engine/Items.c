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

Player sort_items(Player main_character){
    for (int i = 0; i < main_character.item_ammount - 1; i++) {
        for (int j = 0; j < main_character.item_ammount - i - 1; j++) {
            if (main_character.inventoryIDs[j] > main_character.inventoryIDs[j + 1]) {
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
        say(0,"Item not found in inventory.\n");
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

Player equip_item(Player main_character, int itemID) {
    Weapon weapon = get_weapon(itemID);
    if (weapon.item_id == -1) {
        say(0,"Item cannot be equipped.\n");
        return main_character;
    }
    if(!is_weapon_item(itemID)) {
        say(0,"Item is not a weapon and cannot be equipped.\n");
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
            say(0,"Invalid armor slot.\n");
            return main_character;
        }
        if (main_character.armor[armor_index] != -1) {
            main_character = unequip_item(main_character, slot);
        }
        main_character.armor[armor_index] = itemID;
    } else {
        say(0,"Invalid equip slot.\n");
        return main_character;
    }
    main_character = apply_weapon_effects(main_character, weapon);
    main_character = remove_inventory(main_character, itemID, 1);
    return main_character;
}

Player unequip_item(Player main_character, int slot) {
    if (slot == MAIN_HAND) {
        if (main_character.weapon == -1) {
            say(0,"No weapon equipped in main hand.\n");
            return main_character;
        }
        const Weapon w = get_weapon(main_character.weapon);
        main_character = remove_weapon_effects(main_character, w);
        main_character = add_inventory(main_character, main_character.weapon, 1);
        main_character.weapon = -1;
    } else if (slot == OFF_HAND) {
        if (main_character.weapon_OFF_Hand == -1) {
            say(0,"No weapon equipped in off hand.\n");
            return main_character;
        }
        const Weapon w = get_weapon(main_character.weapon_OFF_Hand);
        main_character = remove_weapon_effects(main_character, w);
        main_character = add_inventory(main_character, main_character.weapon_OFF_Hand, 1);
        main_character.weapon_OFF_Hand = -1;
    } else if (slot >= HEAD && slot <= SHOES) {
        int armor_index = slot - HEAD; // map enum to 0-3 indices
        if (armor_index < 0 || armor_index >= 4) {
            say(0,"Invalid armor slot.\n");
            return main_character;
        }
        if (main_character.armor[armor_index] == -1) {
            say(0,"No armor equipped in this slot.\n");
            return main_character;
        }
        Weapon w = get_weapon(main_character.armor[armor_index]);
        main_character = remove_weapon_effects(main_character, w);
        main_character = add_inventory(main_character, main_character.armor[armor_index], 1);
        main_character.armor[armor_index] = -1;
    } else {
        say(0,"Invalid equip slot.\n");
        return main_character;
    }
    return main_character;
}

void open_inventory(Player *main_character) {
    while (1) {
    say(0,"---- Inventory ----\n");
    if (main_character->item_ammount == 0) {
        say(0,"Inventory is empty.\n");
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
                say(0,"%d. %dx %s (%s) ID(%d)\n", ++printed, count, item.name, item_type_to_string(type_code), item.ID);
            } else {
                say(0,"%d. %dx Unknown Item (ID: %d)\n", ++printed, count, current_id);
            }
            index += count;
        }
    }

        say(0,"---- Equipped ----\n");
        say(0,"1. Main Hand: %s\n", equipped_item_name(main_character->weapon));
        say(0,"2. Off Hand: %s\n", equipped_item_name(main_character->weapon_OFF_Hand));
        say(0,"3. Head: %s\n", equipped_item_name(main_character->armor[0]));
        say(0,"4. Chest: %s\n", equipped_item_name(main_character->armor[1]));
        say(0,"5. Legs: %s\n", equipped_item_name(main_character->armor[2]));
        say(0,"6. Shoes: %s\n", equipped_item_name(main_character->armor[3]));

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
        say(0,"Item not found in inventory.\n");
        return;
    }
    Items item = get_items_by_id(item_id);
    if (item.ID < 0) {
        say(0,"Invalid item.\n");
        return;
    }
    if (is_consumable_item(item_id)) {
        use_consumable(main_character, item_id);
        return;
    } else if (is_weapon_item(item_id)) {
        *main_character = equip_item(*main_character, item_id);
        say(0,"You equipped %s.\n", item.name);
        return;
    } else if (is_key_item(item_id)) {
        say(0,"You can't use %s right now!!.\n", item.name);
        return;
    } else {
        say(0,"Item type not usable.\n");
        return;
    }
}

void use_consumable(Player *main_character, int item_id) {
    Consumable consumable = get_consumable(item_id);
    if (consumable.item_id == -1) {
        say(0,"Invalid consumable.\n");
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
            say(0,"You are already at full health. Cannot use %s.\n", item_name);
            return;
        }
        *main_character = heal_player(*main_character, hp_heal);
        say(0,"You consumed %s and restored %d health.\n", item_name, main_character->HP - temp_hp);
        *main_character = remove_inventory(*main_character, item_id, 1);
        return;
    }
    if (hunger_restore > 0) {
        if (main_character->HUNGER == 0) {
            say(0,"You are not hungry. Cannot use %s.\n", item_name);
            return;
        }
        *main_character = decrease_hunger(*main_character, hunger_restore);
        say(0,"You consumed %s and restored %d hunger.\n", item_name, temp_hunger - main_character->HUNGER);
        *main_character = remove_inventory(*main_character, item_id, 1);
        return;
    }
    if(mana_restore >0){
        if (main_character->MANA == (main_character->stats.MAX_MANA*10)){
            say(0,"You are already at full mana. Cannot use %s.\n", item_name);
            return;
        }
        *main_character = add_Mana(*main_character, mana_restore);
        say(0,"You consumed %s and restored %d mana.\n", item_name, main_character->MANA - temp_mana);
        *main_character = remove_inventory(*main_character, item_id, 1);
        return;
    }

    say(0,"This consumable has no effect right now.\n");
    return;
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
