#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "console/console.h"
#include "parser/parser.h"

Error handler(Command command) {
    switch (command.type)
    {
    case EXIT:
        exit(command.data.exitCommand.code);
        break;
    case SELECT:
        printf("You ran a select command with code: %d\n", command.data.selectCommand.code);
        break;
    case INSERT:
        printf("You ran a insert command with code: %d\n", command.data.selectCommand.code);
        break;
    case UPDATE:
        printf("You ran a update command with code: %d\n", command.data.selectCommand.code);
        break;
    case DELETE:
        printf("You ran a delete command with code: %d\n", command.data.selectCommand.code);
        break;
    case OPEN:
        printf("You ran a open command with code: %d\n", command.data.selectCommand.code);
        break;
    case TABLES:
        printf("You ran a tables command with code: %d\n", command.data.selectCommand.code);
        break;
    case SCHEMA:
        printf("You ran a schema command with code: %d\n", command.data.selectCommand.code);
        break;
    default:
        printf("Unkown command '%s'.\n", command.data.unknownCommand.command);
        break;
    }
}

int main(int argc, char* argv[]) {
    start(handler);
}