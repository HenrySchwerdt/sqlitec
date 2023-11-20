#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "console/console.h"
#include "error/error.h"
#include "parser/parser.h"
#include "table/table.h"

Error execute_insert(InsertCommand command, Table *table)
{
    Error err;
    if (table->num_rows >= TABLE_MAX_ROWS)
    {
       
        err.type = CRITICAL;
        err.message = "Table is full";
        return err;
    }

    Row *row_to_insert = &(command.to_insert);

    serialize_row(row_to_insert, row_slot(table, table->num_rows));
    table->num_rows += 1;
    err.type = NONE;
    return err;
}

Error execute_select(SelectCommand command, Table* table) {
  Error err;
  Row row;
  for (uint32_t i = 0; i < table->num_rows; i++) {
     deserialize_row(row_slot(table, i), &row);
     print_row(&row);
  }
  err.type = NONE;
  return err;
}

Error handler(Command command, Table *table)
{
    switch (command.type)
    {
    case EXIT:
        exit(command.data.exitCommand.code);
        break;
    case SELECT:
        execute_select(command.data.selectCommand, table);
        break;
    case INSERT:
        execute_insert(command.data.insertCommand, table);
        // if (err.type == NONE) {
        //     printf("inserted 1 item.\n");
        // } else {
        //     return err;
        // }
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

int main(int argc, char *argv[])
{
    Table *table = new_table();
    start(handler, table);
    free_table(table);
}