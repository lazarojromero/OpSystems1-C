# OpSystems1-C
Lazaro Romero
FSUID: Ljr14e
Design overview:
  The program checks for argc to verify if to enter interactive mode or batch file. If interactive mode is detected then a looping function is called. The program is structured to check for built in commands first such as cd, help, and quit before being sent to execute function. The program executes all commands in parallel, but stops reading commands once quit is detected.
  There are built in functions for the built in commands that are checked using strcmp(). Also, if batch mode is detected the file is opened for reading and is parsed twice for ';\n' and then for other possible delimiters. Then executed similar to interactive mode, but without prompting. The program exits when 'quit' or EOF is detected, printing a **Quitting/EOF** message for the user.

Complete specification:
  In order to avoid conflicts when tokenizing input commands, I created a parsing function that takes in a char** and delimiter so that I am able to tokenize the user's input twice. The first time around by simply parsing with ';' delimiter, then parsing it again in order to pass it through my execute function that implements fork(), execvp(), waitpid(),wait()..

Known bugs or problems:
  TODO
  
