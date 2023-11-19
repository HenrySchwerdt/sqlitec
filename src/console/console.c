#include "console.h"

static Parser* parser;

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
    printf("Welcome to %s.\nThis program is written by %s and is in version %s.\n", PROGRAM, AUTHOR, VERSION);
}

static void print_prompt() { printf("db > "); }

static void read_input(Console* console) {
  ssize_t bytes_read =
      getline(&(console->buffer), &(console->buffer_length), stdin);

  if (bytes_read <= 0) {
    printf("Error reading input\n");
    exit(EXIT_FAILURE);
  }

  console->input_length = bytes_read - 1;
  console->buffer[bytes_read - 1] = 0;
}

void start(Console* console, CommandCallback callback) {
    parser = new_parser();
    print_welcome();
    while (true) {
        print_prompt();
        read_input(console);
        Command command = parse_line(parser, console->buffer);
        callback(command);
    }
}