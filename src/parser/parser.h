#ifndef parser_h
#define parser_h

typedef enum {
    UNKNOWN,
    QUERY,
    INSERT,
    UPDATE,
    DELETE,
    EXIT
} CommandType;

typedef struct {
    char* command;
} UnknownCommand;

typedef struct {
    int code;
} QueryCommand;

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
    CommandType type;
    union {
        QueryCommand queryCommand;
        InsertCommand insertCommand;
        UpdateCommand updateCommand;
        DeleteCommand deleteCommand;
        ExitCommand exitCommand;
        UnknownCommand unknownCommand;
    } data;
} Command;
#endif