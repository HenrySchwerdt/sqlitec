#include "parser.h"

static char advance(ParseData* data) {
    char current = data->line[data->cur];
    data->cur++;
    return current;
}

static char current(ParseData* data) {
    return data->line[data->cur];
}

static char peek(ParseData* data) {
    return data->line[data->cur+1];
}

static Command create_unkown_command(char* command) {
    Command cmd;
    cmd.type = UNKNOWN;
    cmd.data.unknownCommand.command = command;
    return cmd;
}


static CommandType get_command_type(ParseData* data) {
    size_t len = strlen(data->line);
    if (len >= 5 && strncmp(data->line, ".open", 5) == 0) {
        data->cur += 5;
        return OPEN;
    }
        
    if (len >= 7 && strncmp(data->line, ".tables", 7) == 0) {
        data->cur += 7;
        return TABLES;
    }
        
    if (len >= 7 && strncmp(data->line, ".schema", 7) == 0) {
        data->cur += 7;
        return SCHEMA;
    }
       
    if (len >= 5 && strncmp(data->line, ".exit", 5) == 0) {
        data->cur += 5;
        return EXIT;
    }

    if (len >= 6 && strncmp(data->line, "insert", 6) == 0) {
        data->cur += 6;
        return INSERT;
    }
        
    if (len >= 6 && strncmp(data->line, "select", 6) == 0) {
        data->cur += 6;
        return SELECT;
    }
        
    if (len >= 6 && strncmp(data->line, "update", 6) == 0) {
        data->cur += 6;
        return UPDATE;
    }

    if (len >= 6 && strncmp(data->line, "delete", 6) == 0) {
        data->cur += 6;
        return DELETE;
    }
    return UNKNOWN;
}

static Command parse_open_command(ParseData* data) {
    Command cmd;
    cmd.type = OPEN;
    cmd.data.openCommand.code = 1;
    return cmd;
}

static Command parse_tables_command(ParseData* data) {
    Command cmd;
    cmd.type = TABLES;
    cmd.data.tablesCommand.code = 2;
    return cmd;
}

static Command parse_schema_command(ParseData* data) {
    Command cmd;
    cmd.type = SCHEMA;
    cmd.data.schemaCommand.code = 3;
    return cmd;
}

static Command parse_exit_command(ParseData* data) {
    Command cmd;
    cmd.type = EXIT;
    cmd.data.exitCommand.code = 0;
    return cmd;
}

static Command parse_update_command(ParseData* data) {
    Command cmd;
    cmd.type = UPDATE;
    cmd.data.updateCommand.code = 4;
    return cmd;
}

static Command parse_insert_command(ParseData* data) {
    Command cmd;
    cmd.type = INSERT;
    advance(data); // skip ' ' need to code that better later
    Row row;
    int args_assigned = sscanf(&(data->line[data->cur]), "%d %s %s", &(row.id), row.username, row.email);
    if (args_assigned < 3) {
        cmd.type = PARSE_ERROR;
        cmd.data.errorCommand.error = "Expect three fields <int> <string> <string>";
        return cmd;
    }
    cmd.data.insertCommand.to_insert = row;
    return cmd;
}

static Command parse_select_command(ParseData* data) {
    Command cmd;
    cmd.type = SELECT;
    cmd.data.selectCommand.code = 6;
    return cmd;
}

static Command parse_delete_command(ParseData* data) {
    Command cmd;
    cmd.type = DELETE;
    cmd.data.deleteCommand.code = 7;
    return cmd;
}

static Command parse_command(ParseData* data) {
    CommandType command_type = get_command_type(data);
    switch (command_type)
    {
    case OPEN:
        return parse_open_command(data);
    case TABLES:
        return parse_tables_command(data);
    case SCHEMA:
        return parse_schema_command(data);
    case EXIT:
        return parse_exit_command(data);
    case INSERT:
        return parse_insert_command(data);
    case SELECT:
        return parse_select_command(data);
    case UPDATE:
        return parse_update_command(data);
    case DELETE:
        return parse_delete_command(data);
    default: 
        return create_unkown_command(data->line);
    }
}

Command parse_line(ParseData* data) {
    Command cmd = parse_command(data);
    return cmd;
}