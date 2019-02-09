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
  int lines;
  int chars;
};

void displayMenu(void);
int lineCount(const char *);


void main(void) {
  const size_t charSize = sizeof(char);

  while(1) {
    displayMenu();

    char choice = getchar();

    //discard the return charachter
    getchar();
    
    switch(choice) {
    case '1' :
      //read the todo list;
      file = fopen(todoFilePath, "r");
      if(file) {
	char *sentence = (char *) calloc((BUF_SIZE/charSize), charSize);

	//reads in block of 4Kb
	unsigned char noOfItemsRead = fread(sentence, charSize, (BUF_SIZE/charSize), file);
	unsigned char noOfLines = lineCount(sentence);
	
	printf("characters %d Lines %d \n", noOfItemsRead, noOfLines);
	printf("%s\n", sentence);

	if(feof(file)) {
	  printf("We have read entire content of this file.\n");
	}
	
	free(sentence);
	fclose(file);
      } else {
	printf("No todo file is there... Loser..");
      }
      //break from reading from file
      break;

    case '2':
      //write todo
      file = fopen(todoFilePath, "a");
      if(file) {
	char *sentence = (char *) calloc((BUF_SIZE/charSize), charSize);
	char *s = fgets(sentence, (BUF_SIZE/charSize), stdin);
	fwrite(sentence, sizeof(char), strlen(sentence), file);

	fflush(stdout);
	free(sentence);
	fclose(file);
      } else {
	printf("Looks like there is some issues with opening the file for writing.\n");
      }
      //break from writing to todo file
      break;

    case '3' :
      //Exit
      printf("Application Closed.\n");
      return;

    default:
      printf("Invalid Choice. Please select one of options from menu.\n");
      break;
      //End of switch-case
    }
    //end of while(1) loop
  }
  return;
}

void displayMenu(void) {
  
  printf("Enter a choice :- \n");
  printf("1. Read the todo list.\n");
  printf("2. Write todo.\n");
  printf("3. Exit\n");
}

int lineCount(const char *content) {
  int count = 0;
  const char *t = content;
  while(*t) {
    if(*t == '\n') {
      ++count;
    }
    ++t;
  }
  return count;
}
