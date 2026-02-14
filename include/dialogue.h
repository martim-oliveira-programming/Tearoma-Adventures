#ifndef DIALOGUE_H
#define DIALOGUE_H

#include <stdarg.h>

// Print text character by character (like "say").
// Can later change the implementation to wait for input.
void say(const char *format, ...);

// Ask player a choice, return the selected option index
int ask(const char *prompt, ...);

// Clear dialogue / UI
void clear_dialogue();

#endif
