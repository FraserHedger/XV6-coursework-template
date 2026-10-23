#include "kernel/types.h"
#include "user/user.h"

int main() {
  // Declare two pipes
  int p2c[2];
  int c2p[2];
  // p2c - a parent to a child communication
  // c2p - a child to a parent communication

  // Call the pipe() system call to create p2c and c2p
  if (pipe(p2c) == -1 )
  {
    fprintf(2, "Returned error in p2c \n");
    exit(1);
  }
  if (pipe(c2p) == -1)
  {
    fprintf(2, "Returned error in c2p \n");
    exit(1);
  }


  // Declare one byte for sending to the child process
  char our_byte = 'P';
  char their_byte;

  // Fork a new process
  int pid = fork();
  if (pid > 0) {
    
    // 1. PLACE YOUR CODE HERE TO SEND A BYTE TO THE OTHER PROCESS
    write(p2c[1], &our_byte, 1);
    // 5. PLACE YOUR CODE HERE TO RECEIVE THE MODIFIED BYTE
    read(c2p[0], &our_byte, 1);
    printf("%d: received pong, %c\n", getpid(), our_byte);
  }
  else if (pid == 0) {
    // 2. PLACE YOUR CODE HERE TO READ A BYTE IN THE PIPE p2c
    read(p2c[0], &their_byte, 1);
    printf("%d: received pint, %c\n", getpid(), their_byte);

    // 3. PLACE YOUR CODE HERE TO MODIFY THE BYTE TO LETTER 'R'
    their_byte = 'R';
    // 4. PLACE YOUR CODE HERE TO SEND THE BYTE BACK OVER c2p PIPE
    write(c2p[1], &their_byte, 1);
  }
  exit(0); // Exit parent process
}
