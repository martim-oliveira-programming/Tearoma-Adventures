#ifndef MENU_H
#define MENU_H
#include <stdbool.h>
#include "story.h"
#include "mechanics.h"
 
 
#define MAX_INPUT 20

typedef enum{
    QUIT = -1,
    MENU,
    PLAYING,
    //PAUSE,
    //MISSION_SELECTION
}GameState;

char* get_input(char* input);

int menu_selection();
int NewGame();
int Commands();
GameState Continue(Story *out_story, Player *out_player, int *chapter_npc_ids);
int QuitGame();

#endif
