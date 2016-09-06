#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUT_SIZE 1024
#define _DELIM ";"

/*
 * read() will return the user's inputted commands, with error checking
 */

char* read() {
  char line[130];//container for user input
  fgets(line, 130, stdin);//fgets no larger than 1024 bytes from stdin
/*
 * TODO: check if commands entered are valid/supported
 */
  return line;
}//end of read()

/*
 * parse(char*) will parse through the user's input, seperated by ; character.
 * Will return an array of tokens/strings, each token being a command to be exectued
 * by the shell.
 */

char **parse(char *line) {
  int pos = 0;
  int sz = 64;
  int len;
  char **result = malloc(sz * sizeof(char));
  //printf("After malloc check\n");
  char *temp, *temp2;

  if(!result) {//check malloc worked
    fprintf(stderr, "Error allocating!\n");
    exit(EXIT_FAILURE);
  }
  //printf("Before tokenizing\n");
  temp = strtok(line, _DELIM);//tokenize line by ;
  //printf("After tokenizing\n");

  while(temp != NULL) {
    len = strlen(temp);//get length
    temp2 = malloc((++len) * sizeof(char));//malloc individual token
    strcpy(temp2,temp);//copy into temp2
    result[pos++] = temp2;//insert into result[]

    if(pos >= sz) {
      sz += sz;//double size
    //  printf("Before reallocating check\n");
      result = realloc(result, sz);
    //  printf("After reallocating check\n");
    }
    temp = strtok(NULL, _DELIM);
  }
  result[pos] = NULL;//null terminated
  return result;
}

/*
 * exec(tokens) executes array of tokens
 * built in commands then process() from within
 */

int exec(char** tokens) {
  return 0;
}

/*
 * process(**toks) forks the process, saves and returns value.
 */

 int process(char **toks) {
   pid_t pid1, pid2;//parent process id number of child
   int status;

   pid1 = fork();

   if(pid1 == 0) {//child, takes first condition

     if(execvp(toks[0], toks) == -1) {//run command given by user, if returns then error
       perror("error");
        } exit(EXIT_FAILURE);//exit and keep running shell

   } else if(pid1 < 0) {//error when forking
     perror("error");

   } else {//parent, successful fork(), wait for command to finish
      do {
        pid2 = waitpid(pid1, &status, WUNTRACED);//wait for state to change
      } while(!WIFEXITED(status) && !WIFSIGNALED(status));//exited or killed
   }

   return 1;//prompt for more input

 }

void free_tokens(char **tokens) {
  char **itr = tokens;
  while(*itr != NULL) {
    free(*itr);
    itr++;
  }
  free(tokens);
}

int main(int argc, char** argv) {
  char *userInput;//used to read lines from command promt
  char **toks; //commands seperated by ; character
  int status; //decides when to quit/exit

  do {
    printf("prompt> ");
    userInput = read();//read commands from user
    toks = parse(userInput);
    status = exec(toks);

    free(*userInput);//free up space in memory, deallocate
    free_tokens(toks);
  }while(status);



}//end of main()
