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



typedef Error *(CommandCallback)(Command);

void start(CommandCallback callback);


#endif