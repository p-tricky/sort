#include "dbEntries.h"
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

long numFiles = 9;
dbEntries *files[9]; //global array that contains each threads srtd struct
void *sort_files(void* file);

//
// each thread runs sort_files
//
void* sort_files(void *file) {
  long myFile = (long) file; 
  printf("hello from thread %ld\n", myFile);
  char path[100];
  sprintf(path, "./data/%ld", myFile); //files in data/ and titled 0-numFiles
  FILE *data = fopen(path, "r");
  dbEntries *ents = dbEntries_init();
  read_file(data, ents); //read file into struct
  sort_entries(ents); //sort struct
  files[myFile] = ents; //add srtd struct to global array where main can access 
  fclose(data); //close /data file
  return NULL;
}

int merge_files(FILE *db) {
  unsigned int next = 1, max = 0; 
  dbEntry *next_entry;
  int i;
  for (i=0; i<numFiles; i++) { //count total entries
    max += files[i]->numEntries;
  }
  while (next <= max) { //loop till we merge all entries
    for (i=0; i<numFiles; i++) { //find and write next entry
      next_entry = files[i]->entries[files[i]->next];
      if (next_entry->index == next) { //next entry found
        writeToFile(db, next_entry); //write
        if (files[i]->next < files[i]->numEntries-1) files[i]->next++;
      }
    }
    next++;
  }
  return 0;
}

int main() {
 long thread;
 pthread_t *thread_handles;
 thread_handles = malloc(numFiles*sizeof(pthread_t));
 for (thread=0; thread<numFiles; thread++)
   pthread_create(&thread_handles[thread], NULL, sort_files, (void*)thread);
 for (thread=0; thread<numFiles; thread++)
   pthread_join(thread_handles[thread], NULL);
 FILE *db = fopen("database", "w");
 merge_files(db);
 fclose(db);
 exit(EXIT_SUCCESS);

}

