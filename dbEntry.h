#ifndef _dbEntry_h
#define _dbEntry_h

#include <stdio.h>

typedef struct dbEntry {
  char *username;
  char *password;
  char *bloodtype;
  char *domain;
  unsigned int index;
} dbEntry;

dbEntry *dbEntry_init();
void dbEntry_destroy(dbEntry *self);
void writeToFile(FILE *output, dbEntry *self);
void populateEntryFromLine(char *line, dbEntry *self);
#endif

