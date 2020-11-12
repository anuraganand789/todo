#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "ll.h"

void main(void) {
  int modified = 0;
  clearTerminal();
  displayTodoFiles();
  updateTodoFileName();
  //  getchar();
  initTodoList();

  while(1) {
    clearTerminal();
    displayTodoList(todoHead, -1, NULL);
    displayMenu();

    char choice = getchar();
    //discard the return charachter
    getchar();

    //Make Terminal Look Fresh again
    clearTerminal();
    displayTodoList(todoHead, -1, NULL);
    
    switch(choice) {
    default:
      printf("Invalid Choice. Please select one of options from menu.\n");
      break;
    case '1':
      addNewTodo(); break;
    case '2' :
      update("\e[48;5;022m"); save(); break;
    case '3':
      delete(); save(); break;
    case '4' :
      //Exit
      clearTerminal(); return;
    case '5' : 
      displayMenu((); break;
    }
    //end of while(1) loop
  }
  return;
}
