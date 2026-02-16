#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "story.h"
#include "menu.h"
#include "save.h"
#include "mechanics.h"
#include "items.h"
#include "abilities.h"
#include "npc.h"
#include "dialogue.h"
#include <unistd.h> 

char* get_input(char* prompt) {
    say(0,"%s", prompt);
    char *choice = malloc(MAX_INPUT);
    if (!choice) return NULL;
    
    if (!fgets(choice, MAX_INPUT, stdin)) {
        if(choice)free(choice);
        return NULL;
    }
    choice[strcspn(choice, "\n")] = '\0';
    return choice;
}
//Base Menu
GameState menu_selection(void) {
    char* command = get_input(
        "\nNewGame: Start a new game.\n"
        "Continue: Continue from last save\n"
        "Commands: Show the game's commands\n"
        //"Options: Open the options menu\n"
        "QuitGame: Leave the game\n\n"
    );
    
    if (!command) return 0;

    int result = 0;
    
    if (strcmp(command, "NewGame") == 0) {
        result = NewGame();
    }
    else if(strcmp(command,"Commands")==0){
        result = Commands();
    }
    else if (strcmp(command, "Continue") == 0) {
        result = PLAYING;
    }
    else if (strcmp(command, "QuitGame") == 0) {
        result = QuitGame();
    }
    else {
        say(0,"Invalid command. Please try again.\n\n");
        result = menu_selection();
    }
    
    if (command)free(command);
    return result;
}

GameState Commands(void){
    say(0,"Quit: (Quit the game and go to Main Menu.\nThis will NOT save the game.\nThe game saves automatically after each Chapter.)\n\n");
    return MENU;
}

GameState NewGame(void) {
    if(file_exists("save.txt")) {
        int choice = ask("Are you sure you want to start a new game? "
            "The old save file will be deleted forever.\n", "Yes", "No", NULL);
        
        if (choice<0||choice >1) return MENU;

        if (choice == 0) {
            secure_wipe();
            say(0,"Starting new game...\n");
            return PLAYING;
        }
        else if (choice == 1) {
             return MENU;
        }
        else {
            say(0,"Please answer with 1 or 2.\n");
            return MENU;
        }
    }
    else {
        say(0,"No save file found. Starting new game...\n");
        return PLAYING;
    }
}

GameState Continue(Story *out_story, Player *out_player, int *chapter_npc_ids) {
    int choice;
    say(0,"Loading your saved game...\n");
    
    Story loaded_story = {0};
    Player loaded_player = {0};
    int loaded_npc_ids[1] = {-1};
    
    int load_status = load_save(&loaded_story, &loaded_player, loaded_npc_ids);
    if (!load_status) {
        say(0,"Select NewGame to start a New Game.\nReturning to Menu...\n");
        return MENU;
    }

    if (out_story->Chapter == 0){
        choice = 0; // auto-continue if no current game
    }else{
        choice = ask("Found save file. Do you wish to proceed to the next Chapter?\n", "Yes", "No", NULL);
    }
    if (choice <0) 
    {return MENU;}

    if (choice == 0) {
        // copy loaded into caller-provided structures
        // free any existing dynamic fields in out_player if needed before overwrite
        if (out_player->name) { free(out_player->name); out_player->name = NULL; }
        if (out_player->hair_colour) { free(out_player->hair_colour); out_player->hair_colour = NULL; }
        // shallow copy whole struct then replace dynamic pointers
        *out_story = loaded_story;
        *out_player = loaded_player;
        if (chapter_npc_ids) chapter_npc_ids[0] = loaded_npc_ids[0];

        // show minimal info
        say(2,"\n--- Loaded Game ---\n");
        say(2,"Player: %s\n", out_player->name ? out_player->name : "(unknown)");
        say(2,"Age: %d\n", out_player->age);
        say(2,"Chapter: %d\n", out_story->Chapter);
        say(2,"NPC ID: %d\n", (chapter_npc_ids) ? chapter_npc_ids[0] : -1);
        return PLAYING;
    } else {
        // free loaded allocations because user declined
        if (loaded_player.name) free(loaded_player.name);
        if (loaded_player.hair_colour) free(loaded_player.hair_colour);
        if (loaded_player.inventoryIDs) free(loaded_player.inventoryIDs);
        if (loaded_player.abilitiesIDs) free(loaded_player.abilitiesIDs);
        if (loaded_player.summonIDs) free(loaded_player.summonIDs);
        return MENU;
    }
}

GameState QuitGame(void){
    return QUIT; //Quit the game (end program)
}

//In Game Menu 
 