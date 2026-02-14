#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "story.h"
#include "menu.h"
#include "save.h"
#include "mechanics.h"
#include "dialogue.h"
#include "raylib.h"
#include <unistd.h> 
#include <time.h>

int main() {
    InitWindow(800, 600, "Tearoma Adventures");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello, Raylib!", 200, 200, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;


    srand(time(NULL)); // Seed the random number generator
    GameState current_state = MENU;
    Story story = {0}; // Initialize story
    Player main_character = {0};
    int chapter_npc_ids[1] = {-1}; // Placeholder for NPC IDs relevant to the current chapter

    // Main game loop
    while (current_state != QUIT) {
        switch(current_state) {
            
            case MENU:
                say("\nWelcome to Tearoma Adventures what whould you like to do?\n");
                current_state = menu_selection();
                break;
                
            case PLAYING: {
                // Initialize new game if no save exists
                if (!file_exists("save.txt")) {
                    main_character = character_creation(); // Create the player's character
                    story.Chapter = Chapter_1;
                    story.Path = 0;
                    save_game(story, main_character, chapter_npc_ids);
                } else {
                    // Load existing game
                    int status = load_save(&story, &main_character, chapter_npc_ids);
                    if (!status) {
                        say("Save load failed. Starting new game.\n");
                        main_character = character_creation();
                        story.Chapter = Chapter_1;
                        story.Path = 0;
                        save_game(story, main_character, chapter_npc_ids);
                    }
                }
                say("Starting game -- Chapter %d -- Hello %s\n", story.Chapter + 1, main_character.name);

                // Ask Continue (may return MENU, PLAYING, QUIT, etc.)
                current_state = Continue(&story, &main_character, chapter_npc_ids);

                if (current_state == PLAYING) {
                    // actually play the chapter and persist changes
                    main_character = play_chapter(main_character, &story, chapter_npc_ids);
                    save_game(story, main_character, chapter_npc_ids);
                }
                break;
            }
            case QUIT:
                break;
        }
    }
    say("\nGoodbye!\n\n");
    // Cleanup
    if (main_character.name) free(main_character.name);
    // chapter_npc_ids are plain ints; nothing to free
    return 0;
}
 