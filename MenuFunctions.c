#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"
#include <unistd.h> 

char* get_input(char* prompt) {
    printf("%s", prompt);
    char *choice = malloc(MAX_INPUT);
    if (!choice) return NULL;
    
    if (!fgets(choice, MAX_INPUT, stdin)) {
        free(choice);
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
        result = Continue();
    }
    else if (strcmp(command, "QuitGame") == 0) {
        result = QuitGame();
    }
    else {
        printf("Invalid command. Please try again.\n\n");
        result = menu_selection();
    }
    
    free(command);
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
            free(choice);
            secure_wipe();
            printf("Starting new game...\n");
            return PLAYING;
        }
        else if (strcmp(choice, "no") == 0) {
            free(choice);
            return MENU;
        }
        else {
            printf("Please answer with 'yes' or 'no'.\n");
            free(choice);
            return MENU;
        }
    }
    else {
        printf("No save file found. Starting new game...\n");
        return PLAYING;
    }
}

GameState Continue() {
    printf("Loading your saved game...\n");
    
    Story loaded_story = {0};
    Player loaded_player = {0};
    NPC loaded_npcs[1] = {0};
    
    int found_file = load_save(&loaded_story, &loaded_player, loaded_npcs);
    
    if(found_file==1){
    char *choice = get_input("Found save file. Load it? (yes/no)\n");
    
    if(strcmp(choice,"yes")==0){
        // Only show details if they say yes
        printf("\n--- Loaded Game ---\n");
        usleep(200000); // 0.2s delay
        printf("Player: %s\n", loaded_player.name);
        usleep(200000);
        printf("Age: %d\n", loaded_player.age);
        usleep(200000);
        printf("Chapter: %d\n", loaded_story.Chapter);
        usleep(200000);
        printf("NPC: %s\n", loaded_npcs[0].name);
        usleep(1000000); // 1s delay
        
        free(choice);
        return PLAYING;
    } else {
        free(choice);
        // Clean up allocations before returning
        free(loaded_player.name);
        free(loaded_npcs[0].name);
        return MENU;
    }
}
else{
    printf("Select NewGame to start a New Game.\n Returning to Menu...\n");
    return MENU;
}
}

GameState QuitGame(){
    return QUIT; //Quit the game (end program)
}

//In Game Menu 
 