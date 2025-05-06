#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"
#include <unistd.h> 

Player character_creation() {
    Player main_character = {0}; // Zero-initialize first
    
    main_character.name = get_input("What is your character's name?\n");
    main_character.hair_colour = get_input("What is your character's hair colour?\n");
    main_character.age = 15;
    main_character.RANK = 'E';
    main_character.items = (char*[]){"", NULL};
    main_character.LEVEL = 0;
    main_character.EXP = 0;

    
    // Initialize empty armor
    for (int i = 0; i < 4; i++) {
        strcpy(main_character.armor[i], "None"); // Now safe
    }
    printf("\nThe build you choose for your character will give you your initial attributes and possible weapons/abilities but you can nourish your other abilities throughout the story.\n");
    usleep(2500);
    printf("Select a build for your character:\n");
    usleep(2500);
    main_character.build = get_input(
        "Assassin: Very high Speed and great with long range weapons and dual wielding daggers.\n"
        "Tank: High Health and Strength. Is able to use powerful shields.\n"
        "Monk: High Strength, Speed and Health. Does not use weapons or Magic.\n"
        "Ninja: Very high Stealth, close range Weapon Usage and midium magic usage.\n"
        "Mage: High Magic Power and Mana reserves. Mostely a mid to long range attacker.\n"
        "Healer: High Magic Power and Mana reserves. Mostely but not limited to Healing Magic.\n"
        "Summoner: Is abble to summon creatures to aid in combat or other situations.\n"
        "Balanced: Evenly distibuited tallent. 'Jack of all trades, master of none'.\n"
    );
    
    get_attributes(&main_character);
    main_character.stats.MAX_HP *= 10;
    main_character.stats.MAX_MANA *=10;
    main_character.HP = main_character.stats.MAX_HP;
    main_character.MANA = main_character.stats.MAX_MANA;
    main_character.GOODNESS = 0;
    return main_character;
}

