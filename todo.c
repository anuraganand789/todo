#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//4Kb i guess
#define BUF_SIZE 4048

const char *todoFilePath = "/home/anuraganand/todo.do";
const size_t charSize = sizeof(char);

//my todo file
FILE *file = NULL;

//Number of Todo Items
int numberOfTodos = 0;
int totalCharInTodos = 0;

//Linked List of Todos
struct Todo {
  struct Todo *nextTodo;
  char *todo;
} ;

//global todo object
static struct Todo *todoHead;
static struct Todo *todoTail;

struct Todo *createTodoObject();
void allocTodoList(struct Todo *);
void deallocTodoList(char **);
void destroyTodoObject(struct Todo *);
void displayMenu(void);
void charAndLineCount(const char *, struct Todo *);
void clearTerminal();
void printTodoWithLineNumber(struct Todo *);
void parseTodoList(const char *);
void initTodoList();
void addNewTodo();


void main(void) {
  int modified = 0;

  initTodoList();
  
  while(1) {
    displayMenu();

    char choice = getchar();

    //discard the return charachter
    getchar();

    //Make Terminal Look Fresh again
    clearTerminal();
    
    switch(choice) {
    default:
      printf("Invalid Choice. Please select one of options from menu.\n");
      break;
    case '1' :
      printTodoWithLineNumber(todoHead);
      break;
    case '2':
      addNewTodo();
      //break from writing to todo file
      break;
    case '3' :
      //Exit
      printf("Application Closed.\n");
      return;
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
 
void clearTerminal() {
  //Clear the terminal
  printf("\e[1;1H\e[2J");
}

void printTodoWithLineNumber(struct Todo *todo) {
  if(todo && todo->todo) {
    struct Todo *temp = todo;
    int lineNumber = 1;
    while(temp) {
      printf("%d. %s\n", lineNumber, temp->todo);
      temp = temp->nextTodo;
      ++lineNumber;
    }
  }
}

struct Todo *createTodoObject() {
  struct Todo *todo = (struct Todo *) malloc(sizeof(struct Todo *));

  //remove all the garbage values from the memory
  todo->nextTodo = NULL;
  todo->todo = NULL;
  
  return todo;
}

void destroyTodoObject(struct Todo *todo) {
  free(todo->todo);
  todo->todo = NULL;
  
  free(todo);
  todo = NULL;
}

void destroyTodoList(struct Todo *todo) {
  if(todo) {
    struct Todo *temp = todo;
    while(temp) {
      struct Todo *next = temp->nextTodo;
      destroyTodoObject(temp);
      temp = next;
    }
    temp = NULL;
  }
}

void parseTodoList(const char *content) {
  if(content) {
    destroyTodoList(todoHead);
    todoTail = todoHead = NULL;
    struct Todo *tempHead = todoHead;
    
    const char *temp = content;
    char newLine = '\n';

    while(*temp) {
      struct Todo *todoObject = createTodoObject();
      
      int numberOfCharachtersBeforeNewLine = strcspn(temp, &newLine);

      //+1 is to count new-line in number of charachters.
      //Because, new line is also a charachter.
      totalCharInTodos = totalCharInTodos + numberOfCharachtersBeforeNewLine + 1;
      
      // +1 to make space for a null charachter
      size_t sizeOfCharToBeRead = (numberOfCharachtersBeforeNewLine + 1) * charSize;

      char *line = (char *) malloc(sizeOfCharToBeRead);
      strncpy(line, temp, sizeOfCharToBeRead);
      //add null at the end - array starts at zero - remember?
      line[numberOfCharachtersBeforeNewLine] = '\0';

      todoObject->todo = line;
      line = NULL;
      
      //move temp to the start point of next line
      temp = temp + numberOfCharachtersBeforeNewLine + 1;

      //number of todo goes up by one
      ++numberOfTodos;

      if(todoHead == NULL) {
	//Initialize the head of todo list
	todoHead = todoObject;
	todoTail = tempHead = todoHead;
      } else {
	todoTail = todoObject;
	tempHead->nextTodo = todoObject;
	tempHead = tempHead->nextTodo;
      }
    }
  }
}
				   
 void initTodoList() {
      //read the todo list;
      file = fopen(todoFilePath, "r");
      if(file) {
	char *sentence = (char *) calloc((BUF_SIZE/charSize), charSize);

	//reads in block of 4Kb
	totalCharInTodos = fread(sentence, charSize, (BUF_SIZE/charSize), file);
	parseTodoList(sentence);	
	printf("characters %d Lines %d \n\n", totalCharInTodos, numberOfTodos);
	


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
}

void addNewTodo() {
        //write todo
      file = fopen(todoFilePath, "a");
      if(file) {
	char *sentence = (char *) calloc((BUF_SIZE/charSize), charSize);
	char *s = fgets(sentence, (BUF_SIZE/charSize), stdin);

	if(!s) {
	  free(sentence);
	  printf("An error occurred, while reading line from file.");
	  return ;
	}
	
	//If first charachter is new line - then do not add.
	//prevents an empty line in the todo
	if(*sentence != '\n') {
	  fwrite(sentence, sizeof(char), strlen(sentence), file);

	  struct Todo *newTodo = createTodoObject();
	  newTodo->todo = sentence;

	  if(todoHead == NULL) {
	    todoHead = todoTail = newTodo;
	  } else {
	    todoTail->nextTodo = newTodo;
	    todoTail = newTodo;
	  }
	}
	
	fflush(stdout);
	fclose(file);
      } else {
	printf("Looks like there is some issues with opening the file for writing.\n");
      }

}
