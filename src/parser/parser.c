#include "parser.h"
Parser* new_parser() {
    Parser* parser = malloc(sizeof(Parser));
    parser->cur = 0;
    parser->line = NULL;
}

void free_parser(Parser* parser) {
   free(parser);
}

static char advance(Parser* parser) {
    char current = parser->line[parser->cur];
    parser->cur++;
    return current;
}

static char current(Parser* parser) {
    return parser->line[parser->cur];
}

static char peek(Parser* parser) {
    return parser->line[parser->cur+1];
}

static Command create_unkown_command(char* command) {
    Command cmd;
    cmd.type = UNKNOWN;
    cmd.data.unknownCommand.command = command;
    return cmd;
}


static CommandType parse_dot_command_type(Parser* parser) {
    if (strncmp(&(parser->line[parser->cur]), "open", 5) == 0)
        return OPEN;
    if (strncmp(&(parser->line[parser->cur]), "tables", 7) == 0)
        return TABLES;
    if (strncmp(&(parser->line[parser->cur]), "schema", 7) == 0)
        return SCHEMA;
    if (strncmp(&(parser->line[parser->cur]), "exit", 5) == 0)
        return EXIT;
    return UNKNOWN;
}

static Command parse_dot_command(Parser* parser) {
    advance(parser);
    Command cmd;
    cmd.type = parse_dot_command_type(parser);
    if (cmd.type == UNKNOWN) {
        cmd.data.unknownCommand.command = parser->line;
    }
    if (cmd.type == EXIT) {
        cmd.data.exitCommand.code = 0;
    }
    return cmd;
}

static Command parse_where_command(Parser* parser) {
    Command cmd;
    return cmd;
}

static Command parse_command(Parser* parser) {
    if (current(parser) == '.') {
        return parse_dot_command(parser);
    } else if (strncmp(parser->line, "WHERE", 6) == 0) {
        return parse_where_command(parser);
    } else {
        return create_unkown_command(parser->line);
    }
}

Command parse_line(Parser* parser, char* line) {
    parser->line = line;
    parser->cur = 0;
    return parse_command(parser);
}