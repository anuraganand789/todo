#ifndef UTIL_H
#define UTIL_H

//4Kb
const int BUF_SIZE = 4096;

char *todoFilePath = "/home/anuraganand/todo.do";
char *todoConfigLocation = "/home/anuraganand/.todo.conf";

struct  TodoFiles{
  char **todoFiles;
  int fileCount;
};

struct TodoFiles *TodoFilesChoices = NULL;
const size_t charSize = sizeof(char);

//my todo file
FILE *file = NULL;

//Number of Todo Items
int numberOfTodos = 0;
int totalCharInTodos = 0;

void displayMeny(void);
void clearTerminal();
char *readString();
void chooseTodo();
void displayTodoFiles();
void updateTodoFileName();

void chooseTodo() {
  long int addressOfFirstFile = -1;
  DIR *d;
  struct dirent *dir;
  d = opendir(todoConfigLocation);
  
  if (d) { 
    int fileCount = 0;
    while ((dir = readdir(d)) != NULL) {
      if(dir->d_type == DT_REG) {
	if(fileCount == 0) {
	  //this means this is the first file
	  //get it's address, later we will be moving back to this file.
	  addressOfFirstFile = telldir(d);
	}
	++fileCount;
	printf("%d. %s\n",fileCount ,dir->d_name);
      }
    }

    //----Storing the file names with
    //directory names in a multi dimensional array.
    //allocate memory
    //allocate memory for todo choices
    TodoFilesChoices = (struct TodoFiles *) calloc(1, sizeof(struct TodoFiles *));
    TodoFilesChoices->todoFiles = (char **) calloc(fileCount, sizeof(char *));
    TodoFilesChoices->fileCount = fileCount;
   
    //create an iterartor - because I don't want to miss reference to the first
    //element
    char **iter = TodoFilesChoices->todoFiles;

    //Move to the first-file
    //    seekdir(d, addressOfFirstFile);
    rewinddir(d);

    //+1 for making memory for forward-slash '/'
    int confDirLenName = strlen(todoConfigLocation) + 1;
    //Now copy all the names
    //name format will be todoConfigLocation + '/' + d_name
    int filesRead  = 0;
    while ((dir = readdir(d)) != NULL) {
      if(dir->d_type == DT_REG) {
	++filesRead;
	//+1 for null charachter
	*iter = (char *) calloc( confDirLenName + strlen(dir->d_name) + 1, charSize);

	int i = 0;
	//copy directory name
	while(todoConfigLocation[i] != '\0') {
	  (*iter)[i] = todoConfigLocation[i];
	  ++i;
	}

	(*iter)[i] = '/';
	++i;

	int c = 0;
	while(dir->d_name[c] != '\0') {
	  (*iter)[i] = dir->d_name[c];
	  ++i;
	  ++c;
	}
	(*iter)[i] = '\0';

	if(filesRead < fileCount) {
	  ++iter;
	}
      }
    }
    //close the file stream
    closedir(d);
   
  } else {
    printf("Failed to read directory -> %s.\n", todoConfigLocation);
  }
}

void displayTodoFiles(void) {
  printf("\n");
  printf("\e[48;5;0m Select Todo File :- \n");
  //reset the color of the line
  printf("\e[0m");
  chooseTodo();
}

void updateTodoFileName() {
    if(TodoFilesChoices != NULL && TodoFilesChoices->fileCount > 0) {
    printf("\n");
    printf("Enter todo Serial Number...\n");
    int fileChoice;
    scanf("%d", &fileChoice);
    //get rid of return charachters.
    getchar();
    
    //In case of invalid value set 1 as default value.
    if(fileChoice > 0 && fileChoice <= TodoFilesChoices->fileCount) {
      char **iter = TodoFilesChoices->todoFiles;
      //I need to reduce the count by one because
      //array starts from '0'
      //that's why first file name is going to be at location 0 not 1.
      todoFilePath = *(iter + (fileChoice - 1) );
    }
  } else {
    printf("NO todo file available.\n");
  }
}

void displayMenu(void) {
  printf("\n");
  printf("\e[48;5;0m Select An Operation :- \n");
  //reset the color of the line
  printf("\e[0m");
  printf("1. Add.\n");
  printf("2. Update.\n");
  printf("3. Delete.\n");
  printf("4. Exit.\n");
  printf("5. Main Menu.\n");
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
