#include "dbEntries.h"
#include "dbg.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

typedef int (*cmpfn) (const void*, const void*);

int cmpfunc( dbEntry **entry1, dbEntry **entry2) {
  if ( (*entry1)->index > (*entry2)->index) return 1;
  else return -1;
}

dbEntries *dbEntries_init() {
  dbEntries *entries = malloc(sizeof(dbEntries));
  entries->entries = NULL;
  entries->next = 0;
  entries->numEntries= 0;
  return entries;
}

void dbEntries_destroy(dbEntries *self) {
  unsigned int entry = 0;
  while (entry < self->numEntries) {
    dbEntry_destroy(self->entries[entry]);
    entry++;
  }
  free(self->entries);
  free(self);
}

int add_entry(dbEntries *self) {
  if ((self->numEntries % 100) == 0) {
    self->entries = realloc(self->entries, (self->numEntries+100)*sizeof(dbEntry *));
    check_mem(self->entries);
  }
  self->entries[(self->numEntries)++] = dbEntry_init();
  return 0;
error:
  return -1;
}

int read_file(FILE *stream, dbEntries *self) {
  char *line = NULL;
  size_t bufsize = 0;
  unsigned int entry = 0;
  while (getline(&line, &bufsize, stream) > 0) {
    add_entry(self);
    populateEntryFromLine(line, self->entries[entry++]);
  }
  free(line);
  return 0;
}

void write_entries_to_file(FILE *output, dbEntries *self) {
  for (unsigned int i=0; i<self->numEntries; i++) {
    writeToFile(output, self->entries[i]);
  }
}

void sort_entries(dbEntries *self) {
  qsort((void *)self->entries, self->numEntries, sizeof(dbEntry *), (cmpfn)cmpfunc);
}

/*
int main() {
  long myFile = 0;
  char path[100];
  sprintf(path, "./A4_ParallelSort/data/%ld", myFile);
  FILE *data = fopen(path, "r");
  dbEntries *ents = dbEntries_init();
  read_file(data, ents);
  sort_entries(ents);
  write_entries_to_file(stdout, ents);
  fclose(data);
  dbEntries_destroy(ents);
}
*/

