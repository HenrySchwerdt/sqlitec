#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "console/console.h"
#include "parser/parser.h"

Error handler(Command command) {
    if (command.type == EXIT) {
        exit(command.data.exitCommand.code);
    } else if (command.type == UNKNOWN) {
        printf("Unkown command '%s'.\n", command.data.unknownCommand.command);
    }
}

int main(int argc, char* argv[]) {
    Console* console = new_console();
    start(console, handler);
}