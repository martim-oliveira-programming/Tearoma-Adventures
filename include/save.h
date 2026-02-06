#ifndef SAVE_H
#define SAVE_H
#include <stdbool.h>
#include "story.h"

void save_game(Story story,Player player,NPC* chapter_NPCs);
int load_save(Story *story, Player *player, NPC *chapter_NPCs);
void secure_wipe();
int file_exists(const char* filename);
void xor_crypt(unsigned char *data, int len);
#endif
