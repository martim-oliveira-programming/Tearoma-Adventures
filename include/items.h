#ifndef ITEMS_H
#define ITEMS_H
#include "mechanics.h"

//Inventory Management
Player add_inventory(Player main_character, int itemID, int amount);
Player remove_inventory(Player main_character, int itemID, int amount);

//Equip/Unequip
Player equip_item(Player main_character, int itemID);
Player unequip_item(Player main_character, int slot);

//Item helper functions
const char *item_type_to_string(int type);
const char *equipped_item_name(int item_id);

//Inventory menu
void open_inventory(Player *main_character);

//Item usage
void use_item(Player *main_character, int item_id);
void use_consumable(Player *main_character, int item_id);
Player apply_weapon_effects(Player main_character, Weapon weapon);
Player remove_weapon_effects(Player main_character, Weapon weapon);
Player sort_items(Player main_character);

//Item type checks
int is_consumable_item(int item_id);
int is_key_item(int item_id);
int is_weapon_item(int item_id);

#endif
