#include "dbEntries.h"
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


dbEntries *dbEntries_init() {
  dbEntries *entries = malloc(sizeof(dbEntries));
  entries->nextEntry = 0;
  entries->numEntries= 0;
  return entries;
}

void dbEntries_destroy(dbEntries *self) {
  unsigned int entry = 0;
  while (entry < self->numEntries) free(self->entries[entry]);
  free(self);
}

void* Thread() {
  char test_buf[] = "Hello,World\nFoo,Bar\n";
  char *saveptr1, *saveptr2, *line, *token;
  line = strtok_r(test_buf, "\n", &saveptr1);
  fprintf(stdout, "%s\n", line);
  token = strtok_r(line, ",", &saveptr2);
  fprintf(stdout, "token: %s\n", token);
  token = strtok_r(NULL, ",", &saveptr2);
  fprintf(stdout, "token: %s\n", token);
  return NULL;
}

int main() {
  pthread_t threadA, threadB; // need to name the thread
  int rc;
	if ( (rc = pthread_create(&threadA , NULL, Thread, NULL)) )
      {fprintf(stdout,"ERROR; return pthread_create()" );
         	exit(1); }
	if ( (rc = pthread_create(&threadB , NULL, Thread, NULL)) )
      {fprintf(stdout,"ERROR; return pthread_create()" );
         	exit(1); }
  pthread_join(threadA, NULL);
  pthread_join(threadB, NULL);
  exit(EXIT_SUCCESS);
}

