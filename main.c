#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <limits.h>
#include "shell.h"
// need to clean that up later

int main(){
    int status;
    char* str = malloc(50);
    while (1){
        int i = 0;
        str = command_line();
        char ** user_input = parse_args(str, ";");
        while (user_input[i]){
          //printf("----------------------------------------\n" );
          //printf("user_input[%d]: %s\n", i, user_input[i]);
          user_input[i] = white_space(user_input[i]);
          int j = 0;
          int redirect_num = find_redirect(user_input[i]);
          if (redirect_num == 1){
              char ** user_input_2 = parse_args(str, "|");
              redirect_pipe(user_input_2);
          }
          else{
              char ** arr = malloc(256);
              if (!redirect_num){
                  arr = parse_args(user_input[i], " ");
                  if (!strcmp(arr[0], "cd")){
                      chdir(arr[1]);
                  }
                  if (!strcmp(arr[0], "exit")){
                      return 0;
                  }
              }
          int first = fork();
          if (!first){
              if (redirect_num == 2){
                  redirect_output(user_input[i]);
              }
              else if (redirect_num == 3){
                redirect_input(user_input[i]);
              }
              else{
                execvp(arr[0], arr);
                return 0;
              }
          }
          else {
            int child = wait(&status);
          }
        }
          i++;
        }
    }
    return 0;
}
