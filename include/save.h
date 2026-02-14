#ifndef SAVE_H
#define SAVE_H
#include <stdbool.h>
#include "story.h"

void save_game(Story story, Player player, int *chapter_npc_ids);
int load_save(Story *story, Player *player, int *chapter_npc_ids);
void secure_wipe(void);
int file_exists(const char* filename);
void xor_crypt(unsigned char *data, int len);
#endif
