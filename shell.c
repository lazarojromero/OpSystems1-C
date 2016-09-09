#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define INPUT_SIZE 1024
/* TODO:
 * batch mode
 */
/*
 * MARK: Built in commands that need to be run from within shell itself
 */

char *commands[] = {
  "cd",
  "quit",
  "help"
};

/*
 * MARK: Must first change second arg exits before calling chdir()
 */

int cd(char** path) {
  if(path[1] == NULL) {//if second arg is missing
    fprintf(stderr, "Error: second arguement for cd command missing..\n");
  } else {
    if(chdir(path[1]) != 0) {//if chdir() fails...
      perror("Error: could not change directory\n");
    }
  }
  return 1;
}

/*
 * MARK: returns 0 to exit shell loop
 */

int quit_loop() {
  return 0;
}

/*
 * MARK: message that lists all commands
 */

int help() {
  printf("Lazaro's shell currently has the following built-in commands:\n");
  for(int i = 0; i < (sizeof(commands)/sizeof(char *)); i++) {
    printf("  %s\n", commands[i]);
  }
  return 1;
}

/*
 * MARK: parse(char*) will parse through the user's input, seperated by ; character.
 * Will return an array of tokens/strings, each token being a command to be exectued
 * by the shell.
 */

char **parse(char line[INPUT_SIZE], char delim[]) {
  int pos = 0;
  int sz = 64;
  int len;
  char **result = malloc(sz*(sizeof(char)));
  char *temp, *temp2;
  if(!result) {//check malloc worked
    fprintf(stderr, "Error allocating!\n");
    exit(EXIT_FAILURE);
  }
  temp = strtok(line, delim);//tokenize line by ;
  while(temp != NULL) {
    len = strlen(temp);//get length of each command
    temp2 = malloc((++len) * sizeof(char));//malloc individual token
    strcpy(temp2,temp);//copy into temp2
    result[pos++] = temp2;//insert into result[]
    if(pos >= sz) {
      sz += sz;//double size
      result = realloc(result, sz);
    }
    temp = strtok(NULL, delim);
  }
  result[pos] = NULL;//null terminated
  return result;
}//end of parse()

/*
* MARK: execute(**argv) creates a new process for each new command.
*/

int execute(char **argv) {
  pid_t pid, c;
  int status;
  if((pid = fork()) < 0) {
    printf("Error: forking child process failed\n");
    exit(1);
  } else if(pid == 0) {
    execvp(argv[0], argv);//if returns then failed
    //printf("Error: exec failed\n");
    exit(1);
  } else {
      c = wait(&status);
  }
  return 1;
}

int checkCmd(char **args) {
  if(args[0] == NULL) {
    return 1;
  }
  if(strcmp(args[0],"quit") == 0) {
    return quit_loop();
  } else if(strcmp(args[0],"cd")==0) {
    return cd(args);
  } else if(strcmp(args[0],"help")==0) {
    return help();
  }
  return execute(args);
}

/*
 * Run interactive mode only if batchfile is not present
 */

void interactiveMode() {
  char userInput[INPUT_SIZE];//used to read lines from command promt
  char **toks; //commands seperated by ; character
  int status = 1;
  while(1) {
    printf("prompt> ");
    gets(userInput);
    if(strcmp(userInput,"")==0) {
      continue;
    } else {
    toks = parse(userInput, ";");
    char **arr;
    for(int i = 0; i < sizeof(toks) && toks != NULL; i++) {
          arr = parse(toks[i], " \t\n");
          if(arr != NULL) {
            status = checkCmd(arr);
            if(!status) {
              exit(0);
            }
          }
      }//end of tok 'for loop'
    }//end of userInput != ""
  }//end of while()
}//end of interactiveMode()

/*
 * MARK: main(argc, argv[]) start shell loop
 */

int main(int argc, char* argv[]) {
  if(argc < 2) {
    interactiveMode();
  } else {
    printf("Batch mode\n");
  }
}//end of main()
