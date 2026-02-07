#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "story.h"
#include "menu.h"
#include "save.h"
#include "mechanics.h"
#include <unistd.h> 

char* get_input(char* prompt) {
    printf("%s", prompt);
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
GameState menu_selection() {
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
        printf("Invalid command. Please try again.\n\n");
        result = menu_selection();
    }
    
    if (command)free(command);
    return result;
}

GameState Commands(){
    printf("Quit: (Quit the game and go to Main Menu.\nThis will NOT save the game.\nThe game saves automatically after each Chapter.)\n\n");
    return MENU;
}

GameState NewGame() {
    if(file_exists("save.txt")) {
        char* choice = get_input(
            "Are you sure you want to start a new game? "
            "The old save file will be deleted forever. (yes/no)\n"
        );
        
        if (!choice) return MENU;

        if (strcmp(choice, "yes") == 0) {
            if(choice)free(choice);
            secure_wipe();
            printf("Starting new game...\n");
            return PLAYING;
        }
        else if (strcmp(choice, "no") == 0) {
            if(choice)free(choice);
            return MENU;
        }
        else {
            printf("Please answer with 'yes' or 'no'.\n");
            if(choice)free(choice);
            return MENU;
        }
    }
    else {
        printf("No save file found. Starting new game...\n");
        return PLAYING;
    }
}

GameState Continue(Story *out_story, Player *out_player, int *chapter_npc_ids) {
    char *choice;
    printf("Loading your saved game...\n");
    
    Story loaded_story = {0};
    Player loaded_player = {0};
    int loaded_npc_ids[1] = {-1};
    
    int found_file = load_save(&loaded_story, &loaded_player, loaded_npc_ids);
    if (!found_file) {
        printf("Select NewGame to start a New Game.\nReturning to Menu...\n");
        return MENU;
    }

    if (out_story->Chapter == 0){
        choice = "yes"; // auto-continue if no current game
    }else{
        choice = get_input("Found save file. Do you wish to proceed to the next Chapter? (yes/no)\n");
    }
    if (!choice) return MENU;

    if (strcmp(choice, "yes") == 0) {
        // copy loaded into caller-provided structures
        // free any existing dynamic fields in out_player if needed before overwrite
        if (out_player->name) { free(out_player->name); out_player->name = NULL; }
        if (out_player->hair_colour) { free(out_player->hair_colour); out_player->hair_colour = NULL; }
        // shallow copy whole struct then replace dynamic pointers
        *out_story = loaded_story;
        *out_player = loaded_player;
        if (chapter_npc_ids) chapter_npc_ids[0] = loaded_npc_ids[0];

        // show minimal info
        printf("\n--- Loaded Game ---\n");
        usleep(200000);
        printf("Player: %s\n", out_player->name ? out_player->name : "(unknown)");
        usleep(200000);
        printf("Age: %d\n", out_player->age);
        usleep(200000);
        printf("Chapter: %d\n", out_story->Chapter);
        usleep(200000);
        printf("NPC ID: %d\n", (chapter_npc_ids) ? chapter_npc_ids[0] : -1);
        usleep(1000000);

        if (out_story->Chapter != 0){if(choice)free(choice);}
        return PLAYING;
    } else {
        if(choice)free(choice);
        // free loaded allocations because user declined
        if (loaded_player.name) free(loaded_player.name);
        if (loaded_player.hair_colour) free(loaded_player.hair_colour);
        if (loaded_player.inventoryIDs) free(loaded_player.inventoryIDs);
        if (loaded_player.abilitiesIDs) free(loaded_player.abilitiesIDs);
        if (loaded_player.summonIDs) free(loaded_player.summonIDs);
        return MENU;
    }
}

GameState QuitGame(){
    return QUIT; //Quit the game (end program)
}

//In Game Menu 
 