#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "story.h"
#include "menu.h"
#include "mechanics.h"
#include "items.h"
#include "abilities.h"
#include "npc.h"
#include "save.h"
#include "fights.h"
#include "dialogue.h"
#include <unistd.h> 

Player character_creation(void) {
    Player main_character = {0}; // Zero-initialize first
    //char *gender= get_input("Are you a boy or a girl?\n");
    int gender_choice = ask("Are you a boy or a girl?", "Boy", "Girl",NULL);
    main_character.gender = gender_choice;
    
    main_character.name = get_input("What is your character's name?\n");
    main_character.hair_colour = get_input("What is your character's hair colour?\n");
    main_character.age = 15;
    main_character.RANK = E;
    main_character.stats.PERCEPTION = 3;
    main_character.team_memberIDs = malloc(1 * sizeof(int));
    main_character.inventoryIDs= malloc(1 * sizeof(int));
    main_character.abilitiesIDs= malloc(1 * sizeof(int));
    main_character.summonIDs= malloc(1 * sizeof(int));
    main_character.equipped_items = malloc(MAX_EQUIPPED_ITEMS * sizeof(int));
    main_character.mana_elements = malloc(1 * sizeof(int));
    main_character = add_mana_type(main_character, BASE); // Start with Dorment mana type
    main_character.DNA = malloc(1 * sizeof(int));
    main_character.DNA_ammount = 0;
    main_character = add_DNA(main_character, All); //All means everyone can learn these abilities
    main_character.mana_elements_ammount = 1;
    main_character.team_size = 0;
    main_character.item_ammount = 0;
    main_character.HUNGER = 0;
    main_character.Skill_Points = 0;
    main_character.LEVEL = 0;
    main_character.EXP = 0;

    // Initialize empty armor
    for (int i = 0; i < 4; i++) {
        main_character.armor[i] = -1;
    }
    say(0,"\nThe build you choose for your character will give you your initial attributes and possible weapons/abilities but you can nourish your other abilities throughout the story.\n");
    say(1,"Select a build for your character:\n");
    int build_input = ask(
    "Assassin: Very high Speed and great with long range weapons and dual wielding daggers.\n"
    "Tank: High Health and Strength. Is able to use powerful shields.\n"
    "Monk: High Strength, Speed and Health. Does not use weapons or Magic.\n"
    "Ninja: Very high Stealth, close range Weapon Usage and midium magic usage.\n"
    "Mage: High Magic Power and Mana reserves. Mostely a mid to long range attacker.\n"
    "Healer: High Magic Power and Mana reserves. Mostely but not limited to Healing Magic.\n"
    "Summoner: Is abble to summon creatures to aid in combat or other situations.\n"
    "Balanced: Evenly distibuited tallent. 'Jack of all trades, master of none'.\n","Assassin","Tank","Monk","Ninja","Mage","Healer","Summoner","Balanced",NULL);

    
    main_character = set_mc_build(main_character, build_input);
    main_character.money = 0; // Starting money
    main_character.abilitiesIDs = malloc(1 * sizeof(int));
    main_character.abilities_ammount = 0;
    main_character.summonIDs = malloc(1 * sizeof(int));
    main_character.summons_ammount = 0;
    main_character.stats = (Attributes){0}; // Zero-initialize stats
    get_attributes(&main_character);
    main_character.HP = main_character.stats.MAX_HP;
    main_character.MANA = main_character.stats.MAX_MANA;
    main_character.HP *= 10;
    main_character.MANA *= 10;
    main_character.GOODNESS = 0;
    main_character.weapon = -1; // No weapon equipped
    main_character.weapon_OFF_Hand = -1; // No off-hand weapon equipped
    return main_character;
}

//TODO: Make the story more descriptive
Player play_chapter(Player main_character, Story *story, int *chapter_npc_ids) {
    const char* pronoun = choose_pronoun(main_character);

    switch (story->Chapter)
    {
    case Chapter_1:{
        return chapter1(main_character,story);
    }
    case Chapter_2:{
        NPC rival;
        int rival_id = (main_character.gender == Boy) ? 0 : 1;
        chapter_npc_ids[0] = rival_id; // Store rival's ID for later reference
        rival = get_npc_by_id(rival_id);
        if (rival.ID < 0) {
            say(0,"Error: rival NPC not found for id %d.\n", rival_id);
            rival = (NPC){0};
        }
        main_character = chapter_2(main_character, story, chapter_npc_ids);
        return main_character;
        break;
    }
    case Chapter_3:{
        say(0,"-------------------------\nChapter 3: To Be Continued...\n-------------------------\n");
        sleep(1);
        //Temporary fight to test the fight function and the chapter transition, will be replaced by the actual chapter content later
        NPC rival;
        int rival_id = (main_character.gender == Boy) ? 0 : 1;
        chapter_npc_ids[0] = rival_id; // Store rival's ID for later reference
        rival = get_npc_by_id(rival_id);
        open_inventory(&main_character);
        main_character = fight(main_character, rival, story, NULL, false);
        main_character = lost_fight(main_character, story, chapter_npc_ids); // Check if player lost the fight and handle it
        
        sleep(5);
        say(0,"-------------------------\nChapter 3 Completed\n-------------------------\n");
        //story->Chapter = Chapter_4;
        return main_character;
        break;
    }
    return main_character;
    }



    return main_character;
}

void open_player_menu(Player *main_character) {
    while (1) {
        say(0,"---- Player Menu ----\n");
        say(0,"View Stats\n");
        say(0,"Open Inventory\n");
        say(0,"See Abilities\n");
        say(0,"Exit Menu\n");

        int choice = ask("Choose an option:", "View Stats", "Open Inventory", "See Abilities", "Exit Menu", NULL);

        if (choice == 3) {
            break;
        }
        switch (choice) {
            case 0:
                player_stats(*main_character);
                break;
            case 1:
                open_inventory(main_character);
                break;
            case 2: {
                open_abilities(main_character);
                break;
            }
            default:
                say(0,"Invalid option. Please try again.\n");
                break;
        }
    }
}

void print_player_info(Player main_character) {
    say(0,"You have %d€.\n", main_character.money);
    say(0,"Hunger: %d/100\n\n", main_character.HUNGER);
    say(0,"You have %d Skill Points to use.\n", main_character.Skill_Points);
    
    say(0,"---- Player Stats ----\n");
    say(0,"HP: %d/%d\n", main_character.HP, main_character.stats.MAX_HP);
    say(0,"Mana: %d/%d\n", main_character.MANA, main_character.stats.MAX_MANA);
    say(0,"Damage: %d\n", main_character.stats.DAMAGE);
    say(0,"Magic Power: %d\n", main_character.stats.MAGIC_POWER);
    say(0,"Defence: %d\n", main_character.stats.DEFENCE);
    say(0,"Speed: %d\n", main_character.stats.SPEED);
    say(0,"Stealth: %d\n", main_character.stats.STEALTH);
    say(0,"Weapon Damage: %d\n", main_character.stats.WEAPON_DAMAGE);
    say(0,"Preception: %d\n", main_character.stats.PERCEPTION);
    say(0,"Press 'q' to exit stats menu.\n");
}

Player player_stats(Player main_character) {

    StatUpgrade upgrades[] = {
        { &main_character.stats.MAX_HP,          10, 0  },  // 0: MAX HP
        { &main_character.stats.MAX_MANA,        0,  10 },  // 1: MAX MANA
        { &main_character.stats.DAMAGE,          0,  0  },  // 2: DAMAGE
        { &main_character.stats.MAGIC_POWER,     0,  0  },  // 3: MAGIC POWER
        { &main_character.stats.DEFENCE,         0,  0  },  // 4: DEFENCE
        { &main_character.stats.SPEED,           0,  0  },  // 5: SPEED
        { &main_character.stats.STEALTH,         0,  0  },  // 6: STEALTH
        { &main_character.stats.WEAPON_DAMAGE,   0,  0  },  // 7: WEAPON DAMAGE
    };
    int num_upgrades = sizeof(upgrades) / sizeof(upgrades[0]);

    int Sp = main_character.Skill_Points;
    print_player_info(main_character);
    while (Sp > 0) {
        print_player_info(main_character);
        int choice = ask("Enter the number of the stat you want to increase: ",
                         "MAX HP","MAX MANA","DAMAGE","MAGIC POWER",
                         "DEFENCE","SPEED","STEALTH","WEAPON DAMAGE","Exit",NULL);

        if (choice == num_upgrades) { // Exit
            return main_character;
        }
        if (choice < 0 || choice >= num_upgrades) {
            say(0,"Invalid choice.\n");
            continue;
        }
        *upgrades[choice].stat += 1;
        main_character = heal_player(main_character, upgrades[choice].hp_bonus); // Heal player for any HP increase
        main_character = add_Mana(main_character, upgrades[choice].mana_bonus); // Add mana for any MANA increase
        Sp -= 1;
    }
    return main_character;
}

