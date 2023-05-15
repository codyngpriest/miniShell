#include "main.h"

int main(int ac, char **argv)
{
  char *prompt = "(attempt) $ ";
  char *lineptr = NULL, *lineptr_copy = NULL;
  size_t n = 0;
  ssize_t nchars_read;
  const char *delim = " \n";
  int num_tokens = 0;
  char *token;
  int i;
  pid_t pid;
  pid = fork();

  /* declare void variables */
  (void)ac;

  /* create a loop for all the shells prompts */
  while (1){
  printf("%s", prompt);

  nchars_read = getline(&lineptr, &n, stdin);

/* check if the getline function failed or reached EOF or user used CTRL + D */
  if (nchars_read == -1)
  {
   printf("Exiting shell....\n");
      return (-1);
  }
  /* allocate space for a copy of the lineptr */
    lineptr_copy = malloc(sizeof(char) * nchars_read);
    if (lineptr_copy == NULL) {
      perror("tsh: memory allocation error");
      return (-1);
    }
  /* copy lineptr to lineptr_copy */
  strcpy(lineptr_copy, lineptr);
 /***** split the string (lineptr) into an array of words *****/
/* calculate the total of tokens */
  token = strtok(lineptr, delim);

  while (token != NULL) {
      num_tokens++;
      token = strtok(NULL, delim);
    }
    num_tokens++;

/* allocate space to hold the array of string */
    argv = malloc(sizeof(char *) * num_tokens);
/* store each token in the argv array */
    token = strtok(lineptr_copy, delim);

    for (i = 0; token != NULL; i++){
      argv[i] = malloc(sizeof(char) * strlen(token));
      strcpy(argv[i], token);

      token = strtok(NULL, delim);
    }
    argv[i] = NULL;
    

    /* check if fork failed */
    if (pid < 0) {
      perror("tsh: fork error");
      return (-1);
    }
    /* child process */
    else if (pid == 0) {
      /* execute command */
      execmd(argv);
      exit(0);
    }

    /* parent process */
    else {
      /* wait for child process to complete */
      waitpid(pid, NULL, 0);
    }

    /* execute command */
   /* execmd(argv); */

  printf("%s\n", lineptr);
  }

  /* free up allocated memory */
  free(lineptr_copy);
  free(lineptr);

  return (0);
}
