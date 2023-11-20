#include "console.h"

static void print_welcome() {
    printf("Welcome to %s.\nThis program is written by %s and is in version %s.\n", PROGRAM, AUTHOR, VERSION);
}

static void print_prompt() { printf("%sdb > %s", GRN, CRESET); }

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

static void print_error(Error error) {
    switch (error.type)
    {
    case CRITICAL:
        printf("%s[critical]:%s ", BMAG, CRESET);
        break;
    case ERROR:
        printf("%s[error]:%s ", BRED, CRESET);
        break;
    case WARN: 
        printf("%s[warn]:%s ", BYEL, CRESET);
        break;
    }
    printf("%s\n", error.message);
}

static void print_info(Info info) {
    printf("%s[info]:%s ", BGRN, CRESET);
    printf("%s\n", info.message);
}

void start(CommandCallback callback, Table* table) {
    print_welcome();
    while (true) {
        print_prompt();
        ParseData* parse_data = read_input();
        Command command = parse_line(parse_data);
        if (command.type == PARSE_ERROR) {
            printf("%s\n", command.data.errorCommand.error);
            free(parse_data);
            continue;
        }
        Result* result = callback(command, table);
        if (result->type == INFO) {
            print_info(result->data.info);
        } else {
            print_error(result->data.error);
        }
        free_result(result);
        free(parse_data);
    }
}