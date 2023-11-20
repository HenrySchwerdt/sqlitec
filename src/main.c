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
    void* node = get_page(table->pager, table->root_page_num);

    if ((*leaf_node_num_cells(node) >= LEAF_NODE_MAX_CELLS))
    {
        ResultData data = { .error= { .type = CRITICAL, .message = "table is full."}};
        return new_result(FAILURE, data);
    }

    Row *row_to_insert = &(command.to_insert);

    Cursor* cursor = table_end(table);
    leaf_node_insert(cursor, row_to_insert->id, row_to_insert);
    free(cursor);
    ResultData data = { .info = { .message = "added 1 entry."}};
    return new_result(INFO, data);
}

Result* execute_select(SelectCommand command, Table* table) {
    Cursor* cursor = table_start(table);
    Row row;
    int num_entries = 0;
    while(!(cursor->end_of_table)) {
        deserialize_row(cursor_value(cursor), &row);
        print_row(&row);
        cursor_advance(cursor);
        num_entries++;
    }
    free(cursor);
    char msg[200];
    sprintf(msg, "found %s%d%s entries.", BGRN, num_entries, COLOR_RESET);
    ResultData data = { .info = { .message = msg}};
    return new_result(INFO, data);
}

Result* handler(Command command, Table *table)
{
    switch (command.type)
    {
    case EXIT:
        db_close(table);
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
    if (argc < 2) {
        printf("USAGE: sqlitec <filepath>\n");
        exit(EXIT_FAILURE);
    }
    char* filename = argv[1];
    Table* table = db_open(filename);
    start(handler, table);
}