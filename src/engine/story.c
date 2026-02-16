#include "story.h"
#include "mechanics.h"
#include "items.h"
#include "abilities.h"
#include "npc.h"
#include "dialogue.h"
#include "fights.h"
#include <stdio.h>
#include <unistd.h>

char* choose_pronoun(Player main_character){
    if (main_character.gender == Boy){
        return"he";
    }
    else if (main_character.gender == Girl){
        return "she";
    }
    return "error";
}

int get_story_path(Story story){
    return story.Path;
}

int get_story_chapter(Story story){
    return story.Chapter;
}

void set_story_chapter(Story *story, int chapter) {
    if (chapter >= Chapter_1 && chapter <= Chapter_5) {
        story->Chapter = chapter;
    }
}

void set_story_path(Story *story, int path) {
    story->Path = path;
}

Player chapter1(Player main_character, Story *story) {
    say(1,"-------------------------\nChapter 1: I Can't Loose Him\n-------------------------\n");
    say(5,"It's a cold and rainy night.\nYou are at home when you hear someone calling you.\n");
    say(6,"\?\?\?-- %s!!! Let's eat, dinner's ready.\nOK Mom, I'm going! - %s\n",main_character.name,main_character.name);
    say(7,"Mom-- Your dad is missing and No one knows where he is...\nYou seem lost in thought and then you finnaly say:\n");
    say(8,"-- What do you mean Dad's missing? where did he go?!\nHe said he whould only finish some things at work.?\nYou get up in shock.\n");
    say(10,"Mom-- ... I'm ... Sorry I .. I don't know ...\n- Your Mom mumbles while she starts to cry which makes you calm down and say:\n-- Hey Mom, don't worry I'm going to find Dad and bring him back OK?\n");
    say(8,"Mom-- No, where are you going?\nLet's wait for the police to find him.\nYou're only %i.\nYou can't go around town loocking for him.\n",main_character.age);
    say(7,"%s-- I can't wait for the police!!\nI'm only going to Dad's work and then I will come back wether I find him or not. Deal??\n",main_character.name);
    say(5,"Mom-- Please ... don't go. I can't loose you too! - Your Mom begs\n\n");

    int choice = ask("Should I go search for my Dad or stay with my Mom (Dad/Mom)\n", "Dad", "Mom", NULL);
    if(choice == 0){ // Player chose to search for Dad
        main_character = path_1(main_character,story);
    }
    else{ // Player chose to stay with Mom
        main_character = path_2(main_character,story);
    }
    
    say(3,"-------------------------\nChapter 1 Completed\n-------------------------\n");
    set_story_chapter(story,Chapter_2);
    return main_character;
}


Player path_1_help(Player main_character){
    say(5,"You decide to help the elderly lady with her bags.\nAs you approach her, you realize she's trembling and looks scared.\n");
    say(6,"Elderly Lady-- Oh, thank you so much! I was afraid to be out here alone in the dark.\n%s-- No problem, I'm happy to help. Do you need any more assistance?\n",main_character.name);
    say(7,"Elderly Lady-- No, that's all. Thank you again!\nHere! Take these 2 sandwitches!!\nYou help her carry her bags to her nearby house and then continue on your way to the mine.\n");
    say(5,"'You received 2 Chicken Sandwitches'.\n");
    main_character = add_inventory(main_character,0,2);//Chicken Sandwich
    main_character = change_mc_goodness(main_character,2);
    main_character = increase_mc_perception(main_character,2);
    return main_character;
}

Player path_1_dont_help(Player main_character){
    say(6,"You decide not to help the lady and keep going as fast as you can.\nAs you walk away you hear the lady mumbling something about a curse and bad luck.\nYou feel a bit guilty but you have to find your Dad. You hope she is ok but you don't have time to loose.\n");
    main_character = change_mc_goodness(main_character,-2);
    return main_character;
}

Player path_1_cut(Player main_character){
    say(5,"You try to cut the fence but get zapped by it and fall to the ground.\n");
    say(5,"You wake up next to the security guards.\nThey tell you that you can't be here and that they will have to take you to the police station.\n");
    main_character = damage_player(main_character,10);
    main_character = increase_hunger(main_character,20);
    main_character = change_mc_goodness(main_character,-4);
    return main_character;
}

Player path_1_ask(Player main_character){
    say(2,"You approach the security guards' desk.\n");
    main_character = change_mc_goodness(main_character,1);
    
    return main_character;
}

Player path_1(Player main_character,Story *story){
    set_story_path(story,1);
    say(6,"%s-- I .. just can't Mom but I love you and I will come back soon.\n-- Hopefully with Dad.\n",main_character.name);
    say(6,"You leave and start heading toward your Dad's office when you remember he said he whoudn't work from there today and whould instead visit the new mine his company was exploring.\n");
    say(7,"It's alredy dark.\nThe street lights aren't all working and last you checked the time it was 22:54.\nThis area of the city is known to be dangerous so you are moving at a fast pace.\n\n");
    int choice = ask("I see what seems to be an elderly lady struggling with some bags but it's too dark to be sure.\nShould I help her?\n", "Yes", "No", NULL);
    if (choice == 0){ // Player chose to help the lady
        main_character = path_1_help(main_character);
    }
    else{ // Player chose not to help the lady
        main_character = path_1_dont_help(main_character);
    }
    say(5,"You finally reach the mine's entrance. It's a big cave in the side of a mountain with some mining equipment outside.\n");
    say(5,"Uppon arival, you check the premesis for an entrance but the place seems to have a metal fence all around.\n\n");
    choice = ask("Should I try to cut the fence or try to ask the security to get in?\n","Cut","Ask",NULL);
    if(choice == 0){
        main_character = path_1_cut(main_character);
    }
    else{
        main_character = path_1_ask(main_character);
    }
    say(6,"You explain the situation to the security guards and ask if you can go in to look for your Dad.\n");
    say(6,"Reluctantly they let you in and one of them comes with you.\nThe guard gives you a flashlight to proceed with your search.\nAs you advance in the tunnels, you start to see a purple light that illuminates the cave.\n");
    say(1,"'You recieved 1 Flashlight'.\n");
    say(6,"Security Guard-- I don't think we should keep going. It can get dangerous and we aren't suposed to be here anyway!\n%s-- Maybe but this light is really weird and we came this far...\n",main_character.name);
    say(5,"You keep going and the light gets stronger and stronger until you reach a big cavern where you see a group of people trying to remove a big rock off what seems to be the light's source.\n");
    say(5,"%s-- Excuse me! What are you doing?\nMiner-- Some of our crew entered what looked like some kind of secret passage when this giant rock fell and trapped them inside. We are trying to get them out.\n",main_character.name);
    say(5,"%s-- Do you know if one of them is called Luca Lanister?\nMiner-- Unfortunately yes. Mr.Lanister is one of the trapped people.\nHe was the one overseeing the operation.\n",main_character.name);
    say(5,"The miners look at each other and then at you.\nMiner-- Look kid, we are really sorry about your dad we are trying to move the rock as fast as we can. If you want to help us, go ahead but if you want to go back now is your chance.\n");
    say(5,"%s-- How did you know he is my dad?\nMiner-- A kid in the mines at this hour is pretty unusual.\nWe just put two and two together.\n",main_character.name);
    say(5,"I will help you move the rock to save my Dad and the other trapped people.\n");
    say(4,"As the team finnaly moves the rock you fall into the purple crystal hole that looks like a weird passage or portal.\n");  
    main_character = add_inventory(main_character,1,1);
    main_character = increase_hunger(main_character,13);
    return main_character;
}

Player path_2(Player main_character,Story *story){
    set_story_path(story,2);
    say(7,"%s-- You're right Mom. I'm sorry. Let's wait for the police together.\n-- I love you.\n",main_character.name);
    say(7,"You stay with your Mom and try to comfort her as best as you can.\nThe police arrive a few hours later and start investigating your Dad's disappearance.\n");
    say(7,"You tell them everything you know and they promise to do their best to find him.\nThe next day, the police imform you that they will search the mine your Dad was working at since it's the last place he was seen.\n");
    say(5,"You insist on going and your mom decides to come with you to keep you safe.\nBecause the police needs someone that knows your Dad to identify him if they find him, they let you both go.\n");
    say(5,"At the mine entrance, you see the security guards and explain the situation to them.\nThey let you in and one of them comes with you.\nAs you advance in the tunnels, you start to see a purple light that illuminates the cave.\n");
    say(5,"You keep going and the light gets stronger and stronger until you reach a big cavern where you see a group of people that have removed a big rock off what seems to be the light's source.\n");
    say(5,"%s-- Excuse me! What are you doing?\nMiner-- Some of our crew entered what looked like some kind of secret passage when this giant rock fell and trapped them inside. We just got the rock out and there's this purple passage.\n-No one has had the courage to go through it!!",main_character.name);
    say(5,"%s-- Do you know if one of them is called Luca Lanister?\nMiner-- Unfortunately yes. Mr.Lanister is one of the trapped people.\nHe was the one overseeing the operation.\n",main_character.name);
    say(5,"The police and miners look at each other and then at you.\nPolice Officer-- Look kid, we are really sorry about your dad but you can't get near that thing.\nNo one knows what it is!!\n");
    say(5,"%s-- But my Dad is in there!! Please I have to go in!\nPolice Officer-- I'm sorry but we can't let you. It's too dangerous.\n",main_character.name);
    say(5,"You insist and beg them to let you go in but they refuse.\nYou feel helpless and frustrated.\nSuddenly, your Mom, out of nowhere, steps forward and dives in, going trough the purple portal.\n");
    int choice = ask("I have to go after her right?!!\n","Go","Stay");
    if (choice == 0){
        main_character = path_2_go(main_character);
    }
    else{
        main_character = path_2_stay(main_character);
    }
    
    main_character = increase_hunger(main_character,13);
    
    
    return main_character;
}

Player path_2_go(Player main_character){
    say(5,"Mom-- I'm going in! I have to find him!\n%s-- Mom no! I'm going in!\n",main_character.name);
    say(4,"The police try to stop both of you but were too late.\n");
    say(5,"Both you and your mom enter the portal.\nYou feel a strange sensation in your body as you pass through it.\n");
    main_character = increase_mc_speed(main_character,2);
    return main_character;
}

Player path_2_stay(Player main_character){
    say(6,"You decide not to go after your Mom and hope that she will be ok.\nYou wait for her to come back but she doesn't.\nAfter a while, you start to worry and try to find a way to go after her but you don't know how and the police won't let you go back there.\n");
    say(5,"You feel helpless and scared but you have to stay strong and hope that your Mom will be ok and that the police will find her soon.\n");
    say(5,"After a while the police organize a search party.\nAs they're going in you follow unnoticed.\n");
    main_character = increase_mc_stealth(main_character,1);
    return main_character;
}

