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