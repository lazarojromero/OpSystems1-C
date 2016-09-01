#include <stdio.h>
#include <string.h>

#define INPUT_SIZE 1024

int main(int argc, char** argv) {

  char *userInput;//used to read lines from command promt
  char *tokens; //commands seperated by ; character
  int status; //decides when to quit/exit

  do {
    printf("prompt> ");
    userInput = read();//read commands from user


  }while(status);



}//end of main()

char* read() {

  char* line;//container for user input
  fgets(&line, INPUT_SIZE, stdin);//fgets no larger than 1024 bytes from stdin
  printf("%s\n", line);

//TODO: line error checking

  return line;

}//end of read()
