#include "apue.h"
#include "dbEntry.h"

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

int main() {
  dbEntry *first = dbEntry_init();
  dbEntry *second = dbEntry_init();
  first->username = strdup("phloftus");
  first->password = strdup("swordfish");
  dbEntry_destroy(first);
  dbEntry_destroy(second);
}

