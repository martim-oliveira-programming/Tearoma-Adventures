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

#endif
