#include "dbEntry.h"
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

dbEntry *dbEntry_init() {
  dbEntry *dbEnt = (dbEntry *)malloc(sizeof(dbEntry));
  dbEnt->username = NULL;
  dbEnt->password = NULL;
  dbEnt->bloodtype = NULL;
  dbEnt->domain = NULL;
  return dbEnt;
}

void dbEntry_destroy(dbEntry *self) {
  if (self->username) free(self->username);
  if (self->password) free(self->password);
  if (self->bloodtype) free(self->bloodtype);
  if (self->domain) free(self->domain);
  free(self);
}

void writeToFile(FILE *output, dbEntry *self) {
  if (output != NULL) {
    char *name = self->username;
    char *pword = self->password;
    char *btype = self->bloodtype;
    char *domain = self->domain;
    int idx = self->index;
    char line[150];
    sprintf(line, "%s,%s,%s,%s,%d\n", name, pword, btype, domain, idx);
    fwrite(line, strlen(line), sizeof(char), output);
  }
}

void populateEntryFromLine(char *line, dbEntry *self) {
  self->username = strdup(strtok(line, ","));
  self->password = strdup(strtok(NULL, ","));
  self->bloodtype = strdup(strtok(NULL, ","));
  self->domain = strdup(strtok(NULL, ","));
  self->index = atoi(strtok(NULL, "\n"));
}

/*
int main() {
  dbEntry *first = dbEntry_init();
  dbEntry *second = dbEntry_init();
  char *line = NULL;
  size_t bufsize = 0;
  getline(&line, &bufsize, stdin);
  populateEntryFromLine(line, first);
  free(line);
  writeToFile(stdout, first);
  dbEntry_destroy(first);
  dbEntry_destroy(second);
}
*/

