#ifndef LL_H
#define LL_H

#ifndef UTIL_H
#include "util.h"

//Linked List of Todos
struct Todo {
  struct Todo *nextTodo;
  char *todo;
} ;

//global todo object
struct Todo *todoHead;
struct Todo *todoTail;

//util method to be called from main
void delete();
void update();
void save();

//Operations is done on entire List
void displayTodoList(struct Todo *);
void destroyTodoList(struct Todo *);

//deals with creation of entire todo list datastructure
void parseTodoList(const char *, int );
void initTodoList();



//allocation and deallocation of a todo node
void addNewTodo();
struct Todo *createTodoObject();
void destroyTodoObject(struct Todo *);

//These functions work on individual nodes
//add new node, update a nodes data or delte a node
void upsertTodoAt(const int, char *);
void deleteTodoAt(int);

//does not modify the datastructure
struct Todo *todoAtLocation(const int);

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

void upsertTodoAt(const int index, char *newTodo) {
  //if head needs to be updated and Todo List is not empty
  if (newTodo && index > -1) {
    struct Todo *targetTodo = todoAtLocation(index);
    totalCharInTodos = totalCharInTodos + strlen(newTodo);

    if(targetTodo) {
      if(targetTodo->todo) {
	//reduce the count of charachters 
	totalCharInTodos = totalCharInTodos - strlen(targetTodo->todo);
	free(targetTodo->todo);
      }
      targetTodo->todo = newTodo;
    } else {
      //if we are in Else-statemen
      //Then -> Either the todolist is empty or we have reached the end of the list
      struct Todo *t = createTodoObject();
      t->todo = newTodo;
      //case 1. We have reached the end of the todo list.
      //this is the case of adding a new element at the tail
      if(todoTail) {
	todoTail->nextTodo = t;
	todoTail = t;
      } else {
	//Case 2. Todo list is empty . bitches !!!! hahaha...
	//add *t as the first node 
	if(todoHead == NULL) {
	  todoHead = todoTail = t;
	}
      }
      //Increment number of todos - as this is a new addition
      ++numberOfTodos;
    }
  }
}


struct Todo *todoAtLocation(const int index) {
  struct Todo *iterator = todoHead;
  int count = 1;
  while(count < index && iterator) {
    iterator = iterator->nextTodo;
    ++count;
  }
  return iterator;
}

void displayTodoList(struct Todo *todo) {
  if(numberOfTodos) {
    struct Todo *temp = todo;
    int lineNumber = 1;
    printf("\e[48;5;017m List Of Todos.\n");
    //clear the color
    printf("\e[0m");
    while(temp && temp->todo) {
      printf("%d. %s", lineNumber, temp->todo);
      temp = temp->nextTodo;
      ++lineNumber;
    }
  } else {
    printf("\e[48;5;022m Todo is empty. Select 1 - to add something to it.\n\n");
    //clear the color
    printf("\e[0m");
  }
}

void parseTodoList(const char *content, int totalCharsRead) {
  if(content) {
    destroyTodoList(todoHead);
    todoTail = todoHead = NULL;
    struct Todo *tempHead = todoHead;
    
    const char *temp = content;
    char newLine = '\n';

    while(totalCharsRead > 0) {
      struct Todo *todoObject = createTodoObject();
      char *n = index(temp, '\n');
      int numberOfCharachtersBeforeNewLine = n - temp;
      //int numberOfCharachtersBeforeNewLine = strcspn(temp, &newLine);
      
      //+1 for newLine
      int numberOfCharsReadInCurIter = numberOfCharachtersBeforeNewLine + 1;
      
      // +1 to make space for a null charachter
      size_t sizeOfCharToBeRead = (numberOfCharsReadInCurIter +1) * charSize;

      char *line = (char *) malloc(sizeOfCharToBeRead);
      strncpy(line, temp, sizeOfCharToBeRead);
      //add null at the end - array starts at zero - remember?
      line[numberOfCharsReadInCurIter] = '\0';

      todoObject->todo = line;
      line = NULL;
      
      //+1 is to count new-line in number of charachters.
      //Because, new line is also a charachter.
      totalCharInTodos = totalCharInTodos + numberOfCharsReadInCurIter;
      
      //move temp to the start point of next line
      temp = n + 1;
      //temp = temp + numberOfCharsReadInCurIter;  

      //number of todo goes up by one
      ++numberOfTodos;

      //Total chars remaining
      totalCharsRead = totalCharsRead - numberOfCharsReadInCurIter;
      
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
    int totalCharsRead = fread(sentence, charSize, (BUF_SIZE/charSize), file);
    parseTodoList(sentence, totalCharsRead);	
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
    file = NULL;
  } else {
    printf("No todo file is there... Loser..");
  }
  //      printf("-----------------------------End--------------------------\n");
}

void addNewTodo() {
  //write todo
  file = fopen(todoFilePath, "a");
  if(file) {
    printf("\n");
    printf("Enter New todo below.\n");
    char *sentence = readString();

    //If first charachter is new line - then do not add.
    //prevents an empty line in the todo
    if(sentence && *sentence != '\n') {
      fwrite(sentence, sizeof(char), strlen(sentence), file);
      upsertTodoAt( (numberOfTodos + 1), sentence);
    }
	
    fflush(stdout);
    fclose(file);
    file = NULL;
  } else {
    printf("Looks like there is some issues with opening the file for writing.\n");
  }

}


void update(){
  printf("\n\n");
  printf("Enter the serial Number of the todo :- ");

  int *todoSerialNumber = (int *) calloc(1, sizeof(int));
  scanf("%d", todoSerialNumber);
  getchar();
  
  printf("Enter updated todo below.\n");

  char *todo  = readString();
  if(todo) {
    upsertTodoAt(*todoSerialNumber, todo);
  }
}

void save() {

  if(file) {
    printf("File is already open");
    fflush(file);
    printf("Closing file stream");
    fclose(file);
  }

  //open in write only mode - this will delete previous data
  file = fopen(todoFilePath, "w");
  if(!file) {
    printf("Failed to Open file for writing");
    return;
  }
  
  struct Todo *iterate = todoHead;
  while(iterate) {
    fwrite(iterate->todo, sizeof(char), strlen(iterate->todo), file);
    iterate = iterate->nextTodo;
  }
  
  fflush(stdout);
  fclose(file);
  file = NULL;
}

void delete() {
  printf("\n\n");
  printf("Enter serial Number of Todo to be Deleted.");

  int *serialNumber = (int *) calloc(1, sizeof(int));
  scanf("%d", serialNumber);
  getchar();
  
  deleteTodoAt(*serialNumber);
}

void deleteTodoAt(int serialNumber) {
  if(serialNumber > 0
     && serialNumber <= numberOfTodos
     && todoHead) {
      
    struct Todo *prev = NULL;
    struct Todo *cur = todoHead;
    int count = serialNumber;
    
    while(count > 1 && cur) {
      prev = cur;
      cur = cur->nextTodo;
      --count;
    }

    if(prev) {
      prev->nextTodo = cur->nextTodo;
    }

    //cur should not be NULL here... if it is then
    //numberOfTodos has wrong value in it
    if(cur) {

      //If deleting the first node
      if(cur == todoHead) {
	todoHead = todoHead->nextTodo;
	//if head is the only node
	//then update tail node reference to NULL
	if(todoHead == NULL) {
	  todoTail = NULL;
	}
      }
      
      //update counts of characters and lines
      totalCharInTodos = totalCharInTodos - strlen(cur->todo);
      --numberOfTodos;
    
      //free node
      cur->nextTodo = NULL;
      destroyTodoObject(cur);
      
    } else {
      printf("cur object is null in deleteTodoAt");
    }
  }
}

#endif //UTIL_H
#endif //LL_H 
