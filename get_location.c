#include "main.h"

/*
 * get_location - This function searches for the executable file corresponding to the
 * command in the directories listed in the PATH environment variable.
 * Returns the full path to the executable file if found, or NULL otherwise.
 * The caller is responsible for freeing the returned string.
 */

char *get_location(char *command) {
  char *path, *path_copy, *path_token, *file_path;
  int command_length, directory_length;
  struct stat buffer;

  path = getenv("PATH");
  
  if (path) {
    /* duplicate the path string */
    path_copy = strdup(path);

    /* check if strdup() was successful */
    if (!path_copy) {
      return (NULL);
    }

    /* get length of the command passed */
    command_length = strlen(command);

    /* break path variable and get all available dirs */

    path_token = strtok(path_copy, ":");

    while (path_token != NULL) {
      /* get directory length */
      directory_length = strlen(path_token);

      /* allocate memory for command and directory names */
      file_path = malloc(command_length + directory_length + 2);

      /* build command path */
      strcpy(file_path, path_token);
      strcat(file_path, "/");
      strcat(file_path, command);
      strcat(file_path, "\0");

      /* test to see if file path exist? return : next dir */
      if(stat(file_path, &buffer) == 0) {
        free(path_copy);

        return (file_path);
      }
      else {
       free(file_path);
        path_token = strtok(NULL, ":");
      }
    }
     /* If we got here, the command was not found in any of the directories */
    free(path_copy);

    /* check if command is in the current directory */
    if (stat(command, &buffer) == 0) {
      return strdup(command);
    }
    /* command not found */
    return (NULL);
  }
  /* PATH environment variable not set */
  return (NULL);
}
