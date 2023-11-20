#include "console.h"

static void print_welcome() {
    printf("Welcome to %s.\nThis program is written by %s and is in version %s.\n", PROGRAM, AUTHOR, VERSION);
}

static void print_prompt() { printf("db > "); }

static ParseData* read_input() {
    ParseData* parse_data = malloc(sizeof(ParseData));
    parse_data->buffer_length = 0;
    parse_data->input_length = 0;
    parse_data->line = NULL;
    parse_data->cur = 0;
    ssize_t bytes_read = getline(&(parse_data->line), &(parse_data->buffer_length), stdin);

    if (bytes_read <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    parse_data->input_length = bytes_read - 1;
    parse_data->line[bytes_read - 1] = '\0';
    return parse_data;
}

void start(CommandCallback callback) {
    print_welcome();
    while (true) {
        print_prompt();
        ParseData* parse_data = read_input();
        Command command = parse_line(parse_data);
        callback(command);
        free(parse_data);
    }
}