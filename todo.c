#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//4Kb i guess
#define BUF_SIZE 4048
char content[BUF_SIZE];
const char *todoFilePath = "/home/anuraganand/todo.do";


//my todo file
FILE *file = NULL;

struct Todo {
  char *todos;
};

void main(void) {

  printf("Enter a choice :- \n");
  printf("1. Read the todo list.\n");
  printf("2. Write todo.\n");
  
  int choice = 0;
  scanf("%d\n", &choice);

  switch(choice) {
  case 1 :
    //read the todo list;
    break;
  case 2:
    //write todo
    file = fopen(todoFilePath, "a");
    if(file) {
      char *sentence =  (char *) malloc(100 * sizeof(char));
      fgets(sentence, 100, stdin);
      fwrite(sentence, sizeof(char), strlen(sentence), file);
      fflush(stdout);
      fclose(file);
      free(sentence);
    }
    
    break;
  }
  
  
  return;
}
