#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

/* helper: parse comma separated ints into allocated array */
static int parse_int_list(const char *src, int **out_arr) {
    if (!src || *src == '\0') {
        *out_arr = NULL;
        return 0;
    }
    // count items
    int count = 1;
    for (const char *p = src; *p; ++p) if (*p == ',') ++count;
    int *arr = malloc(sizeof(int) * count);
    if (!arr) return 0;
    int idx = 0;
    char *copy = strdup(src);
    char *tok = strtok(copy, ",");
    while (tok && idx < count) {
        arr[idx++] = atoi(tok);
        tok = strtok(NULL, ",");
    }
    free(copy);
    *out_arr = arr;
    return idx;
}

int file_exists(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file) { fclose(file); return 1; }
    return 0;
}

/* Save everything relevant from story and main_character */
void save_game(Story story, Player main_character, NPC* chapter_NPCs) {
    FILE *save_file = fopen("save.txt", "w");
    if (!save_file) {
        perror("Error saving game");
        return;
    }

    // Basic story/player info
    fprintf(save_file, "PlayerName: %s\n", main_character.name ? main_character.name : "");
    fprintf(save_file, "Age: %d\n", main_character.age);
    fprintf(save_file, "Chapter: %d\n", story.Chapter);
    fprintf(save_file, "Path: %d\n", story.Path);

    // simple player fields
    fprintf(save_file, "HUNGER: %d\n", main_character.HUNGER);
    fprintf(save_file, "RANK: %d\n", main_character.RANK);
    fprintf(save_file, "LEVEL: %d\n", main_character.LEVEL);
    fprintf(save_file, "EXP: %d\n", main_character.EXP);

    // Attributes (expand to whatever fields Attributes contains)
    fprintf(save_file, "STAT_DEFENCE: %d\n", main_character.stats.DEFENCE);
    fprintf(save_file, "STAT_MAX_HP: %d\n", main_character.stats.MAX_HP);
    fprintf(save_file, "STAT_MAX_MANA: %d\n", main_character.stats.MAX_MANA);
    fprintf(save_file, "STAT_MAGIC_POWER: %d\n", main_character.stats.MAGIC_POWER);
    fprintf(save_file, "STAT_WEAPON_DAMAGE: %d\n", main_character.stats.WEAPON_DAMAGE);
    fprintf(save_file, "STAT_DAMAGE: %d\n", main_character.stats.DAMAGE);
    fprintf(save_file, "STAT_SPEED: %d\n", main_character.stats.SPEED);
    fprintf(save_file, "STAT_STEALTH: %d\n", main_character.stats.STEALTH);
    fprintf(save_file, "STAT_WEAPON_USER: %d\n", main_character.stats.WEAPON_USER ? 1 : 0);
    fprintf(save_file, "STAT_DUAL_WIELD: %d\n", main_character.stats.DUAL_WILDING);
    fprintf(save_file, "STAT_MAGIC_USER: %d\n", main_character.stats.MAGIC_USER ? 1 : 0);

    // Inventory
    fprintf(save_file, "InventoryCount: %d\n", main_character.item_ammount);
    fprintf(save_file, "Inventory:");
    for (int i = 0; i < main_character.item_ammount; ++i) {
        if (i) fprintf(save_file, ",");
        fprintf(save_file, "%d", main_character.inventoryIDs[i]);
    }
    fprintf(save_file, "\n");

    // Abilities
    fprintf(save_file, "AbilitiesCount: %d\n", main_character.abilities_ammount);
    fprintf(save_file, "Abilities:");
    for (int i = 0; i < main_character.abilities_ammount; ++i) {
        if (i) fprintf(save_file, ",");
        fprintf(save_file, "%d", main_character.abilitiesIDs[i]);
    }
    fprintf(save_file, "\n");

    // Summons
    fprintf(save_file, "SummonsCount: %d\n", main_character.summons_ammount);
    fprintf(save_file, "Summons:");
    for (int i = 0; i < main_character.summons_ammount; ++i) {
        if (i) fprintf(save_file, ",");
        fprintf(save_file, "%d", main_character.summonIDs[i]);
    }
    fprintf(save_file, "\n");

    // Save first NPC name if present
    if (chapter_NPCs && chapter_NPCs[0].name) {
        fprintf(save_file, "NPC0: %s\n", chapter_NPCs[0].name);
    } else {
        fprintf(save_file, "NPC0:\n");
    }

    fclose(save_file);
}

/* Load everything. Caller must ensure main_character/story memory is managed.
   This will strdup names and allocate arrays for inventory/abilities/summons.
*/
int load_save(Story *story, Player *main_character, NPC *chapter_NPCs) {
    FILE *save_file = fopen("save.txt", "r");
    if (!save_file) {
        // no save
        return 0;
    }

    // free previous dynamic arrays/names if present to avoid leaks
    if (main_character->name) { free(main_character->name); main_character->name = NULL; }
    if (chapter_NPCs && chapter_NPCs[0].name) { free(chapter_NPCs[0].name); chapter_NPCs[0].name = NULL; }
    if (main_character->inventoryIDs) { free(main_character->inventoryIDs); main_character->inventoryIDs = NULL; main_character->item_ammount = 0; }
    if (main_character->abilitiesIDs) { free(main_character->abilitiesIDs); main_character->abilitiesIDs = NULL; main_character->abilities_ammount = 0; }
    if (main_character->summonIDs) { free(main_character->summonIDs); main_character->summonIDs = NULL; main_character->summons_ammount = 0; }

    char line[512];
    while (fgets(line, sizeof(line), save_file)) {
        // remove trailing newline
        char *nl = strchr(line, '\n'); if (nl) *nl = '\0';

        if (strncmp(line, "PlayerName: ", 12) == 0) {
            main_character->name = strdup(line + 12);
        } else if (strncmp(line, "Age: ", 5) == 0) {
            main_character->age = atoi(line + 5);
        } else if (strncmp(line, "Chapter: ", 9) == 0) {
            story->Chapter = atoi(line + 9);
        } else if (strncmp(line, "Path: ", 6) == 0) {
            story->Path = atoi(line + 6);
        } else if (strncmp(line, "HUNGER: ", 8) == 0) {
            main_character->HUNGER = atoi(line + 8);
        } else if (strncmp(line, "RANK: ", 6) == 0) {
            main_character->RANK = atoi(line + 6);
        } else if (strncmp(line, "LEVEL: ", 7) == 0) {
            main_character->LEVEL = atoi(line + 7);
        } else if (strncmp(line, "EXP: ", 5) == 0) {
            main_character->EXP = atoi(line + 5);
        } else if (strncmp(line, "STAT_DEFENCE: ", 14) == 0) {
            main_character->stats.DEFENCE = atoi(line + 14);
        } else if (strncmp(line, "STAT_MAX_HP: ", 13) == 0) {
            main_character->stats.MAX_HP = atoi(line + 13);
        } else if (strncmp(line, "STAT_MAX_MANA: ", 15) == 0) {
            main_character->stats.MAX_MANA = atoi(line + 15);
        } else if (strncmp(line, "STAT_MAGIC_POWER: ", 18) == 0) {
            main_character->stats.MAGIC_POWER = atoi(line + 18);
        } else if (strncmp(line, "STAT_WEAPON_DAMAGE: ", 20) == 0) {
            main_character->stats.WEAPON_DAMAGE = atoi(line + 20);
        } else if (strncmp(line, "STAT_DAMAGE: ", 13) == 0) {
            main_character->stats.DAMAGE = atoi(line + 13);
        } else if (strncmp(line, "STAT_SPEED: ", 12) == 0) {
            main_character->stats.SPEED = atoi(line + 12);
        } else if (strncmp(line, "STAT_STEALTH: ", 14) == 0) {
            main_character->stats.STEALTH = atoi(line + 14);
        } else if (strncmp(line, "STAT_WEAPON_USER: ", 18) == 0) {
            main_character->stats.WEAPON_USER = atoi(line + 18) ? true : false;
        } else if (strncmp(line, "STAT_DUAL_WIELD: ", 17) == 0) {
            main_character->stats.DUAL_WILDING = atoi(line + 17);
        } else if (strncmp(line, "STAT_MAGIC_USER: ", 17) == 0) {
            main_character->stats.MAGIC_USER = atoi(line + 17) ? true : false;
        } else if (strncmp(line, "Inventory:", 10) == 0) {
            int *arr = NULL;
            int count = parse_int_list(line + 10, &arr);
            main_character->inventoryIDs = arr;
            main_character->item_ammount = count;
        } else if (strncmp(line, "Abilities:", 10) == 0) {
            int *arr = NULL;
            int count = parse_int_list(line + 10, &arr);
            main_character->abilitiesIDs = arr;
            main_character->abilities_ammount = count;
        } else if (strncmp(line, "Summons:", 8) == 0) {
            int *arr = NULL;
            int count = parse_int_list(line + 8, &arr);
            main_character->summonIDs = arr;
            main_character->summons_ammount = count;
        } else if (strncmp(line, "NPC0: ", 6) == 0) {
            if (chapter_NPCs) chapter_NPCs[0].name = strdup(line + 6);
        }
    }

    fclose(save_file);
    return 1;
}

void secure_wipe() {
    const char* filename = "save.txt";
    if (!file_exists(filename)) {
        printf("No save file to wipe.\n");
        return;
    }
    FILE* file = fopen(filename, "r+b");
    if (!file) { perror("Error opening file for wiping"); return; }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    srand((unsigned)time(NULL));
    for (int i = 0; i < 3; i++) {
        fseek(file, 0, SEEK_SET);
        for (long j = 0; j < size; j++) fputc(rand() % 256, file);
        fflush(file);
    }
    fclose(file);
    if (remove(filename) != 0) perror("Error deleting file");
}
