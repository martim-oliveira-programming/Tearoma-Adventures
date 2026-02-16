#ifndef STORY_H
#define STORY_H
#include <stdbool.h>

typedef enum{
    Chapter_1,
    Chapter_2,
    Chapter_3,
    Chapter_4,
    Chapter_5,
}Chapters;

typedef struct story{
    int Chapter;
    int Path;
}Story;

#include "mechanics.h"

char *choose_pronoun(Player main_character);

int get_story_path(Story story);
int get_story_chapter(Story story);
void set_story_path(Story *story, int path);
void set_story_chapter(Story *story, int chapter);

//Chapter functions
Player chapter1(Player main_character, Story *story);

// Paths
Player path_1(Player main_character,Story *story);
Player path_2(Player main_character,Story *story);

//Sub paths for chapter 1
Player path_1_help(Player main_character);
Player path_1_dont_help(Player main_character);
Player path_1_cut(Player main_character);
Player path_1_ask(Player main_character);
Player path_2_go(Player main_character);
Player path_2_stay(Player main_character);


#endif
