#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"
#include <unistd.h> 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"
#include <unistd.h> 

void get_attributes(Player *main_character) {
    if (strcmp(main_character->build, "Assassin") == 0) {
        main_character->weapon = "basic dagger";
        main_character->weapon_OFF_Hand = "basic dagger";
        main_character->abilities = (char*[]){"Speed Boost", NULL};
        
        // Initialize armor slots
        strcpy(main_character->armor[0], "");
        strcpy(main_character->armor[1], "");
        strcpy(main_character->armor[2], "");
        strcpy(main_character->armor[3], "");
        
        main_character->stats = (Attributes){
            .armor_points = 0,
            .DAMAGE = 4,
            .MAGIC_POWER = 1,
            .MAX_HP = 3,
            .MOUNT = NULL,
            .MAX_MANA = 10,
            .SPEED = 20,
            .STEALTH = 10,
            .WEAPON_DAMAGE = 15,
            .DUAL_WILDING = 1
        };
    }
    else if (strcmp(main_character->build, "Tank") == 0) {
        main_character->weapon = "basic sword";
        main_character->weapon_OFF_Hand = "basic shield";
        main_character->abilities = (char*[]){"Shield Bash", NULL};
        
        // Initialize armor
        strcpy(main_character->armor[0], "leather helmet");
        strcpy(main_character->armor[1], "leather chestplate");
        strcpy(main_character->armor[2], "leather pants");
        strcpy(main_character->armor[3], "leather boots");
        
        main_character->stats = (Attributes){
            .armor_points = 4,
            .DAMAGE = 6,
            .MAGIC_POWER = 1,
            .MAX_HP = 10,
            .MOUNT = NULL,
            .MAX_MANA = 5,
            .SPEED = 10,
            .STEALTH = 5,
            .WEAPON_DAMAGE = 12,
            .DUAL_WILDING = 0
        };
    }
    // Add other builds here...
}
