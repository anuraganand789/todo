#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//4Kb i guess
#define BUF_SIZE 4048
const char *todoFilePath = "/home/anuraganand/todo.do";
const size_t charSize = sizeof(char);

//my todo file
FILE *file = NULL;

struct Todo {
  char *todos;
  int lines;
  int chars;
};

void displayMenu(void);
int lineCount(const char *);
void clearTerminal();
void printWithLineNumber(const char *);

void main(void) {

  while(1) {
    displayMenu();

    char choice = getchar();

    //discard the return charachter
    getchar();

    //Make Terminal Look Fresh again
    clearTerminal();
    
    switch(choice) {
    case '1' :
      //read the todo list;
      file = fopen(todoFilePath, "r");
      if(file) {
	char *sentence = (char *) calloc((BUF_SIZE/charSize), charSize);

	//reads in block of 4Kb
	unsigned char noOfItemsRead = fread(sentence, charSize, (BUF_SIZE/charSize), file);
	unsigned char noOfLines = lineCount(sentence);
	
	printf("characters %d Lines %d \n\n", noOfItemsRead, noOfLines);
	
	printWithLineNumber(sentence);

	if(feof(file)) {
	  //make this a whlie loop and put all of the code inside it.
	  //to read big files.
	  //i will add buffering to prevent from loading all data at once
	  //	  printf("\nWe have read entire content of this file.\n\n");
	}
	
	free(sentence);
	sentence = NULL;
	
	fclose(file);
      } else {
	printf("No todo file is there... Loser..");
      }
      printf("-----------------------------End--------------------------\n");
      //break from reading from file
      break;

    case '2':
      //write todo
      file = fopen(todoFilePath, "a");
      if(file) {
	char *sentence = (char *) calloc((BUF_SIZE/charSize), charSize);
	char *s = fgets(sentence, (BUF_SIZE/charSize), stdin);

	//If first charachter is new line - then do not add.
	//prevents an empty line in the todo
	if(*s != '\n') {
	  fwrite(sentence, sizeof(char), strlen(sentence), file);
	}
	
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
  printf("Select An Operation :- \n");
  printf("1. Read Todos.\n");
  printf("2. Add A Todo.\n");
  printf("3. Exit.\n");
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

void clearTerminal() {
  //Clear the terminal
  printf("\e[1;1H\e[2J");
}

void printWithLineNumber(const char *content) {
  if(content) {
    int lineCount = 1;
    const char *temp = content;
    char newLine = '\n';
    while(*temp) {
      int numberOfCharachtersBeforeNewLine = strcspn(temp, &newLine);
      // +1 to make space for a null charachter
      //size is in Bytes
      size_t sizeOfCharToBeRead = (numberOfCharachtersBeforeNewLine + 1) * charSize;

      char *line = (char *) malloc(sizeOfCharToBeRead);
      strncpy(line, temp, sizeOfCharToBeRead);

      //add null at the end - array starts at zero - remember?
      line[numberOfCharachtersBeforeNewLine] = '\0';
      
      //Move temp after '\n'
      //+1 to move to next charachter after the \n
      temp = temp + numberOfCharachtersBeforeNewLine + 1;

      printf("%d. %s\n", lineCount, line);
      //      printf("----remaining----\n");
      //      printf("%s\n", temp);
      ++lineCount;
    }
  }
}
