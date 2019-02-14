#ifndef UTIL_H
#define UTIL_H

//4Kb i guess
const int BUF_SIZE = 4048;

const char *todoFilePath = "/home/anuraganand/todo.do";
const size_t charSize = sizeof(char);


//my todo file
FILE *file = NULL;

//Number of Todo Items
int numberOfTodos = 0;
int totalCharInTodos = 0;

void displayMeny(void);
void clearTerminal();
char *readString();


void displayMenu(void) {
  // printf("\n\n");
  printf("Select An Operation :- \n");
  printf("1. Read Todos.\n");
  printf("2. Add A Todo.\n");
  printf("3. Update A Todo.\n");
  printf("4. Exit.\n");
}
 
void clearTerminal() {
  //Clear the terminal
  printf("\e[1;1H\e[2J");
}

char *readString() {
  size_t itemCount = BUF_SIZE/charSize;
  char *sentence = (char *) calloc(itemCount, charSize);
  char *s = fgets(sentence, itemCount, stdin);

  if(!s) {
    free(sentence);
    sentence = NULL;
    s = NULL;
    printf("An error occurred, while reading string.");
  }
  return sentence;
}

#endif //UTIL_H
