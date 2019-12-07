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

char * command_line() {
  char * prompt = (char *)calloc(256,1);
  printf("$ " );
  fgets(prompt,256,stdin);
  prompt[strlen(prompt)-1] = 0;
  return prompt;
}

// adapted from previous assignment
char ** parse_args( char * line, char * limit ){
  char ** args = malloc(256);
  char * token;
  int i = 0;
  // counts number of tokens
  while (token){
    // all items on the command line are to be separated by a single space
    token = strsep(&line, limit);
    args[i] = token;
    i++;
  }
  return args;
}

// Return 1 if pipe, 0 if not -- SINGLE 
int special(char * args){
  if (strstr(args,"|")){
    printf("Pipe successful\n" );
    return 1;
  }
  return 0;
}

int redirect_pipe(char ** args){
    printf("larg[0]: %s\n",args[0] );
    printf("arg[1]: %s\n",args[1] );
    char * input  = args[0];
    char * output = args[1];
    char line[256];
    char cmd[256];

    FILE *read = popen(input,"r");

    while (fgets(line,256,read)) {
      line[sizeof(line)-1] =0;
      strcat(cmd,line);
    }

    pclose(read);
    FILE *write=popen(output,"w");

    fprintf(write,"%s",cmd);
    pclose(write);
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
