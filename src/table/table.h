#ifndef table_h
#define table_h
#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include "../btree/btree.h"


typedef struct {
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE];
    char email[COLUMN_EMAIL_SIZE];
} Row;

#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)
#define ID_SIZE size_of_attribute(Row, id)
#define USERNAME_SIZE size_of_attribute(Row, username)
#define EMAIL_SIZE size_of_attribute(Row, email)
#define ID_OFFSET 0
#define USERNAME_OFFSET (ID_OFFSET + ID_SIZE)
#define EMAIL_OFFSET (USERNAME_OFFSET + USERNAME_SIZE)
#define ROW_SIZE (ID_SIZE + USERNAME_SIZE + EMAIL_SIZE)

void serialize_row(Row* source, void* destination);
void deserialize_row(void* source, Row* destination);

#define PAGE_SIZE  4096
#define TABLE_MAX_PAGES 100


typedef struct {
    int file_descriptor;
    uint32_t file_length;
    uint32_t num_pages;
    void* pages[TABLE_MAX_PAGES];
} Pager;

typedef struct {
    uint32_t root_page_num;
    Pager* pager;    
} Table;

typedef struct {
    Table* table;
    uint32_t page_num;
    uint32_t cell_num;
    bool end_of_table;
} Cursor;

void* cursor_value(Cursor* cursor);
void print_row(Row* row);
Table* db_open();
Cursor* table_start(Table* table);
Cursor* table_end(Table* table);
void cursor_advance(Cursor* cursor);
void leaf_node_insert(Cursor* cursor, uint32_t key, Row* value);
void db_close(Table* table);
void *get_page(Pager *pager, uint32_t page_num);

#endif