#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

void execute_line(char** args) {

  // Use fork() to create a child process. Determine if the process
  // is a parent or a child, and run exec() if it is a child, and
  // run wait() if it is a parent.
  // For guidance, the model solution has 9 lines of code.
  int p[2];
  pipe(p);
  //child
  int f = fork();
  if (f < 0) {
    fprintf(2, "run_command: fork failed\n");
    exit(1);
  } else if (f == 0){
    close(1);
    dup(p[1]);
    close(p[0]);
    close(p[1]);
    exec(args[0], args);
    fprintf(2, "exec failed\n");
    exit(1);
  }

  f = fork();
  if (f < 0) {
    fprintf(2, "run_command: fork failed\n");
    exit(1);
  } else if (f == 0)
  {
    close(0);
    dup(p[0]);
    close(p[0]);
    close(p[1]);
    exec(args[3], &args[3]);
    fprintf(2,"exec failed\n");
    exit(1);
  }
  close(p[0]);
  close(p[1]);
  wait(0);
  wait(0);

}


int main(int argc, char *argv[]) {

  // Two pointers: to a command and to a null terminator.
  char *args[6] = {0};
  // Fixed-size storage for reading in a line of input, and a pointer
  // to a particular character in this storage.
  char buf[512], *b;
  // Point b to the first character in the line.
  b = buf;
  int n = 0;
  args[0] = buf;
  // Read characters from the standard input. When we find '\n' that
  // means one line has terminated - execute the command.
  fprintf(2, "\nPlease enter the first command and press enter (type 'q' to exit):\n");
  while (read(0, b, 1) > 0) {
    if (*b == '\n')
    {      
      *b = 0;
      if(strcmp(buf, "q") == 0)
      {
        exit(0);
      }
      n = n + 1;
      args[n] = 0;

      if (n==2)
      {
        b = b + 1;
        n = n + 1;
        args[n] = b;
        fprintf(2, "\nPlease enter the second command and press enter:\n");
      
      }
      else 
      {
        execute_line(args);
        b = buf;
        n=0;
        fprintf(2, "\nPlease enter the first command and press enter (type 'q' to exit):\n");
      }
     
    }
    else if (*b == ' ')
    {
      *b = 0;
      b = b + 1;
      n=n+1;
      args[n] = b;
    }
    else
    {
      b = b + 1;
    }
    
    
    

  
    // Check the current character in b. If it is not special, move the pointer
    // b to the next character and continue reading. If the command string has
    // been fully entered ('\n' is found in b), execute the command by calling
    // execute_line().
    // For guidance, the model solution has 10 lines of code in this loop.
  }
  exit(0);
}