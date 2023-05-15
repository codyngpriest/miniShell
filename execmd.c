#include "main.h"

void execmd(char **argv)
{
 pid_t pid;
 char *command = NULL, *actual_command = NULL;
  if (argv) {
    /* get the command */
    command = argv[0];

    /* generate the path to this command before passing it to execve */
    actual_command = get_location(command);

    /* fork a child process */
    pid = fork();
    if (pid == -1) {
      perror("Error:");
      return;
    }

    if (pid == 0) {
      /* this is the child process */
      /* execute the command with exexve */
      if (execve(actual_command, argv, NULL) == -1) {
        perror("Error: ");
      }
      exit(EXIT_FAILURE); /* exit child process if execve fails */
    }
    else {
      /* this is the parent process */
      waitpid(pid, NULL, 0); /* wait for child process to finish */
    }

    /* execute the commad with execve */
    /*if (execve(actual_command, argv, NULL) == -1) {
      perror("Error:");
    } */
  }
}
