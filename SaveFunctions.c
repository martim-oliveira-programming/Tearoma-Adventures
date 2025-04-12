#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"


int file_exists(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1; // File exists
    }
    return 0; // File doesn't exist
}


void save_game(Story story, Player player, NPC* chapter_NPCs) {
    FILE *save_file = fopen("save.txt", "w");
    if (!save_file) {
        perror("Error saving game");
        return;
    }

    fprintf(save_file, "Player: %s\nAge: %d\nChapter: %d\nNPC: %s\n",
            player.name, player.age, story.Chapter, 
            chapter_NPCs[0].name);
    fclose(save_file);
    printf("Game saved successfully!\n");
}

int load_save(Story *story, Player *player, NPC *chapter_NPCs) {
    FILE *save_file = fopen("save.txt", "r");
    if (!save_file) {
        printf("No save file found!\n");
        return 0;
    }
 
    // Temporary buffers
    char line[100];
    char player_name[50];
    char npc_name[50];
    int age, chapter;

    // Read and parse each line
    while (fgets(line, sizeof(line), save_file)) {
        if (sscanf(line, "Player: %49[^\n]", player_name) == 1) {
            player->name = strdup(player_name);
        }
        else if (sscanf(line, "Age: %d", &age) == 1) {
            player->age = age;
        }
        else if (sscanf(line, "Chapter: %d", &chapter) == 1) {
            story->Chapter = chapter;
        }
        else if (sscanf(line, "NPC: %49[^\n]", npc_name) == 1) {
            chapter_NPCs[0].name = strdup(npc_name);
        }
    }

    fclose(save_file);
    printf("Game loaded successfully!\n");
    return 1;
}

void secure_wipe() {
    const char* filename = "save.txt";
    
    if (!file_exists(filename)) {
        printf("No save file to wipe.\n");
        return;
    }

    FILE* file = fopen(filename, "r+b");
    if (!file) {
        perror("Error opening file for wiping");
        return;
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    // Overwrite 3 times with random data
    srand(time(0));
    for (int i = 0; i < 3; i++) {
        fseek(file, 0, SEEK_SET);
        for (long j = 0; j < size; j++) {
            fputc(rand() % 256, file);
        }
        fflush(file);
    }

    fclose(file);
    
    if (remove(filename) != 0) {
        perror("Error deleting file");
    }
}

