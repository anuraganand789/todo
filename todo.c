#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ll.h"

void main(void) {
  int modified = 0;
  clearTerminal();
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
       displayTodoList(todoHead);
      break;
    case '2':
      addNewTodo();
      //break from writing to todo file
      clearTerminal();
      displayTodoList(todoHead);
      break;
    case '3' :
      displayTodoList(todoHead);
      update();
      clearTerminal();
      displayTodoList(todoHead);
      //store in a file
      save();
      break;
    case '4':
      displayTodoList(todoHead);
      delete();
      clearTerminal();
      displayTodoList(todoHead);
      save();
      break;
    case '5' :
      //Exit
      printf("Application Closed.\n");
      return;
      //End of switch-case
    }
    //end of while(1) loop
  }
  return;
}
