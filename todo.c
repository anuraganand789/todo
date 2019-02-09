#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//4Kb i guess
#define BUF_SIZE 4048
const char *todoFilePath = "/home/anuraganand/todo.do";

//my todo file
FILE *file = NULL;

struct Todo {
  char *todos;
};

void main(void) {
  const size_t charSize = sizeof(char);

  printf("Enter a choice :- \n");
  printf("1. Read the todo list.\n");
  printf("2. Write todo.\n");
  


  while(1) {
    char choice = getchar();

    switch(choice) {
    case '1' :
      //read the todo list;
      file = fopen(todoFilePath, "r");
      if(file) {
	fflush(stdout);
	char *sentence = (char *) calloc(1024, charSize);
	printf("size allocated.\n");
	fflush(stdout);
	//reads in block of 4Kb
	unsigned int noOfItemsRead = fread(sentence, charSize, (BUF_SIZE/charSize), file);
	printf("total %d characters read from file\n", noOfItemsRead);
	printf("%s\n", sentence);
	if(feof(file)) {
	  printf("We have read entire content of this file.\n");
	}
	fclose(file);
      } else {
	printf("No todo file is there... Loser..");
      }
      //break from reading from file
      break;
    case '2':
      //write todo
      //get rid of newlines
      getchar();
      file = fopen(todoFilePath, "a");
      if(file) {
	char *sentence = (char *) calloc((BUF_SIZE/charSize), charSize);
	char *s = fgets(sentence, (BUF_SIZE/charSize), stdin);
	printf("%s\n", s);
	fwrite(sentence, sizeof(char), strlen(sentence), file);
	fflush(stdout);
	free(sentence);
	fclose(file);
      } else {
	printf("Looks like there is some issues with opening the file for writing.\n");
      }
      //break from writing to todo file
      break;
    }

    //reset choice
    choice = '\0';
  }
  return;
}
