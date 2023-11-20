#ifndef table_h
#define table_h
#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE];
    char email[COLUMN_EMAIL_SIZE];
} Row;

#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)
extern const uint32_t ID_SIZE;
extern const uint32_t USERNAME_SIZE;
extern const uint32_t EMAIL_SIZE;
extern const uint32_t ID_OFFSET;
extern const uint32_t USERNAME_OFFSET;
extern const uint32_t EMAIL_OFFSET;
extern const uint32_t ROW_SIZE;

void serialize_row(Row* source, void* destination);
void deserialize_row(void* source, Row* destination);

extern const uint32_t PAGE_SIZE;
extern const uint32_t ROWS_PER_PAGE;
extern const uint32_t TABLE_MAX_ROWS;
#define TABLE_MAX_PAGES 100

typedef struct {
  uint32_t num_rows;
  void* pages[TABLE_MAX_PAGES];
} Table;

void* row_slot(Table* table, uint32_t row_num);
void print_row(Row* row);
Table* new_table();

void free_table(Table* table);

#endif