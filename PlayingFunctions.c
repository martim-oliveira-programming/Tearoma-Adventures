#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"
#include <unistd.h> 

Player character_creation() {
    Player main_character = {0}; // Zero-initialize first
    main_character.gender= get_input("Are you a boy or a girl?");    
    main_character.name = get_input("What is your character's name?\n");
    main_character.hair_colour = get_input("What is your character's hair colour?\n");
    main_character.age = 15;
    main_character.RANK = 'E';
    main_character.items = (char*[]){"", NULL};
    main_character.item_ammount = (int[]){0, 0};
    main_character.HUNGER = 0;
    main_character.Skill_Points = 0;
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
    main_character.HP = main_character.stats.MAX_HP;
    main_character.MANA = main_character.stats.MAX_MANA;
    main_character.HP *= 10;
    main_character.MANA *= 10;
    main_character.GOODNESS = 0;
    return main_character;
}



Player play(Player main_character, Story story){

    char *pronoun ="";
    char *choice;

    if (strcmp(main_character.gender,"boy")==0 ){
        pronoun = "he";
    }
    else if (strcmp(main_character.gender,"girl")== 0){
        pronoun = "she";
    }

    switch (story.Chapter)
    {
    case Chapter_1:{
        printf("%s!!! Come here, dinner's ready. - ???\nOk Mom I'm going! - %s\n",main_character.name,main_character.name);
        printf("I have to tell you something sweety, your dad is missing and No one knows where he is.-Mom\n... - %s seems lost in thought and then says\n",main_character.name);
        printf("What do you mean Dad's missing? where did he go?! He said he whould only finish some things at work.? - says %s as %s gets up in shock.\n",main_character.name,pronoun);
        printf("... I'm ... Sorry I .. I don't know ... - Your Mom mumbles while she starts to cry which makes you calm down and say:\nHey Mom, don't worry I'm going to find Dad and bring him back OK?\n");
        printf("No, where are you going? Let's wait for the police to find him. You're only %i. You can't go around town loocking for him. - Mom\n",main_character.age);
        printf("I can't wait for the police and I'm only going to Dad's work and then I will come back wether I find him or not. Deal?? - %s\n",main_character.name);
        printf("Please ... don't go. I can't loose you too! - Your Mom begs\n\n");
        choice = get_input("Do you wish to go seartch for your Dad or Stay with your Mom (Dad/Mom)\n");
        if(strcmp(choice,"Dad")== 0){
            story.Path = 1;
            main_character.HUNGER +=1;
            printf("I .. just can't Mom but I love you and I will come back soon. Hopefully with Dad. - %s\n",main_character.name);
            printf("You leave and start heading towards your Dad's office when you remember your Dad said he whoudn't work from there today and whould instead visit the new mine his company was exploring.\n");
            printf("It's alredy dark. The street lights aren't all working and last you checked the time it was 22:54. This area of the city is known to be dangerous so you are moving at a fast pace.\n\n");
            choice = get_input("You see what seems to be an elderly lady struggling with some bags but it's too dark to be sure.\n Do you help? (Yes/No)\n");
            if (strcmp(choice,"Yes")== 0){
                printf("You get closer and confirm your previous assessment and help the lady with her bags.\nThank you so much for the help %s, here is a gift for the help. - Old Lady\n",main_character.gender);
                printf("You recieved 2 chicken sandwiches.\n");
                main_character = add_inventory(main_character,"Chicken_Sandwich",2);
                main_character.GOODNESS +=2;
                printf("Thank You so much. I really need to get going now though. Goodbye! - says %s as %s thinks:\nI hope I'm not to late.",main_character.name,pronoun);
            }
            printf("Uppon arival, you check the premesis for an entrance but the place seems to have a metal fence all around.\n\n");
            main_character.HUNGER += 4;
            choice = get_input("Should you try to cut the fence or try to ask the security to get in? (Cut/Ask)\n");
        
            if (strcmp(choice, "Cut") == 0) {
            printf("You try to cut the fence but get zapped by it and fall to the ground.\n");
            main_character.HP -= 10;
            main_character.HUNGER += 20;
            main_character.GOODNESS -= 1;

            printf("You wake up next to the security and explain the whole situation to them.\n");
        }

        main_character = add_inventory(main_character, "Flashlight", 1);
        printf("Reluctantly they let you in and one of them comes with you.\nThe guard gives you a flashlight to proceed with your search.\nAs you advance in the tunnels, you start to see a purple light that illuminates the cave.\n");
        printf("");//TODO

        }



        return main_character;
        break;
    }

    }
    return main_character;
}




