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
    say(6,"-- What do you mean Dad's missing? where did he go?!\nHe said he whould only finish some things at work.?\nYou get up in shock.\n");
    say(7,"Mom-- ... I'm ... Sorry I .. I don't know ...\n- Your Mom mumbles while she starts to cry which makes you calm down and say:\n-- Hey Mom, don't worry I'm going to find Dad and bring him back OK?\n");
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

Player chapter_2(Player main_character, Story *story, int *chapter_npc_ids) {
    char *mc_name = get_mc_name(main_character);
    int rival_id = chapter_npc_ids[0];
    NPC rival = get_npc_by_id(rival_id);
    int ability_id = get_mc_abilitiesIDs(main_character)[0]; 
    char *rival_name = get_ability_name(ability_id);
    char *pronoun = choose_pronoun(main_character);
    say(1,"-------------------------\nChapter 2: A New World!\n-------------------------\n");
    say(5,"%s-- Where am I? This place looks... strange.\nYou look around and see that you are in a huge grassy field.\n",mc_name);
    say(5,"You see some strange plants and creatures around you.\nThe sky is a weird shade of purple and there are two suns in the sky.\n");
    say(5,"%s --What... is this place?\nYou start to walk around trying to find any sign of civilization or your Dad.\n",mc_name);
    say(5,"You start to feel a bit uneasy.\nYou check your backpack\n");
    say(5,"***This is the inventory.***\n");
    say(5,"When inside the inventory you can use an item by typing its id number.\n");
    say(2,"If the item is consumable it will be eaten lowering your hunger imediatly.\nIf it's equippable you will equip it.\nIf you alredy have an item equiped on that slot you will switch them.\n");
    open_inventory(&main_character);
    say(5,"You keep walking and exploring the area hoping to find some clue about where you are.\n");
    say(4,"There are some small caves, trees, boars, pigs etc...\nYou shout:");
    int path = get_story_path(*story);
    if (path == 1){
        say(2,"%s-- Dad? Where are you?\nYou call out for your Dad but there's no answer.\n",mc_name);

    }
    else if(path ==2){
        say(2,"%s-- Mom? Are you here?\nMOM!!\nYou call out for your Mom but there's no answer.\n",mc_name);
        say(2,"--How can we not be toguether if we went through the portal basicly at the same time?\n");

    }
    say(4,"??? -- Hello there!\nYou look behind you and find a girl, not taller than 1.60, brown hair, big smile and a fit body.\nShe seems to be around your age and is wearing some kind of kymono uniform.\n");
    say(5,"%s-- Who are you? Do you know where we are?\nStranger-- I am Lillian, my friends call me Lilly and we are on the outskirts of Volution!!\n",mc_name);
    say(5,"??? -- Hello there!\nYou turn around and see a strange person looking at you.\n");
    say(5,"%s-- Who are you? Do you know where we are?\nStranger-- I am Lilly and we are on the outskirts of Volution!!\n",mc_name);
    say(5,"%s-- Volution? What is that?\nLilly-- It's the capital of Thearoma??\nHow do you not know that?\nDid you hit your head or something?",mc_name);
    say(5,"%s-- I don't know how I got here. I'm looking for someone but I don't even know where to start looking.\nLilly-- Who are you looking for? Maybe I can help.\n",mc_name);
    say(5,"%s-- Did someone else seem to be new here too?\nLilly-- I don't think so... But if you're new here or don't remember how to live here I can show you around and help you get used to it.\n",mc_name);
    say(5,"%s-- That would be great! Thank you so much!\nLilly-- No problem! Follow me!\n",mc_name);
    say(5,"Lilly-- Have you graduated from the academy yet?\n%s-- No, I don't even know what that is.\nLilly-- Oh, you really are new here aren't you? The academy is where everyone goes to learn how to survive in this world and get a job.\n",mc_name);
    say(5,"Lilly-- Do you know what city you're from?\n%s-- Lisbon, Portugal.\nLilly-- Where's that and how are you a teenager and haven't heard of the academy?\n", mc_name);
    say(5,"%s-- Well, where I come from, we don't have an academy like this. We have schools but they are nothing like this place.\nLilly-- What do you mean?.\n",mc_name);
    say(5,"%s-- We don't have gear like what you do. We don't fight a lot anymore. Schools are just for learning and we don't have to worry about surviving or fighting monsters.\nLilly-- Wow, that sounds like you came from a different world or something hahaha. I can't even imagine what it's like to live there.\n",mc_name);
    say(5,"***You aproach Volution! Massive gates and a giant wall all around the capital.***\n");
    say(5,"Lilly-- Hello!!\nPlease open the gates!!\nI brought a visitor!!\nThe gates open and you enter the city of Volution for the first time.\n");
    say(5,"%s-- Wow, this place is huge!!\nLilly-- Yeah, it's pretty big. We have a lot of shops and diffrent places.\n%s-- I can't wait to see everything!!\n",mc_name,mc_name);
    say(5,"??? -- Hey Lilly!! Who's your friend??\nLilly-- Oh hey Mark!! This is %s, my new friend. %s just got here and doesn't know much about this place yet.\nMark-- Oh cool! Welcome to Volution %s!!\n",mc_name,pronoun,mc_name);
    say(5,"*** Mark is tall, fit and has a strong presence.***\n");
    say(5,"%s-- Hey, nice to meet you! and thanks!\nMark-- No problem! If you need any help just ask for me or Lilly, we are pretty well known here so we can get you almost anything you need.\n",mc_name);
    say(5,"Lilly-- Are you going to the academy?\nMark-- Yeah, there's the introduction class in 15 minutes.\nYou should bring %s with you, it's a good way to meet people and get used to the place.\n",mc_name);
    say(5,"Lilly-- Great idea! Come on %s, let's go to the academy with Mark!\n",mc_name);
    say(5,"%s-- Sure!\nYou go to the academy with Mark and Lilly and attend the introduction class.\n", mc_name);
    say(4,"*** The academy is a huge building with a big courtyard in the middle. There are a lot of students and teachers walking around.\nThe teacher is a middle aged man with a beard and glasses. He seems to be the one in charge of the class.***\n");
    say(5,"The teacher explains how the academy works and what you can expect from it.\n");
    say(5,"Teacher-- I see we have a new student here today!! Welcome to the academy!!\n%s-- Thank you!\n",mc_name);
    say(5,"Teacher-- We have a lot of different classes and activities here at the academy.\nWe have combat classes, magic classes, survival classes, crafting classes and a lot more.\n");
    say(5,"Teacher-- So, you have any experience with fighting and magic or right?\n%s-- No, not really.\nTeacher-- Oh, really weird since the academy starts at 10 yo and you seem way older than that. But don't worry, we will help you get used to this place and teach you everything you need to know.\n",mc_name);
    say(5,"Teacher-- For now, we are going to start with some basic combat training.\nWe will have some demonstrations and then you will get to practice with each other.\n");
    say(5,"Teacher-- Now I'm going to call Lilly and Mark to demonstrate combat and then I will choose pairs of students to try some combat.\nLilly and Mark go to the center of the room and start demonstrating some basic combat techniques.\n");
    say(4,"Teacher-- Ok,now Marta and Laura,...,%s and %s, since you are the only 15 year-olds, you are going to fight each other!!\nI am being paired with a (really good looking... What am I thinking, focus!) student  and we start fighting each other.\n",mc_name,mc_name);
    
    
    if(main_character.gender == 0)say(4,"***%s is 1.68 m tall, a finee body with all the right proportions long brunette hair and a focused look on her face with those deep blue eyes.\n",rival_name);
    else say(4,"***%s is 1.88m tall, muscular body, great smell, sharp jaw, perfect dark brown hair and emerald green eyes with a focudes look.***\n",rival_name);

    main_character = fight(main_character, rival, story, chapter_npc_ids, false);
    say(5,"Teacher-- Wow, that was a great fight!! You both did really well for your first time!!\n%s-- Thanks, I guess...\nYou are a bit confused since you didn't really know how to fight and you don't understand how you did so well but you are happy with the compliment.\n",mc_name);
    say(4,"My body feels different... I feel stronger and faster than before. I don't know how to explain it but I feel like I can do things I couldn't do before.\n");
    say(2,"Not to talk about how I just used %s\n",rival_name);
    say(3,"%s -- Good match %s!!",mc_name,rival_name);
    say(2,"%s -- Sure...\n***You see %s leave the class probably anoyed that they lost***\n",rival_name,rival_name);
    say(3,"%s -- I hope %s is ok...\n");//TODO: Continue from here!! Treat unused variables and make sure the story makes sense with the choices and the fight outcome. Also add more dialogue and interactions with the rival and other characters in the academy. Maybe add some side quests or activities in the academy to make it more interesting. Also, make sure to update the chapter npc ids and the story path accordingly.
    

    say(3,"-------------------------\nChapter 2 Completed\n-------------------------\n");
    set_story_chapter(story,Chapter_3);
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

