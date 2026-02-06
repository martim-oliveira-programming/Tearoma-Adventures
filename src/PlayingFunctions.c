#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "story.h"
#include "menu.h"
#include "mechanics.h"
#include "save.h"
#include <unistd.h> 

Player character_creation() {
    Player main_character = {0}; // Zero-initialize first
    char *gender= get_input("Are you a boy or a girl?\n");    
    if (strcmp(gender,"boy")==0 ){
        main_character.gender = Boy;
    }
    else if (strcmp(gender,"girl")== 0){
        main_character.gender = Girl;
    }
    else{
        printf("Invalid input. Please enter 'boy' or 'girl'.\n");
        return character_creation(); // Recursively call until valid input
    }
    main_character.name = get_input("What is your character's name?\n");
    main_character.hair_colour = get_input("What is your character's hair colour?\n");
    main_character.age = 15;
    main_character.RANK = E;
    main_character.inventoryIDs= malloc(1 * sizeof(int));
    main_character.item_ammount = 0;
    main_character.HUNGER = 0;
    main_character.Skill_Points = 0;
    main_character.LEVEL = 0;
    main_character.EXP = 0;

    // Initialize empty armor
    for (int i = 0; i < 4; i++) {
        main_character.armor[i] = 0;
    }
    printf("\nThe build you choose for your character will give you your initial attributes and possible weapons/abilities but you can nourish your other abilities throughout the story.\n");
    usleep(2500);
    printf("Select a build for your character:\n");
    usleep(2500);
    char *build_input = get_input(
        "Assassin: Very high Speed and great with long range weapons and dual wielding daggers.\n"
        "Tank: High Health and Strength. Is able to use powerful shields.\n"
        "Monk: High Strength, Speed and Health. Does not use weapons or Magic.\n"
        "Ninja: Very high Stealth, close range Weapon Usage and midium magic usage.\n"
        "Mage: High Magic Power and Mana reserves. Mostely a mid to long range attacker.\n"
        "Healer: High Magic Power and Mana reserves. Mostely but not limited to Healing Magic.\n"
        "Summoner: Is abble to summon creatures to aid in combat or other situations.\n"
        "Balanced: Evenly distibuited tallent. 'Jack of all trades, master of none'.\n"
    );
    main_character.build = parse_build(build_input);
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
    main_character.armor[0] = -1; // Head
    main_character.armor[1] = -1; // Chest
    main_character.armor[2] = -1; // Legs
    main_character.armor[3] = -1; // Boots
    main_character.weapon = -1; // No weapon equipped
    main_character.weapon_OFF_Hand = -1; // No off-hand weapon equipped
    return main_character;
}

Player fight(Player main_character, NPC enemy, Story *story,NPC* npcs) {
    while(check_alive(&main_character,story,npcs) && !check_win(enemy, &main_character)) {
        printf("\n%s's HP: %d, MANA: %d\n", enemy.name, enemy.HP, enemy.MANA);
        printf("\nYour HP: %d, MANA: %d\n", main_character.HP, main_character.MANA);
        char *action = get_input("Choose your action (Attack (D)/Use Ability (A)/Use Item (I)):\n");
        if (strcmp(action, "D") == 0) {
            // Placeholder for attack logic
            int damage = 10; // Example damage value
            enemy = damage_npc(enemy, damage);
            printf("You dealt %d damage to %s!\n", damage, enemy.name);
        } else if (strcmp(action, "A") == 0) {
            // Placeholder for defend logic
            printf("You brace yourself for the next attack.\n");
        } else if (strcmp(action, "I") == 0) {
            // Placeholder for item usage logic
            printf("You rummage through your inventory...\n");
        } else {
            printf("Invalid action. Please choose Attack, Use Ability, or Use Item.\n");
        }
        // Placeholder for enemy's turn logic
        printf("%s is preparing to attack you!\n", enemy.name);
    }
    printf("You are fighting %s!\n", enemy.name);
    // Placeholder for combat logic
    // This is where you would implement the actual combat mechanics
    return main_character; // Return the updated player state after combat
}


Player play_chapter(Player main_character, Story *story){
    char *choice;
    const char* pronoun;
    if (main_character.gender == Boy){
        pronoun = "he";
    }
    else if (main_character.gender == Girl){
        pronoun = "she";
    }

    switch (story->Chapter)
    {
    case Chapter_1:{
        printf("-------------------------\nChapter 1: I Can't Loose Him\n-------------------------\n");
        sleep(1);
        printf("It's a cold and rainy night.\nYou are at home when you hear someone calling you.\n");
        sleep(5);
        printf("\?\?\?-- %s!!! Let's eat, dinner's ready.\nOk Mom I'm going! - %s\n",main_character.name,main_character.name);
        printf("Mom-- I have to tell you something sweety...\n");
        sleep(6);
        printf("Mom-- Your dad is missing and No one knows where he is...\nYou seem lost in thought and then you finnaly say:\n");
        sleep(7);
        printf("-- What do you mean Dad's missing? where did he go?!\nHe said he whould only finish some things at work.?\nYou get up in shock.\n");
        sleep(8);
        printf("Mom-- ... I'm ... Sorry I .. I don't know ...\n- Your Mom mumbles while she starts to cry which makes you calm down and say:\n-- Hey Mom, don't worry I'm going to find Dad and bring him back OK?\n");
        sleep(10);
        printf("Mom-- No, where are you going?\nLet's wait for the police to find him.\nYou're only %i.\nYou can't go around town loocking for him.\n",main_character.age);
        sleep(8);
        printf("%s-- I can't wait for the police!!\nI'm only going to Dad's work and then I will come back wether I find him or not. Deal??\n",main_character.name);
        sleep(7);
        printf("Mom-- Please ... don't go. I can't loose you too! - Your Mom begs\n\n");
        sleep(5);
        choice = get_input("Should I go search for my Dad or stay with my Mom (Dad/Mom)\n");
        if(strcmp(choice,"Dad")== 0){
            story->Path = 1;
            main_character.HUNGER +=1;
            printf("%s-- I .. just can't Mom but I love you and I will come back soon.\n-- Hopefully with Dad.\n",main_character.name);
            sleep(7);
            printf("You leave and start heading towards your Dad's office when you remember he said he whoudn't work from there today and whould instead visit the new mine his company was exploring.\n");
            sleep(7);
            printf("It's alredy dark.\nThe street lights aren't all working and last you checked the time it was 22:54.\nThis area of the city is known to be dangerous so you are moving at a fast pace.\n\n");
            sleep(8);
            choice = get_input("I see what seems to be an elderly lady struggling with some bags but it's too dark to be sure.\nShould I help her? (Yes/No)\n");
            
            if (strcmp(choice,"Yes")== 0){
                printf("You get closer and confirm your previous assessment was correct and help the lady with her bags.\nOld Lady-- Thank you so much for the help %s, here is a gift.\n-- Thank you for all your help.\n",gender_to_string(main_character.gender));
                sleep(5);
                printf("'You recieved 2 chicken sandwiches'.\n");
                main_character = add_inventory(main_character,0,2);//Chicken Sandwich
                main_character.GOODNESS +=2;
                sleep(5);
                printf("%s-- Thank You so much. I really need to get going now. Goodbye!\n--I hope I'm not to late...\n",main_character.name);
            }
            else if (strcmp(choice,"No")== 0){
                sleep(5);
                printf("You decide not to help the lady and keep going as fast as you can.\nAs you walk away you hear the lady mumbling something about a curse and bad luck.\nYou feel a bit guilty but you have to find your Dad. You hope she is ok but you don't have time to loose.\n");
                main_character.GOODNESS -=2;
            }

            sleep(5);
            printf("You finally reach the mine's entrance. It's a big cave in the side of a mountain with some mining equipment outside.\n");
            sleep(5);
            printf("Uppon arival, you check the premesis for an entrance but the place seems to have a metal fence all around.\n\n");
            main_character.HUNGER += 4;
            choice = get_input("Should I try to cut the fence or try to ask the security to get in? (Cut/Ask)\n");
        
            if (strcmp(choice, "Cut") == 0) { 
                sleep(2);
                printf("You try to cut the fence but get zapped by it and fall to the ground.\n");
                main_character.HP -= 10;
                main_character.HUNGER += 20;
                main_character.GOODNESS -= 4;
                sleep(5);
                printf("You wake up next to the security guards.\nThey tell you that you can't be here and that they will have to take you to the police station.\n");
            }
            else if (strcmp(choice, "Ask") == 0) {
                sleep(2);
                printf("You approach the security guards' desk.\n");
                main_character.GOODNESS += 1;
            }
            sleep(5);
            main_character = add_inventory(main_character,1, 1); //Flashlight
            printf("You explain the situation to the security guards and ask if you can go in to look for your Dad.\n");
            sleep(6);
            printf("Reluctantly they let you in and one of them comes with you.\nThe guard gives you a flashlight to proceed with your search.\nAs you advance in the tunnels, you start to see a purple light that illuminates the cave.\n");
            sleep(6);
            printf("'You recieved 1 Flashlight'.\n");
            sleep(5);
            printf("Security Guard-- I don't think we should keep going. It can get dangerous and we aren't suposed to be here anyway!\n%s-- Maybe but this light is really weird and we came this far...\n",main_character.name);
            sleep(6);
            printf("Security Guard-- Fine but if anything happens I'm leaving you here! I can't get in trouble.\n%s-- Deal.\n",main_character.name);
            printf("You keep going and the light gets stronger and stronger until you reach a big cavern where you see a group of people trying to remove a big rock off what seems to be the light's source.\n");
            sleep(5);
            printf("%s-- Excuse me! What are you doing?\nMiner-- Some of our crew entered what looked like some kind of secret passage when this giant rock fell and trapped them inside. We are trying to get them out.\n",main_character.name);
            sleep(5);
            printf("%s-- Do you know if one of them is called Luca Lanister?\nMiner-- Unfortunately yes. Mr.Lanister is one of the trapped people.\nHe was the one overseeing the operation.\n",main_character.name);
            sleep(5);
            printf("The miners look at each other and then at you.\nMiner-- Look kid, we are really sorry about your dad we are trying to move the rock as fast as we can. If you want to help us, go ahead but if you want to go back now is your chance.\n");
            main_character.HUNGER += 8;
            sleep(5);
            printf("%s-- How did you know he is my dad?\nMiner-- A kid in the mines at this hour is pretty unusual.\nWe just put two and two together.\n",main_character.name);
            sleep(5);

            choice = get_input("Should I help the miners or go back home to Mom? (Help/Back)\n");
            
            if (strcmp(choice,"Help")== 0){
                printf("I will help you move the rock to save my Dad and the other trapped people.\n");
                sleep(5);
                printf("As the team finnaly moves the rock you fall into the purple crystal hole that looks like a weird passage or portal.\n");
                
            }
            else if (strcmp(choice,"Back")== 0){
                printf("I have to see how Mom's doing.\nAs you turn around to leave ,disapointed, you are called by someone.\nThe miners finally removed the rock!!\nYou are distracted and trip, falling into the purple crystal portal.\n");
                
            }
    }
    else if (strcmp(choice,"Mom")== 0){
        story->Path = 2;
        printf("%s-- You're right Mom. I'm sorry. Let's wait for the police together.\n-- I love you.\n",main_character.name);
        sleep(7);
        printf("You stay with your Mom and try to comfort her as best as you can.\nThe police arrive a few hours later and start investigating your Dad's disappearance.\n");
        sleep(7);
        printf("You tell them everything you know and they promise to do their best to find him.\nThe next day, the police imform you that they will search the mine your Dad was working at since it's the last place he was seen.\n");
        sleep(5);
        printf("You insist on going and your mom decides to come with you to keep you safe.\nBecause the police needs someone that knows your Dad to identify him if they find him, they let you both go.\n");
        sleep(5);
        printf("At the mine entrance, you see the security guards and explain the situation to them.\nThey let you in and one of them comes with you.\nAs you advance in the tunnels, you start to see a purple light that illuminates the cave.\n");
        sleep(6);
        printf("You keep going and the light gets stronger and stronger until you reach a big cavern where you see a group of people that have removed a big rock off what seems to be the light's source.\n");
        sleep(5);
        printf("%s-- Excuse me! What are you doing?\nMiner-- Some of our crew entered what looked like some kind of secret passage when this giant rock fell and trapped them inside. We just got the rock out and there's this purple passage.\n-No one has had the courage to go through it!!",main_character.name);
        sleep(5);
        printf("%s-- Do you know if one of them is called Luca Lanister?\nMiner-- Unfortunately yes. Mr.Lanister is one of the trapped people.\nHe was the one overseeing the operation.\n",main_character.name);
        sleep(5);
        printf("The police and miners look at each other and then at you.\nPolice Officer-- Look kid, we are really sorry about your dad but you can't get near that thing.\nNo one knows what it is!!\n");
        sleep(5);
        printf("%s-- But my Dad is in there!! Please I have to go in!\nPolice Officer-- I'm sorry but we can't let you. It's too dangerous.\n",main_character.name);
        sleep(5);
        printf("You insist and beg them to let you go in but they refuse.\nYou feel helpless and frustrated.\nSuddenly, your Mom, out of nowhere, steps forward and dives in, going trough the purple portal.\n");
        sleep(5);
        printf("Mom-- I'm going in! I have to find him!\n%s-- Mom no! I'm going in!\n",main_character.name);
        sleep(5);
        printf("Both you and your mom enter the portal.\nYou feel a strange sensation in your body as you pass through it.\n");
        main_character.HUNGER += 15;
    }
    sleep(5);   
    printf("-------------------------\nChapter 1 Completed\n-------------------------\n");
    story->Chapter = Chapter_2;
    return main_character;
    break;
    }
    case Chapter_2:{
        NPC rival;
        int rival_id = (main_character.gender == Boy) ? 0 : 1;
        NPC *rival_ptr = get_npc_by_id(rival_id);
        if (rival_ptr) {
            rival = *rival_ptr;
        } else {
            printf("Error: rival NPC not found for id %d.\n", rival_id);
            rival = (NPC){0};
        }

        printf("-------------------------\nChapter 2: A New World!\n-------------------------\n");
        sleep(1);
        printf("%s-- Where am I? This place looks... strange.\nYou look around and see that you are in a huge grassy field.\n",main_character.name);
        sleep(5);
        printf("You see some strange plants and creatures around you.\nThe sky is a weird shade of purple and there are two suns in the sky.\n");
        sleep(5);
        printf("%s --What... is this place?\nYou start to walk around trying to find any sign of civilization or your Dad.\n",main_character.name);
        sleep(5);
        if (story->Path == 1){//You came alone
            printf("%s-- Dad? Where are you?\nYou call out for your Dad but there's no answer.\n",main_character.name);
            sleep(5);
            printf("You start to feel a bit uneasy.\nYou check your backpack\n");
            sleep(5);
            printf("***This is the inventory. When in action you can access it anytime by typing 'I'.***\n");
            sleep(5);
            printf("When inside the inventory you can use an item by typing its number.\nFor example, to use the first item in the list, type '1'.\n");
            sleep(2);
            printf("If the item is consumable it will be eaten lowering your hunger imediatly.\nIf it's equippable you will equip it.\nIf you alredy have an item equiped on that slot you will switch them.\n");
            printf("Type 'q' to exit the inventory.\n");
            sleep(5);
            open_inventory(&main_character);
            sleep(5);
            printf("You keep walking and exploring the area hoping to find some clue about where you are or where your Dad is.\n");

            sleep(5);
        }
        else if(story->Path == 2){//You are with Mom
            printf("%s-- Mom? Are you here?\nMOM!!\nYou call out for your Mom but there's no answer.\n",main_character.name);
            sleep(5);
            printf("It seems even though you went through the portal together, you got separated somehow.\n");
            sleep(5);
            printf("You start to feel a bit uneasy.\nYou check your backpack");
            printf("***This is the inventory. When in action you can access it anytime by typing 'I'.***\n");
            sleep(5);
            printf("When inside the inventory you can use an item by typing its number.\nFor example, to use the first item in the list, type '1'.\n");
            sleep(2);
            printf("If the item is consumable it will be eaten lowering your hunger imediatly.\nIf it's equippable you will equip it.\nIf you alredy have an item equiped on that slot you will switch them.\n");
            sleep(3);
            printf("Type 'q' to exit the inventory.\n");
            open_inventory(&main_character);
            printf("You keep walking and exploring the area hoping to find some clue about where you are or where your Mom is.\n");
            sleep(5);
        }
        else{
            printf("\nError: Invalid story path.\n");
            return main_character;
        }
        printf("???-- Hello there!\nYou turn around and see a strange person looking at you.\n");
        sleep(4);
        printf("%s-- Who are you? Do you know where we are?\nStranger-- I am Lilly and we are on the outskirts of Volution!!\n",main_character.name);
        sleep(5);
        printf("%s-- Volution? What is that?\nLilly-- It's the capital of Thearoma??\nHow do you not know that?\nDid you hit your head or something?",main_character.name);
        sleep(5);
        printf("%s-- I don't know how I got here. I'm looking for someone but I don't even know where to start looking.\nLilly-- Who are you looking for? Maybe I can help.\n",main_character.name);
        sleep(5);
        printf("%s-- Did someone else seem to be new here too?\nLilly-- I don't think so... But if you're new here or don't remember how to live here I can show you around and help you get used to it.\n",main_character.name);
        sleep(5);
        printf("%s-- That would be great! Thank you so much!\nLilly-- No problem! Follow me!\n",main_character.name);
        sleep(4);
        printf("Lilly-- Have you graduated from the academy yet?\n%s-- No, I don't even know what that is.\nLilly-- Oh, you really are new here aren't you? The academy is where everyone goes to learn how to survive in this world and get a job.\n",main_character.name);
        sleep(5);
        printf("Lilly-- Do you know what city you're from?\n%s-- Lisbon, Portugal.\nLilly-- Where's that and how are you a teenager and haven't heard of the academy?\n");
        sleep(5);
        printf("%s-- Well, where I come from, we don't have an academy like this. We have schools but they are nothing like this place.\nLilly-- What do you mean?.\n",main_character.name);
        sleep(5);
        printf("%s-- We don't have gear like what you do. We don't fight a lot anymore. Schools are just for learning and we don't have to worry about surviving or fighting monsters.\nLilly-- Wow, that sounds like you came from a different world or something hahaha. I can't even imagine what it's like to live there.\n",main_character.name);
        sleep(5);
        printf("Lilly-- Hello!!\nPlease open the gates!!\nI brought a visitor!!\nThe gates open and you enter the city of Volution for the first time.\n");
        sleep(4);
        printf("%s-- Wow, this place is huge!!\nLilly-- Yeah, it's pretty big. We have a lot of shops and diffrent places.\n%s-- I can't wait to see everything!!\n",main_character.name,main_character.name);
        sleep(3);
        printf("???-- Hey Lilly!! Who's your friend??\nLilly-- Oh hey Mark!! This is %s, my new friend. %s just got here and doesn't know much about this place yet.\nMark-- Oh cool! Welcome to Volution %s!!\n",main_character.name,pronoun,main_character.name);
        sleep(5);
        printf("%s-- Hey, nice to meet you! ans thanks!\nMark-- No problem! If you need any help just ask for me or Lilly, we are pretty well known here so we can get you almost anything you need.\n",main_character.name);
        sleep(4);
        printf("Lilly-- Are you going to the academy?\nMark-- Yeah, there's the introduction class in 15 minutes.\nYou should bring %s with you, it's a good way to meet people and get used to the place.\n",main_character.name);
        sleep(5);
        printf("Lilly-- Great idea! Come on %s, let's go to the academy with Mark!\n",main_character.name);
        sleep(2);
        printf("%s-- Sure!\nYou go to the academy with Mark and Lilly and attend the introduction class.\nThe teacher explains how the academy works and what you can expect from it.\n");
        sleep(3);
        printf("Teacher-- I see we have a new student here today!! Welcome to the academy!!\n%s-- Thank you!\nTeacher-- So, you have any experience with fighting and magic or right?\n%s-- No, not really.\nTeacher-- Oh, really weird since the academy starts at 10 yo and you seem way older than that. But don't worry, we will help you get used to this place and teach you everything you need to know.\n",main_character.name,main_character.name);
        sleep(5);
        if (story->Path == 1){
            printf("You think to yourself, 'If things work how the teacher said, I think I will have to learn a lot and become stronger if I want to find my Dad'.\nWhat a mess.\n");
        }
        else if (story->Path == 2){
            printf("You think to yourself, 'If things work how the teacher said, I think I will have to learn a lot and become stronger if I want to find my parents'.\nWhat a mess.\n");
        }
        sleep(3);
        printf("Teacher-- Now I'm going to call Lilly and Mark to demonstrate combat and then I will choose pairs of students to try some combat.\nLilly and Mark go to the center of the room and start demonstrating some basic combat techniques.\n");
        sleep(4);
        printf("Teacher-- Ok,now Marta and Laura,...,%s and %s, since you are the only 15 year-olds, you are going to fight each other!!\nYou are paired with a random (kinda good looking... What am I thinking, focus!) student  and start fighting each other.\n",main_character.name,main_character.name);
        sleep(4);




        sleep(5);
        printf("-------------------------\nChapter 2 Completed\n-------------------------\n");

        
        story->Chapter = Chapter_3;
        return main_character;
        break;
    }
    return main_character;
    }
    return main_character;
}
