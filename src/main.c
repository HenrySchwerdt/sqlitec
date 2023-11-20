#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "console/console.h"
#include "error/error.h"
#include "parser/parser.h"
#include "table/table.h"

Result* execute_insert(InsertCommand command, Table *table)
{
    if (table->num_rows >= TABLE_MAX_ROWS)
    {
        ResultData data = { .error= { .type = CRITICAL, .message = "table is full."}};
        return new_result(FAILURE, data);
    }

    Row *row_to_insert = &(command.to_insert);

    serialize_row(row_to_insert, row_slot(table, table->num_rows));
    table->num_rows += 1;
    ResultData data = { .info = { .message = "added 1 entry."}};
    return new_result(INFO, data);
}

Result* execute_select(SelectCommand command, Table* table) {
    Row row;
    for (uint32_t i = 0; i < table->num_rows; i++) {
        deserialize_row(row_slot(table, i), &row);
        print_row(&row);
    }
    char msg[200];
    sprintf(msg, "found %s%d %s entries.", BGRN, table->num_rows, CRESET);
    ResultData data = { .info = { .message = msg}};
    return new_result(INFO, data);
}

Result* handler(Command command, Table *table)
{
    switch (command.type)
    {
    case EXIT:
        exit(command.data.exitCommand.code);
        break;
    case SELECT:
        return execute_select(command.data.selectCommand, table);
    case INSERT:
        return execute_insert(command.data.insertCommand, table);
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
    default:{
        char msg[200];
        sprintf(msg, "unkown command '%s%s%s'.", BRED, command.data.unknownCommand.command, CRESET);
        ResultData data = {.error = {.type = WARN, .message = msg}};
        return new_result(FAILURE, data);
    }
       
    }
}

int main(int argc, char *argv[])
{
    Table *table = new_table();
    start(handler, table);
    free_table(table);
}