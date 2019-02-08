#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//4Kb i guess
#define BUF_SIZE 4048
char content[BUF_SIZE];
const char *todoFilePath = "/home/anuraganand/todo.do";


//my todo file
FILE *file;

struct Todo {
  char *todos;
};

void main(void) {
  char *sentence =  (char *) malloc(100 * sizeof(char));
  printf("Enter a choice :- ");
  int choice = 0;
  scanf("%d", &choice); 
  fgets(sentence, 100, stdin);
  printf("Sentence %s \n", sentence);
  int l = strlen(sentence);
  file = fopen(todoFilePath, "a");
  if(file) {
    fwrite(sentence, sizeof(char), l, file);
    fclose(file);
  }
  free(sentence);
  return;
}
