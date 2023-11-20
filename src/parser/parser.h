#ifndef parser_h
#define parser_h
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef enum {
    UNKNOWN,
    SELECT,
    INSERT,
    UPDATE,
    DELETE,
    OPEN,
    TABLES,
    SCHEMA,
    EXIT,
} CommandType;

typedef struct {
    char* command;
} UnknownCommand;

typedef struct {
    int code;
} SelectCommand;

typedef struct {
    int code;
} InsertCommand;

typedef struct {
    int code;
} UpdateCommand;

typedef struct {
    int code;
} DeleteCommand;

typedef struct {
    int code;
} ExitCommand;

typedef struct {
    int code;
} TablesCommand;

typedef struct {
    int code;
} OpenCommand;

typedef struct {
    int code;
} SchemaCommand;

typedef struct {
    CommandType type;
    union {
        SelectCommand selectCommand;
        InsertCommand insertCommand;
        UpdateCommand updateCommand;
        DeleteCommand deleteCommand;
        ExitCommand exitCommand;
        TablesCommand tablesCommand;
        OpenCommand openCommand;
        SchemaCommand schemaCommand;
        UnknownCommand unknownCommand;
    } data;
} Command;



typedef struct {
    char* line;
    int buffer_length;
    int input_length;
    int cur;
} ParseData;




Command parse_line(ParseData* data);
#endif