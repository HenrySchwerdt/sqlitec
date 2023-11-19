#ifndef console_h
#define console_h
#include "../parser/parser.h"
#include "../error/error.h"
#include "../parser/parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../sqlitec.h"



typedef struct {
  char* buffer;
  size_t buffer_length;
  ssize_t input_length;
} Console;

typedef Error *(CommandCallback)(Command);

Console* new_console();

void free_console(Console* console);

void start(Console* console, CommandCallback callback);


#endif