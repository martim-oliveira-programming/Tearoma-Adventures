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
    main_character = add_DNA(main_character, Learned); //Learned means everyone can learn these abilities
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

        say(0,"-------------------------\nChapter 2: A New World!\n-------------------------\n");
        sleep(1);
        say(0,"%s-- Where am I? This place looks... strange.\nYou look around and see that you are in a huge grassy field.\n",main_character.name);
        sleep(5);
        say(0,"You see some strange plants and creatures around you.\nThe sky is a weird shade of purple and there are two suns in the sky.\n");
        sleep(5);
        say(0,"%s --What... is this place?\nYou start to walk around trying to find any sign of civilization or your Dad.\n",main_character.name);
        sleep(5);
        if (story->Path == 1){//You came alone
            say(0,"%s-- Dad? Where are you?\nYou call out for your Dad but there's no answer.\n",main_character.name);
            sleep(5);
            say(0,"You start to feel a bit uneasy.\nYou check your backpack\n");
            sleep(5);
            say(0,"***This is the inventory. When in action you can access it anytime by typing 'I'.***\n");
            sleep(5);
            say(0,"When inside the inventory you can use an item by typing its number.\nFor example, to use the first item in the list, type '1'.\n");
            sleep(2);
            say(0,"If the item is consumable it will be eaten lowering your hunger imediatly.\nIf it's equippable you will equip it.\nIf you alredy have an item equiped on that slot you will switch them.\n");
            say(0,"Type 'q' to exit the inventory.\n");
            sleep(5);
            open_inventory(&main_character);
            sleep(5);
            say(0,"You keep walking and exploring the area hoping to find some clue about where you are or where your Dad is.\n");

            sleep(5);
        }
        else if(story->Path == 2){//You are with Mom
            say(0,"%s-- Mom? Are you here?\nMOM!!\nYou call out for your Mom but there's no answer.\n",main_character.name);
            sleep(5);
            say(0,"It seems even though you went through the portal together, you got separated somehow.\n");
            sleep(5);
            say(0,"You start to feel a bit uneasy.\nYou check your backpack");
            say(0,"***This is the inventory. When in action you can access it anytime by typing 'I'.***\n");
            sleep(5);
            say(0,"When inside the inventory you can use an item by typing its number.\nFor example, to use the first item in the list, type '1'.\n");
            sleep(2);
            say(0,"If the item is consumable it will be eaten lowering your hunger imediatly.\nIf it's equippable you will equip it.\nIf you alredy have an item equiped on that slot you will switch them.\n");
            sleep(3);
            say(0,"Type 'q' to exit the inventory.\n");
            open_inventory(&main_character);
            say(0,"You keep walking and exploring the area hoping to find some clue about where you are or where your Mom is.\n");
            sleep(5);
        }
        else{
            say(0,"\nError: Invalid story path.\n");
            return main_character;
        }
        say(0,"??? -- Hello there!\nYou turn around and see a strange person looking at you.\n");
        sleep(4);
        say(0,"%s-- Who are you? Do you know where we are?\nStranger-- I am Lilly and we are on the outskirts of Volution!!\n",main_character.name);
        sleep(5);
        say(0,"%s-- Volution? What is that?\nLilly-- It's the capital of Thearoma??\nHow do you not know that?\nDid you hit your head or something?",main_character.name);
        sleep(5);
        say(0,"%s-- I don't know how I got here. I'm looking for someone but I don't even know where to start looking.\nLilly-- Who are you looking for? Maybe I can help.\n",main_character.name);
        sleep(5);
        say(0,"%s-- Did someone else seem to be new here too?\nLilly-- I don't think so... But if you're new here or don't remember how to live here I can show you around and help you get used to it.\n",main_character.name);
        sleep(5);
        say(0,"%s-- That would be great! Thank you so much!\nLilly-- No problem! Follow me!\n",main_character.name);
        sleep(4);
        say(0,"Lilly-- Have you graduated from the academy yet?\n%s-- No, I don't even know what that is.\nLilly-- Oh, you really are new here aren't you? The academy is where everyone goes to learn how to survive in this world and get a job.\n",main_character.name);
        sleep(5);
        say(0,"Lilly-- Do you know what city you're from?\n%s-- Lisbon, Portugal.\nLilly-- Where's that and how are you a teenager and haven't heard of the academy?\n", main_character.name);
        sleep(5);
        say(0,"%s-- Well, where I come from, we don't have an academy like this. We have schools but they are nothing like this place.\nLilly-- What do you mean?.\n",main_character.name);
        sleep(5);
        say(0,"%s-- We don't have gear like what you do. We don't fight a lot anymore. Schools are just for learning and we don't have to worry about surviving or fighting monsters.\nLilly-- Wow, that sounds like you came from a different world or something hahaha. I can't even imagine what it's like to live there.\n",main_character.name);
        sleep(5);
        say(0,"Lilly-- Hello!!\nPlease open the gates!!\nI brought a visitor!!\nThe gates open and you enter the city of Volution for the first time.\n");
        sleep(4);
        say(0,"%s-- Wow, this place is huge!!\nLilly-- Yeah, it's pretty big. We have a lot of shops and diffrent places.\n%s-- I can't wait to see everything!!\n",main_character.name,main_character.name);
        sleep(3);
        say(0,"??? -- Hey Lilly!! Who's your friend??\nLilly-- Oh hey Mark!! This is %s, my new friend. %s just got here and doesn't know much about this place yet.\nMark-- Oh cool! Welcome to Volution %s!!\n",main_character.name,pronoun,main_character.name);
        sleep(5);
        say(0,"%s-- Hey, nice to meet you! ans thanks!\nMark-- No problem! If you need any help just ask for me or Lilly, we are pretty well known here so we can get you almost anything you need.\n",main_character.name);
        sleep(4);
        say(0,"Lilly-- Are you going to the academy?\nMark-- Yeah, there's the introduction class in 15 minutes.\nYou should bring %s with you, it's a good way to meet people and get used to the place.\n",main_character.name);
        sleep(5);
        say(0,"Lilly-- Great idea! Come on %s, let's go to the academy with Mark!\n",main_character.name);
        sleep(2);
        say(0,"%s-- Sure!\nYou go to the academy with Mark and Lilly and attend the introduction class.\nThe teacher explains how the academy works and what you can expect from it.\n", main_character.name);
        sleep(3);
        say(0,"Teacher-- I see we have a new student here today!! Welcome to the academy!!\n%s-- Thank you!\nTeacher-- So, you have any experience with fighting and magic or right?\n%s-- No, not really.\nTeacher-- Oh, really weird since the academy starts at 10 yo and you seem way older than that. But don't worry, we will help you get used to this place and teach you everything you need to know.\n",main_character.name,main_character.name);
        sleep(5);
        if (story->Path == 1){
            say(0,"You think to yourself, 'If things work how the teacher said, I think I will have to learn a lot and become stronger if I want to find my Dad'.\nWhat a mess.\n");
        }
        else if (story->Path == 2){
            say(0,"You think to yourself, 'If things work how the teacher said, I think I will have to learn a lot and become stronger if I want to find my parents'.\nWhat a mess.\n");
        }
        sleep(3);
        say(0,"Teacher-- Now I'm going to call Lilly and Mark to demonstrate combat and then I will choose pairs of students to try some combat.\nLilly and Mark go to the center of the room and start demonstrating some basic combat techniques.\n");
        sleep(4);
        say(0,"Teacher-- Ok,now Marta and Laura,...,%s and %s, since you are the only 15 year-olds, you are going to fight each other!!\nI am being paired with a (kinda good looking... What am I thinking, focus!) student  and we start fighting each other.\n",main_character.name,main_character.name);
        sleep(4);
        main_character = fight(main_character, rival, story, NULL, false);
        //TODO: Continue implementing the rest of the chapter after the fight, 
        
        
        sleep(5);
        say(0,"-------------------------\nChapter 2 Completed\n-------------------------\n");

        
        story->Chapter = Chapter_3;
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

