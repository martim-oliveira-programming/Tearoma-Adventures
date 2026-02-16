#ifndef DIALOGUE_H
#define DIALOGUE_H

#include <stdarg.h>

// Can later change the implementation to wait for input.
void say(int wait_seconds,const char *format, ...);

// Ask player a choice, return the selected option index
int ask(const char *prompt, ...);

// Clear dialogue / UI
void clear_dialogue(void);

#endif
