#include "story.h"
#include "dialogue.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void say(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf("\n");
    usleep(300000);
}

int ask(const char *prompt, ...) {
    say("%s", prompt);

    va_list args;
    va_start(args, prompt);

    const char *options[10]; // max 10 options for simplicity
    int count = 0;
    const char *opt;

    while ((opt = va_arg(args, const char *)) != NULL && count < 10) {
        options[count++] = opt;
    }
    va_end(args);

    for (int i = 0; i < count; i++) {
        say("%d) %s", i + 1, options[i]);
    }

    char line[32];
    if (!fgets(line, sizeof(line), stdin)) {
        return 0; // default fallback on input failure
    }

    char *endptr = NULL;
    long choice = strtol(line, &endptr, 10);
    if (choice < 1 || choice > count) choice = 1; // default fallback
    return (int)(choice - 1);
}

void clear_dialogue(void) {
    fputs("\n\n", stdout);
}
