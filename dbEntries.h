#ifndef _dbEntries_h
#define _dbEntries_h

#include "dbEntry.h"

typedef struct dbEntries {
    dbEntry **entries;
    unsigned int next;
    unsigned int numEntries;
} dbEntries;

dbEntries *dbEntries_init();
void dbEntries_destroy(dbEntries *self);
int read_file(FILE *stream, dbEntries *self);
void sort_entries(dbEntries *self);
void write_entries_to_file(FILE *output, dbEntries *self);
#endif

