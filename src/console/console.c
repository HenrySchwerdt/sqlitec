#include "console.h"


Console* new_console() {
    Console* console = (Console*)malloc(sizeof(Console));
    console->buffer = NULL;
    console->buffer_length = 0;
    console->input_length = 0;

    return console;
}

void free_console(Console* console) {
    free(console->buffer);
    free(console);
}

static void print_welcome() {
    printf("Welcome to %s. This program is written by %s and is in version %s.", PROGRAM, AUTHOR, VERSION);
}

static void print_prompt() { printf("db > "); }


void start(Console* console, CommandCallback callback) {

}