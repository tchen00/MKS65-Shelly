#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <limits.h>
// need to clean that up later




// Return 1 if pipe, 0 if not -- SINGLE
int special(char * args){
  if (strstr(args,"|")){
    printf("Pipe successful\n" );
    return 1;
  }
  return 0;
}



int main(){
  int status;
  char* str = malloc(50);
  while (1){
    int i = 0;
    str = command_line();
    char ** full_arr = parse_args(str, ";");
    while(full_arr[i]){
      printf("----------------------------------------\n" );
      printf("full_arr[%d]: %s\n", i, full_arr[i]);
      int j = 0;
      if (special(full_arr[i])){
        char ** full_arr2 = parse_args(str, "|");
        redirect_pipe(full_arr2);
      }
      else {
        printf("clipped \n" );
        char ** arr = parse_args(full_arr[i] , " ");
        while(arr[j]){
          printf("arr[%d]: %s\n", j, arr[j]);
          j++;
        }
        if (!strcmp(arr[0], "cd")){
          chdir(arr[1]);
        }
        else if (!strcmp(arr[0], "exit")){
          return 0;
        }
        else {
          // child
          int firstborn = fork();
          if (!firstborn){
            printf("-------------------------------\nEXECVP Testing-------------------------\n");
            execvp(arr[0],arr);
            return 0;
          }
          else {
            // parent
            int child_id = wait(&status);
          }
        }
        i++;
      }
    }
  }
  printf("finished the full_arr\n");
  return 0;
}
