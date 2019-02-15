#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ll.h"

void main(void) {
  int modified = 0;
  clearTerminal();
  initTodoList();

  while(1) {
    clearTerminal();
    displayTodoList(todoHead);
    displayMenu();

    char choice = getchar();
    //discard the return charachter
    getchar();

    //Make Terminal Look Fresh again
    clearTerminal();
    displayTodoList(todoHead);
    
    switch(choice) {
    default:
      printf("Invalid Choice. Please select one of options from menu.\n");
      break;
    case '1':
      addNewTodo();
      break;
    case '2' :
      update();
      save();
      break;
    case '3':
      delete();
      save();
      break;
    case '4' :
      //Exit
      clearTerminal();
      printf("Application Closed.\n");
      return;
      //End of switch-case
    }
    //end of while(1) loop
  }
  return;
}
