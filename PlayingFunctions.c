#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "header.h"
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
    main_character.item_ammount = 0;
    return main_character;
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
        printf("Chapter 1: The Beginning\n");
        sleep(1);
        printf("It's a cold and rainy night.\nYou are at home with your Mom when you hear her calling you.\n");
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
        if(strcmp(choice,"Dad")== 0){ //TODO Mom
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
            
            if (strcmp(choice,"Help")== 0){//TODO Back
                story->Path = 11;
                printf("You help the miners move the rock to save your Dad and the other trapped people.\n");
                sleep(5);
                printf("As the team finnaly moves the rock you fall into the purple crystal hole that looks like a weird passage or portal.\n");
                sleep(4);
                printf("----------------------\nChapter 1 Completed\n-------------------\n");
                story->Chapter = Chapter_2;
                return main_character;
            }

            

        /*
        printf("You wake up and do not recognize the world around you.\n The miners are gone and you feel a strange sensation in your body.\n");
            printf("You look around and see a big city in the distance. You decide to head there and try to find your way back home.\n");
            main_character.HUNGER += 20;
            printf("You're very hungry and tired. You need to find food and a place to rest.\n");
            usleep(2000);
            printf("You arrive at the city and see a big market place with many people around.\n");
            usleep(2000);
        */

        return main_character;
        break;
    }

    }
    return main_character;
}
return main_character;
}
